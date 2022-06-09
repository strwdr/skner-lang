#include "../../doctest.h"
#include "../../../lexer/Lexer.h"
#include "../../helpers/SsLexer.h"


TEST_SUITE("lexer") {
    TEST_CASE("whitespaces") {
        const std::string validComments[] = {
                "    ",
                "\t\t\t\r",
                "\t     \t   \r",
                "",

        };
        auto ssLexer = SsLexer();
        short int cnt = 0;
        for (const auto &_: validComments) {
            cnt++;
            SUBCASE(std::string("whitespace %" + std::to_string(cnt)).c_str()) {
                ssLexer << _;
                CHECK(ssLexer.getNextToken().type == T_ETX);
            }
        }

        SUBCASE("whitespaces after id + whitespace before keyword") {
            ssLexer << "someid     \n\t   \r\nend;";
            CHECK(ssLexer.getNextToken().type == T_IDENTIFIER);
            CHECK(ssLexer.getNextToken().type == T_END);
            CHECK(ssLexer.getNextToken().type == T_SEMICOLON);
            CHECK(ssLexer.getNextToken().type == T_ETX);
        }
    }

}
