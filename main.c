#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "helpers.h"

void addToQueue(Queue *queue, Car car) {
    if (queue->size >= MAX_CARS_IN_QUEUE) {
        perror("ERROR: Exceeded the size of Queue");
        return;
    }
    if (queue == NULL) {
        perror("ERROR: Queue is NULL.");
        exit(EXIT_FAILURE);
    }
    queue->cars[queue->size] = car;
    queue->size++;
}

void deleteFromQueue(Queue *queue) {
    for (int i = 1; i < queue->size; i++) {
        queue->cars[i - 1] = queue->cars[i];
    }
    queue->size--;
}

Car initCar() {
    PrivilegeDeterminator determinator = isCarPrivileged();
    static int ID = 0;
    Direction random = (Direction)rand() % 4;
    Car car;
    car.ID = ID++;
    car.direction = getCarDirection(random);
    car.location = random;
    car.privileged = determinator.isPrivileged;
    car.type = determinator.carType;
    return car;
}

Queue initQueue(Direction location) {
    Queue queue;
    queue.location = location;
    queue.cars = malloc(sizeof(Car) * MAX_CARS_IN_QUEUE);
    if (queue.cars == NULL) perror("ERROR: Cannot allocate memory for queue.cars.");
    queue.size = 0;
    return queue;
}

Entry* initEntries() {
    Entry* entries = malloc(sizeof(Entry) * MAX_ENTRIES);
    if (entries == NULL) return NULL;
    for (int i = 0; i < MAX_ENTRIES; i++) {
        Direction location = (Direction)i;
        entries[i].location = location;
        entries[i].queue = initQueue(location);
    }
    return entries;
}

TrafficLight* initTrafficLights() {
    TrafficLight* lights = malloc(sizeof(TrafficLight) * MAX_TRAFFIC_LIGHTS);
    if (lights == NULL) return NULL;
    for (int i = 0; i < MAX_TRAFFIC_LIGHTS; i++) {
        switch (i) {
            case NORTH:
                lights[i].location = NORTH;
                lights[i].direction = SOUTH;
                break;
            case EAST:
                lights[i].location = EAST;
                lights[i].direction = WEST;
                break;
            case SOUTH:
                lights[i].location = SOUTH;
                lights[i].direction = NORTH;
                break;
            case WEST:
                lights[i].location = WEST;
                lights[i].direction = EAST;
                break;
            default:
                perror("ERROR: Cannot set TrafficLights attributes.");
                return NULL;
        }
        lights[i].color = RED;
    }
    return lights;
}

Intersection initIntersection() {
    Intersection intersection;
    intersection.lights = initTrafficLights();
    if (intersection.lights == NULL) {
        perror("ERROR: Cannot initialize lights for object Intersection.");
        exit(EXIT_FAILURE);
    }
    intersection.carsOnIntersection = malloc(sizeof(Car) * MAX_CARS_IN_QUEUE);
    intersection.entries = initEntries();
    if (intersection.entries == NULL) {
        perror("ERROR: Cannot initialize entries for object Intersection.");
        exit(EXIT_FAILURE);
    }
    intersection.currentStep = 0;

    return intersection;
}

void print(Intersection *intersection) {
    int step = intersection->currentStep;
    printf("%s (N-S), %s (W-E) --> STEP %d\n", getColorName(intersection->lights[0].color), getColorName(intersection->lights[1].color), step);
}

void setTrafficLights(Intersection *intersection, Lights NSColor, Lights WEColor) {
    for (int i = 0; i < MAX_TRAFFIC_LIGHTS; i++) {
        if (intersection->lights[i].location == NORTH || intersection->lights[i].location == SOUTH) {
            intersection->lights[i].color = NSColor;
        }
        else {
            intersection->lights[i].color = WEColor;
        }
    }
}

void updateTrafficLights(Intersection *intersection) {
    int step = intersection->currentStep;
    TrafficPhase phase = getCurrentTrafficPhase(step);
    getCurrentTrafficPhase(phase);
    switch (phase) {
        case PHASE_ALL_RED:
            setTrafficLights(intersection, RED, RED);
            break;
        case PHASE_NS_YELLOW_WE_RED:
            setTrafficLights(intersection, YELLOW, RED);
            break;
        case PHASE_NS_GREEN_WE_RED:
            setTrafficLights(intersection, GREEN, RED);
            break;
        case PHASE_NS_RED_WE_YELLOW:
            setTrafficLights(intersection, RED, YELLOW);
            break;
        case PHASE_NS_RED_WE_GREEN:
            setTrafficLights(intersection, RED, GREEN);
            break;
        default:
            perror("ERROR: Invalid traffic phase.");
            setTrafficLights(intersection, RED, RED);
            break;
    }
}

static void executeStep(Intersection *intersection) {
    int currentStep = intersection->currentStep;

    if (currentStep < 0 || currentStep >= 60) {
        perror("ERROR: Current simulation step is out of range.");
        return;
    }

    updateTrafficLights(intersection);

    intersection->currentStep++;
}

Intersection runSimulation(Intersection *intersection) {
    while (intersection->currentStep < 60) {
        print(intersection);
        executeStep(intersection);
    }
}

int executeCommand(Intersection *intersection) {
    char c;
    scanf(" %c", &c);
    switch (c) {
        case 'X': case 'x':
            return 0;
        case 'C': case 'c': {
            Car car = initCar();
            addToQueue(&intersection->entries[(int)car.direction].queue, car);
            break;
        }
        case 'S': case 's':
            runSimulation(intersection);
            break;
        case 'P': case 'p':
            print(intersection);
            break;
        default:
            perror("ERROR: Invalid command.");
            break;
    }
    return 1;
}

int main(void) {
    srand(time(NULL));
    Intersection intersection = initIntersection();
    while (executeCommand(&intersection));
    return 0;
}