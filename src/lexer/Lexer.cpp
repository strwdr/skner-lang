#include "Lexer.h"
#include "../error_handler/exeptions/LexerException.h"

Lexer::Lexer(std::istream &stream) : stream(stream) {}

const std::set<TokenType> Lexer::singleCharTokens = {
        /* operators */
        T_OR,
        T_AND,
        T_EVALUATE,
        T_PLUS,
        T_MINUS,
        T_DIVIDE,
        T_MULTIPLY,
        T_MODULO,
        T_DELETE,

        /* punctuators */
        T_COMMA,
        T_OPEN_BRACKET,
        T_CLOSE_BRACKET,

        /* other */
        T_SEMICOLON,
};

const std::map<std::string, TokenType> Lexer::keywords = {
        /* functions  */
        {"function", T_FUNCTION},
        {"continue", T_CONTINUE},
        {"return",   T_RETURN},

        /* statements */
        {"while",    T_WHILE},
        {"if",       T_IF},
        {"elif",     T_ELIF},
        {"else",     T_ELSE},
        {"end",      T_END},
        {"break",    T_BREAK},

        /* type specifiers */
        {"number",   T_NUMBER},
        {"string",   T_STRING},
        {"boolean",  T_BOOLEAN},

        /* literals */
        {"true",     T_TRUE},
        {"false",    T_FALSE},

        /* bonus keywords */
        {"and",      T_AND},
        {"or",       T_OR},
        {"exit",     T_EXIT},
};

const std::map<std::string, TokenType> &Lexer::getKeywords() {
    return keywords;
}

bool Lexer::skipWhitespaces() {
    bool skipped = false;
    while (iswspace(character)) {
        if (nextCharacter()) break;
        skipped = true;
    }
    return skipped;
}

bool Lexer::skipComments() {
    if (character == '#') {
        bool skipped = false;
        while (character != '\n'){
            if (nextCharacter()) break;
            skipped = true;
        }
        return skipped;
    }
    return false;
}

const Token &Lexer::getToken() const {
    return token;
}

Token Lexer::getNextToken() {
    // skip whitespaces and comments
    while (skipWhitespaces() or skipComments());

    tokenPosition = currentPosition;
    token = Token{T_UNDEFINED, tokenPosition};

    if (tryBuildETX()) return token;
    if (tryBuildMultiCharOpToken()) return token;
    if (tryBuildSingleCharOpToken()) return token;
    if (tryBuildKeywordOrIdToken()) return token;
    if (tryBuildStringLiteralToken()) return token;
    if (tryBuildNumberLiteralToken()) return token;

    auto oldToken = token;
    auto oldCharacter = character;

    nextCharacter();
    skipToNextNewline();

    throw LexerException(
            std::string("Unknown symbol of code " + std::to_string(int(oldCharacter))),
            oldToken
    );
}

bool Lexer::nextCharacter() {
    auto &curCol = currentPosition.column;
    auto &curRow = currentPosition.row;

    do {
        if (character == '\n') {
            curCol = 0;
            curRow++;
        }
        stream.get(character);
        curCol++;
    } while (!stream.eof() and character == '\r');  // windows compatibility workaround

    return stream.eof();
}

bool Lexer::skipToNextNewline() {
    while (character != '\n')
        if (nextCharacter())
            return false;
    if (nextCharacter())
        return false;
    return true;
}
