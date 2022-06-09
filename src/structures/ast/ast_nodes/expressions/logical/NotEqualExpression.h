#ifndef SKNER_NOTEQUALEXPRESSION_H
#define SKNER_NOTEQUALEXPRESSION_H

#include "../../virtual/IBinaryExpression.h"

class NotEqualExpression : public IBinaryExpression {
public:
    NotEqualExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_NOT_EQUAL_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_NOTEQUALEXPRESSION_H
