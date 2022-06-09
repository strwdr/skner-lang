#ifndef SKNER_FUNCTIONDEFINITION_H
#define SKNER_FUNCTIONDEFINITION_H


#include <vector>
#include "StatementBlock.h"
#include "../../AstNodeType.h"
#include "../../Datatypes.h"


class FunctionDefinition : public IStatement {
public:
    // argument definition -- pair of type and identifier
    typedef std::pair<DataType, std::string> ParameterDefinition;

    explicit FunctionDefinition(const std::string &_functionName,
                                const DataType &_returnType,
                                std::vector<ParameterDefinition> &_parameterDefinitions,
                                UniStatementPtr _functionBody) :
            functionName(_functionName),
            returnType(_returnType),
            functionBody(std::move(_functionBody)) {
        for (auto &parameterDefinition: _parameterDefinitions) {
            parameterDefinitions.push_back(std::move(parameterDefinition));
        }
    }

    ~FunctionDefinition() = default;

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_FUNCTION_DEFINITION;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }

    [[nodiscard]] DataType getReturnType() const {
        return returnType;
    }

    std::vector<ParameterDefinition> &getParameterDefinitions() {
        return parameterDefinitions;
    }

    IStatement *getRawFunctionBody() {
        return functionBody.get();
    }

    UniStatementPtr getUniFunctionBody() {
        return std::move(functionBody);
    }

    std::string getFunctionName() const {
        return functionName;
    }

private:
    DataType returnType = UNDEFINED;

    std::vector<ParameterDefinition> parameterDefinitions;

    UniStatementPtr functionBody;

    std::string functionName;
};

#endif //SKNER_FUNCTIONDEFINITION_H
