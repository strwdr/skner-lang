#ifndef SKNER_CONTINUE_H
#define SKNER_CONTINUE_H

#include "../virtual/IAstNode.h"

class Continue : public IStatement {
public:
    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_CONTINUE;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_CONTINUE_H
