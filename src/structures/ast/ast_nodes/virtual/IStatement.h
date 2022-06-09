#ifndef SKNER_ISTATEMENT_H
#define SKNER_ISTATEMENT_H

#include "IAstNode.h"

class IStatement : public IAstNode {
public:
    virtual void acceptStatementVisitor(IStatementVisitor &visitor) = 0;

    void acceptCommonVisitor(ICommonVisitor &visitor) override = 0;

    [[nodiscard]] AstNodeType getNodeType() const override = 0;
};

#endif //SKNER_ISTATEMENT_H
