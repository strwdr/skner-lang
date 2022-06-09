#ifndef SKNER_PARSERTESTSHELPERS_H
#define SKNER_PARSERTESTSHELPERS_H

#include <list>
#include "../../structures/ast/AstNodeType.h"
#include "SsParser.h"
#include "SsLexer.h"
#include "SsEvaluator.h"

template<class T>
static bool checkPreOrder(T calculated, T expected) {
    if (calculated.size() != expected.size()) return false;
    auto it1 = calculated.begin();
    auto it2 = expected.begin();
    while (it1 != calculated.end() && it2 != expected.end()) {
        if (*it1 != *it2) {
            return false;
        } else {
            it1++;
            it2++;
        }
    }
    return true;
}

static void printAstNodeTypeArr(std::vector<AstNodeType> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << astNodeTypeToString(arr[i]);
        if (i != arr.size() - 1) std::cout << ",";
    }
    std::cout << "]";
}

#endif //SKNER_PARSERTESTSHELPERS_H
