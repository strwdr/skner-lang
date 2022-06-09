#include "Lexer.h"
#include "../error_handler/exeptions/LexerException.h"

bool Lexer::tryBuildMultiCharOpToken() {
    std::string tmpStr;
    TokenType tokenType = T_UNDEFINED;
    tmpStr += character;
    auto operTokenType = helpers::multOperToTokenType(tmpStr);
    while (operTokenType != T_UNDEFINED) {
        tokenType = operTokenType;
        if (nextCharacter()) break;
        tmpStr += character;
        operTokenType = helpers::multOperToTokenType(tmpStr);
    }

    if (tokenType != T_UNDEFINED) {
        token = {tokenType, tokenPosition};
        return true;
    }
    return false;
}

bool Lexer::tryBuildSingleCharOpToken() {
    auto singleCharTokenType = static_cast<TokenType>(character);
    if (singleCharTokens.contains(singleCharTokenType)) {
        token = Token{singleCharTokenType, tokenPosition};
        nextCharacter();
        return true;
    }
    return false;
}

bool Lexer::tryBuildKeywordOrIdToken() {
    std::string tmpStr;
    TokenType tokenType;
    if (helpers::isIdentifierFirstChar(character)) {
        tmpStr += character;
    } else return false;
    while (!nextCharacter() and helpers::isIdentifierChar(character)) {
        tmpStr += character;
    }
    if (tmpStr.length() > 0) {
        auto keywordTokenTypeIt = keywords.find(tmpStr);
        if (keywordTokenTypeIt != keywords.end()) {
            tokenType = keywordTokenTypeIt->second;
        } else tokenType = T_IDENTIFIER;
        token = Token{tokenType, tokenPosition, tmpStr};
        return true;
    }
    return false;
}

bool Lexer::tryBuildETX() {
    if (stream.eof()) {
        token = {T_ETX, tokenPosition};
        return true;
    }
    return false;
}

bool Lexer::tryBuildStringLiteralToken() {
    if (character != '"') return false;
    std::string tmpStr;
    if (nextCharacter()) throw LexerException("ETX symbol found unexpectedly in string", token);
    while (character != '"') {
        if (character == '\\') {
            if (nextCharacter()) throw LexerException("ETX symbol found unexpectedly in string", token);
            try {
                tmpStr += helpers::escapeCharToEscapeSymbol(character);
            }
            catch (const std::exception &e) {
                throw LexerException("Invalid escape symbol", token);
            }
        } else {
            tmpStr += character;
        }
        if (nextCharacter()) throw LexerException("ETX symbol found unexpectedly in string", token);
    }
    nextCharacter();
    token = {T_STRING_LITERAL, tokenPosition, tmpStr};
    return true;
}

bool Lexer::tryBuildNumberLiteralToken() {
    if (!helpers::isDigit(character)) return false;
    std::string tmpStr;
    while (helpers::isDigit(character)) {
        tmpStr += character;
        if (nextCharacter()) break;
    }
    if (character == '.') {
        tmpStr += character;
        if (nextCharacter()) throw LexerException("Invalid number - found EOF after '.' symbol", token);
        bool atLeastOneNum = false;
        while (helpers::isDigit(character)) {
            tmpStr += character;
            atLeastOneNum = true;
            if (nextCharacter()) break;
        }
        if (!atLeastOneNum) {
            throw LexerException("Invalid number - there are no digits after '.' symbol", token);
        }
    }
    token = {T_NUMBER_LITERAL, tokenPosition, std::stod(tmpStr)};
    return true;
}


