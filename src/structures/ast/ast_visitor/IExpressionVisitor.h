#ifndef SKNER_IEXPRESSION_VISITOR_H
#define SKNER_IEXPRESSION_VISITOR_H

#include "../ast_nodes/NodesDeclarations.h"

class IExpressionVisitor {
public:
    virtual void visit(AddExpression *node) = 0;

    virtual void visit(SubtractExpression *node) = 0;

    virtual void visit(GreaterEqualExpression *node) = 0;

    virtual void visit(GreaterExpression *node) = 0;

    virtual void visit(LessEqualExpression *node) = 0;

    virtual void visit(LessExpression *node) = 0;

    virtual void visit(EqualExpression *node) = 0;

    virtual void visit(NotEqualExpression *node) = 0;

    virtual void visit(DivideExpression *node) = 0;

    virtual void visit(ModuloExpression *node) = 0;

    virtual void visit(MultiplyExpression *node) = 0;

    virtual void visit(EvaluateExpression *node) = 0;

    virtual void visit(MinusExpression *node) = 0;

    virtual void visit(NegateExpression *node) = 0;

    virtual void visit(AndExpression *node) = 0;

    virtual void visit(OrExpression *node) = 0;

    virtual void visit(FunctionCallExpression *node) = 0;

    virtual void visit(VariableReference *node) = 0;

    virtual void visit(BooleanLiteral *node) = 0;

    virtual void visit(NumberLiteral *node) = 0;

    virtual void visit(StringLiteral *node) = 0;
};


#endif //SKNER_IEXPRESSION_VISITOR_H
