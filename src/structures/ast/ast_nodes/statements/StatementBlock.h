#ifndef SKNER_STATEMENTBLOCK_H
#define SKNER_STATEMENTBLOCK_H

#include <vector>

#include "../virtual/IAstNode.h"
#include "../../AstNodeType.h"
#include "../../../../lexer/structures/TokenType.h"
#include "../virtual/IBinaryExpression.h"


class StatementBlock : public IStatement {
public:
    explicit StatementBlock(std::vector<UniStatementPtr> &_statements) {
        for (auto &statement: _statements) {
            statements.push_back(std::move(statement));
        }
    }

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_STATEMENT_BLOCK;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }

    std::vector<IStatement *> getRawStatements() {
        std::vector<IStatement *> rawStatements;
        for (auto &statement: statements)
            rawStatements.push_back(statement.get());
        return rawStatements;
    }

private:
    std::vector<UniStatementPtr> statements;
};

#endif //SKNER_STATEMENTBLOCK_H
