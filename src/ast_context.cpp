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
        for (int i = 9; i <= 12; ++i) { // a0-a3
            if (usedRegs[i] == 0) {
                useReg(i);
                return i;
            }
        }
        for (int i = 25; i <= 27; ++i) { // t4-t6
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
        frame.offsetTracker = 8; // locals start at offset 8 (we subtract to grow down)
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

    int Context::allocate() {
        return registers.allocate();
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


    int Context::addLocalVar(const std::string& name) {
        if (stack.empty()) {
            throw std::runtime_error("No active stack frame to add local variable.");
        }
        auto& frame = stack.back();
        if (frame.inFrame(name)) {
            throw std::runtime_error("Variable already exists in the current scope: " + name);
        }

        frame.offsetTracker -= currentVariableSize;
        frame.varBindings[name] = {currentVariableSize, frame.offsetTracker, -1, TypeSpecifier::INT};

        return frame.offsetTracker;
    }

    int Context::getVariableOffset(const std::string& name) const {
        if (stack.empty()) {
            throw std::runtime_error("No active stack frame to get variable offset.");
        }
        auto& frame = stack.back();
        if (!frame.inFrame(name)) {
            throw std::runtime_error("Variable not found in the current scope: " + name);
        }
        return frame.varBindings.at(name).offsetTracker
        ;
    }


    int Context::getCurrentFrameSize() const {
        if (stack.empty()) {
            throw std::runtime_error("No active stack frame to get current frame size.");
        }
        return stack.back().offsetTracker;
    }

}
