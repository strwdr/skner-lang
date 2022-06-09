#include "Evaluator.h"

#include <utility>

#include "../structures/ast/ast_nodes/NodesIncludes.h"
#include "../error_handler/exeptions/InterpreterExeption.h"
#include "Helpers.h"


ValueVariant Evaluator::evaluateExpression(IExpression *root) {
    initExpressionEvaluator();
    root->acceptExpressionVisitor(*this);
    if (topDataType == UNDEFINED) {
        throw InterpreterException("datatype of expression is undefined");
    }
    return topValue;
}

std::string Evaluator::evaluateExpressionToString(IExpression *root) {
    return helpers::valueVariantToString(evaluateExpression(root));
}

void Evaluator::updateExpressionTop(DataType newTopDataType) {
    topDataType = newTopDataType;
}

void Evaluator::updateExpressionTop(DataType newTopDataType, ValueVariant newValue) {
    updateExpressionTop(newTopDataType);
    topValue = std::move(newValue);
}

helpers::BinaryExpressionEvaluationOutput
Evaluator::getValuesFromBinaryExpression(IBinaryExpression *node,
                                         const std::vector<DataType> &expectedDataTypes,
                                         const std::string &exceptionMsg) {
    node->getRawLeftOperand()->acceptExpressionVisitor(*this);
    std::optional<DataType> firstDataType = {};
    for (auto expectedDataType: expectedDataTypes) {
        if (expectedDataType == topDataType) {
            firstDataType = expectedDataType;
            break;
        }
    }
    if (!firstDataType) {
        throw InterpreterException("invalid datatype in " + exceptionMsg + " (left)");
    }
    auto leftValue = topValue;
    node->getRawRightOperand()->acceptExpressionVisitor(*this);
    if (topDataType != firstDataType) {
        throw InterpreterException("datatypes in " + exceptionMsg + " does not match (right)");
    }
    auto rightValue = topValue;
    return helpers::BinaryExpressionEvaluationOutput{leftValue, rightValue, firstDataType.value()};
}

void Evaluator::visit(AddExpression *node) {
    //expected types - numbers, strings
    auto binValues = getValuesFromBinaryExpression(node, {NUMBER, STRING}, "add");
    ValueVariant newValue;
    if (binValues.dataType == NUMBER)
        newValue = std::get<double>(binValues.leftValue) + std::get<double>(binValues.rightValue);
    else
        newValue = std::get<std::string>(binValues.leftValue) + std::get<std::string>(binValues.rightValue);
    updateExpressionTop(binValues.dataType, newValue);
}

void Evaluator::visit(SubtractExpression *node) {
    //expected types -numbers
    auto binValues = getValuesFromBinaryExpression(node, {NUMBER}, "subtract");
    updateExpressionTop(NUMBER, std::get<double>(binValues.leftValue) - std::get<double>(binValues.rightValue));
}

void Evaluator::visit(AndExpression *node) {
    //expected types - booleans
    auto binValues = getValuesFromBinaryExpression(node, {BOOLEAN}, "and");
    updateExpressionTop(BOOLEAN, std::get<bool>(binValues.leftValue) && std::get<bool>(binValues.rightValue));
}

void Evaluator::visit(EqualExpression *node) {
    //expected types - all (same)
    auto binValues = getValuesFromBinaryExpression(node, {BOOLEAN, STRING, NUMBER}, "equal");
    updateExpressionTop(BOOLEAN, binValues.leftValue == binValues.rightValue);
}

void Evaluator::visit(GreaterEqualExpression *node) {
    //expected types - numbers
    auto binValues = getValuesFromBinaryExpression(node, {NUMBER}, "greater equal");
    updateExpressionTop(BOOLEAN, std::get<double>(binValues.leftValue) >= std::get<double>(binValues.rightValue));
}

void Evaluator::visit(GreaterExpression *node) {
    //expected types - numbers
    auto binValues = getValuesFromBinaryExpression(node, {NUMBER}, "greater");
    updateExpressionTop(BOOLEAN, std::get<double>(binValues.leftValue) > std::get<double>(binValues.rightValue));
}

void Evaluator::visit(LessEqualExpression *node) {
    //expected types - numbers
    auto binValues = getValuesFromBinaryExpression(node, {NUMBER}, "lesser equal");
    updateExpressionTop(BOOLEAN, std::get<double>(binValues.leftValue) <= std::get<double>(binValues.rightValue));
}

void Evaluator::visit(LessExpression *node) {
    //expected types - numbers
    auto binValues = getValuesFromBinaryExpression(node, {NUMBER}, "lesser");
    updateExpressionTop(BOOLEAN, std::get<double>(binValues.leftValue) < std::get<double>(binValues.rightValue));
}

void Evaluator::visit(NotEqualExpression *node) {
    //expected types - all (same)
    auto binValues = getValuesFromBinaryExpression(node, {BOOLEAN, STRING, NUMBER}, "not equal");
    updateExpressionTop(BOOLEAN, binValues.leftValue != binValues.rightValue);
}

void Evaluator::visit(OrExpression *node) {
    //expected types - booleans
    auto binValues = getValuesFromBinaryExpression(node, {BOOLEAN}, "or");
    updateExpressionTop(BOOLEAN, std::get<bool>(binValues.leftValue) || std::get<bool>(binValues.rightValue));
}

void Evaluator::visit(FunctionCallExpression *node) {
    handleBaseFunctionCall(node);
    // return datatype is already checked
    // handle return
    auto returnedDataType = returnToHandleValue.dataType;
    auto returnedValue = returnToHandleValue.returnValue;

    clearInterruptionToHandle();
    updateExpressionTop(returnedDataType, returnedValue);
}

void Evaluator::visit(DivideExpression *node) {
    //expected types - numbers
    auto binValues = getValuesFromBinaryExpression(node, {NUMBER}, "divide");
    auto rightVal = std::get<double>(binValues.rightValue);
    if (rightVal == 0) {
        throw InterpreterException("divide by 0");
    }
    updateExpressionTop(NUMBER, std::get<double>(binValues.leftValue) / rightVal);
}

void Evaluator::visit(ModuloExpression *node) {
    //expected types - numbers
    auto binValues = getValuesFromBinaryExpression(node, {NUMBER}, "modulo");
    auto leftVal = static_cast<int>(std::get<double>(binValues.leftValue));
    auto rightVal = static_cast<int>(std::get<double>(binValues.rightValue));
    if (rightVal == 0) {
        throw InterpreterException("divide by 0");
    }
    auto doubleMod = static_cast<double>(leftVal % rightVal);
    updateExpressionTop(NUMBER, doubleMod);
}

void Evaluator::visit(MultiplyExpression *node) {
    //expected types - numbers
    auto binValues = getValuesFromBinaryExpression(node, {NUMBER}, "multiply");
    updateExpressionTop(NUMBER, std::get<double>(binValues.leftValue) * std::get<double>(binValues.rightValue));
}

void Evaluator::visit(EvaluateExpression *node) {
    //expected types - any
    node->getRawOperand()->acceptExpressionVisitor(*this); // sets topDataType
    updateExpressionTop(topDataType); // pass
}

void Evaluator::visit(MinusExpression *node) {
    //expected types - numbers
    node->getRawOperand()->acceptExpressionVisitor(*this);
    if (topDataType != NUMBER) {
        throw InterpreterException("invalid datatype in minus expression (expected number)");
    }
    updateExpressionTop(NUMBER, -std::get<double>(topValue));
}

void Evaluator::visit(NegateExpression *node) {
    //expected types - boolean
    node->getRawOperand()->acceptExpressionVisitor(*this);
    if (topDataType != BOOLEAN) {
        throw InterpreterException("invalid datatype in negate expression (expected boolean)");
    }
    updateExpressionTop(BOOLEAN, !std::get<bool>(topValue));
}

void Evaluator::visit(VariableReference *node) {
    auto variableName = node->getVariableName();
//    std::cout<<"variablereference is calling"<<std::endl;
    auto foundVariable = findVariable(variableName);
    if (!foundVariable)
        throw InterpreterException("could not find variable named " + variableName);
    auto value = foundVariable.value().value;
    auto datatype = foundVariable.value().type;
    updateExpressionTop(datatype, value);
}

void Evaluator::visit(BooleanLiteral *node) {
    updateExpressionTop(BOOLEAN, node->getValue());
}

void Evaluator::visit(NumberLiteral *node) {
    updateExpressionTop(NUMBER, node->getValue());
}

void Evaluator::visit(StringLiteral *node) {
    updateExpressionTop(STRING, node->getValue());
}

void Evaluator::initExpressionEvaluator() {
    topDataType = UNDEFINED;
}