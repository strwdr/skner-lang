#ifndef SKNER_IUNARYEXPRESSION_H
#define SKNER_IUNARYEXPRESSION_H

#include <iostream>
#include <optional>
#include <utility>
#include <vector>

#include "IAstNode.h"
#include "IExpression.h"
#include "../../AstNodeType.h"
#include "../../../../lexer/structures/TokenType.h"
#include "../../ast_visitor/ICommonVisitor.h"

class IUnaryExpression : public IExpression {
public:
    IUnaryExpression(UniExpressionPtr _operand) : operand(std::move(_operand)) {}

    IExpression *getRawOperand() {
        return operand.get();
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override = 0;

    void acceptCommonVisitor(ICommonVisitor &visitor) override = 0;

    [[nodiscard]] AstNodeType getNodeType() const override = 0;

private:
    UniExpressionPtr operand;

};

#endif //SKNER_IUNARYEXPRESSION_H
