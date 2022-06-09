#include "HelperTraverser.h"

#include "../ast_nodes/NodesIncludes.h"

HelperTraverser::HelperTraverser(bool _evaluateExpressions) : expressionEvaluator(inputStream, outputStream) {
    init();
    evaluateExpressions = _evaluateExpressions;
}

void HelperTraverser::init() {
    tmpAddString.clear();
    moreThanOne = std::stack<bool>();
    moreThanOne.push(false);
    preOrderNodes.clear();
    treeString.clear();
    depth = 0;
}

std::vector<AstNodeType> HelperTraverser::traverseGetPreOrder(IAstNode *root) {
    init();
    root->acceptCommonVisitor(*this);
    return preOrderNodes;
}

std::string HelperTraverser::traverseTreeString(IAstNode *root) {
    init();
    root->acceptCommonVisitor(*this);
    return treeString;
}

void HelperTraverser::startVisit(IAstNode *node) {
    if (!moreThanOne.top() and depth != 0){
        for (int i = 0; i < depth-1; i++)
            treeString += "|\t";
        treeString += "{\n";

        moreThanOne.top() = true;

    }
    for (int i = 0; i < depth; i++)
        treeString += "|\t";
    if(!tmpAddString.empty())
        tmpAddString = " <" + tmpAddString  + ">";
    treeString += astNodeTypeToString(node->getNodeType()) + tmpAddString;
    treeString += "\n";

    depth++;
    moreThanOne.push(false);
}

void HelperTraverser::endVisit(IAstNode *node) {

    depth--;
    if (moreThanOne.top()) {
        for (int i = 0; i < depth; i++)
            treeString += "|\t";
        treeString += "}\n";
    }
    moreThanOne.pop();

    preOrderNodes.push_back(node->getNodeType());
    tmpAddString.clear();
}

void HelperTraverser::updateTmpAddString(IExpression *exPtr) {
    if (evaluateExpressions)
        tmpAddString = expressionEvaluator.evaluateExpressionToString(exPtr);
}

void HelperTraverser::visit(AddExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(SubtractExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(AndExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(EqualExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(GreaterEqualExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(GreaterExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(LessEqualExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(LessExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(NotEqualExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(OrExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(FunctionCallExpression *node) {
//    updateTmpAddString(node);
    startVisit(node);
    for (const auto &operand: node->getRawArguments())
        operand->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(DivideExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(ModuloExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(MultiplyExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawLeftOperand()->acceptCommonVisitor(*this);
    node->getRawRightOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(EvaluateExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(MinusExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(NegateExpression *node) {
    updateTmpAddString(node);
    startVisit(node);
    node->getRawOperand()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(VariableReference *node) {
//    updateTmpAddString(node);
    startVisit(node);
    endVisit(node);
}

void HelperTraverser::visit(BooleanLiteral *node) {
    updateTmpAddString(node);
    startVisit(node);
    endVisit(node);
}

void HelperTraverser::visit(NumberLiteral *node) {
    updateTmpAddString(node);
    startVisit(node);
    endVisit(node);
}

void HelperTraverser::visit(StringLiteral *node) {
    updateTmpAddString(node);
    startVisit(node);
    endVisit(node);
}

void HelperTraverser::visit(Break *node) {
    startVisit(node);
    endVisit(node);
}

void HelperTraverser::visit(ConditionalStatementBlock *node) {
    startVisit(node);
    node->getRawCondition()->acceptCommonVisitor(*this);
    node->getRawStatementBlock()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(Continue *node) {
    startVisit(node);
    endVisit(node);
}

void HelperTraverser::visit(DeleteStatement *node) {
    startVisit(node);
    endVisit(node);
}

void HelperTraverser::visit(Exit *node) {
    startVisit(node);
    endVisit(node);
}

void HelperTraverser::visit(FunctionCallStatement *node) {
    startVisit(node);
    for (const auto &operand: node->getRawArguments())
        operand->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(FunctionDefinition *node) {
    startVisit(node);
    node->getRawFunctionBody()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(IfStatement *node) {
    startVisit(node);
    for (const auto &ifStatement: node->getRawIfStatements())
        ifStatement->acceptCommonVisitor(*this);
    if(node->hasElse())
        node->getRawElseStatement()->acceptCommonVisitor(*this);
    endVisit(node);

}

void HelperTraverser::visit(ReturnStatement *node) {
    startVisit(node);
    if (!node->isNullReturn())
        node->getRawReturnExpression()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(StatementBlock *node) {
    startVisit(node);
    for (const auto &statement: node->getRawStatements())
        statement->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(VariableAssignment *node) {
    startVisit(node);
    node->getRawValueExpression()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(VariableDefinition *node) {
    startVisit(node);
    node->getRawValueExpression()->acceptCommonVisitor(*this);
    endVisit(node);
}

void HelperTraverser::visit(WhileStatement *node) {
    startVisit(node);
    node->getRawWhileStatement()->acceptCommonVisitor(*this);
    endVisit(node);
}