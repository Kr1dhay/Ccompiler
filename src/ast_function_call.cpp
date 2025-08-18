#include "ast_function_call.hpp"


namespace ast{


    void FunctionCall::EmitRISC(std::ostream &stream, Context &context) const {

        std::string funcName = function_->getName();
        context.freeParamRegisters(stream);

        if (arguments_) {
            context.freeRegister(28);
            arguments_->EmitRISC(stream, context);
            stream << "mv a0, x28" << std::endl;
        }

        stream << "call " << funcName << std::endl;

    }

    void FunctionCall::Print(std::ostream &stream) const {
        stream << "FunctionCall: ";
        if (function_) {
            function_->Print(stream);
        } else {
            stream << "null";
        }
        stream << "(";
        if (arguments_) {
            arguments_->Print(stream);
        } else {
            stream << "null";
        }
        stream << ")";
    }
}
