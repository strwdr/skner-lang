#ifndef SKNER_INTERPRETEREXEPTION_H
#define SKNER_INTERPRETEREXEPTION_H

#include "ISknerException.h"

class InterpreterException : public ISknerException {
public:
    InterpreterException(const std::string &msg) : ISknerException(msg) {};

    [[nodiscard]] std::string getInfo() const override {
        return std::string("interpreter error: " + msg);
    }
};

#endif //SKNER_INTERPRETEREXEPTION_H
