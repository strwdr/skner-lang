#ifndef SKNER_TYPEDEFS_H
#define SKNER_TYPEDEFS_H

#include <memory>
#include <variant>
#include <map>
#include <string>
#include "ast/ast_nodes/NodesDeclarations.h"
#include "DataTypeVal.h"

typedef std::unique_ptr<IAstNode> UniNodePtr;
typedef std::unique_ptr<IExpression> UniExpressionPtr;
typedef std::unique_ptr<IStatement> UniStatementPtr;
typedef std::unique_ptr<BaseFunctionCall> UniFunctionCallPtr;
typedef std::variant<std::string, double, bool> ValueVariant;
typedef std::map<std::string, std::unique_ptr<FunctionDefinition>> FuncsMap;
typedef std::map<std::string, DataTypeVal> VarsMap;

#endif //SKNER_TYPEDEFS_H
