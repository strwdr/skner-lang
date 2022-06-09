#ifndef SKNER_TOKENTYPE_H
#define SKNER_TOKENTYPE_H

enum TokenType {
    /*-------------------- literals -------------------*/
    T_NUMBER_LITERAL = 256,
    T_STRING_LITERAL = 258,

    /*-------------------- keywords -------------------*/
    /* functions  */
    T_FUNCTION = 259,
    T_CONTINUE = 260,
    T_BREAK = 261,
    T_RETURN = 262,

    /* statements */
    T_WHILE = 263,
    T_IF = 264,
    T_ELIF = 265,
    T_ELSE = 266,
    T_END = 267,

    /* type specifiers */
    T_NUMBER = 268,
    T_STRING = 269,
    T_BOOLEAN = 270,

    /* literals */
    T_TRUE = 271,
    T_FALSE = 272,

    /*------------------ identifiers ------------------*/
    T_IDENTIFIER = 273,

    /*------------------- operators -------------------*/
    T_GREATER_EQUAL = 274, // >=
    T_LESSER_EQUAL = 275, // <=
    T_GREATER = 276, // >
    T_LESSER = 277, // <
    T_NOT_EQUAL = 278, // !=
    T_EQUAL = 279, // ==
    T_NEGATE = 280, // !
    T_ASSIGNMENT = 281, // =

    /* single character */
    T_OR = '|',
    T_AND = '&',

    T_EVALUATE = '$',
    T_PLUS = '+',
    T_MINUS = '-',
    T_DIVIDE = '/',
    T_MULTIPLY = '*',
    T_MODULO = '%',
    T_DELETE = '~',

    /*------------------ punctuators ------------------*/
    T_COMMA = ',',
    T_OPEN_BRACKET = '(',
    T_CLOSE_BRACKET = ')',
    T_SEMICOLON = ';',

    /*--------------------- other ---------------------*/
    T_ETX = 282,
    T_UNDEFINED = 283,
    T_EXIT = 284,
};

#endif //SKNER_TOKENTYPE_H
