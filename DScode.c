#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROAD_LENGTH 100  // Length of the road
#define MAX_SPEED 299    // Maximum speed limit
#define NUM_VEHICLES 5   // Number of vehicles on the road

typedef struct {
	int position;
	int speed;
	char symbol; // Symbol to represent the vehicle
} VehicleData;

typedef struct {
	int vehicle_id;
	VehicleData data;
} Vehicle;

void initializeVehicles(Vehicle vehicles[]) {
	char symbols[] = {'A', 'B', 'C', 'D', 'E'};
   
	printf("Enter initial positions and speeds for %d vehicles:\n", NUM_VEHICLES);
	for (int i = 0; i < NUM_VEHICLES; i++) {
		printf("Vehicle %d:\n", i + 1);
		printf("Position: ");
		scanf("%d", &vehicles[i].data.position);
		printf("Speed: ");
		scanf("%d", &vehicles[i].data.speed);
// Validate speed input
		if (vehicles[i].data.speed < 0 || vehicles[i].data.speed > MAX_SPEED) {
		printf("Invalid speed input! Speed should be between 0 and %d.\n", MAX_SPEED);
			exit(1);
		}
		vehicles[i].vehicle_id = i + 1;
		vehicles[i].data.symbol = symbols[i];
	}
}

void updateVehiclePositions(Vehicle vehicles[]) {
	for (int i = 0; i < NUM_VEHICLES; i++) {
		vehicles[i].data.position += vehicles[i].data.speed;
		if (vehicles[i].data.position >= ROAD_LENGTH)
			vehicles[i].data.position = 0;  // Start over if reached the end of the road
	}
}

void displayRoadStatus(Vehicle vehicles[]) {
	printf("Road Status:\n");
	for (int i = 0; i < ROAD_LENGTH; i++) {
		char symbol = '-';
		for (int j = 0; j < NUM_VEHICLES; j++) {
			if (vehicles[j].data.position == i) {
				symbol = vehicles[j].data.symbol;  // Use vehicle symbol
				break;
			}
		}
		printf("%c", symbol);
	}
	printf("\n");
}

int main() {
	Vehicle vehicles[NUM_VEHICLES];

	initializeVehicles(vehicles);

	while (1) {
		system("clear");  // Clear screen for better visualization (works on Unix-like systems)
		updateVehiclePositions(vehicles);
		displayRoadStatus(vehicles);

		usleep(500000);  // Sleep for 0.5 seconds
	}

	return 0;
}
