#include "../../doctest.h"
#include "../../helpers/Helpers.h"
#include "../../../error_handler/exeptions/ParserException.h"

TEST_SUITE("parser") {

    TEST_CASE("three statements") {
        auto ssParser = SsParser(
                "if(a)exit;end while(true) break; end function somefunc(string a) a = \"string\"; exit; end");
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
        auto expected = std::vector<AstNodeType>(
                {N_VARIABLE_REFERENCE,N_EXIT,N_STATEMENT_BLOCK,N_CONDITIONAL_STATEMENT_BLOCK,N_IF_STATEMENT});
        CHECK(checkPreOrder(preOrder, expected));

        preOrder = ssParser.getPreOrderParsedProgramStatement();
        expected = {N_BOOLEAN_LITERAL, N_BREAK, N_STATEMENT_BLOCK, N_CONDITIONAL_STATEMENT_BLOCK,
                    N_WHILE_STATEMENT};
        CHECK(checkPreOrder(preOrder, expected));

        preOrder = ssParser.getPreOrderParsedProgramStatement();
        expected = {N_STRING_LITERAL, N_VARIABLE_ASSIGNMENT, N_EXIT, N_STATEMENT_BLOCK, N_FUNCTION_DEFINITION};
        CHECK(checkPreOrder(preOrder, expected));

        CHECK(ssParser.parseProgramStatement().get() == nullptr);

    }

    TEST_CASE("big statement") {
        auto ssParser = SsParser("if(a)\n"
                                 "  number a = 100;\n"
                                 "  number function dummyAdd(number a, number b)\n"
                                 "    number tmp = 1;\n"
                                 "    while(tmp <= b)\n"
                                 "        a = a + tmp;\n"
                                 "        tmp = tmp + 1;\n"
                                 "    end\n"
                                 "    return tmp + a;\n"
                                 "  end\n"
                                 "  dummyAdd(4, 5);\n"
                                 "  number something = dummyAdd(a, dummyAdd(3, 5));\n"
                                 "  exit;\n"
                                 "end\n");
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
//            ssParser.printProgramStatementTree();
//            printAstNodeTypeArr(preOrder);
        auto expected = std::vector<AstNodeType>(
                {N_VARIABLE_REFERENCE, N_NUMBER_LITERAL, N_VARIABLE_ASSIGNMENT, N_NUMBER_LITERAL,
                 N_VARIABLE_ASSIGNMENT, N_VARIABLE_REFERENCE, N_VARIABLE_REFERENCE, N_LESS_EQUAL_EXPRESSION,
                 N_VARIABLE_REFERENCE, N_VARIABLE_REFERENCE, N_ADD_EXPRESSION, N_VARIABLE_ASSIGNMENT,
                 N_VARIABLE_REFERENCE, N_NUMBER_LITERAL, N_ADD_EXPRESSION, N_VARIABLE_ASSIGNMENT, N_STATEMENT_BLOCK,
                 N_CONDITIONAL_STATEMENT_BLOCK, N_WHILE_STATEMENT, N_VARIABLE_REFERENCE, N_VARIABLE_REFERENCE,
                 N_ADD_EXPRESSION, N_RETURN_STATEMENT, N_STATEMENT_BLOCK, N_FUNCTION_DEFINITION, N_NUMBER_LITERAL,
                 N_NUMBER_LITERAL, N_FUNCTION_CALL, N_VARIABLE_REFERENCE, N_NUMBER_LITERAL, N_NUMBER_LITERAL,
                 N_FUNCTION_CALL, N_FUNCTION_CALL, N_VARIABLE_ASSIGNMENT, N_EXIT, N_STATEMENT_BLOCK,
                 N_CONDITIONAL_STATEMENT_BLOCK, N_IF_STATEMENT});
        CHECK(checkPreOrder(preOrder, expected));


    }

    TEST_CASE("return null statement") {
        auto ssParser = SsParser("return;");
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
        auto expected = std::vector<AstNodeType>({N_RETURN_STATEMENT});
        CHECK(checkPreOrder(preOrder, expected));
    }

    TEST_CASE("exit statement") {
        auto ssParser = SsParser("exit;");
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
        auto expected = std::vector<AstNodeType>({N_EXIT});
        CHECK(checkPreOrder(preOrder, expected));
    }

    TEST_CASE("continue statement") {
        auto ssParser = SsParser("continue;");
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
        auto expected = std::vector<AstNodeType>({N_CONTINUE});
        CHECK(checkPreOrder(preOrder, expected));
    }

    TEST_CASE("break statement") {
        auto ssParser = SsParser("break;");
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
        auto expected = std::vector<AstNodeType>({N_BREAK});
        auto invalid = std::vector<AstNodeType>({N_DELETION});
        CHECK(checkPreOrder(preOrder, expected));
        CHECK(!checkPreOrder(preOrder, invalid));
    }

    TEST_CASE("delete statement") {
        auto ssParser = SsParser("~someid;");
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
        auto expected = std::vector<AstNodeType>({N_DELETION});
        auto invalid = std::vector<AstNodeType>({N_IF_STATEMENT});
        CHECK(checkPreOrder(preOrder, expected));
        CHECK(!checkPreOrder(preOrder, invalid));
    }

    TEST_CASE("statement block") {
        auto ssParser = SsParser(
                "while (true) a = 10; b=fun(fun(fun(\"strin\"))); fun(20); continue; return 0; exit; end");
        auto preOrder = ssParser.getPreOrderParsedProgramStatement();
        auto expected = std::vector<AstNodeType>(
                {N_BOOLEAN_LITERAL, N_NUMBER_LITERAL, N_VARIABLE_ASSIGNMENT,
                 N_STRING_LITERAL, N_FUNCTION_CALL, N_FUNCTION_CALL,
                 N_FUNCTION_CALL, N_VARIABLE_ASSIGNMENT,
                 N_NUMBER_LITERAL, N_FUNCTION_CALL, N_CONTINUE,
                 N_NUMBER_LITERAL, N_RETURN_STATEMENT, N_EXIT,
                 N_STATEMENT_BLOCK, N_CONDITIONAL_STATEMENT_BLOCK, N_WHILE_STATEMENT}
        );
        CHECK(checkPreOrder(preOrder, expected));
    }

    TEST_CASE("bad statements") {
        auto checkArr = {
                "a = 10\nb=40 fun(20)return continue\nexit\n",
                " =var_3 (fun(-2))",
                "return a",
        };
        for (auto programToCheck: checkArr) {
            SUBCASE(programToCheck) {
                auto ssParser = SsParser(programToCheck);
                CHECK_THROWS_AS(ssParser.parseProgramStatement(), ParserException);
            }
        }
    }
}
