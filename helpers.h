#ifndef SYGNALIZACJA_HELPERS_H
#define SYGNALIZACJA_HELPERS_H
#include "helpers.h"

const char* getDirectionName(Direction d) {
    static const char* directionNames[] = {
        "NORTH",
        "EAST",
        "SOUTH",
        "WEST",
    };

    if (d < NORTH || d > WEST) return "UNKNOWN";

    return directionNames[d];
}

const char* getColorName(Lights color) {
    static const char* colorNames[] = {
        "RED",
        "YELLOW",
        "GREEN"
    };

    if (color < RED || color > GREEN) return "UNKNOWN";

    return colorNames[color];
}

Direction getCarDirection(Direction direction) {
    return (Direction)((direction + 2) % 4);
}

PrivilegeDeterminator isCarPrivileged() {
    PrivilegeDeterminator determinator;
    determinator.isPrivileged = rand() % 2 == 0;
    if (determinator.isPrivileged) {
        determinator.carType = rand() % 4;
    }
    else {
        determinator.carType = rand() % (CAR_TYPE_COUNTER - 4 + 1) + 4;
    }
    return determinator;
}

TrafficPhase getCurrentTrafficPhase(int step) {
    int currentBound = 0;

    currentBound = currentBound + RED_TIME;
    if (step < currentBound) return PHASE_ALL_RED;

    currentBound = currentBound + YELLOW_START_TIME;
    if (step < currentBound) return PHASE_NS_YELLOW_WE_RED;

    currentBound = currentBound + GREEN_TIME;
    if (step < currentBound) return PHASE_NS_GREEN_WE_RED;

    currentBound = currentBound + YELLOW_END_TIME;
    if (step < currentBound) return PHASE_NS_YELLOW_WE_RED;

    currentBound = currentBound + RED_TIME;
    if (step < currentBound) return PHASE_ALL_RED;

    currentBound = currentBound + YELLOW_START_TIME;
    if (step < currentBound) return PHASE_NS_RED_WE_YELLOW;

    currentBound = currentBound + GREEN_TIME;
    if (step < currentBound) return PHASE_NS_RED_WE_GREEN;

    currentBound = currentBound + YELLOW_END_TIME;
    if (step < currentBound) return PHASE_NS_RED_WE_YELLOW;

    return PHASE_ALL_RED;
}

#endif //SYGNALIZACJA_HELPERS_H
