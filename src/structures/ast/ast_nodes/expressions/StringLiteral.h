#ifndef SKNER_STRINGLITERAL_H
#define SKNER_STRINGLITERAL_H

#include <utility>

#include "../virtual/ILiteralNodeT.h"
#include "../../AstNodeType.h"

class StringLiteral : public ILiteralNodeT<std::string> {
public:
    explicit StringLiteral(const std::string &_value) : ILiteralNodeT(_value) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_STRING_LITERAL;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_STRINGLITERAL_H
