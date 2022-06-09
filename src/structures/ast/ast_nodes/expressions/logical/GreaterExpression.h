#ifndef SKNER_GREATEREXPRESSION_H
#define SKNER_GREATEREXPRESSION_H

#include "../../virtual/IBinaryExpression.h"

class GreaterExpression : public IBinaryExpression {
public:
    GreaterExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_GREATER_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_GREATEREXPRESSION_H
