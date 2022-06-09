#ifndef SKNER_VARIABLEASSIGNMENT_H
#define SKNER_VARIABLEASSIGNMENT_H


#include <utility>

#include "../../AstNodeType.h"
#include "../virtual/IBinaryExpression.h"


class VariableAssignment : public IStatement {
public:
    explicit VariableAssignment(const std::string &_variableName,
                                UniExpressionPtr valueExpression)
            : variableName(_variableName),
              valueExpression(std::move(valueExpression)) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_VARIABLE_ASSIGNMENT;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }

    IExpression *getRawValueExpression() {
        return valueExpression.get();
    }

    UniExpressionPtr getValueExpression() {
        return std::move(valueExpression);
    }

    [[nodiscard]] std::string getVariableName() const{
        return variableName;
    }

private:
    UniExpressionPtr valueExpression;

    std::string variableName;

};


#endif //SKNER_VARIABLEASSIGNMENT_H
