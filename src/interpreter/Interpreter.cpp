#include "Interpreter.h"

bool Interpreter::streamReadLoop() {
    while (auto stmt = parser.parseProgramStatement()) {
        if(!evaluator.executeProgramStatement(stmt.get())) break;
    }
    return true;
}

int Interpreter::run() {
    ErrorHandlerMode errorHandlerMode;
    switch (streamProvider.getReaderMode()) {
        case FILE_READER:
            errorHandlerMode = STOP_AFTER_CATCH;
            break;
        case CONSOLE_READER:
            errorHandlerMode = RETRY_AFTER_CATCH;
            break;
        default:
            errorHandlerMode = STOP_AFTER_CATCH;
            break;
    }
    ErrorHandler errorHandler(std::bind(&Interpreter::streamReadLoop, this),
                              errorHandlerMode,
                              evaluator,
                              streamProvider,
                              parser);
    return errorHandler.run();
}

Interpreter::Interpreter(StreamProvider &streamProvider) :
        streamProvider(streamProvider),
        evaluator(std::cin, std::cout),
        parser(streamProvider.getStream()) {}