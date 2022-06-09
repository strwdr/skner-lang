#ifndef SKNER_SSEVALUATOR_H
#define SKNER_SSEVALUATOR_H

#include <sstream>
#include "../../parser/Parser.h"
#include "../../interpreter/Evaluator.h"

class SsEvaluator : public Parser {
private:
    std::stringstream inputProgramStream;
    std::stringstream outputStream;
    std::stringstream inputStream;
    std::unique_ptr<HelperTraverser> traverser;
    Evaluator evaluator;
public:
    explicit SsEvaluator(const std::string &testText = "") : Parser(inputProgramStream),
                                                             evaluator(inputStream, outputStream) {
        inputProgramStream << testText;
        traverser = std::make_unique<HelperTraverser>(true);
    }

    std::string getStringTree() {
        return traverser->traverseTreeString(parseExpression().get());
    }

    ValueVariant parseAndGetExpressionValue() {
        return evaluator.evaluateExpression(parseExpression().get());
    }

    void executeProgram() {
        while(auto stmt = parseProgramStatement())
            evaluator.executeProgramStatement(stmt.get());
    }

    void writeStrToIstream(const std::string &a) {
        inputStream << a;
    }

    std::string readStrFromOstream() {
        std::string outVal;
        outputStream >> outVal;
        return outVal;
    }

};

#endif //SKNER_SSEVALUATOR_H
