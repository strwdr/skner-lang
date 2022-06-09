#ifndef SKNER_BASEFUNCTIONCALL_H
#define SKNER_BASEFUNCTIONCALL_H

#include <vector>

#include "../virtual/IExpression.h"
#include "../virtual/IStatement.h"
#include "../../ast_visitor/ICommonVisitor.h"

class FunctionCallExpression;
class FunctionCallStatement;

class BaseFunctionCall { // common for statement and expression
public:
    explicit BaseFunctionCall(const std::string &_functionName, std::vector<UniExpressionPtr> &_arguments) :
            functionName(_functionName) {
        for (auto &argument: _arguments)
            arguments.push_back(std::move(argument));
    }

    std::vector<IExpression *> getRawArguments() {
        std::vector<IExpression *> rawVec;
        for (auto &argument: arguments)
            rawVec.push_back(argument.get());
        return rawVec;
    }

    std::string getFunctionName() const{
        return functionName;
    }

    explicit operator FunctionCallStatement();

    explicit operator FunctionCallExpression();
protected:
    std::vector<UniExpressionPtr> arguments;
    std::string functionName;
};

#endif //SKNER_BASEFUNCTIONCALL_H
