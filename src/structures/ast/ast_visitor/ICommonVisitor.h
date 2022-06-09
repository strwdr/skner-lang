#ifndef SKNER_ICOMMONVISITOR_H
#define SKNER_ICOMMONVISITOR_H

#include "IExpressionVisitor.h"
#include "IStatementVisitor.h"

class ICommonVisitor : public IExpressionVisitor, public IStatementVisitor{
public:
    void visit(AddExpression *node) override = 0;

    void visit(SubtractExpression *node) override = 0;

    void visit(GreaterEqualExpression *node) override = 0;

    void visit(GreaterExpression *node) override = 0;

    void visit(LessEqualExpression *node) override = 0;

    void visit(LessExpression *node) override = 0;

    void visit(EqualExpression *node) override = 0;

    void visit(NotEqualExpression *node) override = 0;

    void visit(DivideExpression *node) override = 0;

    void visit(ModuloExpression *node) override = 0;

    void visit(MultiplyExpression *node) override = 0;

    void visit(EvaluateExpression *node) override = 0;

    void visit(MinusExpression *node) override = 0;

    void visit(NegateExpression *node) override = 0;

    void visit(AndExpression *node) override = 0;

    void visit(OrExpression *node) override = 0;

    void visit(FunctionCallExpression *node) override = 0;

    void visit(VariableReference *node) override = 0;

    void visit(BooleanLiteral *node) override = 0;

    void visit(NumberLiteral *node) override = 0;

    void visit(StringLiteral *node) override = 0;

    void visit(Break *node) override = 0;

    void visit(ConditionalStatementBlock *node) override = 0;

    void visit(Continue *node) override = 0;

    void visit(DeleteStatement *node) override = 0;

    void visit(Exit *node) override = 0;

    void visit(FunctionCallStatement *node) override = 0;

    void visit(FunctionDefinition *node) override = 0;

    void visit(IfStatement *node) override = 0;

    void visit(ReturnStatement *node) override = 0;

    void visit(StatementBlock *node) override = 0;

    void visit(VariableAssignment *node) override = 0;

    void visit(VariableDefinition *node) override = 0;

    void visit(WhileStatement *node) override = 0;
};


#endif //SKNER_ICOMMONVISITOR_H
