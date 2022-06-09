#ifndef SKNER_BOOLEANLITERAL_H
#define SKNER_BOOLEANLITERAL_H

#include <utility>

#include "../virtual/ILiteralNodeT.h"
#include "../../AstNodeType.h"

class BooleanLiteral : public ILiteralNodeT<bool> {
public:
    explicit BooleanLiteral(const bool &_value) : ILiteralNodeT(_value) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_BOOLEAN_LITERAL;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_BOOLEANLITERAL_H
