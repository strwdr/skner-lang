#include "BaseFunctionCall.h"

#include "../statements/FunctionCallStatement.h"
#include "../expressions/FunctionCallExpression.h"

BaseFunctionCall::operator FunctionCallStatement() {
    return FunctionCallStatement(functionName, arguments);
}

BaseFunctionCall::operator FunctionCallExpression() {
    return FunctionCallExpression(functionName, arguments);
}