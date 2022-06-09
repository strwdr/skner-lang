#ifndef SKNER_TOKEN_H
#define SKNER_TOKEN_H
#include <iostream>
#include <variant>
#include <string>
#include "TokenType.h"
#include "../../structures/Position.h"


struct Token {
    TokenType type;
    Position position;
    std::variant<std::string, double> value;
};


#endif // SKNER_TOKEN_H
