#include "../../doctest.h"
#include "../../../lexer/Lexer.h"
#include "../../helpers/SsLexer.h"
#include "../../../error_handler/exeptions/LexerException.h"


TEST_SUITE("lexer") {
    TEST_CASE("valid operators") {
        const std::pair<std::string, TokenType> operatorsAndTokens[] = {
                // multi-char operators
                std::pair(">=", T_GREATER_EQUAL),
                std::pair("<=", T_LESSER_EQUAL),
                std::pair(">", T_GREATER),
                std::pair("<", T_LESSER),
                std::pair("!=", T_NOT_EQUAL),
                std::pair("==", T_EQUAL),
                std::pair("!", T_NEGATE),
                std::pair("=", T_ASSIGNMENT),

                // single-char tokens
                std::pair("|", T_OR),
                std::pair("&", T_AND),
                std::pair("$", T_EVALUATE),
                std::pair("+", T_PLUS),
                std::pair("-", T_MINUS),
                std::pair("*", T_MULTIPLY),
                std::pair("/", T_DIVIDE),
                std::pair("%", T_MODULO),
                std::pair("~", T_DELETE),
                std::pair(",", T_COMMA),
                std::pair("(", T_OPEN_BRACKET),
                std::pair(")", T_CLOSE_BRACKET),
                std::pair(";", T_SEMICOLON),
        };

        auto ssLexer = SsLexer();
        for (auto &opTk: operatorsAndTokens) {
            SUBCASE(opTk.first.c_str()) {
                ssLexer << opTk.first;
                auto token = ssLexer.getNextToken();
                CHECK(token.type == opTk.second);
                CHECK(ssLexer.getNextToken().type == T_ETX);
            }
        }
    }

    TEST_CASE("invalid operators") {
        const std::string invalidOperators[] = {
                "^",
                "@",
                "[",
                ".",
                ":"
        };
        auto ssLexer = SsLexer();
        for (auto &opTk: invalidOperators) {
            SUBCASE(opTk.c_str()) {
                ssLexer << opTk;
                CHECK_THROWS_AS(ssLexer.getNextToken(), LexerException);
                CHECK(ssLexer.getToken().type == T_UNDEFINED);
                CHECK(ssLexer.getNextToken().type == T_ETX);
            }
        }
    }
}
