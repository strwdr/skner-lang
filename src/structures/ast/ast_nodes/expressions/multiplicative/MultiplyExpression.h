#ifndef SKNER_MULTIPLYEXPRESSION_H
#define SKNER_MULTIPLYEXPRESSION_H
#include "../../virtual/IBinaryExpression.h"

class MultiplyExpression : public IBinaryExpression {
public:
    MultiplyExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_MULTIPLY_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_MULTIPLYEXPRESSION_H
