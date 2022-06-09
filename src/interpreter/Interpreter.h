#ifndef SKNER_INTERPRETER_H
#define SKNER_INTERPRETER_H

#include "../error_handler/ErrorHandler.h"
#include <iostream>
#include <string>
#include <fstream>
#include "../error_handler/ErrorHandlerMode.h"
#include "../stream_provider/StreamProvider.h"
#include "../parser/Parser.h"
#include "Evaluator.h"

class Interpreter {
public:
    explicit Interpreter(StreamProvider &streamProvider);

    bool streamReadLoop();

    int run();

private:
    StreamProvider & streamProvider;
    Parser parser;
    Evaluator evaluator;
};


#endif //SKNER_INTERPRETER_H
