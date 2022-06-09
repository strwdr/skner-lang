#include "../../doctest.h"
#include "../../helpers/Helpers.h"
#include "../../../error_handler/exeptions/ParserException.h"


TEST_SUITE("parser") {
    TEST_CASE("no argument function call") {
        auto ssParser = SsParser("asd(asd,asdf);");
//                IAstNode::preOrderArrayToOstream(std::cout, parsedPtr);
//                std::cout << std::endl;
//                IAstNode::nestedTreeToOstream(std::cout, parsedPtr);

        auto expected = std::vector<AstNodeType>(
                {N_VARIABLE_REFERENCE, N_VARIABLE_REFERENCE, N_FUNCTION_CALL});
        auto invalid = std::vector<AstNodeType>(
                {N_VARIABLE_REFERENCE, N_VARIABLE_REFERENCE, N_NUMBER_LITERAL});

        auto preOrder = ssParser.getPreOrderParsedProgramStatement();

        CHECK(checkPreOrder(preOrder, expected));
        CHECK(!checkPreOrder(preOrder, invalid));
    }

    TEST_CASE("two expression arguments function call") {
        auto ssParser = SsParser("asd(-otherfun(), (20));");
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
//        ssParser.printProgramStatementTree();
        auto expected = std::vector<AstNodeType>(
                {N_FUNCTION_CALL, N_MINUS_EXPRESSION, N_NUMBER_LITERAL, N_FUNCTION_CALL});
        auto invalid = std::vector<AstNodeType>(
                {N_FUNCTION_CALL, N_NUMBER_LITERAL, N_NUMBER_LITERAL, N_FUNCTION_CALL});

        CHECK(checkPreOrder(preOrder, expected));
        CHECK(!checkPreOrder(preOrder, invalid));
    }
}