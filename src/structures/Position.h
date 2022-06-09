#ifndef SKNER_POSITION_H
#define SKNER_POSITION_H


struct Position {
    unsigned int row = 1, column = 0;

    [[nodiscard]] std::string msg() const {
        std::string msg = "[row: " + std::to_string(row) + ", col: " + std::to_string(column) + "]";
        return msg;
    }
};


#endif //SKNER_POSITION_H
