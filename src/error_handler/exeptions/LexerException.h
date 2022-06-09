#ifndef SKNER_LEXEREXCEPTION_H
#define SKNER_LEXEREXCEPTION_H

#include <utility>

#include "ISknerException.h"

class LexerException : public ISknerException {
private:
    Token token;
public:
    LexerException(const std::string &msg, const Token &_token) : ISknerException(msg), token(_token) {};

    [[nodiscard]] std::string getInfo() const override {
        return std::string(
                "lexer error in " + helpers::tokenTypeToString(token.type) + " token at " + token.position.msg() + ": " +
                msg);
    }

    [[nodiscard]] const Token &getToken() const {
        return token;
    }
};


#endif //SKNER_LEXEREXCEPTION_H
