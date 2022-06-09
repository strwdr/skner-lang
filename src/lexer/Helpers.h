#ifndef SKNER_LEXERHELPERS_H
#define SKNER_LEXERHELPERS_H

#include <iostream>
#include "structures/TokenType.h"

namespace helpers {
    static std::string tokenTypeToString(TokenType tokenType) {
        switch (tokenType) {
                /*-------------------- literals -------------------*/
            case T_NUMBER_LITERAL:
                return "number literal";
            case T_STRING_LITERAL:
                return "string literal";

                /*-------------------- keywords -------------------*/
            case T_FUNCTION:
                return "function keyword";
            case T_CONTINUE:
                return "continue keyword";
            case T_BREAK:
                return "break keyword";
            case T_RETURN:
                return "return keyword";
            case T_WHILE:
                return "while keyword";
            case T_IF:
                return "if keyword";
            case T_ELIF:
                return "elif keyword";
            case T_ELSE:
                return "else keyword";
            case T_END:
                return "end keyword";
            case T_NUMBER:
                return "number keyword";
            case T_STRING:
                return "string keyword";
            case T_BOOLEAN:
                return "boolean keyword";
            case T_TRUE:
                return "true literal";
            case T_FALSE:
                return "false literal";
            case T_EXIT:
                return "exit keyword";

                /*------------------ identifiers ------------------*/
            case T_IDENTIFIER:
                return "identifier";

                /*------------------- operators -------------------*/
            case T_GREATER_EQUAL:
                return ">= operator";
            case T_LESSER_EQUAL:
                return "<= operator";
            case T_GREATER:
                return "> operator";
            case T_LESSER:
                return "< operator";
            case T_NOT_EQUAL:
                return "!= operator";
            case T_EQUAL:
                return "== operator";
            case T_NEGATE:
                return "! operator";
            case T_ASSIGNMENT:
                return "= operator";
            case T_OR:
                return "'or' operator";
            case T_AND:
                return "'and' operator";
            case T_EVALUATE:
                return "$ operator";
            case T_PLUS:
                return "+ operator";
            case T_MINUS:
                return "- operator";
            case T_DIVIDE:
                return "/ operator";
            case T_MULTIPLY:
                return "* operator";
            case T_MODULO:
                return "% operator";
            case T_DELETE:
                return "~ operator";

                /*------------------ punctuators ------------------*/
            case T_COMMA:
                return "comma";
            case T_OPEN_BRACKET:
                return "open bracket";
            case T_CLOSE_BRACKET:
                return "close bracket";
            case T_SEMICOLON:
                return "semicolon";

                /*--------------------- other ---------------------*/
            case T_ETX:
                return "ETX";
            case T_UNDEFINED:
                return "undefined";
            default:
                return "UNKNOWN ENUM VALUE";
        }
    }

    static TokenType multOperToTokenType(const std::string &op) {
        if (op == ">=") return T_GREATER_EQUAL;
        if (op == "<=") return T_LESSER_EQUAL;
        if (op == ">") return T_GREATER;
        if (op == "<") return T_LESSER;
        if (op == "!=") return T_NOT_EQUAL;
        if (op == "==") return T_EQUAL;
        if (op == "!") return T_NEGATE;
        if (op == "=") return T_ASSIGNMENT;
        return T_UNDEFINED;
    }

    static bool isIdentifierChar(char c) {
        return (std::isalnum(c) or c == '_');
    }

    static bool isIdentifierFirstChar(char c) {
        return (std::isalpha(c) or c == '_');
    }

    static bool isDigit(char c) {
        return (c >= '0' and c <= '9');
    }

    static char escapeCharToEscapeSymbol(char c) {
        switch (c){
            case 'a': return '\a';
            case 'b': return '\b';
            case 'n': return '\n';
            case 'v': return '\v';
            case 'f': return '\f';
            case 'r': return '\r';
            case '"': return '\"';
            case '\\': return '\\';
            default:
                throw std::exception();
        }
    }
}

#endif //SKNER_LEXERHELPERS_H
