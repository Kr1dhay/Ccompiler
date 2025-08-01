// An object of class Context is passed between ast nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <utility>

#pragma once

namespace ast {



// RISC-V Register file
struct RegisterFile
{
    int usedRegs[32] =
    { 1, // x0 = zero, always 0
      1, // x1 = ra (return address) (caller)
      1, // x2 = sp (stack pointer) (callee)
      1, // x3 = gp (global pointer)
      1, // x4 = tp (thread pointer)
      0, 0, 0, // x5-x7 = t0-t2 temporaries (caller)
      1, // x8 = s0/fp Saved register/frame pointer (callee)
      1, //x9 = s1 saved register (callee)
      0, 0, // x10-x11 = a0-a1 Function arguments/return values (caller)
      0, 0, 0, 0, 0, 0, // x12–17 = a2–7 Function arguments (caller)
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,// x18–27 = s2–11 Saved registers (callee)
      0, 0, 0, 0, // x28–31 = t3–6 Temporaries (caller)
    };

    void useReg(int i);
    void freeReg(int i);
    int allocate();
    // int allocateFloat();
};

// === Type Specifier ===
// struct Specifier {
//     enum Type { _int, _void, _float, _double };
// };


// === Variable ===
struct variable
{
    unsigned int size; // bytes
    int offset;        // fp-relative offset
    int reg;           // register allocated, -1 if in memory
    // Specifier type = Specifier::_int;
};

// === Function ===
struct function
{
    unsigned int size; // Total size of args
    std::vector<unsigned int> argSize;
};

// // === Enum ===
// struct enumeration
// {
//     std::string id;
//     int value;
// };

// === Stack Frame ===
struct stackFrame
{
    std::map<std::string, variable> varBindings;
    unsigned int offset = 0;
    std::string startLabel; // for continue/break
    std::string endLabel;
    // Specifier returnType; // comment out for now


    bool inFrame(std::string name);
};

std::ostream &operator<<(std::ostream &dst, stackFrame frame);


class Context
{

    private:
        RegisterFile registers;
        std::vector<stackFrame> stack;

        std::map<std::string, /*Specifier*/int> globals; // only int for now
        std::map<std::string, function> functions;
        // std::map<std::string, enumeration> enums;

        int labelCounter = 0;

    public:
        std::string makeLabel(std::string base);

        bool isGlobal(const std::string &name);

        // bool isEnum(const std::string &name) {
        //     return enums.find(name) != enums.end();
        // }

        void enterScope(std::ostream &dst);
        // void exitScope(std::ostream &dst);
        void exitScope();

        int allocate();
};

// What could go inside Context now:
// A method like emitFunctionPrologue(std::ostream& stream)
// ⤷ Handles stack adjustment, saving ra and fp

// A method like emitFunctionEpilogue(std::ostream& stream)
// ⤷ Restores fp, ra, resets stack

// A register allocator:

// int allocateRegister();     // e.g. return t0-t6 if free
// void freeRegister(int reg); // frees after use

} // namespace ast
