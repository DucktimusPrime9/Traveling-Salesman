/**Author**///: Guadalupe Delgado
/**Problem**///: (User input) given a list of cities and the distances between each city,
//what is the shortest possible route that visits each city and returns to the original city.
/**PURPOSE**///: Project for CSC350 and also figuring out a way to best work out the TSP problem
/** METHOD(S)**///: Permuting
/** HELP RECEIVED**///I received help from Dr. Toth.
/** REFERENCES**/ //http://www.cplusplus.com/reference/algorithm/next_permutation/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "omp.h"

#define NUM_CITIES 7

using namespace std; // package space we are using

// define this later; tells c compiler that you will use this later. Prototype.
void fillArray(int costs[NUM_CITIES][NUM_CITIES]);
void printArray(int costs[NUM_CITIES][NUM_CITIES]);
void printCities(int arrCities[NUM_CITIES]);

int main() {
    int row, col, index, bestCost;
    //To check if program is starting
    printf("Traveling salesman program started!\n");
    // 2D array of costs
    int costs[NUM_CITIES][NUM_CITIES];
    //Array of cities
    int arrCities[NUM_CITIES];
    //NEW ADDITION
    int bestTour[NUM_CITIES];
    /////////////////////////////////////////////////////////


    // Fill array of cities
    for (index = 0; index < NUM_CITIES; index++) {
        arrCities[index] = index;
    }

    // Fill the array of costs
    fillArray(costs);
    //printArray(costs);


    //For each possible tour we're going to print the tour and the cost
    //printCities(arrCities);
    // Calculate cost of tour
    //FIND BEST TOUR
    for (index = 0; index < NUM_CITIES; index++) {
        bestTour[index] = arrCities[index];
        printf("%d ", bestTour[index]);

    }
    printf("\n");

    //FIND BEST COST
    int cost = 0;
    for (index = 0; index < NUM_CITIES; index++) {
        int src = arrCities[index];
        int dest = arrCities[(index + 1) % NUM_CITIES];

        cost = cost + costs[src][dest];

    }
    bestCost = cost;




    //Next permutation

    while (next_permutation(arrCities, arrCities + NUM_CITIES)) {
        printCities(arrCities);
        // Now find the cost between each city pair and update!
        cost = 0;
        for (index = 0; index < NUM_CITIES; index++) {
            int src = arrCities[index];
            int dest = arrCities[(index + 1) % NUM_CITIES];

            cost = cost + costs[src][dest];

        }

        printf("%d\n======================\n", cost);
        //FINDING OUT BEST COST
        if (cost < bestCost) {
            bestCost = cost;
            for (index = 0; index < NUM_CITIES; index++) {
                bestTour[index] = arrCities[index];
                //printf("%d ", bestTour[index]);

            }
            //printf("%d ", bestCost);

        }

    }// end while next perm
    printf("The best cost is: %d ", bestCost);
    printf("The best tour is: ");
    for (index = 0; index < NUM_CITIES; index++) {

        printf("%d ", bestTour[index]);

    }
    printf("\n");


    return 0;
}

void fillArray(int costs[NUM_CITIES][NUM_CITIES]) {
    int row, col;
    FILE *fp;
    fp = fopen("test7cities.txt", "r");

    if (fp == NULL) {
        printf("Input file was not found\n");
    }

    for (row = 0; row < NUM_CITIES; row++) {
        for (col = 0; col < NUM_CITIES; col++) {
            fscanf(fp, "%d", &costs[row][col]);
            // To see output
            //printf("%d\t", holdMACosts[row][col]);
        }

    }
    fclose(fp);
}

void printArray(int costs[NUM_CITIES][NUM_CITIES]) {
    int row, col;
    for (row = 0; row < NUM_CITIES; row++) {
        for (col = 0; col < NUM_CITIES; col++) {
            printf("%d ", costs[row][col]);
        }
        printf("\n");
    }
}

void printCities(int arrCities[NUM_CITIES]) {
    int index;

    for (index = 0; index < NUM_CITIES; index++) {
        printf("%d ", arrCities[index]);
    }
    printf("\n");
}