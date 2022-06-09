#ifndef SKNER_BREAK_H
#define SKNER_BREAK_H

#include "../virtual/IAstNode.h"

class Break : public IStatement {
public:
    AstNodeType getNodeType() const override {
        return N_BREAK;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_BREAK_H
