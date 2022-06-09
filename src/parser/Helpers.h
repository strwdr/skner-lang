#ifndef SKNER_PARSERHELPERS_H
#define SKNER_PARSERHELPERS_H

#include <utility>
#include <string>
#include <memory>
#include "../lexer/structures/Token.h"

namespace helpers {
    static std::string stringValueFromToken(Token argToken) {
        return std::get<std::string>(argToken.value);
    }

    static double doubleValueFromToken(Token argToken) {
        return std::get<double>(argToken.value);
    }
}


#endif //SKNER_PARSERHELPERS_H
