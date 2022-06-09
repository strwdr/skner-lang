#ifndef SKNER_GREATEREQUALEXPRESSION_H
#define SKNER_GREATEREQUALEXPRESSION_H

#include "../../virtual/IBinaryExpression.h"


class GreaterEqualExpression : public IBinaryExpression {
public:
    GreaterEqualExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_GREATER_EQUAL_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};
#endif //SKNER_GREATEREQUALEXPRESSION_H
