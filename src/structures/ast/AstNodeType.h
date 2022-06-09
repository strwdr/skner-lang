#ifndef SKNER_ASTNODETYPE_H
#define SKNER_ASTNODETYPE_H

#include <string>

enum AstNodeType {
    // statements
    N_VARIABLE_ASSIGNMENT,
    N_VARIABLE_DEFINITION,
    N_FUNCTION_DEFINITION,
    N_WHILE_STATEMENT,
    N_IF_STATEMENT,
    N_DELETION,
    N_EXIT,
    N_BREAK,
    N_RETURN_STATEMENT,
    N_CONTINUE,
    N_STATEMENT_BLOCK,
    N_CONDITIONAL_STATEMENT_BLOCK,
    // expressions
    N_ADD_EXPRESSION,
    N_SUBTRACT_EXPRESSION,
    N_VARIABLE_REFERENCE,
    N_OR_EXPRESSION,
    N_AND_EXPRESSION,
    N_EQUAL_EXPRESSION,
    N_GREATER_EQUAL_EXPRESSION,
    N_GREATER_EXPRESSION,
    N_LESS_EQUAL_EXPRESSION,
    N_LESS_EXPRESSION,
    N_NOT_EQUAL_EXPRESSION,
    N_DIVIDE_EXPRESSION,
    N_MODULO_EXPRESSION,
    N_MULTIPLY_EXPRESSION,
    N_EVALUATE_EXPRESSION,
    N_MINUS_EXPRESSION,
    N_NEGATE_EXPRESSION,
    N_STRING_LITERAL,
    N_BOOLEAN_LITERAL,
    N_NUMBER_LITERAL,
    // common
    N_FUNCTION_CALL,
    // other
    N_UNDEFINED
};


static std::string astNodeTypeToString(AstNodeType astNodeType) {
    switch (astNodeType) {
        case N_VARIABLE_ASSIGNMENT:
            return "N_VARIABLE_ASSIGNMENT";

        case N_VARIABLE_DEFINITION:
            return "N_VARIABLE_DEFINITION";

        case N_FUNCTION_DEFINITION:
            return "N_FUNCTION_DEFINITION";

        case N_WHILE_STATEMENT:
            return "N_WHILE_STATEMENT";

        case N_IF_STATEMENT:
            return "N_IF_STATEMENT";

        case N_DELETION:
            return "N_DELETION";

        case N_EXIT:
            return "N_EXIT";

        case N_BREAK:
            return "N_BREAK";

        case N_RETURN_STATEMENT:
            return "N_RETURN_STATEMENT";

        case N_CONTINUE:
            return "N_CONTINUE";

        case N_STATEMENT_BLOCK:
            return "N_STATEMENT_BLOCK";

        case N_CONDITIONAL_STATEMENT_BLOCK:
            return "N_CONDITIONAL_STATEMENT_BLOCK";

        case N_ADD_EXPRESSION:
            return "N_ADD_EXPRESSION";

        case N_SUBTRACT_EXPRESSION:
            return "N_SUBTRACT_EXPRESSION";

        case N_VARIABLE_REFERENCE:
            return "N_VARIABLE_REFERENCE";

        case N_OR_EXPRESSION:
            return "N_OR_EXPRESSION";

        case N_AND_EXPRESSION:
            return "N_AND_EXPRESSION";

        case N_EQUAL_EXPRESSION:
            return "N_EQUAL_EXPRESSION";

        case N_GREATER_EQUAL_EXPRESSION:
            return "N_GREATER_EQUAL_EXPRESSION";

        case N_GREATER_EXPRESSION:
            return "N_GREATER_EXPRESSION";

        case N_LESS_EQUAL_EXPRESSION:
            return "N_LESS_EQUAL_EXPRESSION";

        case N_LESS_EXPRESSION:
            return "N_LESS_EXPRESSION";

        case N_NOT_EQUAL_EXPRESSION:
            return "N_NOT_EQUAL_EXPRESSION";

        case N_DIVIDE_EXPRESSION:
            return "N_DIVIDE_EXPRESSION";

        case N_MODULO_EXPRESSION:
            return "N_MODULO_EXPRESSION";

        case N_MULTIPLY_EXPRESSION:
            return "N_MULTIPLY_EXPRESSION";

        case N_EVALUATE_EXPRESSION:
            return "N_EVALUATE_EXPRESSION";

        case N_MINUS_EXPRESSION:
            return "N_MINUS_EXPRESSION";

        case N_NEGATE_EXPRESSION:
            return "N_NEGATE_EXPRESSION";

        case N_STRING_LITERAL:
            return "N_STRING_LITERAL";

        case N_BOOLEAN_LITERAL:
            return "N_BOOLEAN_LITERAL";

        case N_NUMBER_LITERAL:
            return "N_NUMBER_LITERAL";

        case N_FUNCTION_CALL:
            return "N_FUNCTION_CALL";

        case N_UNDEFINED:
        default:
            return "N_UNDEFINED";

    }

}


#endif //SKNER_ASTNODETYPE_H
