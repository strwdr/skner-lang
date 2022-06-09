#include "../../doctest.h"
#include "../../../lexer/Lexer.h"
#include "../../helpers/SsLexer.h"


TEST_SUITE("lexer") {
    TEST_CASE("lexer boolean literals") {
        auto lexer = SsLexer("true   false");
        CHECK(lexer.getNextToken().type == T_TRUE);
        CHECK(lexer.getNextToken().type == T_FALSE);
        CHECK(lexer.getNextToken().type == T_ETX);
    }
}
