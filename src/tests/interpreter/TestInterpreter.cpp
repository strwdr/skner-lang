#include "../doctest.h"
#include "../helpers/Helpers.h"
#include "../../error_handler/exeptions/InterpreterExeption.h"

TEST_SUITE("interpreter") {
    TEST_CASE("simple program") {
        auto evaluator = SsEvaluator("number a = 10.1;"
                                     "number b = a + 10;"
                                     "print(b, a);");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "20.1");
        CHECK(evaluator.readStrFromOstream() == "10.1");
    }

    TEST_CASE("simple read/write program") {
        auto evaluator = SsEvaluator("string a = read();"
                                     "string b = \"test\";"
                                     "b = read();"
                                     "print(a, b);");

        evaluator.writeStrToIstream("somestring string2");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "somestring");
        CHECK(evaluator.readStrFromOstream() == "string2");
    }

    TEST_CASE("fibbonaci sequence program") {
        auto evaluator = SsEvaluator("number function fib(number a)"
                                     "   if(a < 2) "
                                     "       return 1;"
                                     "   else "
                                     "       return fib(a-1) + fib(a-2);"
                                     "   end "
                                     "end "
                                     "println(fib(10)); "
                                     "println(fib(11)); "
                                     "println(fib(12)); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "89");
        CHECK(evaluator.readStrFromOstream() == "144");
        CHECK(evaluator.readStrFromOstream() == "233");
    }

    TEST_CASE("while return test program") {
        auto evaluator = SsEvaluator("number a = 10; "
                                     "while(true) "
                                     "  if(a == 5) "
                                     "     break; "
                                     "  end "
                                     "  a = a - 1;"
                                     "end "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "5");
    }

    TEST_CASE("while continue test program") {
        auto evaluator = SsEvaluator("number a = 10; "
                                     "while(a != -49) "
                                     "  if(a == 20) "
                                     "     a = -50; "
                                     "     continue; "
                                     "  end "
                                     "  a = a + 1; "
                                     "end "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "-49");
    }

    TEST_CASE("test exit") {
        auto evaluator = SsEvaluator("number a = 10; "
                                     "while(true) "
                                     "  if(a == 20) "
                                     "     exit; "
                                     "  end "
                                     "  a = a + 1; "
                                     "end "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "20");
    }

    TEST_CASE("number to string") {
        auto evaluator = SsEvaluator("string a = to_string(10) + \"test\"; "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "10test");
    }

    TEST_CASE("boolean to string") {
        auto evaluator = SsEvaluator("string a = to_string(true) + \"test\"; "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "truetest");
    }

    TEST_CASE("string to string") {
        auto evaluator = SsEvaluator("string a = to_string(\"test\") + \"test\"; "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "testtest");
    }

    TEST_CASE("string to number") {
        auto evaluator = SsEvaluator("number a = to_number(\"10\") + 100; "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "110");
    }

    TEST_CASE("boolean to number") {
        auto evaluator = SsEvaluator("number a = to_number(true) + 100; "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "101");
    }

    TEST_CASE("number to number") {
        auto evaluator = SsEvaluator("number a = to_number(4) + 100; "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "104");
    }

    TEST_CASE("number to true boolean") {
        auto evaluator = SsEvaluator("boolean a = to_boolean(4); "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "true");
    }

    TEST_CASE("number to false boolean") {
        auto evaluator = SsEvaluator("boolean a = to_boolean(-4); "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "false");
    }

    TEST_CASE("string to false boolean") {
        auto evaluator = SsEvaluator("boolean a = to_boolean(\"asdfas\"); "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "false");
    }
    TEST_CASE("string to false boolean 2") {
        auto evaluator = SsEvaluator("boolean a = to_boolean(\"false\"); "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "false");
    }

    TEST_CASE("string to true boolean ") {
        auto evaluator = SsEvaluator("boolean a = to_boolean(\"true\"); "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "true");
    }

    TEST_CASE("boolean to boolean ") {
        auto evaluator = SsEvaluator("boolean a = to_boolean(true); "
                                     "print(a); ");
        evaluator.executeProgram();
        CHECK(evaluator.readStrFromOstream() == "true");
    }

    TEST_CASE("number expression 1") {
        auto evaluator = SsEvaluator("5 * 5/(5%3)/5/5*5 + 5");
        auto value = evaluator.parseAndGetExpressionValue();
//        std::cout<<std::get<double>(value);
//        std::cout<<evaluator.getStringTree();
        CHECK(std::get<double>(value) == 7.5);
    }

    TEST_CASE("number expression 2") {
        auto evaluator = SsEvaluator("1+2+3*4*5+6-3*6+25+2*7/2/3*6");
        auto value = evaluator.parseAndGetExpressionValue();
//        std::cout<<std::get<double>(value);
//        std::cout<<evaluator.getStringTree();
        CHECK(std::get<double>(value) == 90);
    }

    TEST_CASE("equal expression") {
        auto evaluator = SsEvaluator("(5*5) == 25");
        auto value = evaluator.parseAndGetExpressionValue();
        CHECK(std::get<bool>(value) == true);
    }

    TEST_CASE("equal expression") {
        auto evaluator = SsEvaluator("2 > 1");
        auto value = evaluator.parseAndGetExpressionValue();
        CHECK(std::get<bool>(value) == true);
    }

    TEST_CASE("negate expression") {
        auto evaluator = SsEvaluator("!(!(!true))");
        auto value = evaluator.parseAndGetExpressionValue();
        CHECK(std::get<bool>(value) == false);
    }

    TEST_CASE("minus expression") {
        auto evaluator = SsEvaluator("10 - - 1");
        auto value = evaluator.parseAndGetExpressionValue();
        CHECK(std::get<double>(value) == 11);
    }

    TEST_CASE("string add expression") {
        auto evaluator = SsEvaluator(R"("test1" + "test2")");
        auto value = evaluator.parseAndGetExpressionValue();
        CHECK(std::get<std::string>(value) == "test1test2");
    }

    TEST_CASE("double divide expression") {
        auto evaluator = SsEvaluator("25/5/5");
        auto value = evaluator.parseAndGetExpressionValue();
        CHECK(std::get<double>(value) == 1);
    }
}
