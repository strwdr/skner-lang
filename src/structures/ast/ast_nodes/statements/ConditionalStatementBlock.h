#ifndef SKNER_CONDITIONALSTATEMENTBLOCK_H
#define SKNER_CONDITIONALSTATEMENTBLOCK_H

// common part for ifStatementNode, and whileStatementNode

#include <vector>

#include "../virtual/IAstNode.h"
#include "../../AstNodeType.h"
#include "../../../../lexer/structures/TokenType.h"
#include "../virtual/IBinaryExpression.h"
#include "StatementBlock.h"

class ConditionalStatementBlock : public IStatement {
public:
    ConditionalStatementBlock(UniExpressionPtr _condition,
                              UniStatementPtr _statementBlock) :
            statementBlock(std::move(_statementBlock)),
            condition(std::move(_condition)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_CONDITIONAL_STATEMENT_BLOCK;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }

    IExpression *getRawCondition() {
        return condition.get();
    }

    IStatement *getRawStatementBlock() {
        return statementBlock.get();
    }

private:
    UniExpressionPtr condition;

    UniStatementPtr statementBlock;
};

#endif //SKNER_CONDITIONALSTATEMENTBLOCK_H
