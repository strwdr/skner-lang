#include "../../doctest.h"
#include "../../helpers/Helpers.h"

TEST_SUITE("parser") {
    TEST_CASE("bool literal eq bool literal expression") {
        auto checkArr = {
                "a = true==false;",
                "b = false==false;",
                "c = false == false;",
                "d = true == true;"
        };

        auto expected = std::vector<AstNodeType>(
                {N_BOOLEAN_LITERAL, N_BOOLEAN_LITERAL, N_EQUAL_EXPRESSION,
                 N_VARIABLE_ASSIGNMENT}
        );

        for (auto exToCheck: checkArr) {
            SUBCASE(exToCheck) {
                auto ssParser = SsParser(exToCheck);
                auto preOrder = ssParser.getPreOrderParsedProgramStatement();
                CHECK(checkPreOrder(preOrder, expected));
            }
        }
    }

    TEST_CASE("bool literal not eq bool literal expression") {
        auto checkArr = {
                "a = true!=false;",
                "b = false!=false;",
                "c = false != false;",
                "d = true != true;"
        };

        auto expected = std::vector<AstNodeType>(
                {N_BOOLEAN_LITERAL, N_BOOLEAN_LITERAL, N_NOT_EQUAL_EXPRESSION,
                 N_VARIABLE_ASSIGNMENT}
        );

        for (auto exToCheck: checkArr) {
            SUBCASE(exToCheck) {
                auto ssParser = SsParser(exToCheck);
                auto preOrder = ssParser.getPreOrderParsedProgramStatement();
                CHECK(checkPreOrder(preOrder, expected));
            }
        }
    }

    TEST_CASE("(number literal rel zeroArgFun call) expression") {
        auto checkArr = {
                "a = 123 > asd();"
        };
        auto expected = std::vector<AstNodeType>(
                {N_NUMBER_LITERAL, N_FUNCTION_CALL, N_GREATER_EXPRESSION,
                 N_VARIABLE_ASSIGNMENT}
        );
        for (auto exToCheck: checkArr) {
            SUBCASE(exToCheck) {
                auto ssParser = SsParser(exToCheck);
                auto preOrder = ssParser.getPreOrderParsedProgramStatement();
                CHECK(checkPreOrder(preOrder, expected));
            }
        }
    }

    TEST_CASE("(number literal rel twoArgFun call) expression") {
        auto checkArr = {
                "a = 123 > asd(124,124);",
                "b = 124215.1 > something(1522,2515);",
                "c = 1521 > velylongfunctionnamethatisnoteveninanyconvention(123,12);",
                "d = 0 > fun(214, 124);"
        };
        auto expected = std::vector<AstNodeType>(
                {N_NUMBER_LITERAL, N_NUMBER_LITERAL, N_NUMBER_LITERAL,
                 N_FUNCTION_CALL, N_GREATER_EXPRESSION, N_VARIABLE_ASSIGNMENT}

        );
        for (auto exToCheck: checkArr) {
            SUBCASE(exToCheck) {
                auto ssParser = SsParser(exToCheck);
                auto preOrder = ssParser.getPreOrderParsedProgramStatement();

                CHECK(checkPreOrder(preOrder, expected));
            }
        }
    }

    TEST_CASE("simple nested expressions") {
        auto checkArr = {
                "c = (something(-2));",
                "var_3 = (fun(-2));",
        };
        auto expected = std::vector<AstNodeType>(
                {N_NUMBER_LITERAL, N_MINUS_EXPRESSION, N_FUNCTION_CALL, N_VARIABLE_ASSIGNMENT}
        );

        for (auto exToCheck: checkArr) {
            SUBCASE(exToCheck) {
                auto ssParser = SsParser(exToCheck);
                auto preOrder = ssParser.getPreOrderParsedProgramStatement();

                CHECK(checkPreOrder(preOrder, expected));
            }
        }
    }

    TEST_CASE("double simple nested expression") {
        auto ssParser = SsParser("a = ((20));");
        auto expected = std::vector<AstNodeType>(
                {N_NUMBER_LITERAL, N_VARIABLE_ASSIGNMENT}
        );
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
        CHECK(checkPreOrder(preOrder, expected));
    }

    TEST_CASE("negate expression") {
        auto ssParser = SsParser("boolean a = !(!(false));");
        auto expected = std::vector<AstNodeType>(
                {N_BOOLEAN_LITERAL, N_NEGATE_EXPRESSION, N_NEGATE_EXPRESSION, N_VARIABLE_ASSIGNMENT}
        );
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
//        printAstNodeTypeArr(preOrder);
//        ssParser.printProgramStatementTree();
        CHECK(checkPreOrder(preOrder, expected));
    }

    TEST_CASE("add expression") {
        auto ssParser = SsParser("a = 20+20;");
        auto expected = std::vector<AstNodeType>(
                {N_NUMBER_LITERAL, N_NUMBER_LITERAL, N_ADD_EXPRESSION, N_VARIABLE_ASSIGNMENT}
        );
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
        CHECK(checkPreOrder(preOrder, expected));
    }


    TEST_CASE("big nested expression") {
        auto ssParser = SsParser("a = ("
                                 "      (20) + ("
                                 "              fun(a,4) * 5 / 4 / ("
                                 "                                  5*3+fun()*4*("
                                 "                                              $something("
                                 "                                                          asd("
                                 "                                                              asd"
                                 "                                                              )"
                                 "                                                          )"
                                 "                                               )"
                                 "                                  ) "
                                 "              )"
                                 "      );");

        auto expected = std::vector<AstNodeType>(
                {N_NUMBER_LITERAL, N_VARIABLE_REFERENCE, N_NUMBER_LITERAL, N_FUNCTION_CALL, N_NUMBER_LITERAL,
                 N_NUMBER_LITERAL, N_DIVIDE_EXPRESSION, N_NUMBER_LITERAL, N_NUMBER_LITERAL, N_MULTIPLY_EXPRESSION,
                 N_FUNCTION_CALL, N_NUMBER_LITERAL, N_MULTIPLY_EXPRESSION, N_VARIABLE_REFERENCE, N_FUNCTION_CALL,
                 N_FUNCTION_CALL, N_EVALUATE_EXPRESSION, N_MULTIPLY_EXPRESSION, N_ADD_EXPRESSION, N_DIVIDE_EXPRESSION,
                 N_MULTIPLY_EXPRESSION, N_ADD_EXPRESSION, N_VARIABLE_ASSIGNMENT}
        );

        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
        CHECK(checkPreOrder(preOrder, expected));
        //        std::cout<<evaluator.getStringTree();


    }
}
