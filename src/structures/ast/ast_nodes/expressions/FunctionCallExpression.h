#ifndef SKNER_FUNCTIONCALLEXPRESSION_H
#define SKNER_FUNCTIONCALLEXPRESSION_H

#include <vector>

#include "../../AstNodeType.h"
#include "../common/BaseFunctionCall.h"

class FunctionCallExpression : public BaseFunctionCall, public IExpression {
public:
    explicit FunctionCallExpression(const std::string &_functionName, std::vector<UniExpressionPtr> &_arguments) :
            BaseFunctionCall(_functionName, _arguments) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_FUNCTION_CALL;
    }

     void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }


};
#endif //SKNER_FUNCTIONCALLEXPRESSION_H
