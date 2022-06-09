#ifndef SKNER_VARIABLEREFERENCE_H
#define SKNER_VARIABLEREFERENCE_H

#include <utility>

class VariableReference : public IExpression {
public:
    explicit VariableReference(const std::string &_variableName) : variableName(_variableName) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_VARIABLE_REFERENCE;
    }

    void acceptExpressionVisitor(IExpressionVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }

    std::string getVariableName() {
        return variableName;
    }

private:
    std::string variableName;
};

#endif //SKNER_VARIABLEREFERENCE_H
