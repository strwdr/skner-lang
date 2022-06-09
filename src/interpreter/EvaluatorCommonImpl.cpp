#include "Evaluator.h"

#include "../structures/ast/ast_nodes/NodesIncludes.h"
#include "../error_handler/exeptions/InterpreterExeption.h"


Evaluator::Evaluator(std::istream &_inputStream, std::ostream &_outputStream) :
        topDataType(UNDEFINED),
        interruptionToHandle(NONE),
        inputStream(_inputStream),
        outputStream(_outputStream) {
    initExpressionEvaluator();
    while(!funCallsVariablesContextsStack.empty()){
        funCallsVariablesContextsStack.pop();
    }
    initStatementEvaluator();
}

void Evaluator::handleBaseFunctionCall(BaseFunctionCall *node) {
    auto functionName = node->getFunctionName();

    if (handlePrintFunctions(node))
        return;
    if (handleReadFunction(node))
        return;
    if (handleCastFunctions(node))
        return;



    FunctionDefinition *foundFunctionDefinition = findFunction(functionName);
    if (!foundFunctionDefinition)
        throw InterpreterException("could not find function " + functionName);
    if (foundFunctionDefinition->getParameterDefinitions().size() != node->getRawArguments().size())
        throw InterpreterException("invalid argument count in function " + functionName);
    auto nodeArguments = node->getRawArguments();
    auto parameters = foundFunctionDefinition->getParameterDefinitions();
    argumentsToAppend.clear();
    for (int argId = 0; argId < nodeArguments.size(); argId++) {
        auto argExpression = nodeArguments[argId];
        auto expectedDataType = parameters[argId].first;
        evaluateExpression(argExpression);
        if (topDataType != expectedDataType) {
            throw InterpreterException("invalid datatype in function call argument");
        }
        auto argName = parameters[argId].second;
        argumentsToAppend.emplace_back(argName, DataTypeVal{topDataType, topValue});
    }
    funCallsVariablesContextsStack.emplace(); // add function call context
    foundFunctionDefinition->getRawFunctionBody()->acceptStatementVisitor(*this);
    if (hasInterruptionToHandle() and interruptionToHandle == RETURN) {
        // handle return
        auto returnedDataType = returnToHandleValue.dataType;
        auto returnedValue = returnToHandleValue.returnValue;
        if (returnedDataType != foundFunctionDefinition->getReturnType()) {
            throw InterpreterException("function " + node->getFunctionName() + " returns invalid datatype");
        }
    } else if (foundFunctionDefinition->getReturnType() != UNDEFINED) {
        throw InterpreterException("function " + node->getFunctionName() + " does not return anything");
    }
    funCallsVariablesContextsStack.pop(); // delete function call context
}