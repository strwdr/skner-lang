#include <memory>
#include "Parser.h"

#include "../structures/ast/ast_nodes/expressions/BooleanLiteral.h"
#include "../error_handler/exeptions/ParserException.h"
#include "Helpers.h"

template<class T>
UniExpressionPtr
Parser::parseBinaryExpressionTemplate(const std::function<UniExpressionPtr(void)> &thisParseExpression,
                                      const std::function<UniExpressionPtr(void)> &nextParseExpression,
                                      const std::string &name,
                                      const TokenType &acceptableOperatorToken) {

    auto leftOperand = nextParseExpression();
    if (!leftOperand)
        return nullptr;
    if (!acceptNext({acceptableOperatorToken}))
        return leftOperand;
    auto tmpOperand = nextParseExpression();
    if (!tmpOperand)
        throw ParserException("couldn't parse binary expression (" + name + " expression)", getNextToken(),
                              {acceptableOperatorToken});
    tmpOperand = std::make_unique<T>(std::move(leftOperand), std::move(tmpOperand));


    while (acceptNext({acceptableOperatorToken})) {
        if (auto nextThisOperand = nextParseExpression())
            tmpOperand = std::make_unique<T>(std::move(tmpOperand), std::move(nextThisOperand));
        else
            throw ParserException("couldn't parse binary expression (" + name + " expression)", getNextToken(),
                                  {acceptableOperatorToken});
    }
    return tmpOperand;
}

template<class T>
UniExpressionPtr
Parser::parseUnaryExpressionTemplate(const std::function<UniExpressionPtr(void)> &thisParseExpression,
                                     const std::function<UniExpressionPtr(void)> &nextParseExpression,
                                     const std::string &name,
                                     const TokenType &acceptableOperatorToken) {
    auto operand = nextParseExpression(); // try parse normal expression
    if (operand)
        return operand;
    if (!acceptNext({acceptableOperatorToken}))
        return nullptr;
    auto thisUnaryOperand = nextParseExpression();
    if (!thisUnaryOperand)
        throw ParserException("couldn't parse n-th expression in " + name + " expression", getNextToken(),
                              {acceptableOperatorToken});
    return std::make_unique<T>(std::move(thisUnaryOperand));
}
UniExpressionPtr Parser::parseExpression() {
    return parseOrExpression();
}

UniExpressionPtr Parser::parseOrExpression() {
    return parseBinaryExpressionTemplate<OrExpression>(std::bind(&Parser::parseOrExpression, this),
                                                       std::bind(&Parser::parseAndExpression, this),
                                                       "or",
                                                       {T_OR});
}

UniExpressionPtr Parser::parseAndExpression() {
    return parseBinaryExpressionTemplate<AndExpression>(std::bind(&Parser::parseAndExpression, this),
                                                        std::bind(&Parser::parseEqualExpression, this),
                                                        "and",
                                                        {T_AND});
}

UniExpressionPtr Parser::parseEqualExpression() {
    return parseBinaryExpressionTemplate<EqualExpression>(std::bind(&Parser::parseEqualExpression, this),
                                                          std::bind(&Parser::parseNotEqualExpression, this),
                                                          "equal",
                                                          {T_EQUAL});
}

UniExpressionPtr Parser::parseNotEqualExpression() {
    return parseBinaryExpressionTemplate<NotEqualExpression>(std::bind(&Parser::parseNotEqualExpression, this),
                                                             std::bind(&Parser::parseGreaterEqualExpression, this),
                                                             "not equal",
                                                             {T_NOT_EQUAL});
}


UniExpressionPtr Parser::parseGreaterEqualExpression() {
    return parseBinaryExpressionTemplate<GreaterEqualExpression>(std::bind(&Parser::parseGreaterEqualExpression, this),
                                                                 std::bind(&Parser::parseGreaterExpression, this),
                                                                 "greater equal",
                                                                 {T_GREATER_EQUAL});
}


UniExpressionPtr Parser::parseGreaterExpression() {
    return parseBinaryExpressionTemplate<GreaterExpression>(std::bind(&Parser::parseGreaterExpression, this),
                                                            std::bind(&Parser::parseLessEqualExpression, this),
                                                            "greater",
                                                            {T_GREATER});
}


UniExpressionPtr Parser::parseLessEqualExpression() {
    return parseBinaryExpressionTemplate<LessEqualExpression>(std::bind(&Parser::parseLessEqualExpression, this),
                                                              std::bind(&Parser::parseLessExpression, this),
                                                              "lesser equal",
                                                              {T_LESSER_EQUAL});
}


UniExpressionPtr Parser::parseLessExpression() {
    return parseBinaryExpressionTemplate<LessExpression>(std::bind(&Parser::parseLessExpression, this),
                                                         std::bind(&Parser::parseAddExpression, this),
                                                         "lesser",
                                                         {T_LESSER});
}


UniExpressionPtr Parser::parseAddExpression() {
    return parseBinaryExpressionTemplate<AddExpression>(std::bind(&Parser::parseAddExpression, this),
                                                        std::bind(&Parser::parseSubtractExpression, this),
                                                        "add",
                                                        {T_PLUS});
}

UniExpressionPtr Parser::parseSubtractExpression() {
    return parseBinaryExpressionTemplate<SubtractExpression>(std::bind(&Parser::parseSubtractExpression, this),
                                                             std::bind(&Parser::parseMultiplyExpression, this),
                                                             "subtract",
                                                             {T_MINUS});
}

UniExpressionPtr Parser::parseMultiplyExpression() {
    return parseBinaryExpressionTemplate<MultiplyExpression>(std::bind(&Parser::parseMultiplyExpression, this),
                                                             std::bind(&Parser::parseDivideExpression, this),
                                                             "multiply",
                                                             {T_MULTIPLY});
}

UniExpressionPtr Parser::parseDivideExpression() {
    return parseBinaryExpressionTemplate<DivideExpression>(std::bind(&Parser::parseDivideExpression, this),
                                                           std::bind(&Parser::parseModuloExpression, this),
                                                           "divide",
                                                           {T_DIVIDE});
}

UniExpressionPtr Parser::parseModuloExpression() {
    return parseBinaryExpressionTemplate<ModuloExpression>(std::bind(&Parser::parseModuloExpression, this),
                                                           std::bind(&Parser::parseEvaluateExpression, this),
                                                           "modulo",
                                                           {T_MODULO});
}

UniExpressionPtr Parser::parseEvaluateExpression() {
    return parseUnaryExpressionTemplate<EvaluateExpression>(std::bind(&Parser::parseEvaluateExpression, this),
                                                            std::bind(&Parser::parseMinusExpression, this),
                                                            "evaluateExpression",
                                                            {T_EVALUATE});
}

UniExpressionPtr Parser::parseMinusExpression() {
    return parseUnaryExpressionTemplate<MinusExpression>(std::bind(&Parser::parseMinusExpression, this),
                                                         std::bind(&Parser::parseNegateExpression, this),
                                                         "minus",
                                                         {T_MINUS});
}

UniExpressionPtr Parser::parseNegateExpression() {
    return parseUnaryExpressionTemplate<NegateExpression>(std::bind(&Parser::parseNegateExpression, this),
                                                          std::bind(&Parser::parseBaseExpression, this),
                                                          "negate",
                                                          {T_NEGATE});
}
UniExpressionPtr Parser::parseBaseExpression() {
    if (auto baseExp = parseFunctionCallOrVariableReference())
        return baseExp;
    if (acceptNext({T_OPEN_BRACKET})) {// nested expression
        if (auto baseExp = parseExpression()) {
            acceptNextOrThrow({T_CLOSE_BRACKET}, "no close bracket in nested expression");
            return baseExp;
        }
        throw ParserException("couldn't parse nested expression", getNextToken(), {T_OPEN_BRACKET});
    }
    if(auto baseExp = parseStringLiteral())
        return baseExp;
    if(auto baseExp = parseBooleanLiteral())
        return baseExp;
    if(auto baseExp = parseNumberLiteral())
        return baseExp;
    return nullptr;
}

UniExpressionPtr Parser::parseVariableReference(const std::string & identifier) {
    return std::make_unique<VariableReference>(identifier);
}


UniExpressionPtr Parser::parseFunctionCallOrVariableReference() {
    if (!acceptNext({T_IDENTIFIER}))
        return nullptr;
    auto identifier = helpers::stringValueFromToken(token);
    if (auto funCallPtr = parseFunctionCall(identifier)) {
        auto funCallExpressionPtr = std::make_unique<FunctionCallExpression>(
                static_cast<FunctionCallExpression>(std::move(funCallPtr.value())));
        return funCallExpressionPtr;
    }
    if (auto varReferencePtr = parseVariableReference(identifier))
        return varReferencePtr;
    throw ParserException("couldn't parse function call or variable reference", getNextToken(), {T_IDENTIFIER});
}

std::optional<BaseFunctionCall> Parser::parseFunctionCall(const std::string &identifier) {
    if (!acceptNext({T_OPEN_BRACKET}))
        return {};
    std::vector<UniExpressionPtr> arguments;
    auto exPtr = parseExpression();
    if (exPtr) {
        arguments.push_back(std::move(exPtr));
        while (acceptNext({T_COMMA})) {
            exPtr = parseExpression();
            if (!exPtr)
                throwNext("couldn't parse function call argument after comma");
            arguments.push_back(std::move(exPtr));
        }
    }
    acceptNextOrThrow({T_CLOSE_BRACKET}, "no close bracket in function call");

    return BaseFunctionCall(identifier, arguments);
}

UniExpressionPtr Parser::parseStringLiteral() {
    if (!acceptNext({T_STRING_LITERAL}))
        return nullptr;
    return std::make_unique<StringLiteral>(helpers::stringValueFromToken(token));
}

UniExpressionPtr Parser::parseBooleanLiteral() {
    if (!acceptNext({T_TRUE, T_FALSE}))
        return nullptr;
    if (token.type == T_TRUE)
        return std::make_unique<BooleanLiteral>(true);
    return std::make_unique<BooleanLiteral>(false);
}

UniExpressionPtr Parser::parseNumberLiteral() {
    if (!acceptNext({T_NUMBER_LITERAL}))
        return nullptr;
    return std::make_unique<NumberLiteral>(helpers::doubleValueFromToken(token));
}
