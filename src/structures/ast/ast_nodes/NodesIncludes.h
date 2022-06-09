#ifndef SKNER_NODESINCLUDES_H
#define SKNER_NODESINCLUDES_H

#include "virtual/IAstNode.h"
#include "virtual/IStatement.h"
#include "virtual/IExpression.h"
#include "common/BaseFunctionCall.h"

#include "expressions/logical/AndExpression.h"
#include "expressions/logical/EqualExpression.h"
#include "expressions/logical/OrExpression.h"
#include "expressions/logical/GreaterEqualExpression.h"
#include "expressions/logical/GreaterExpression.h"
#include "expressions/logical/LessEqualExpression.h"
#include "expressions/logical/LessExpression.h"
#include "expressions/logical/NotEqualExpression.h"

#include "expressions/VariableReference.h"
#include "expressions/BooleanLiteral.h"
#include "expressions/NumberLiteral.h"
#include "expressions/StringLiteral.h"
#include "expressions/FunctionCallExpression.h"

#include "expressions/additive/SubtractExpression.h"
#include "expressions/additive/AddExpression.h"

#include "expressions/multiplicative/DivideExpression.h"
#include "expressions/multiplicative/ModuloExpression.h"
#include "expressions/multiplicative/MultiplyExpression.h"

#include "expressions/unary/EvaluateExpression.h"
#include "expressions/unary/MinusExpression.h"
#include "expressions/unary/NegateExpression.h"

#include "statements/Break.h"
#include "statements/ConditionalStatementBlock.h"
#include "statements/Continue.h"
#include "statements/DeleteStatement.h"
#include "statements/Exit.h"
#include "statements/FunctionCallStatement.h"
#include "statements/FunctionDefinition.h"
#include "statements/IfStatement.h"
#include "statements/ReturnStatement.h"
#include "statements/StatementBlock.h"
#include "statements/VariableAssignment.h"
#include "statements/VariableDefinition.h"
#include "statements/WhileStatement.h"


#endif //SKNER_NODESINCLUDES_H
