#include <iostream>
#include "elevator.h"

int main() {
    // Create an elevator system with 5 floors
    Elevator elevator(5);

    // Simulate some external requests
    elevator.handleExternalRequest(ExternalRequest(1, Direction::kUp));   // Request to go up from floor 1
    elevator.handleExternalRequest(ExternalRequest(3, Direction::kDown));  // Request to go down from floor 3

    // Simulate internal requests
    elevator.insertButton(ElevatorButton(2, &elevator));  // Request to go to floor 2
    elevator.insertButton(ElevatorButton(4, &elevator));  // Request to go to floor 4

    // Open and close the elevator gate to see how it handles requests
    elevator.openGate();
    elevator.closeGate();
    elevator.openGate();
    elevator.closeGate();

    return 0;
}
