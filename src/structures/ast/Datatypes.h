#ifndef SKNER_DATATYPES_H
#define SKNER_DATATYPES_H

#include <exception>
#include "../../lexer/structures/TokenType.h"

enum DataType{
    BOOLEAN,
    NUMBER,
    STRING,
    UNDEFINED
};

static DataType remapTokenTypeToDatatype(TokenType tokenType){
    switch(tokenType){
        case(T_NUMBER_LITERAL):
        case(T_NUMBER):
            return NUMBER;
        case(T_TRUE):
        case(T_FALSE):
        case(T_BOOLEAN):
            return BOOLEAN;
        case(T_STRING):
        case(T_STRING_LITERAL):
            return STRING;
        default:
            return UNDEFINED;
    }
}

#endif //SKNER_DATATYPES_H
