#include "elevator.h" // Include the header file for the Elevator class

// Constructor for the Elevator class, initializing member variables
Elevator::Elevator(int n) : current_level_(0),
                            status_(Status::kIdle),
                            up_stops_(n, false),   // Initialize up stop requests to false for n floors
                            down_stops_(n, false)   // Initialize down stop requests to false for n floors
{
    std::cout << "An elevator system with " << n << " floors has been initialized successfully!\n";
    std::cout << "**********************************************************************************************\n";
}

// Function to insert an ElevatorButton into the elevator's button list
void Elevator::insertButton(ElevatorButton eb)
{
    buttons_.push_back(eb);
}

// Function to handle external requests for the elevator
void Elevator::handleExternalRequest(ExternalRequest r)
{
    // Handle the external request to go Up
    if (r.getDirection() == Direction::kUp)
    {
        up_stops_[r.getLevel() - 1] = true; // Mark the requested level for Up direction
        if (noRequests(down_stops_))         // Check if there are no down requests
            status_ = Status::kUp;           // Set elevator status to Up
    }
    // Handle the external request to go Down
    else
    {
        down_stops_[r.getLevel() - 1] = true; // Mark the requested level for Down direction
        if (noRequests(up_stops_))              // Check if there are no up requests
            status_ = Status::kDown;            // Set elevator status to Down
    }

    // Demonstrate the state after handling the external request
    std::cout << this->getElevatorRequestListInfo();
}

// Function to handle internal requests for the elevator
void Elevator::handleInternalRequest(InternalRequest r)
{
    // If the elevator is going Up, mark the stop for the requested level
    if (status_ == Status::kUp)
    {
        if (r.getLevel() >= current_level_ + 1)
            up_stops_[r.getLevel() - 1] = true; // Only allow stops above the current level
    }
    // If the elevator is going Down, mark the stop for the requested level
    else if (status_ == Status::kDown)
    {
        if (r.getLevel() <= current_level_ + 1)
            down_stops_[r.getLevel() - 1] = true; // Only allow stops below the current level
    }

    // Demonstrate the state after handling the internal request
    std::cout << this->getElevatorRequestListInfo();
}

// Function to open the elevator gate
void Elevator::openGate()
{
    std::cout << "The elevator gate is open!\n";

    // If the elevator is moving Up
    if (status_ == Status::kUp)
    {
        for (int i = 0; i < up_stops_.size(); i++)
        {
            int check_level = (current_level_ + i) % up_stops_.size(); // Check levels in a circular manner
            if (up_stops_[check_level] == true) // If there's a stop at this level
            {
                current_level_ = check_level;    // Move to the stop level
                up_stops_[check_level] = false;   // Mark the stop as handled
                break; // Exit the loop after servicing one request
            }
        }
    }
    // If the elevator is moving Down
    else if (status_ == Status::kDown)
    {
        for (int i = 0; i < down_stops_.size(); i++)
        {
            int check_level = (current_level_ + down_stops_.size() - i) % down_stops_.size(); // Check levels in reverse
            if (down_stops_[check_level] == true) // If there's a stop at this level
            {
                current_level_ = check_level;     // Move to the stop level
                down_stops_[check_level] = false; // Mark the stop as handled
                break; // Exit the loop after servicing one request
            }
        }
    }

    // Demonstrate the current elevator status
    std::cout << this->getElevatorStatusInfo();
}

// Function to close the elevator gate
void Elevator::closeGate()
{
    std::cout << "The elevator gate is closed!\n";

    // If the elevator is idle
    if (status_ == Status::kIdle)
    {
        if (noRequests(down_stops_)) // Check for any down requests
        {
            status_ = Status::kUp; // Change status to Up if no down requests exist
            return;
        }

        if (noRequests(up_stops_)) // Check for any up requests
        {
            status_ = Status::kDown; // Change status to Down if no up requests exist
            return;
        }
    }
    else if (status_ == Status::kUp) // If the elevator is moving Up
    {
        if (noRequests(up_stops_)) // Check if there are no more up requests
        {
            if (noRequests(down_stops_)) // If there are also no down requests
                status_ = Status::kIdle; // Set status to Idle
            else
                status_ = Status::kDown; // Otherwise, set status to Down
        }
    }
    else // status_ = Status::kDown
    {
        if (noRequests(down_stops_)) // Check if there are no more down requests
        {
            if (noRequests(up_stops_)) // If there are also no up requests
                status_ = Status::kIdle; // Set status to Idle
            else
                status_ = Status::kUp; // Otherwise, set status to Up
        }
    }

    // Demonstrate the current elevator status
    std::cout << this->getElevatorStatusInfo();
}

// Function to check if there are no requests
bool Elevator::noRequests(const std::vector<bool> &stops)
{
    // Check if any of the levels needs stopping
    for (auto stop : stops)
    {
        if (stop == true) // If there's a request to stop at any level
            return false; // Return false if at least one stop is true
    }
    return true; // Return true if no stops are needed
}

// Helper function to convert a vector of bools to a formatted string representation
std::string writeVector(const std::vector<bool> &vec)
{
    std::string temp = "[ ";
    for (auto elem : vec)
    {
        if (elem)
            temp += "1, "; // Represent true as 1
        else
            temp += "0, "; // Represent false as 0
    }

    // Remove the last ", " if the vector is not empty
    if (temp.size() > 2)
    {
        temp.erase(temp.size() - 2, 2); // Remove the last comma and space
        temp += " ]"; // Close the vector representation
    }

    return temp; // Return the formatted string
}

// Function to get a summary of the elevator's request list
std::string Elevator::getElevatorRequestListInfo() const
{
    std::string description = "- Up   stop request list: " + writeVector(up_stops_) + ".\n" +
                              "- Down stop request list: " + writeVector(down_stops_) + ".\n" +
                              "**********************************************************************************************\n";
    return description; // Return the request list info
}

// Function to get a summary of the elevator's current status
std::string Elevator::getElevatorStatusInfo() const
{
    std::string status;
    if (status_ == Status::kUp)
        status = "UP";
    if (status_ == Status::kDown)
        status = "DOWN";
    if (status_ == Status::kIdle)
        status = "IDLE";

    // Construct a description of the elevator's status and request lists
    std::string description = "- The elevator is currently at floor # " + std::to_string(current_level_ + 1) + ".\n" +
                              "- The next elevator status will be: " + status + ".\n" +
                              "- Up   stop request list: " + writeVector(up_stops_) + ".\n" +
                              "- Down stop request list: " + writeVector(down_stops_) + ".\n" +
                              "**********************************************************************************************\n";
    return description; // Return the status info
}

// Function to handle button presses on the ElevatorButton
void ElevatorButton::pressButton()
{
    InternalRequest req = InternalRequest(level); // Create an internal request for the button's level
    elevator->handleInternalRequest(req); // Forward the request to the associated elevator
}
