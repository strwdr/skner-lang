#ifndef SKNER_DELETESTATEMENT_H
#define SKNER_DELETESTATEMENT_H


#include "../../AstNodeType.h"

class DeleteStatement : public IStatement {
public:
    explicit DeleteStatement(const std::string &_identifier) : identifier(_identifier) {}

    [[nodiscard]] AstNodeType getNodeType() const override {
        return N_DELETION;
    }

    void acceptStatementVisitor(IStatementVisitor &visitor) override {
        visitor.visit(this);
    }

    void acceptCommonVisitor(ICommonVisitor &visitor) override {
        visitor.visit(this);
    }

    std::string getIdentifier() const {
        return identifier;
    }

private:
    std::string identifier;
};

#endif //SKNER_DELETESTATEMENT_H
