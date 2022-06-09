#ifndef SKNER_LESSEQUALEXPRESSION_H
#define SKNER_LESSEQUALEXPRESSION_H

#include "../../virtual/IBinaryExpression.h"

class LessEqualExpression : public IBinaryExpression {
public:
    LessEqualExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_LESS_EQUAL_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_LESSEQUALEXPRESSION_H
