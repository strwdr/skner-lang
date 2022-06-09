#ifndef SKNER_LEXER_H
#define SKNER_LEXER_H

#include <string>
#include <map>
#include <set>
#include <iostream>
#include <vector>

#include "structures/Token.h"
#include "structures/TokenType.h"
#include "../structures/Position.h"
#include "Helpers.h"

class Lexer {
public:
    explicit Lexer(std::istream &stream);

    Token getNextToken();

    bool skipToNextNewline();

    [[nodiscard]] const Token &getToken() const;

    static const std::map<std::string, TokenType> &getKeywords();

private:
    // variables

    static const std::map<std::string, TokenType> keywords;
    static const std::set<TokenType> singleCharTokens;
    std::istream &stream;
    Token token;
    Position tokenPosition;
    Position currentPosition;
    char character = ' ';

    // methods

    bool skipWhitespaces();

    bool skipComments();

    bool nextCharacter();

    bool tryBuildSingleCharOpToken();

    bool tryBuildMultiCharOpToken();

    bool tryBuildKeywordOrIdToken();

    bool tryBuildETX();

    bool tryBuildStringLiteralToken();

    bool tryBuildNumberLiteralToken();
};


#endif //SKNER_LEXER_H
