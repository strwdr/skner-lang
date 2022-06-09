#ifndef SKNER_OREXPRESSION_H
#define SKNER_OREXPRESSION_H

#include "../../virtual/IBinaryExpression.h"

class OrExpression : public IBinaryExpression {
public:
    OrExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_OR_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};


#endif //SKNER_OREXPRESSION_H
