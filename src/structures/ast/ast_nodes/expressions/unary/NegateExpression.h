#ifndef SKNER_NEGATEEXPRESSION_H
#define SKNER_NEGATEEXPRESSION_H

#include "../../virtual/IUnaryExpression.h"

class NegateExpression : public IUnaryExpression {
public:
    NegateExpression(UniExpressionPtr _operand) : IUnaryExpression(std::move(_operand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_NEGATE_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_NEGATEEXPRESSION_H
