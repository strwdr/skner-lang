#include "Evaluator.h"
#include "../structures/ast/ast_nodes/NodesIncludes.h"
#include "../error_handler/exeptions/InterpreterExeption.h"


bool Evaluator::handlePrintFunctions(BaseFunctionCall *node) {
    auto functionName = node->getFunctionName();
    if (functionName == "println" or functionName == "print") {
        auto arguments = node->getRawArguments();
        if (arguments.empty()) {
            outputStream<<std::endl;
            return true;
        }
        bool first = true;
        for (auto arg: arguments) {
            if (!first)
                outputStream << " ";
            first = false;
            auto expressionToPrint = evaluateExpressionToString(arg);
            outputStream << expressionToPrint;
        }
        if (functionName == "println")
            outputStream << std::endl;
        return true;
    }
    return false;
}

bool Evaluator::handleReadFunction(BaseFunctionCall *node) {
    auto functionName = node->getFunctionName();
    if (functionName == "read") {
        auto arguments = node->getRawArguments();
        if (!arguments.empty()) {
            throw InterpreterException("read function has no arguments");
        }
        std::string strFromStream;
        inputStream >> strFromStream;
        updateExpressionTop(STRING, strFromStream);

        returnToHandleValue = helpers::ReturnToHandleValue{STRING, strFromStream};
        interruptionToHandle = RETURN;
        return true;
    }
    return false;
}

bool Evaluator::handleCastFunctions(BaseFunctionCall *node) {
    auto functionName = node->getFunctionName();
    if (functionName == "to_number" or functionName == "to_string" or functionName == "to_boolean") {
        auto arguments = node->getRawArguments();
        if (arguments.empty())
            throw InterpreterException("to_number function has no arguments");
        if (arguments.size() != 1)
            throw InterpreterException("to_number function has invalid number of arguments");

        evaluateExpression(arguments[0]);
        interruptionToHandle = RETURN;

        if(functionName == "to_boolean") {
            auto castedBool = helpers::valueVariantToBoolean(topValue);
            returnToHandleValue = {BOOLEAN, castedBool};
        }
        else if(functionName == "to_number") {
            auto castedNumber = helpers::valueVariantToNumber(topValue);
            returnToHandleValue = {NUMBER, castedNumber};
        }
        else {
            auto castedString = helpers::valueVariantToString(topValue);
            returnToHandleValue = {STRING, castedString};
        }

        return true;
    }
    return false;
}