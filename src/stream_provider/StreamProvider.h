#ifndef SKNER_STREAMPROVIDER_H
#define SKNER_STREAMPROVIDER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../error_handler/exeptions/StreamProviderExeption.h"
#include <limits>

enum ReaderMode {
    SS_MODE,
    FILE_READER,
    CONSOLE_READER,
};


class StreamProvider {
public:
    StreamProvider(std::stringstream *sstream) : readerMode(SS_MODE) {
        this->stream = sstream;
    }

    void resetStream() {
        if (readerMode == CONSOLE_READER) {
            //            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //            stream = &std::cin;
        } else {
            throw StreamProviderException("stream can be reset only in console reader mode");
        }
    }

    StreamProvider(ReaderMode readerMode, const char *srcFilename) : readerMode(readerMode) {
        // select stream
        switch (readerMode) {
            case SS_MODE:
                throw StreamProviderException("invalid initialization of SS_MODE");
            case CONSOLE_READER:
                std::cout << "--- Skner interpreter ---" << std::endl;
                stream = &std::cin;
                break;
            case FILE_READER:
//                std::cout << "--- Running Skner in file interpretation mode ---" << std::endl;
                fileStream = new std::fstream();
                fileStream->open(srcFilename, std::ios::in);
                if (!(*fileStream)) {
                    throw StreamProviderException("file " + std::string(srcFilename) + " does not exist");
                }
                stream = fileStream;
        }
    }

    ~StreamProvider() {
        if (readerMode == FILE_READER) {
            fileStream->close();
            delete stream;
        }
    }

    [[nodiscard]] std::istream &getStream() const {
        return *stream;
    }

    [[nodiscard]] ReaderMode getReaderMode() const {
        return readerMode;
    }

private:
    std::istream *stream;
    std::fstream *fileStream = nullptr;

    ReaderMode readerMode;
};


#endif //SKNER_STREAMPROVIDER_H
