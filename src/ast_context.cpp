#include "ast_context.hpp"



namespace ast {

    // Register File
    void RegisterFile::useReg(int i) { usedRegs[i] = 1; }
    void RegisterFile::freeReg(int i) { usedRegs[i] = 0; }

    int RegisterFile::allocate(){
        for (int i = 5; i <= 7; ++i) { // t0-t2 preferred
            if (usedRegs[i] == 0) {
                useReg(i);
                return i;
            }
        }

        for (int i = 28; i <= 31; ++i) { // t3-t6
            if (usedRegs[i] == 0) {
                useReg(i);
                return i;
            }
        }
        return -1; // No available register
    }

    int RegisterFile::allocateParam(){
        for (int i=10; i<=17; ++i) {
            if (usedRegs[i] == 0) {
                useReg(i);
                return i;
            }
        }
        return -1; // No available register
    }



    // Context

    std::string Context::makeLabel(std::string base) {
            return base + "_" + std::to_string(labelCounter++);
        }

    bool Context::isGlobal(const std::string &name) {
            return globals.find(name) != globals.end();
        }

    void Context::enterScope() {
        stack.emplace_back();
        auto& frame = stack.back();
        frame.frameSize = 8; // locals start at offset 8 (we subtract to grow down)
    }

    void Context::exitScope() {
        if (!stack.empty()) {
            stack.pop_back();
        }
    }

    void Context::setCurrentEndLabel(const std::string& label) {
        if (stack.empty()) {
            throw std::runtime_error("No active stack frame to set end label.");
        }
        stack.back().endLabel = label;
    }

    std::string Context::getCurrentEndLabel() const {
        if (stack.empty()) {
            throw std::runtime_error("No active stack frame to get end label.");
        }
        return stack.back().endLabel;
    }


    void Context::setCurrentVariableSize(TypeSpecifier type) {
        switch (type) {
            case TypeSpecifier::INT:
                currentVariableSize = 4; // Assuming int is 4 bytes
                break;
            case TypeSpecifier::VOID:
                currentVariableSize = 0; // Void has no size
                break;
            case TypeSpecifier::FLOAT:
                currentVariableSize = 4; // Assuming float is 4 bytes
                break;
            case TypeSpecifier::DOUBLE:
                currentVariableSize = 8; // Assuming double is 8 bytes
                break;
        }

    }

    int Context::getCurrentVariableSize() const {
        return currentVariableSize;
    }


    int Context::addLocalVar(const std::string& name, std::ostream &stream) {
        if (stack.empty()) {
            throw std::runtime_error("No active stack frame to add local variable.");
        }
        auto& frame = stack.back();
        if (frame.inFrame(name)) {
            throw std::runtime_error("Variable already exists in the current scope: " + name);
        }

        int reg = registers.allocate();

        stream << "addi sp, sp, -" << currentVariableSize << std::endl;

        frame.frameSize += currentVariableSize;
        int offsetFromFp = -frame.frameSize; // locals go negative from fp
        frame.varBindings[name] = { currentVariableSize, offsetFromFp, reg, TypeSpecifier::INT };

        return offsetFromFp;

    }

    const variable& Context::getVariable(const std::string& name) const {
    if (stack.empty()) {
        throw std::runtime_error("No active stack frame to get variable: " + name);
    }

    const auto& frame = stack.back();
    auto it = frame.varBindings.find(name);
    if (it == frame.varBindings.end()) {
        throw std::runtime_error("Variable not found in current scope: " + name);
    }

    return it->second; // returns a const reference to the variable struct
}


    int Context::getVariableOffset(const std::string& name) const {
        if (stack.empty()) {
            throw std::runtime_error("No active stack frame to get variable offset.");
        }
        auto& frame = stack.back();
        if (!frame.inFrame(name)) {
            throw std::runtime_error("Variable not found in the current scope: " + name);
        }
        return frame.varBindings.at(name).offset;
    }


    int Context::getCurrentFrameSize() const {
        if (stack.empty()) {
            throw std::runtime_error("No active stack frame to get current frame size.");
        }
        return stack.back().frameSize;
    }

    void Context::addLocalVarParam(const std::string& name, std::ostream &stream) {
        if (stack.empty()) {
            throw std::runtime_error("No active stack frame to add local variable.");
        }
        auto& frame = stack.back();
        if (frame.inFrame(name)) {
            throw std::runtime_error("Variable already exists in the current scope: " + name);
        }

        stream << "addi sp, sp, -" << currentVariableSize << std::endl;

        int reg = registers.allocateParam();


        frame.frameSize += currentVariableSize;
        int offsetFromFp = -frame.frameSize; // locals go negative from fp

        if (reg < 10 || reg > 17) {
            throw std::runtime_error("Only up to 8 integer params (a0..a7) supported for now");
        }

        if (reg == 10) {
            // move a0 since it will be overwritten
            stream << "sw x" << reg << ", " << offsetFromFp << "(s0)" << std::endl;
            reg = -1;
        }



        frame.varBindings[name] = { currentVariableSize, offsetFromFp, reg, TypeSpecifier::INT };

        return;

    }

    int Context::allocateRegister(std::ostream &stream) {
        int reg = registers.allocate();
        if (reg != -1) return reg;


        // Spill the first variable we find that has a register
        for (auto &pair : stack.back().varBindings) {
            variable &var = pair.second;
            if (var.reg != -1) {
                stream << "sw x" << var.reg << ", " << var.offset << "(s0)" << std::endl;
                registers.freeReg(var.reg);
                var.reg = -1;
                break;
            }
        }

        return registers.allocate(); // reallocate now that one is free
    }

    void Context::freeRegister(int reg) {
        registers.freeReg(reg);
    }

}
