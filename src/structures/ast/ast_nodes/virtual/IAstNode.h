#ifndef SKNER_IASTNODE_H
#define SKNER_IASTNODE_H

#include <memory>
#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "../../AstNodeType.h"
#include "../../ast_visitor/ICommonVisitor.h"
#include "../../../Typedefs.h"

class IAstNode{
public:

    [[nodiscard]] virtual AstNodeType getNodeType() const = 0;

    virtual void acceptCommonVisitor(ICommonVisitor &visitor) = 0;
};

#endif //SKNER_IASTNODE_H