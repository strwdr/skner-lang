#ifndef SKNER_ISKNEREXCEPTION_H
#define SKNER_ISKNEREXCEPTION_H

#include <iostream>
#include <exception>
#include <utility>
#include "../../structures/Position.h"
#include "../../lexer/Helpers.h"
#include "../../lexer/structures/Token.h"


class ISknerException : public std::exception {
protected:
    const std::string msg;
public:
    ISknerException(const std::string &msg) : std::exception(), msg(msg) {}

    [[nodiscard]] virtual std::string getInfo() const = 0;
};

#endif //SKNER_ISKNEREXCEPTION_H
