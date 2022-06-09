#include "../../doctest.h"
#include "../../../lexer/Lexer.h"
#include "../../helpers/SsLexer.h"


TEST_SUITE("lexer") {
    TEST_CASE("comments") {
        const std::string validComments[] = {
                "#asdfwdfaaw",
                "### aaaddddaasdddad",
                "#apdokpokwd",
                "#",
        };

        auto ssLexer = SsLexer();

        for (auto &_: validComments) {
            SUBCASE(_.c_str()) {
                ssLexer << _;
                auto token = ssLexer.getNextToken();
                CAPTURE(helpers::tokenTypeToString(token.type));
                CHECK(ssLexer.getNextToken().type == T_ETX);
            }
        }

        SUBCASE("2 comments after id + comment after keyword"){
            ssLexer << "someid#comment;\n;#comment\r\nend;#keyword";
            CHECK(ssLexer.getNextToken().type == T_IDENTIFIER);
            CHECK(ssLexer.getNextToken().type == T_SEMICOLON);
            CHECK(ssLexer.getNextToken().type == T_END);
            CHECK(ssLexer.getNextToken().type == T_SEMICOLON);
            CHECK(ssLexer.getNextToken().type == T_ETX);
        }
    }

}
