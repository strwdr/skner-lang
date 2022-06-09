#ifndef SKNER_RETURNSTATEMENT_H
#define SKNER_RETURNSTATEMENT_H


#include <utility>

#include "../virtual/IAstNode.h"
#include "../../AstNodeType.h"
#include "../virtual/IBinaryExpression.h"

class ReturnStatement : public IStatement {
public:
    ReturnStatement() = default;

    explicit ReturnStatement(UniExpressionPtr _returnExpression) :
            returnExpression(std::move(_returnExpression)) {}

    [[nodiscard]] bool isNullReturn() const {
        return returnExpression == nullptr;
    }

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_RETURN_STATEMENT;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }

    IExpression *getRawReturnExpression() {
        if(!isNullReturn())
            return returnExpression.get();
        return nullptr;
    }

private:
    UniExpressionPtr returnExpression = nullptr;
};


#endif //SKNER_RETURNSTATEMENT_H
