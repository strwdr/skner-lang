#ifndef SKNER_EXIT_H
#define SKNER_EXIT_H

#include "../virtual/IAstNode.h"

class Exit : public IStatement {
public:
    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_EXIT;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};


#endif //SKNER_EXIT_H
