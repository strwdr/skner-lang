#ifndef SKNER_WHILESTATEMENT_H
#define SKNER_WHILESTATEMENT_H


#include <utility>

#include "ConditionalStatementBlock.h"

class WhileStatement : public IStatement {
public:
    explicit WhileStatement(std::unique_ptr<ConditionalStatementBlock> whileStatement) :
            whileStatement(std::move(whileStatement)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_WHILE_STATEMENT;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }

    ConditionalStatementBlock *getRawWhileStatement() {
        return whileStatement.get();
    }

private:
    std::unique_ptr<ConditionalStatementBlock> whileStatement;
};


#endif //SKNER_WHILESTATEMENT_H
