#include "../../doctest.h"
#include "../../../lexer/Lexer.h"
#include "../../../error_handler/exeptions/LexerException.h"
#include <string>
#include <vector>
#include "../../helpers/SsLexer.h"

TEST_SUITE("lexer") {
    TEST_CASE("lexer valid number literals") {
        std::vector<std::string> validNumbersStrings = {
                "123412.2314221",
                "1",
                "12.2",
                "123456789",
                "000123456789",
                "12.0000",
                "1.0020",
        };

        for (const auto &numberString: validNumbersStrings) {
            auto ssLexer = SsLexer();
            CAPTURE(numberString);
            ssLexer<<numberString;
            auto token = ssLexer.getNextToken();
            CHECK(token.type == T_NUMBER_LITERAL);
            CHECK(get<double>(token.value) == stod(numberString));
        }
    }

    TEST_CASE("lexer valid number literals") {
        std::vector<std::string> invalidNumbersStrings = {
                ".123",
                "1234.",
                "1234..231124",
        };

        for (const auto &numberString: invalidNumbersStrings) {
            auto ssLexer = SsLexer();
            CAPTURE(numberString);
            ssLexer << numberString; // invalid numberString
            CHECK_THROWS_AS(ssLexer.getNextToken(), LexerException);
            CHECK(ssLexer.getToken().type == T_UNDEFINED);
        }
    }
}
