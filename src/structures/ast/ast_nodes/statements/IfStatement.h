#ifndef SKNER_IFSTATEMENT_H
#define SKNER_IFSTATEMENT_H

#include <vector>

#include "../virtual/IAstNode.h"
#include "../../AstNodeType.h"
#include "ConditionalStatementBlock.h"
#include "StatementBlock.h"

class IfStatement : public IStatement {
public:
    IfStatement(std::vector<std::unique_ptr<ConditionalStatementBlock>> &_ifStatements,
                std::unique_ptr<StatementBlock> _elseStatement) :
            elseStatement(std::move(_elseStatement)) {
        for (auto &ifStatement: _ifStatements) {
            ifStatements.push_back(std::move(ifStatement));
        }
    }

    [[nodiscard]] bool hasElse() const {
        return elseStatement != nullptr;
    }

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_IF_STATEMENT;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }

    std::vector<ConditionalStatementBlock *> getRawIfStatements() {
        std::vector<ConditionalStatementBlock *> rawIfStatements;
        for (auto &statement: ifStatements)
            rawIfStatements.push_back(statement.get());
        return rawIfStatements;
    }

    StatementBlock *getRawElseStatement() {
        if (hasElse())
            return elseStatement.get();
        return nullptr;
    }

private:
    std::vector<std::unique_ptr<ConditionalStatementBlock>> ifStatements;
    std::unique_ptr<StatementBlock> elseStatement;

};


#endif //SKNER_IFSTATEMENT_H
