#ifndef SKNER_SUBTRACTEXPRESSION_H
#define SKNER_SUBTRACTEXPRESSION_H

#include "../../virtual/IBinaryExpression.h"

class SubtractExpression : public IBinaryExpression {
public:
    SubtractExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_SUBTRACT_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};


#endif //SKNER_SUBTRACTEXPRESSION_H
