#include "interpreter/Interpreter.h"
#include "stream_provider/StreamProvider.h"
#include <iostream>



int main(int argc, char **argv) {
    ReaderMode readerMode = CONSOLE_READER;
    char *srcFilename;

    // parse arguments
    if (argc >= 2) {
        readerMode = FILE_READER;
        srcFilename = argv[1];
    }

    StreamProvider streamProvider(readerMode, srcFilename);

    auto interpreter = Interpreter(streamProvider);

    return interpreter.run();
}
