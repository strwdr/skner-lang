#ifndef SKNER_PARSER_H
#define SKNER_PARSER_H


#include "../structures/ast/ast_nodes/NodesIncludes.h"

#include "../stream_provider/StreamProvider.h"
#include "../lexer/Lexer.h"
#include "../structures/ast/ast_nodes/statements/VariableDefinition.h"
#include "../structures/ast/ast_nodes/expressions/NumberLiteral.h"
#include "../structures/ast/ast_nodes/expressions/BooleanLiteral.h"
#include "../structures/ast/ast_nodes/expressions/StringLiteral.h"
#include "../structures/Typedefs.h"

#include <optional>
#include <functional>


class Parser {
public:
    ~Parser() = default;

    explicit Parser(std::istream &stream);

    Token getToken();

    Token getNextToken();

    UniStatementPtr parseProgramStatement();

    void skipSemicolons();

    void skipToNextNewline();

protected:
    void acceptNextOrThrow(const std::initializer_list<TokenType> &acceptable, const std::string & msg);

    std::optional<Token> acceptNext(const std::initializer_list<TokenType> &acceptable);

    std::optional<Token> check(const std::initializer_list<TokenType> &acceptable, bool checkNextToken = false);

    std::optional<Token> checkNext(const std::initializer_list<TokenType> &acceptable);

    std::optional<Token> accept(const std::initializer_list<TokenType> &acceptable, bool acceptNextToken = false);

    void nextToken();

    void throwNext(const std::string &msg);

    template<class T>
    UniExpressionPtr
    parseBinaryExpressionTemplate(const std::function<UniExpressionPtr(void)> &thisParseExpression,
                                  const std::function<UniExpressionPtr(void)> &nextParseExpression,
                                  const std::string &name,
                                  const TokenType &acceptableOperatorToken);

    template<class T>
    UniExpressionPtr
    parseUnaryExpressionTemplate(const std::function<UniExpressionPtr(void)> &thisParseExpression,
                                 const std::function<UniExpressionPtr(void)> &nextParseExpression,
                                 const std::string &name,
                                 const TokenType &acceptableOperatorToken);

    UniExpressionPtr parseExpression();

    UniExpressionPtr parseOrExpression();

    UniExpressionPtr parseAndExpression();

    UniExpressionPtr parseEqualExpression();

    UniExpressionPtr parseNotEqualExpression();

    UniExpressionPtr parseGreaterEqualExpression();

    UniExpressionPtr parseGreaterExpression();

    UniExpressionPtr parseLessEqualExpression();

    UniExpressionPtr parseLessExpression();

    UniExpressionPtr parseAddExpression();

    UniExpressionPtr parseSubtractExpression();

    UniExpressionPtr parseMultiplyExpression();

    UniExpressionPtr parseDivideExpression();

    UniExpressionPtr parseModuloExpression();

    UniExpressionPtr parseEvaluateExpression();

    UniExpressionPtr parseMinusExpression();

    UniExpressionPtr parseNegateExpression();

    UniExpressionPtr parseBaseExpression();

    UniExpressionPtr parseFunctionCallOrVariableReference();

    UniExpressionPtr parseVariableReference(const std::string &identifier);

    UniExpressionPtr parseStringLiteral();

    UniExpressionPtr parseBooleanLiteral();

    UniExpressionPtr parseNumberLiteral();

    std::optional<BaseFunctionCall>
    parseFunctionCall(const std::string &identifier); // is later casted to expression or statement

    std::unique_ptr<ConditionalStatementBlock> parseConditionalStatementBlock();

    UniStatementPtr parseIfStatement();

    UniStatementPtr parseWhileStatement();

    UniStatementPtr parseDeleteStatement();

    UniStatementPtr parseVariableAssignment(const std::string &identifier);

    UniStatementPtr parseFunctionDefinitionOrVariableDefinition();

    UniStatementPtr parseFunctionDefinition(DataType dataType = UNDEFINED);

    UniStatementPtr parseVariableDefinition(DataType dataType);

    UniStatementPtr parseFunctionCallOrVariableAssignment();

    UniStatementPtr parseExit();

    UniStatementPtr parseReturnStatement();

    UniStatementPtr parseBreak();

    UniStatementPtr parseContinue();

    UniStatementPtr parseStatementSemicolonOrThrow(UniStatementPtr statementNode);

    std::unique_ptr<StatementBlock> parseStatementBlock();

    UniStatementPtr parseStatement();

    Lexer lexer;

    Token token;

    std::optional<Token> bufferedNextToken;

    static bool isAcceptable(const Token &_token, const std::initializer_list<TokenType> &acceptable);

};


#endif //SKNER_PARSER_H
