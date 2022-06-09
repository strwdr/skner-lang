#ifndef SKNER_PARSEREXCEPTION_H
#define SKNER_PARSEREXCEPTION_H

#include <utility>

#include "ISknerException.h"

class ParserException : public ISknerException {
public:
    ParserException(const std::string &msg, const Token &_token) :
            ISknerException(msg), token(_token) {};

    ParserException(const std::string &msg, const Token &_token,
                    const std::initializer_list<TokenType> &_expectedTokenTypes) :
            ISknerException(msg), token(_token), expectedTokenTypes(_expectedTokenTypes) {};

    [[nodiscard]] std::string getInfo() const override {
        auto tmpMsg = "parser error at " + token.position.msg() + ": " + msg + " | token provided: " +
                      helpers::tokenTypeToString(token.type);
        if (expectedTokenTypes.empty()) return tmpMsg;
        return std::string(tmpMsg + " tokens expected: " + expectedMsg());
    }

private:
    Token token;

    [[nodiscard]] std::string expectedMsg() const {
        std::string expectedMsg = "{";
        int i = 0;
        for (const auto &expectedToken: expectedTokenTypes) {
            i++;
            expectedMsg += helpers::tokenTypeToString(expectedToken);
            if (i != expectedMsg.size())
                expectedMsg += ",";
        }
        expectedMsg += "}";
        return expectedMsg;
    }

    std::vector<TokenType> expectedTokenTypes{};
};


#endif //SKNER_PARSEREXCEPTION_H
