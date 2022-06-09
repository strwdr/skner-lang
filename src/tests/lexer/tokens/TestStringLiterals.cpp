#include "../../doctest.h"
#include <iostream>
#include "../../../lexer/Lexer.h"
#include "../../helpers/SsLexer.h"
#include "../../../error_handler/exeptions/LexerException.h"
#include <sstream>
#include <string>
#include <vector>
#include <tuple>


TEST_SUITE("lexer") {
    TEST_CASE("valid string literals") {

        const std::pair<std::string, std::string> validStringPairs[] = {
                std::pair(R"("asdf")", "asdf"),
                std::pair(R"("fwfawaf\n")", "fwfawaf\n"),
                std::pair(R"("asfsa\\asdsawfa")", "asfsa\\asdsawfa"),
                std::pair(R"("\a\b\n\v\f\r\"")", "\a\b\n\v\f\r\""),
        };

        for (auto &validString: validStringPairs) {
            CAPTURE(validString.first);
            auto ssLexer = SsLexer(validString.first);
            auto token = ssLexer.getNextToken();
            CHECK(token.type == T_STRING_LITERAL);
            CHECK(get<std::string>(token.value) == validString.second);
            CHECK(ssLexer.getNextToken().type == T_ETX);
        }
    }

    TEST_CASE("quotes in string literals") {
        auto ssLexer = SsLexer();
        SUBCASE("4 quotes") {
            ssLexer << R"("text"id"text2")";
            auto token = ssLexer.getNextToken();
            CHECK(token.type == T_STRING_LITERAL);
            CHECK(get<std::string>(token.value) == "text");
            token = ssLexer.getNextToken();
            CHECK(token.type == T_IDENTIFIER);
            CHECK(get<std::string>(token.value) == "id");
            token = ssLexer.getNextToken();
            CHECK(token.type == T_STRING_LITERAL);
            CHECK(get<std::string>(token.value) == "text2");
            CHECK(token.type == T_STRING_LITERAL);
            CHECK(ssLexer.getNextToken().type == T_ETX);
        }

        SUBCASE("not closed quote string literals") {
            ssLexer << R"("text1test2)";
            CHECK_THROWS_AS(ssLexer.getNextToken(), LexerException);
            CHECK(ssLexer.getToken().type == T_UNDEFINED);
            auto strVal = std::get<std::string>(ssLexer.getToken().value);
            CAPTURE(strVal);
            CHECK(strVal == "");
            CHECK(ssLexer.getNextToken().type == T_ETX);
        }
    }

    TEST_CASE("invalid string literals") {
        const std::string invalidStrings[] = {
                R"("fwawfawfawa\%")",
                R"("\&")",
                R"("\^")",
                R"("\h")"
        };

        for (auto &invalidString: invalidStrings) {
            CAPTURE(invalidString);
            auto ssLexer = SsLexer(invalidString);
            CHECK_THROWS_AS(ssLexer.getNextToken(), LexerException);
            CHECK(ssLexer.getToken().type == T_UNDEFINED);
            ssLexer.getLexer().skipToNextNewline(); // skip all unprocessed characters in line
            CHECK(ssLexer.getNextToken().type == T_ETX);
        }
    }
}
