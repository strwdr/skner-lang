#ifndef SKNER_NUMBERLITERAL_H
#define SKNER_NUMBERLITERAL_H

#include <utility>

#include "../virtual/ILiteralNodeT.h"
#include "../../AstNodeType.h"

class NumberLiteral : public ILiteralNodeT<double> {
public:
    explicit NumberLiteral(const double &_value) : ILiteralNodeT(_value) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_NUMBER_LITERAL;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_NUMBERLITERAL_H
