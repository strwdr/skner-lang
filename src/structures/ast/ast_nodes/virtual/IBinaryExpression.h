#ifndef SKNER_IBINARYEXPRESSION_H
#define SKNER_IBINARYEXPRESSION_H

#include <iostream>
#include <optional>
#include <utility>
#include <vector>

#include "IAstNode.h"
#include "IExpression.h"
#include "../../AstNodeType.h"
#include "../../../../lexer/structures/TokenType.h"
#include "../../ast_visitor/ICommonVisitor.h"

class IBinaryExpression : public IExpression {
public:
    IBinaryExpression(UniExpressionPtr _leftOperand, UniExpressionPtr _rightOperand) : leftOperand(
            std::move(_leftOperand)),
                                                                                       rightOperand(std::move(
                                                                                               _rightOperand)) {}

    IExpression *getRawLeftOperand() {
        return leftOperand.get();
    }

    IExpression *getRawRightOperand() {
        return rightOperand.get();
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override = 0;

    void acceptCommonVisitor(ICommonVisitor &visitor) override = 0;

    [[nodiscard]] AstNodeType getNodeType() const override = 0;

private:
    UniExpressionPtr leftOperand;

    UniExpressionPtr rightOperand;

};

#endif //SKNER_IBINARYEXPRESSION_H
