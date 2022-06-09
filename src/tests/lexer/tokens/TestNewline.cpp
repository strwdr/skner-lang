#include "../../doctest.h"
#include "../../../lexer/Lexer.h"
#include "../../helpers/SsLexer.h"


TEST_SUITE("lexer") {
    TEST_CASE("newlines") {
        const std::string validNewlines[] = {
                "\n",
                "\t\n   ",
                "\r\n",
                "  \r     \n",

        };

        auto ssLexer = SsLexer();

        for (auto &_: validNewlines) {
            SUBCASE(_.c_str()) {
                ssLexer << _;
                CHECK(ssLexer.getNextToken().type == T_ETX);
            }
        }
    }
}
