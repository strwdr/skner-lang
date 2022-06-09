#include "../../doctest.h"
#include "../../../lexer/Lexer.h"
#include "../../helpers/SsLexer.h"


TEST_SUITE("lexer") {
    TEST_CASE("lexer keywords") {
        auto ssLexer = SsLexer();
        for (auto & keyword: ssLexer.getLexer().getKeywords()) {
            SUBCASE(keyword.first.c_str()){
                ssLexer << keyword.first;
                auto token = ssLexer.getNextToken();
                CHECK(token.type == keyword.second);
                CHECK(ssLexer.getNextToken().type == T_ETX);
            }
        }
    }
}
