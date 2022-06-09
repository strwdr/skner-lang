#ifndef SKNER_HELPERTRAVERSER_H
#define SKNER_HELPERTRAVERSER_H

#include <vector>
#include "ICommonVisitor.h"
#include "../AstNodeType.h"
#include "../../../interpreter/Evaluator.h"
#include <stack>
#include <variant>

class IAstNode;

class HelperTraverser : public ICommonVisitor {
public:
    HelperTraverser(bool _evaluateExpressions = false);

    std::vector<AstNodeType> preOrderNodes;
    std::istringstream inputStream;
    std::ostringstream outputStream;
    std::string treeString;
    std::string tmpAddString;
    int depth = 0;
    std::stack<bool> moreThanOne;
    Evaluator expressionEvaluator;
    bool evaluateExpressions;

    void init();

    void updateTmpAddString(IExpression * exPtr);

    void endVisit(IAstNode* node);

    void startVisit(IAstNode* node);

    std::string traverseTreeString(IAstNode *root);

    std::vector<AstNodeType> traverseGetPreOrder(IAstNode *root);

    void visit(AddExpression *node) override;

    void visit(SubtractExpression *node) override;

    void visit(GreaterEqualExpression *node) override;

    void visit(GreaterExpression *node) override;

    void visit(LessEqualExpression *node) override;

    void visit(LessExpression *node) override;

    void visit(EqualExpression *node) override;

    void visit(NotEqualExpression *node) override;

    void visit(DivideExpression *node) override;

    void visit(ModuloExpression *node) override;

    void visit(MultiplyExpression *node) override;

    void visit(EvaluateExpression *node) override;

    void visit(MinusExpression *node) override;

    void visit(NegateExpression *node) override;

    void visit(AndExpression *node) override;

    void visit(OrExpression *node) override;

    void visit(FunctionCallExpression *node) override;

    void visit(VariableReference *node) override;

    void visit(BooleanLiteral *node) override;

    void visit(NumberLiteral *node) override;

    void visit(StringLiteral *node) override;

    void visit(Break *node) override;

    void visit(ConditionalStatementBlock *node) override;

    void visit(Continue *node) override;

    void visit(DeleteStatement *node) override;

    void visit(Exit *node) override;

    void visit(FunctionCallStatement *node) override;

    void visit(FunctionDefinition *node) override;

    void visit(IfStatement *node) override;

    void visit(ReturnStatement *node) override;

    void visit(StatementBlock *node) override;

    void visit(VariableAssignment *node) override;

    void visit(VariableDefinition *node) override;

    void visit(WhileStatement *node) override;

    ~HelperTraverser() = default;
};

#endif //SKNER_HELPERTRAVERSER_H
