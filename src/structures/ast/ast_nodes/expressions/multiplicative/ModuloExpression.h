#ifndef SKNER_MODULOEXPRESSION_H
#define SKNER_MODULOEXPRESSION_H
#include "../../virtual/IBinaryExpression.h"

class ModuloExpression : public IBinaryExpression {
public:
    ModuloExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) :
            IBinaryExpression(std::move(_leftOperand), std::move(_rightOperand)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_MODULO_EXPRESSION;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_MODULOEXPRESSION_H
