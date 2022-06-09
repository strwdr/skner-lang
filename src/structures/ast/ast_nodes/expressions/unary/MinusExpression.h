#ifndef SKNER_MINUSEXPRESSION_H
#define SKNER_MINUSEXPRESSION_H

#include "../../virtual/IUnaryExpression.h"

class MinusExpression : public IUnaryExpression {
public:
    MinusExpression(UniExpressionPtr _operand) : IUnaryExpression(std::move(_operand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_MINUS_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_MINUSEXPRESSION_H
