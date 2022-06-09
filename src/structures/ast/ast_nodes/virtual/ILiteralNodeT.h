#ifndef SKNER_ILITERALNODET_H
#define SKNER_ILITERALNODET_H

#include <utility>

#include "IAstNode.h"

template<class T>
class ILiteralNodeT : public IExpression {
public:
    explicit ILiteralNodeT(T _value) {
        value = _value;
    }

    T getValue() {
        return value;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override = 0;

    void acceptCommonVisitor(ICommonVisitor &visitor) override = 0;

    [[nodiscard]] AstNodeType getNodeType() const override = 0;

private:
    T value;
};


#endif //SKNER_ILITERALNODET_H
