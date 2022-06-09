#ifndef SKNER_SSPARSER_H
#define SKNER_SSPARSER_H

#include <sstream>
#include "../../parser/Parser.h"
#include "../../stream_provider/StreamProvider.h"
#include "../../structures/ast/ast_visitor/HelperTraverser.h"

class SsParser : public Parser {
private:
    std::stringstream stream;
    HelperTraverser *traverser;
public:
    explicit SsParser(const std::string &testText = "", bool evaluateExpressions = false) : Parser(stream) {
        stream << testText;
        traverser = new HelperTraverser(evaluateExpressions);
    }

    std::vector<AstNodeType> getPreOrderParsedProgramStatement() {
        return traverser->traverseGetPreOrder(parseProgramStatement().get());
    }

    void printProgramStatementTree() const {
        std::cout << traverser->treeString;
    }

    std::ostream &operator<<(const std::string &a) {
        return stream << a;
    }
};


#endif //SKNER_SSPARSER_H
