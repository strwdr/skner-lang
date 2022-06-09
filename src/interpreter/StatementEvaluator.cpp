#include "Evaluator.h"

#include <utility>

#include "../structures/ast/ast_nodes/NodesIncludes.h"
#include "../error_handler/exeptions/InterpreterExeption.h"


std::optional<DataTypeVal> Evaluator::findVariableOnBack(const std::string &variableName) {
    auto &variablesMap = globalVariablesContexts.back();
    if(!funCallsVariablesContextsStack.empty()){
        if(funCallsVariablesContextsStack.top().empty()){
            throw InterpreterException("top2 is empty");
        }
        variablesMap = funCallsVariablesContextsStack.top().back();
    }
    auto foundValue = variablesMap.find(variableName);
    if (foundValue != variablesMap.end()) {
        return DataTypeVal(foundValue->second);
    }
    return {};
}

std::optional<DataTypeVal> Evaluator::findVariable(const std::string &variableName) {
    if(!funCallsVariablesContextsStack.empty()){
        auto &variablesMap = funCallsVariablesContextsStack.top().back();
        auto foundValue = variablesMap.find(variableName);
        if (foundValue != variablesMap.end()) {
            return DataTypeVal(foundValue->second);
        }
    }


    for (int i = int(globalVariablesContexts.size()) - 1; i >= 0; i--) {
        auto &variablesMap = globalVariablesContexts[i];
        auto foundValue = variablesMap.find(variableName);
        if (foundValue != variablesMap.end()) {
            return DataTypeVal(foundValue->second);
        }
    }

    return {};
}

FunctionDefinition *Evaluator::findFunction(const std::string &functionName) {
    auto foundValue = functions.find(functionName);
    if (foundValue != functions.end()) {
        return foundValue->second.get();
    }
    return nullptr;
}

bool Evaluator::identifierAlreadyExists(const std::string &id) {
    if (stdLibReservedFunctions.contains(id) or findFunction(id) or findVariable(id))
        return true;
    return false;
}


bool Evaluator::hasInterruptionToHandle() {
    return isInterruption(interruptionToHandle);
}

void Evaluator::initStatementEvaluator() {
    globalVariablesContexts.clear();
    globalVariablesContexts.emplace_back(); // initialize global scope
    interruptionToHandle = NONE;
    argumentsToAppend.clear();
}

bool Evaluator::executeProgramStatement(IStatement *root) {
    root->acceptStatementVisitor(*this);
    if (hasInterruptionToHandle()) {
        if (interruptionToHandle != EXIT) {
            throw InterpreterException(
                    "invalid use of " + interruptionToString(interruptionToHandle) + " interruption");
        } else {
            clearInterruptionToHandle();
            return false;
        }
    }
    return true;
}

void Evaluator::visit(Break *node) {
    interruptionToHandle = BREAK;
}

void Evaluator::visit(ConditionalStatementBlock *node) {
    // no need to implemment that (handled in if and while visit methods)
}

void Evaluator::visit(Continue *node) {
    interruptionToHandle = CONTINUE;
}

void Evaluator::visit(DeleteStatement *node) {
    // delete variable or function from lookup map
    auto identifier = node->getIdentifier();
    auto functionIt = functions.find(identifier);
    if (functionIt != functions.end()) {
        functions.erase(functionIt);
        return;
    }
    auto & variableContexts = globalVariablesContexts;
    if(notInGlobalScope()){
        variableContexts = funCallsVariablesContextsStack.top();
    }
    for (int i = int(variableContexts.size()) - 1; i >= 0; i--) {
        auto &variablesMap = variableContexts[i];
        auto variableIt = variablesMap.find(identifier);
        if (variableIt != variablesMap.end()) {
            variablesMap.erase(variableIt);
            return;
        }
    }
    throw InterpreterException("there is no function or variable named " + identifier);
}

void Evaluator::visit(Exit *node) {
    interruptionToHandle = EXIT;
}

void Evaluator::visit(FunctionCallStatement *node) {
    handleBaseFunctionCall(node); // execute statement
    if (hasInterruptionToHandle() and interruptionToHandle == RETURN) // handle return (ignore)
        clearInterruptionToHandle();
}

void Evaluator::visit(FunctionDefinition *node) {
    // put function definition on function lookup map
    auto functionName = node->getFunctionName();
    if(globalVariablesContexts.size() != 1 or notInGlobalScope()) // function definition must be on level 1 of global scope
        throw InterpreterException("function " + functionName + " must be declared in global scope");

    if (identifierAlreadyExists(functionName))
        throw InterpreterException(
                "cannot declare function " + functionName + " because this identifier is already used");
    functions[functionName] =
            std::make_unique<FunctionDefinition>(node->getFunctionName(),
                                                 node->getReturnType(),
                                                 node->getParameterDefinitions(),
                                                 std::move(node->getUniFunctionBody()));
}

void Evaluator::visit(IfStatement *node) {
    // go through all if statements and execute blocks
    auto rawIfStatements = node->getRawIfStatements();
    for (auto ifStatement: rawIfStatements) {
        auto conditionExpression = ifStatement->getRawCondition();
        auto statementBlock = ifStatement->getRawStatementBlock();
        auto conditionValue = evaluateExpression(conditionExpression);
        if (topDataType != BOOLEAN) {
            throw InterpreterException("invalid if condition expression (expected boolean datatype on top)");
        }
        if (std::get<bool>(conditionValue)) {
            // execute statement block
            statementBlock->acceptStatementVisitor(*this);
            return;
        }
        conditionValue = evaluateExpression(conditionExpression);
    }
    if(node->hasElse()){
        auto statementBlock = node->getRawElseStatement();
        statementBlock->acceptStatementVisitor(*this);
    }
}

void Evaluator::visit(ReturnStatement *node) {
    if (hasInterruptionToHandle())
        throw InterpreterException("there is interruption pending above return statement");
    if (!node->isNullReturn()) {
        auto evaluatedValue = evaluateExpression(node->getRawReturnExpression());
        returnToHandleValue = helpers::ReturnToHandleValue{topDataType, evaluatedValue};
    } else {
        returnToHandleValue = helpers::ReturnToHandleValue{UNDEFINED};
    }
    interruptionToHandle = RETURN;
}

void Evaluator::addVariableToStackBack(const std::string &variableName, const DataTypeVal &dataTypeVal) {
    // check if name is not used by function (variables can be overloaded)
    if (findVariableOnBack(variableName))
        throw InterpreterException("a variable named " + variableName + " already exists in the current scope");
    if (findFunction(variableName) or stdLibReservedFunctions.contains(variableName))
        throw InterpreterException("a function named " + variableName + " already exists");
    if(notInGlobalScope()){
//        std::cout<<"putting " <<variableName << helpers::valueVariantToString(dataTypeVal.value)<<std::endl;
        funCallsVariablesContextsStack.top().back()[variableName] = dataTypeVal;
        return;
    }
    globalVariablesContexts.back()[variableName] = dataTypeVal;
}

void Evaluator::visit(StatementBlock *node) {
    if(notInGlobalScope()){
//        std::cout<<"not in global scope "<< std::endl;
        funCallsVariablesContextsStack.top().emplace_back();
        for (const auto &argToAppend: argumentsToAppend)
            addVariableToStackBack(argToAppend.first, argToAppend.second);
        argumentsToAppend.clear();
    }
    else{
        globalVariablesContexts.emplace_back();
    }

    for (auto statement: node->getRawStatements()) {
        statement->acceptStatementVisitor(*this);
        if (hasInterruptionToHandle())
            break;
    }
    if(notInGlobalScope()){
        funCallsVariablesContextsStack.top().pop_back();
    }
    else{
        globalVariablesContexts.pop_back();
    }
}

void Evaluator::visit(VariableAssignment *node) {
    evaluateExpression(node->getRawValueExpression());
    auto variableName = node->getVariableName();
    auto & variableContexts = globalVariablesContexts;
    if(notInGlobalScope()){
        variableContexts = funCallsVariablesContextsStack.top();
    }
    for (int i = int(variableContexts.size()) - 1; i >= 0; i--) {
        auto &variablesMap = variableContexts[i];
        auto it = variablesMap.find(variableName);
        if (it != variablesMap.end()) {
            if(it->second.type != topDataType)
                throw InterpreterException("invalid datatype in variable definition");
            variablesMap[node->getVariableName()] = DataTypeVal{topDataType, topValue};
            return;
        }
    }
    throw InterpreterException("could not find variable of name " + variableName);
}

void Evaluator::visit(VariableDefinition *node) {
    evaluateExpression(node->getRawValueExpression());
    if(node->getDataType() != topDataType)
        throw InterpreterException("invalid datatype in variable definition");
    addVariableToStackBack(node->getVariableName(), DataTypeVal{topDataType, topValue});
}

void Evaluator::visit(WhileStatement *node) {
    auto conditionExpression = node->getRawWhileStatement()->getRawCondition();
    auto statementBlock = node->getRawWhileStatement()->getRawStatementBlock();
    auto conditionValue = evaluateExpression(conditionExpression);
    if (topDataType != BOOLEAN)
        throw InterpreterException("while condition does not return boolean");
    while (std::get<bool>(conditionValue)) {
        // execute statement block
        statementBlock->acceptStatementVisitor(*this);
        if (hasInterruptionToHandle()) {
            if (interruptionToHandle == BREAK) {
                clearInterruptionToHandle();
                break;
            } else if (interruptionToHandle == CONTINUE) {
                clearInterruptionToHandle();
                continue;
            } else {
                break; // handle interruption above
            }
        }
        // update condition value
        conditionValue = evaluateExpression(conditionExpression);
    }
}

void Evaluator::clearInterruptionToHandle() {
    interruptionToHandle = NONE;
}