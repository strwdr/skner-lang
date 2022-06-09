#ifndef SKNER_DIVIDEEXPRESSION_H
#define SKNER_DIVIDEEXPRESSION_H
#include "../../virtual/IBinaryExpression.h"

class DivideExpression : public IBinaryExpression {
public:
    DivideExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_DIVIDE_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};
#endif //SKNER_DIVIDEEXPRESSION_H
