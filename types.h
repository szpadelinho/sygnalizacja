#ifndef SYGNALIZACJA_TYPES_H
#define SYGNALIZACJA_TYPES_H
#include <stdbool.h>

#define MAX_ENTRIES 4
#define MAX_TRAFFIC_LIGHTS 4
#define MAX_LANES 1
#define MAX_CARS_IN_QUEUE 20
#define MAX_STEPS 60

#define RED_TIME 3
#define YELLOW_START_TIME 1
#define YELLOW_END_TIME 2
#define GREEN_TIME 24

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

typedef enum {
    PHASE_ALL_RED,
    PHASE_NS_YELLOW_WE_RED,
    PHASE_NS_GREEN_WE_RED,
    PHASE_NS_RED_WE_YELLOW,
    PHASE_NS_RED_WE_GREEN
} TrafficPhase;

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
    TARGA,
    CAR_TYPE_COUNTER
} CarType;

typedef enum {
    RED,
    YELLOW,
    GREEN
} Lights;

typedef struct {
    int ID;
    Direction direction; //direction to entry
    Direction location;  //location in entry
    CarType type;
    bool privileged;
} Car;

typedef struct {
    Direction location;
    Car* cars;
    int size;
} Queue;

typedef struct {
    Direction location;
    Queue queue;
} Entry;

typedef struct {
    Direction location;  //where is
    Direction direction; //where to
    Lights color;
} TrafficLight;

typedef struct {
    TrafficLight* lights;
    Entry* entries;
    Car* carsOnIntersection;
    int currentStep;
} Intersection;

typedef struct {
    bool isPrivileged;
    CarType carType;
} PrivilegeDeterminator;

#endif //SYGNALIZACJA_TYPES_H
