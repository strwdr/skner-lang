#ifndef SKNER_ANDEXPRESSION_H
#define SKNER_ANDEXPRESSION_H

#include "../../virtual/IBinaryExpression.h"

class AndExpression : public IBinaryExpression {
public:
    AndExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_AND_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_ANDEXPRESSION_H
