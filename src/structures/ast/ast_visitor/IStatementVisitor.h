#ifndef SKNER_ISTATEMENTVISITOR_H
#define SKNER_ISTATEMENTVISITOR_H

#include "../ast_nodes/NodesDeclarations.h"

class IStatementVisitor {
public:
    virtual void visit(Break *node) = 0;

    virtual void visit(ConditionalStatementBlock *node) = 0;

    virtual void visit(Continue *node) = 0;

    virtual void visit(DeleteStatement *node) = 0;

    virtual void visit(Exit *node) = 0;

    virtual void visit(FunctionCallStatement *node) = 0;

    virtual void visit(FunctionDefinition *node) = 0;

    virtual void visit(IfStatement *node) = 0;

    virtual void visit(ReturnStatement *node) = 0;

    virtual void visit(StatementBlock *node) = 0;

    virtual void visit(VariableAssignment *node) = 0;

    virtual void visit(VariableDefinition *node) = 0;

    virtual void visit(WhileStatement *node) = 0;
};


#endif //SKNER_ISTATEMENTVISITOR_H
