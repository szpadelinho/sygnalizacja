#include <stdbool.h>
#include <stdio.h>
#define MAX_ENTRIES 4
#define MAX_TRAFFIC_LIGHTS 4

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

typedef enum {
    MILITARY,
    SERVICE,
    MINI_TRUCK,
    TRUCK,
    SEDAN,
    COUPE,
    HATCHBACK,
    SUV,
    VAN,
    SPORT,
    HYPER,
    MICRO,
    CONVERTIBLE,
    OFF_ROAD,
    CROSSOVER,
    WAGON,
    MUSCLE,
    ROADSTER,
    MINIVAN,
    MINIBUS,
    BUS,
    TARGA
} CarType;

typedef enum {
    RED = 3,
    YELLOW = 1,
    GREEN = 24
} Lights;

typedef struct {
    int ID;
    Direction dir;
    CarType type;
    bool privileged;
    int arrivalStep;
} Car;

typedef struct {
    Direction direction;
    int lanes;
} Entry;

typedef struct {
    Direction location;
    Car cars[];
} Queue;

typedef struct {
    Direction location;
    Direction direction;
} TrafficLight;

typedef struct {
    TrafficLight lights[MAX_TRAFFIC_LIGHTS];
    Entry entries[MAX_ENTRIES];
    int currentStep;
    int maxSteps;
} Intersection;

int main(void) {
    int step = 0;
    while (step <= 60) {
        if (step == 0) {
            int current_step = step;
            step += RED;

            printf("RED (N-S), RED (W-S):  (%d - %d) \n", current_step, step);
        }
        if (step == 3) {
            int current_step = step;
            step += YELLOW;

            printf("YELLOW (R->G) (N-S), RED (W-S):  (%d - %d) \n", current_step, step);
        }
        if (step == 4) {
            int current_step = step;
            step += GREEN;

            printf("GREEN (N-S), RED (W-S):  (%d - %d) \n", current_step, step);
        }
        if (step == 28) {
            int current_step = step;
            step += YELLOW + 1;

            printf("YELLOW (N-S), RED (W-S):  (%d - %d) \n", current_step, step);
        }
        if (step == 30) {
            int current_step = step;
            step += RED;

            printf("RED (N-S), RED (W-S):  (%d - %d) \n", current_step, step);
        }
        if (step == 33) {
            int current_step = step;
            step += YELLOW;

            printf("RED (N-S), YELLOW (R->G) (W-S):  (%d - %d) \n", current_step, step);
        }
        if (step == 34) {
            int current_step = step;
            step += GREEN;

            printf("RED (N-S), GREEN (W-S):  (%d - %d) \n", current_step, step);
        }
        if (step == 58) {
            int current_step = step;
            step += YELLOW + 1;

            printf("RED (N-S), YELLOW (G->R) (W-S):  (%d - %d) \n", current_step, step);
        }
    }
    return 0;
}