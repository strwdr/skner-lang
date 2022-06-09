#ifndef SKNER_INTERPRETERHELPERS_H
#define SKNER_INTERPRETERHELPERS_H

#include <iomanip>
#include "../error_handler/exeptions/InterpreterExeption.h"

namespace helpers {
    struct AnyGetString {
        std::string operator()(bool value) { return value ? "true" : "false"; }

        std::string operator()(double value) {
            std::stringstream ss;
            ss << std::setprecision(15) << value;
            return ss.str();
        }

        std::string operator()(const std::string &value) { return value; }
    };

    static std::string valueVariantToString(const ValueVariant &input) {
        return std::visit(AnyGetString{}, input);
    }

    struct AnyGetNumber {
        double operator()(bool value) { return value ? 1 : 0; }

        double operator()(double value) {
            return value;
        }

        double operator()(const std::string &value) {
            try {
                return std::stod(value);
            }
            catch (std::invalid_argument &e) {
                throw InterpreterException("cannot cast " + value + " to number");
            }
        }
    };

    static double valueVariantToNumber(const ValueVariant &input) {
        return std::visit(AnyGetNumber{}, input);
    }

    struct AnyGetBoolean {
        bool operator()(bool value) { return value; }

        bool operator()(double value) {
            return value > 0;
        }

        bool operator()(const std::string &value) {
            return value == "true";
        }
    };

    static bool valueVariantToBoolean(const ValueVariant &input) {
        return std::visit(AnyGetBoolean{}, input);
    }

    struct BinaryExpressionEvaluationOutput {
        ValueVariant leftValue{};
        ValueVariant rightValue{};
        DataType dataType{};
    };

    struct ReturnToHandleValue {
        DataType dataType = UNDEFINED;
        ValueVariant returnValue{};
    };
}
#endif //SKNER_INTERPRETERHELPERS_H
