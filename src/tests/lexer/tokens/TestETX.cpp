#include "../../doctest.h"
#include "../../../lexer/Lexer.h"
#include "../../helpers/SsLexer.h"


TEST_SUITE("lexer") {
    TEST_CASE("ETX") {
        auto lexer = SsLexer();
        CHECK(lexer.getNextToken().type == T_ETX);
        CHECK(lexer.getNextToken().type == T_ETX);
    }
}
