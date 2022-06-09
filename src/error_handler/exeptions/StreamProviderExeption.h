#ifndef SKNER_STREAMPROVIDEREXCEPTION_H
#define SKNER_STREAMPROVIDEREXCEPTION_H

#include "ISknerException.h"

class StreamProviderException : public ISknerException {
public:
    explicit StreamProviderException(const std::string &msg) : ISknerException(msg) {};

    [[nodiscard]] std::string getInfo() const override {
        return std::string("stream provider error: " + msg);
    }
};

#endif //SKNER_STREAMPROVIDEREXCEPTION_H
