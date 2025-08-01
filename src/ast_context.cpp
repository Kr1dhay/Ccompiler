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

    // Stack Frame

    bool stackFrame::inFrame(std::string name) {
        return varBindings.find(name) != varBindings.end();
    }


    // Context

    std::string Context::makeLabel(std::string base) {
            return base + "_" + std::to_string(labelCounter++);
        }

    bool Context::isGlobal(const std::string &name) {
            return globals.find(name) != globals.end();
        }

    void Context::enterScope(std::ostream &dst) {
        stack.emplace_back();
        auto& frame = stack.back();
        frame.offset = 0; // locals start at offset 0 (we subtract to grow down)

        dst << "addi sp, sp, -16" << std::endl;     // allocate space for ra + fp
        dst << "sw ra, 12(sp)" << std::endl;        // save ra
        dst << "sw fp, 8(sp)" << std::endl;         // save old frame pointer
        dst << "addi fp, sp, 16" << std::endl;      // set new frame pointer
    }

    void Context::exitScope() {
        if (!stack.empty()) {
            stack.pop_back();
        }
    }
    int Context::allocate() {
        return registers.allocate();
    }


}
