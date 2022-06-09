#include "../doctest.h"
#include "../../lexer/Lexer.h"
#include <string>
#include "../helpers/SsLexer.h"

TEST_SUITE("lexer") {
    TEST_CASE("skip to next newline") {
        auto ssLexer = SsLexer("someid\nfunction\nsomeid2 asdf\n");
        ssLexer.getLexer().skipToNextNewline(); // skip someid identifier
        auto token = ssLexer.getNextToken();
        CHECK(token.type == T_FUNCTION);
        token = ssLexer.getNextToken();
        CHECK(token.type == T_IDENTIFIER);
        CHECK(std::get<std::string>(token.value) == "someid2");
        ssLexer.getLexer().skipToNextNewline();
        CHECK(ssLexer.getNextToken().type == T_ETX);
    }

}
