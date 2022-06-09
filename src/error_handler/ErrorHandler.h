#ifndef SKNER_ERRORHANDLER_H
#define SKNER_ERRORHANDLER_H

#include <functional>
#include <utility>
#include "exeptions/LexerException.h"
#include "ErrorHandlerMode.h"
#include "../interpreter/Evaluator.h"
#include "../parser/Parser.h"


class ErrorHandler {
public:
    explicit ErrorHandler(std::function<bool(void)> streamReadLoop,
                          ErrorHandlerMode mode,
                          Evaluator &evaluator,
                          StreamProvider &streamProvider,
                          Parser &parser) :
            streamReadLoop(std::move(streamReadLoop)),
            mode(mode),
            streamProvider(streamProvider),
            parser(parser),
            evaluator(evaluator) {} //error handler is initialized with main streamReadLoop
    int run();

private:
    void handleException(const ISknerException &e);

    ErrorHandlerMode mode;

    std::function<bool(void)> streamReadLoop;

    Evaluator &evaluator;

    Parser &parser;

    StreamProvider &streamProvider;
};

#endif //SKNER_ERRORHANDLER_H
