#ifndef SKNER_VARIABLEDEFINITION_H
#define SKNER_VARIABLEDEFINITION_H


#include <utility>

#include "../../AstNodeType.h"
#include "../virtual/IBinaryExpression.h"
#include "../../Datatypes.h"


class VariableDefinition : public IStatement {
public:
    VariableDefinition(const DataType &_dataType,
                       const std::string &_variableName,
                       UniExpressionPtr _valueExpression)
            : variableName(_variableName),
              valueExpression(std::move(_valueExpression)),
              dataType(_dataType) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_VARIABLE_ASSIGNMENT;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }

    [[nodiscard]] DataType getDataType() const {
        return dataType;
    }

    IExpression *getRawValueExpression() {
        return valueExpression.get();
    }

    UniExpressionPtr getValueExpression() {
        return std::move(valueExpression);
    }

    std::string getVariableName() const{
        return variableName;
    }

private:
    DataType dataType;

    UniExpressionPtr valueExpression;

    std::string variableName;
};


#endif //SKNER_VARIABLEDEFINITION_H
