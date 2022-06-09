#ifndef SKNER_INTERRUPTIONS_H
#define SKNER_INTERRUPTIONS_H

enum InterruptionType {
    NONE,
    BREAK,
    CONTINUE,
    RETURN,
    EXIT,
};

static bool isInterruption(InterruptionType type) {
    return type != NONE;
}

static std::string interruptionToString(InterruptionType type) {
    switch(type){
        case NONE:
            return "NONE";
        case BREAK:
            return "break";
        case CONTINUE:
            return "continue";
        case RETURN:
            return "return";
        case EXIT:
            return "exit";
    }
    throw std::exception();
}

#endif //SKNER_INTERRUPTIONS_H
