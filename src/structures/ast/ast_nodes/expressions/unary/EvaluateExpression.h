#ifndef SKNER_EVALUATEEXPRESSION_H
#define SKNER_EVALUATEEXPRESSION_H

#include "../../virtual/IUnaryExpression.h"

class EvaluateExpression : public IUnaryExpression {
public:
    EvaluateExpression(UniExpressionPtr _operand) : IUnaryExpression(std::move(_operand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_EVALUATE_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_EVALUATEEXPRESSION_H
