#ifndef SKNER_IEXPRESSION_H
#define SKNER_IEXPRESSION_H

#include "IAstNode.h"

class IExpression : public IAstNode {
public:
    virtual void acceptExpressionVisitor(IExpressionVisitor &visitor) = 0;

    void acceptCommonVisitor(ICommonVisitor &visitor) override = 0;

    [[nodiscard]] AstNodeType getNodeType() const override = 0;
};

#endif //SKNER_IEXPRESSION_H
