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
        frame.varBindings[name] = { currentVariableSize, offsetFromFp, reg, TypeSpecifier::INT, 1 };

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


        frame.varBindings[name] = { currentVariableSize, offsetFromFp, reg, TypeSpecifier::INT , 1};

        return;
    }



void Context::addLocalArray(const std::string& name, int length, std::ostream& s) {
    if (stack.empty()) throw std::runtime_error("No active frame");
    auto &frame = stack.back();
    if (frame.varBindings.count(name)) throw std::runtime_error("Duplicate var: " + name);

    const int elemSize = 4;               // int
    const int totalSize = elemSize * length;

    s << "addi sp, sp, -" << totalSize << "\n";

    // Base offset is at the bottom of this block we just reserved
    const int offsetFromFp = -(frame.frameSize + totalSize);
    frame.frameSize += totalSize;

    // Record: size = elemSize (so “size” means elem size for arrays),
    // offset = base, reg = -1, type = INT, length = length
    frame.varBindings[name] = { elemSize, offsetFromFp, -1, TypeSpecifier::INT, length };
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

    void Context::freeParamRegisters(std::ostream &stream){
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        auto &frame = stack.back();

        for (auto &kv : frame.varBindings) {
            variable &v = kv.second;

            // only spill if the var is currently living in an arg register
            if (v.reg >= 10 && v.reg <= 17) {          // a0..a7

                stream << "sw x" << v.reg << ", " << v.offset << "(s0)" << std::endl;
                registers.freeReg(v.reg);
                v.reg = -1;                             // now lives in memory only
            }
        }


    }

    void Context::freeAllRegisters(std::ostream &stream){
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        auto &frame = stack.back();

        for (auto &kv : frame.varBindings) {
            variable &v = kv.second;

            // only spill if the var is currently living in a register
            if (v.reg != -1) {
                stream << "sw x" << v.reg << ", " << v.offset << "(s0)" << std::endl;
                registers.freeReg(v.reg);
                v.reg = -1;                             // now lives in memory only
            }
        }


    }

    int Context::storeArgument(){
        for (int i=10; i <= 17; ++i) {
            if (!registers.usedRegs[i]) {
                registers.useReg(i);
                return i;
            }
        }
        return -1;  // No available registers
    }

    void Context::setSwitchEnd(std::string label){
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        stack.back().switchEnds.push_back(label);
    }

    std::string Context::getSwitchEnd() const {
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        return stack.back().switchEnds.back();
    }

    std::string Context::popSwitchEnd() {
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        std::string label = stack.back().switchEnds.back();
        stack.back().switchEnds.pop_back();
        return label;
    }

    void Context::setSwitchRegister(int reg){
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        stack.back().switchRegisters.push_back(reg);
    }

    int Context::getSwitchRegister() const {
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        return stack.back().switchRegisters.back();
    }

    int Context::popSwitchRegister() {
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        int reg = stack.back().switchRegisters.back();
        registers.freeReg(reg);
        stack.back().switchRegisters.pop_back();
        return reg;

    }



    void Context::setPendingNextCase(const std::string &l) {
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        stack.back().pendingNextCase = l;
    }

    std::optional<std::string> Context::getPendingNextCase() const {
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        return stack.back().pendingNextCase;
    }


    void Context::clearPendingNextCase() {
        if (stack.empty()) throw std::runtime_error("No active stack frame");
        stack.back().pendingNextCase.reset();
    }



}
