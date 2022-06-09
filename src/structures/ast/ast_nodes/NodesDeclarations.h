#ifndef SKNER_NODESDECLARATIONS_H
#define SKNER_NODESDECLARATIONS_H

// virtual
class IBinaryExpression;
class IAstNode;
class IStatement;
class BaseFunctionCall;
class IExpression;

// base expressions
class FunctionCallExpression;
class VariableReference;
class BooleanLiteral;
class NumberLiteral;
class StringLiteral;
// additive expressions
class SubtractExpression;
class AddExpression;
// logical expressions
class AndExpression;
class EqualExpression;
class OrExpression;
class GreaterEqualExpression;
class GreaterExpression;
class LessEqualExpression;
class LessExpression;
class NotEqualExpression;
// multiplicative expressions
class DivideExpression;
class ModuloExpression;
class MultiplyExpression;
// unary expressions
class EvaluateExpression;
class MinusExpression;
class NegateExpression;
// statements
class Break;
class ConditionalStatementBlock;
class Continue;
class Exit;
class FunctionCallStatement;
class FunctionDefinition;
class IfStatement;
class ReturnStatement;
class StatementBlock;
class VariableAssignment;
class VariableDefinition;
class WhileStatement;
class DeleteStatement;


#endif //SKNER_NODESDECLARATIONS_H
