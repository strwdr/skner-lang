#ifndef SKNER_LESSEXPRESSION_H
#define SKNER_LESSEXPRESSION_H
#include "../../virtual/IBinaryExpression.h"

class LessExpression : public IBinaryExpression {
public:
    LessExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_LESS_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};
#endif //SKNER_LESSEXPRESSION_H
