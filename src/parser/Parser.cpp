#include "Parser.h"
#include <utility>

#include "../error_handler/exeptions/ParserException.h"


Parser::Parser(std::istream &stream) : lexer(stream) {}

void Parser::nextToken() {
    token = getNextToken();
    bufferedNextToken.reset();
}

bool Parser::isAcceptable(const Token &_token, const std::initializer_list<TokenType> &acceptable) {
    for (auto &it: acceptable)
        if (_token.type == it) return true;
    return false;
}

std::optional<Token> Parser::accept(const std::initializer_list<TokenType> &acceptable, bool acceptNextToken) {
    Token _token = token;
    if(acceptNextToken) _token = getNextToken();
    if (isAcceptable(_token, acceptable)) {
        auto oldToken = _token;
        nextToken();
        return oldToken;
    } else {
        return {};
    }
}

std::optional<Token> Parser::check(const std::initializer_list<TokenType> &acceptable, bool checkNextToken) {
    Token _token = token;
    if(checkNextToken) _token = getNextToken();
    if (isAcceptable(_token, acceptable)) {
        return _token;
    } else {
        return {};
    }
}

std::optional<Token> Parser::checkNext(const std::initializer_list<TokenType> &acceptable) {
    return check(acceptable, true);
}

std::optional<Token> Parser::acceptNext(const std::initializer_list<TokenType> &acceptable) {
    return accept(acceptable, true);
}

void Parser::acceptNextOrThrow(const std::initializer_list<TokenType> &acceptable, const std::string & msg) {
    if(!acceptNext(acceptable))
        throw ParserException(msg, getNextToken(), acceptable);
}

Token Parser::getToken(){
    return token;
}

Token Parser::getNextToken() {
    if (!bufferedNextToken.has_value()) {
        bufferedNextToken = lexer.getNextToken();
    }
    return bufferedNextToken.value();
}

void Parser::skipSemicolons() {
    while(getNextToken().type == T_SEMICOLON){
        nextToken();
    }
}

void Parser::throwNext(const std::string & msg) {
    throw ParserException(msg, getNextToken());
}

void Parser::skipToNextNewline(){
    lexer.skipToNextNewline();
    token = lexer.getToken();
    bufferedNextToken = {};
}