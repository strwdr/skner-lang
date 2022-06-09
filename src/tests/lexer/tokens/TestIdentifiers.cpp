#include "../../doctest.h"
#include "../../../lexer/Lexer.h"
#include "../../helpers/SsLexer.h"
#include "../../../error_handler/exeptions/LexerException.h"


TEST_SUITE("lexer") {
    TEST_CASE("valid identifiers") {
        const std::string goodIdentifiers[] = {
                "x",
                "__",
                "_x",
                "_Xd",
                "_abcd31",
                "dffwda__",
                "Bd_df",
                "bb_asd44_"
        };

        auto ssLexer = SsLexer();

        for (auto &identifier: goodIdentifiers) {
            SUBCASE(identifier.c_str()) {
                ssLexer << identifier;
                auto token = ssLexer.getNextToken();
                CHECK(token.type == T_IDENTIFIER);
                CHECK(std::get<std::string>(token.value) == identifier);
                CHECK(ssLexer.getNextToken().type == T_ETX);
            }
        }
    }

    TEST_CASE("invalid identifiers") {
        const std::string badIdentifiers[] = {
                "-x",
                "sda!",
                "@3",
                ")Xd",
                "@_abcd31",
                "dff-da__",
                "Bd-df",
                "bb_asd44_"
        };

        auto ssLexer = SsLexer();

        for (auto &identifier: badIdentifiers) {
            unsigned short errorsCount = 0;
            unsigned short validIdsCount = 0;
            Token token;
            SUBCASE(identifier.c_str()) {
                ssLexer << identifier;
                do {
                    try {
                        token = ssLexer.getNextToken();
                        if (token.type != T_IDENTIFIER) errorsCount++;
                        else validIdsCount++;
                    }
                    catch (const LexerException &e) {
                        errorsCount++;
                    }

                } while (token.type != T_ETX);
                CHECK((validIdsCount != 1 || errorsCount >= 1));
            }
        }
    }
}
