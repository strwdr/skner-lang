#include "ErrorHandler.h"
#include "exeptions/InterpreterExeption.h"
#include "exeptions/ParserException.h"

int ErrorHandler::run() {
    while (true) {
        try {
            if (streamReadLoop()) break;
        }
        catch (const LexerException &e) {
            handleException(e);
        }
        catch (const ParserException &e) {
            handleException(e);
        }
        catch (const InterpreterException &e) {
            handleException(e);
        }
        if (mode == STOP_AFTER_CATCH) return 1;
    }
    return 0;
}

void ErrorHandler::handleException(const ISknerException &e) {
    std::cout << e.getInfo() << std::endl;
    if (streamProvider.getReaderMode() == CONSOLE_READER) {
        evaluator.resetToGlobalScope();
        parser.skipToNextNewline();
    }
}