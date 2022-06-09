#ifndef SKNER_ADDEXPRESSION_H
#define SKNER_ADDEXPRESSION_H

#include "../../virtual/IBinaryExpression.h"

class AddExpression : public IBinaryExpression {
public:
    AddExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_ADD_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};


#endif //SKNER_ADDEXPRESSION_H
