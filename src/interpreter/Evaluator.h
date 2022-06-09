#ifndef SKNER_EVALUATOR_H
#define SKNER_EVALUATOR_H

#include "../structures/ast/ast_visitor/ICommonVisitor.h"
#include "../structures/ast/AstNodeType.h"
#include "../structures/ast/Datatypes.h"
#include "../structures/Typedefs.h"
#include "structures/Interruptions.h"
#include "Helpers.h"

#include <stack>
#include <variant>
#include <vector>
#include <iostream>
#include <optional>
#include <sstream>
#include <iomanip>
#include <set>


class Evaluator : public ICommonVisitor {
public:
    Evaluator(std::istream &_inputStream, std::ostream &_outputStream);

    std::string evaluateExpressionToString(IExpression *root);

    ValueVariant evaluateExpression(IExpression *root);

    bool executeProgramStatement(IStatement *root);

    void resetToGlobalScope() {
        clearInterruptionToHandle();
        while (globalVariablesContexts.size() != 1) {
            globalVariablesContexts.pop_back();
        }
        while(!funCallsVariablesContextsStack.empty()){
            funCallsVariablesContextsStack.pop();
        }
    }

    ~Evaluator() = default;


protected:
    const std::set<std::string> stdLibReservedFunctions = {
            "print",
            "println",
            "read",
            "to_string",
            "to_boolean",
            "to_number"
    };

    std::istream &inputStream;
    std::ostream &outputStream;

    // expressions

    helpers::BinaryExpressionEvaluationOutput
    getValuesFromBinaryExpression(IBinaryExpression *node,
                                  const std::vector<DataType> &expectedDataTypes,
                                  const std::string &exceptionMsg);

    void initExpressionEvaluator();

    DataType topDataType;

    ValueVariant topValue;

    void updateExpressionTop(DataType newTopDataType);

    void updateExpressionTop(DataType newTopDataType, ValueVariant newValue);

    void visit(AddExpression *node) override;

    void visit(SubtractExpression *node) override;

    void visit(GreaterEqualExpression *node) override;

    void visit(GreaterExpression *node) override;

    void visit(LessEqualExpression *node) override;

    void visit(LessExpression *node) override;

    void visit(EqualExpression *node) override;

    void visit(NotEqualExpression *node) override;

    void visit(DivideExpression *node) override;

    void visit(ModuloExpression *node) override;

    void visit(MultiplyExpression *node) override;

    void visit(EvaluateExpression *node) override;

    void visit(MinusExpression *node) override;

    void visit(NegateExpression *node) override;

    void visit(AndExpression *node) override;

    void visit(OrExpression *node) override;

    void visit(FunctionCallExpression *node) override;

    void visit(VariableReference *node) override;

    void visit(BooleanLiteral *node) override;

    void visit(NumberLiteral *node) override;

    void visit(StringLiteral *node) override;

    // statements

    void initStatementEvaluator();

    bool hasInterruptionToHandle();

    InterruptionType interruptionToHandle;

    helpers::ReturnToHandleValue returnToHandleValue;

    void clearInterruptionToHandle();

    std::vector<std::pair<std::string, DataTypeVal>> argumentsToAppend;

    std::optional<DataTypeVal> findVariableOnBack(const std::string &variableName);

    std::optional<DataTypeVal> findVariable(const std::string &variableName);

    FunctionDefinition *findFunction(const std::string &functionName);

    bool identifierAlreadyExists(const std::string &id);

    std::stack<std::vector<VarsMap>> funCallsVariablesContextsStack;

    bool notInGlobalScope(){
        return !funCallsVariablesContextsStack.empty();
    }

    std::vector<VarsMap> globalVariablesContexts;

    FuncsMap functions;

    void visit(Break *node) override;

    void visit(ConditionalStatementBlock *node) override;

    void visit(Continue *node) override;

    void visit(DeleteStatement *node) override;

    void visit(Exit *node) override;

    void visit(FunctionCallStatement *node) override;

    void visit(FunctionDefinition *node) override;

    void visit(IfStatement *node) override;

    void visit(ReturnStatement *node) override;

    void visit(StatementBlock *node) override;

    void visit(VariableAssignment *node) override;

    void visit(VariableDefinition *node) override;

    void visit(WhileStatement *node) override;

    void handleBaseFunctionCall(BaseFunctionCall *node);

    void addVariableToStackBack(const std::string &variableName, const DataTypeVal &dataTypeVal);

    // stdlib

    bool handlePrintFunctions(BaseFunctionCall *node);

    bool handleReadFunction(BaseFunctionCall *node);

    bool handleCastFunctions(BaseFunctionCall *node);

};

#endif //SKNER_EVALUATOR_H
