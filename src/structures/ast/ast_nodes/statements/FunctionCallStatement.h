#ifndef SKNER_FUNCTIONCALLSTATEMENT_H
#define SKNER_FUNCTIONCALLSTATEMENT_H


#include <vector>

#include "../../AstNodeType.h"
#include "../common/BaseFunctionCall.h"

class FunctionCallStatement : public BaseFunctionCall, public IStatement {
public:
    explicit FunctionCallStatement(const std::string &_functionName, std::vector<UniExpressionPtr> &_arguments) :
            BaseFunctionCall(_functionName, _arguments) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_FUNCTION_CALL;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }
};

#endif //SKNER_FUNCTIONCALLSTATEMENT_H
