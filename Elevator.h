#ifndef ELEVATOR_H       // Include Guard Opening
#define ELEVATOR_H       // defining a macro
#include <bits/stdc++.h> //All essential libraries
using namespace std;
#include "request.h" //self-declared header for customised elevator requests
                     // forward declarationS
class Elevator;
class ExternalRequest;
class InternalRequest;
// Enum class for elevator status
enum class Status
{
    kUp = 0,
    kDown = 1,
    kIdle = 2,
};
// ElevatorButton Class Definition
class ElevatorButton
{
private:
    int level = 0;                // The floor level associated with this button
    Elevator *elevator = nullptr; // A pointer to the associated Elevator object.

public:
    // Constructor to initialize button with a level and associated elevator
    ElevatorButton(int l, Elevator *e) : level(l), elevator(e) {}
    // Function to handle button press event
    void pressButton();
};

// Class representing the Elevator itself
class Elevator
{
private:
    vector<ElevatorButton> buttons_; // List of elevator buttons
    vector<bool> up_stops_;          // Stops for going up
    vector<bool> down_stops_;        // Stops for going down
    int current_level_;              // Current level of the elevator
    Status status_;                  // Current status of the elevator

public:
    // Constructor to initialize the elevator with a number of floors
    Elevator(int n);
    // Function to insert a new button into the elevator
    void insertButton(ElevatorButton eb);
    // Handle external requests (e.g., from outside the elevator)
    void handleExternalRequest(ExternalRequest r);
    // Handle internal requests (e.g., from inside the elevator)
    void handleInternalRequest(InternalRequest r);
    // Open the elevator gate
    void openGate();
    // Close the elevator gate
    void closeGate();
    // Check if there are no requests for the given stops
    bool noRequests(const vector<bool> &stops);
    // Get the current status information of the elevator
    string getElevatorStatusInfo() const;
    // Get the list of requests made to the elevator
    string getElevatorRequestListInfo() const;
    // Accessor for the elevator status
    Status getStatus() const { return status_; }
    // Accessor for the current level of the elevator
    int getCurLevel() const { return current_level_; }
};

#endif /* ELEVATOR_H */ // Include Guard Closing
