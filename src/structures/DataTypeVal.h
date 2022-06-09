#ifndef SKNER_DATATYPEVAL_H
#define SKNER_DATATYPEVAL_H

#include "ast/Datatypes.h"
#include <variant>
#include <string>

struct DataTypeVal {
    DataType type{};
    std::variant<std::string, double, bool> value{};
};

#endif //SKNER_DATATYPEVAL_H
