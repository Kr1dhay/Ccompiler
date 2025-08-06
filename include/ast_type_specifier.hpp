#pragma once

#include <string_view>
#include <stdexcept>

namespace ast {

// === Type Specifier ===
enum class TypeSpecifier
{
    INT,
    VOID,
    FLOAT,
    DOUBLE
};


template<typename LogStream>
LogStream& operator<<(LogStream& ls, const TypeSpecifier& type)
{
    const auto TypeToString = [&type] {
        switch (type)
        {
        case TypeSpecifier::INT:
            return "int";
        case TypeSpecifier::VOID:
            return "void";
        case TypeSpecifier::FLOAT:
            return "float";
        case TypeSpecifier::DOUBLE:
            return "double";
        }
        throw std::runtime_error("Unexpected type specifier");
    };
    return ls << TypeToString();
}

}
