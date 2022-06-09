#ifndef SKNER_SSLEXER_H
#define SKNER_SSLEXER_H

#include <sstream>

#include "../../lexer/Lexer.h"

class SsLexer { // class for token tests
    std::stringstream stream;
    Lexer lexer;
public:
    explicit SsLexer(const std::string &testText) : SsLexer() {
        stream << testText;
    }

    std::ostream &operator<<(const std::string &a) {
        return stream << a;
    }

    SsLexer() : lexer(Lexer(stream)) {}

    Lexer &getLexer() {
        return lexer;
    }

    Token getNextToken() {
        return lexer.getNextToken();
    }

    const Token &getToken() const{
        return lexer.getToken();
    }
};


#endif //SKNER_SSLEXER_H
