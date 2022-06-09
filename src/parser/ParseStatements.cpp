#include <memory>
#include "Parser.h"
#include "Helpers.h"
#include "../error_handler/exeptions/ParserException.h"


UniStatementPtr Parser::parseFunctionCallOrVariableAssignment() {
    if (!acceptNext({T_IDENTIFIER}))
        return nullptr;

    auto identifier = helpers::stringValueFromToken(token);

    if (auto funCallPtr = parseFunctionCall(identifier)) {
        auto funCallStatementPtr = std::make_unique<FunctionCallStatement>(std::move(funCallPtr.value()));
        return funCallStatementPtr;
    }

    if (auto varAssignmentPtr = parseVariableAssignment(identifier))
        return std::move(varAssignmentPtr);

    throwNext("couldn't parse function call or variable assignment");
    return nullptr;
}


// statements


UniStatementPtr Parser::parseIfStatement() {
    if (!acceptNext({T_IF}))
        return nullptr;
    std::vector<std::unique_ptr<ConditionalStatementBlock>> ifCondStatementBlocksPtrs;

    if (auto ifCondStatementBlockPtr = parseConditionalStatementBlock())
        ifCondStatementBlocksPtrs.push_back(std::move(ifCondStatementBlockPtr));
    else
        throwNext("couldn't parse conditional statement block in if statement (if)");

    std::unique_ptr<StatementBlock> elseStatementBlock = nullptr;

    while (!acceptNext({T_END})) {
        acceptNextOrThrow({T_ELIF, T_ELSE}, "invalid token ending if statement (expected if/end/else)");
        if (token.type == T_ELIF) {
            if (auto elifCondStatementBlockPtr = parseConditionalStatementBlock())
                ifCondStatementBlocksPtrs.push_back(std::move(elifCondStatementBlockPtr));
            else
                throw ParserException("couldn't parse conditional statement block in if statement (elif)",
                                      getNextToken());
        } else if (!(elseStatementBlock = parseStatementBlock()))
            throwNext("couldn't parse statement block in if statement (else)");
    }

    return std::make_unique<IfStatement>(ifCondStatementBlocksPtrs, std::move(elseStatementBlock));
}

UniStatementPtr Parser::parseWhileStatement() {
    if (!acceptNext({T_WHILE}))
        return nullptr;
    auto conditionalStatementBlockPtr = parseConditionalStatementBlock();
    if (!conditionalStatementBlockPtr)
        throwNext("couldn't parse conditional statement block in while statement");
    acceptNextOrThrow({T_END}, "no end keyword at the end of while statement");
    return std::make_unique<WhileStatement>(std::move(conditionalStatementBlockPtr));
}

UniStatementPtr Parser::parseVariableDefinition(DataType dataType) {
    if (!acceptNext({T_IDENTIFIER}))
        return nullptr;

    auto identifier = helpers::stringValueFromToken(token);

    if (!acceptNext({T_ASSIGNMENT}))
        throwNext("no assignment operator in variable definition");

    if (auto valueExpression = parseExpression())
        return std::make_unique<VariableDefinition>(dataType, identifier, std::move(valueExpression));

    throwNext("no expression after assignment operator");
    return nullptr;
}


UniStatementPtr Parser::parseFunctionDefinitionOrVariableDefinition() {
    DataType dataType = UNDEFINED;
    if (acceptNext({T_BOOLEAN, T_NUMBER, T_STRING}))
        dataType = remapTokenTypeToDatatype(token.type);

    if (auto funDefPtr = parseFunctionDefinition(dataType))
        return std::move(funDefPtr);

    if (dataType == UNDEFINED)
        return nullptr;
    if (auto varDefinitionPtr = parseVariableDefinition(dataType))
        return std::move(varDefinitionPtr);

    throwNext("couldn't parse function definition or variable definition");
    return nullptr;
}

UniStatementPtr Parser::parseFunctionDefinition(DataType dataType) {
    if (!acceptNext({T_FUNCTION}))
        return nullptr;
    acceptNextOrThrow({T_IDENTIFIER}, "no identifier in function definition");
    auto identifier = helpers::stringValueFromToken(token);
    acceptNextOrThrow({T_OPEN_BRACKET}, "no bracket in function definition");
    std::vector<std::pair<DataType, std::string>> parameters;

    while (getNextToken().type != T_CLOSE_BRACKET) {
        acceptNextOrThrow({T_BOOLEAN, T_STRING, T_NUMBER}, "no type specifier in function argument definition");
        auto argDataType = remapTokenTypeToDatatype(token.type);
        acceptNextOrThrow({T_IDENTIFIER}, "no identifier in function argument definition");
        parameters.emplace_back(argDataType, helpers::stringValueFromToken(token));
        if (!acceptNext({T_COMMA}))
            break;
    }
    acceptNextOrThrow({T_CLOSE_BRACKET}, "no close bracket in function definition");
    // parse function body
    auto funBodyPtr = parseStatementBlock();
    if (!funBodyPtr)
        throwNext("couldn't parse statement block in function definition body");
    acceptNextOrThrow({T_END}, "no end keyword in function definition");
    return std::make_unique<FunctionDefinition>(identifier, dataType, parameters, std::move(funBodyPtr));

}

UniStatementPtr Parser::parseExit() {
    if (!acceptNext({T_EXIT}))
        return nullptr;
    return std::make_unique<Exit>();
}

UniStatementPtr Parser::parseReturnStatement() {
    if (!acceptNext({T_RETURN}))
        return nullptr;
    if (auto exPtr = parseExpression())
        return std::make_unique<ReturnStatement>(std::move(exPtr));
    return std::make_unique<ReturnStatement>();
}

UniStatementPtr Parser::parseBreak() {
    if (!acceptNext({T_BREAK}))
        return nullptr;
    return std::make_unique<Break>();
}

UniStatementPtr Parser::parseContinue() {
    if (!acceptNext({T_CONTINUE}))
        return nullptr;
    return std::make_unique<Continue>();
}

UniStatementPtr Parser::parseDeleteStatement() {
    if (!acceptNext({T_DELETE}))
        return nullptr;
    acceptNextOrThrow({T_IDENTIFIER}, "no identifier in delete statement");
    return std::make_unique<DeleteStatement>(helpers::stringValueFromToken(token));
}

UniStatementPtr Parser::parseVariableAssignment(const std::string &identifier) {
    if (!acceptNext({T_ASSIGNMENT}))
        return nullptr;
    if (auto valueExpression = parseExpression())
        return std::make_unique<VariableAssignment>(identifier, std::move(valueExpression));
    throwNext("no expression after assignment operator");
    return nullptr;
}

std::unique_ptr<ConditionalStatementBlock> Parser::parseConditionalStatementBlock() {
    acceptNextOrThrow({T_OPEN_BRACKET}, "no open bracket in conditional statement block condition");
    auto condition = parseExpression();
    if (!condition)
        throwNext("couldn't parse condition in conditional statement block");

    acceptNextOrThrow({T_CLOSE_BRACKET}, "no close bracket in conditional statement block condition");
    auto statementBlock = parseStatementBlock();
    if (!statementBlock)
        throwNext("couldn't parse statement block in conditional statement block");
    return std::make_unique<ConditionalStatementBlock>(std::move(condition), std::move(statementBlock));
}

std::unique_ptr<StatementBlock> Parser::parseStatementBlock() {
    std::vector<UniStatementPtr> statementPtrs;
    while (auto statementPtr = parseStatement())
        statementPtrs.push_back(std::move(statementPtr));
    return std::make_unique<StatementBlock>(statementPtrs);
}

UniStatementPtr Parser::parseProgramStatement() {
    if (auto statementPtr = parseStatement())
        return std::move(statementPtr);
    if (acceptNext({T_ETX}))
        return nullptr;
    throwNext("couldn't parse program statement - no etx or statement");
    return nullptr; // warning workaround
}

UniStatementPtr Parser::parseStatementSemicolonOrThrow(UniStatementPtr statementNode) {
    if (acceptNext({T_SEMICOLON}))
        return statementNode;
    throwNext("no semicolon after statement");
    return nullptr;
}

UniStatementPtr Parser::parseStatement() {
    if (auto s = parseFunctionDefinitionOrVariableDefinition()) { // function definition can be put only at the top level
        if (s->getNodeType() == N_FUNCTION_DEFINITION)
            return s; // dont parse semicolon
        return parseStatementSemicolonOrThrow(std::move(s)); // variable definition - parse semicolon
    }
    if (auto s = parseFunctionCallOrVariableAssignment()) return parseStatementSemicolonOrThrow(std::move(s));
    if (auto s = parseContinue()) return parseStatementSemicolonOrThrow(std::move(s)); // only while
    if (auto s = parseDeleteStatement()) return parseStatementSemicolonOrThrow(std::move(s));
    if (auto s = parseBreak()) return parseStatementSemicolonOrThrow(std::move(s)); // only while
    if (auto s = parseReturnStatement()) return parseStatementSemicolonOrThrow(std::move(s)); // only function
    if (auto s = parseExit()) return parseStatementSemicolonOrThrow(std::move(s));
    if (auto s = parseWhileStatement()) return s;
    if (auto s = parseIfStatement()) return s;
    return nullptr;
}
