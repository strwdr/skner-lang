#ifndef SKNER_EQUALEXPRESSION_H
#define SKNER_EQUALEXPRESSION_H

#include "../../virtual/IBinaryExpression.h"

class EqualExpression : public IBinaryExpression {
public:
    EqualExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_EQUAL_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};


#endif //SKNER_EQUALEXPRESSION_H
