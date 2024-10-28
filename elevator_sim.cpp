#include "elevator.h"
using namespace std;
int main(int argc, char **argv)
{
    // Let the user init a N-floor elevator system
    int N = 0;
    std::cout << "Please set elevator system with N floors/levels, where N should a positive integer: " << '\n';
    cin >> N;

    // instantiate the object
    Elevator elev(N);

    // execute a infite loop to simulate the elevator system
    while (true)
    {
        int ext_req_floor = 0; // external request floor #
        string ext_req_dir;    // external request direction
        cout << "At this moment, the elevator system has a state information as: " << '\n';
        cout << elev.getElevatorStatusInfo();

        int ext_button_num = 0; // Number of external requests
        cout << "Now let's start. Firstly let's shoot some external requests first!\n";
        cout << "Please give an input: at how many floors the external elevator button is pushed (from 1 to " << N << ") \n";
        cin >> ext_button_num;

        // iterate for ext_button_num times to obtain all the information from user
        for (int i = 0; i < ext_button_num; i++)
        {
            // Get the floor for the external button press
            cout << "Please give an input: at which floor the external elevator button is pushed (from 1 to " << N << ") \n";
            cin >> ext_req_floor;
            // Get the direction for the external request
            cout << "Which button you would press, Up or Down (u/d)? \n";
            cin >> ext_req_dir;

            cout << "Thanks for the input! The elevator's stop request list has been updated! \n";
            // Handle the external request based on the input direction
            if (ext_req_dir == "u" ||
                ext_req_dir == "U" ||
                ext_req_dir == "up" ||
                ext_req_dir == "Up" ||
                ext_req_dir == "UP")
            {
                elev.handleExternalRequest(ExternalRequest(ext_req_floor, Direction::kUp));
            }
            else if (ext_req_dir == "d" ||
                     ext_req_dir == "D" ||
                     ext_req_dir == "down" ||
                     ext_req_dir == "Down" ||
                     ext_req_dir == "DOWN")
            {
                elev.handleExternalRequest(ExternalRequest(ext_req_floor, Direction::kDown));
            }
        }

        // start to execute the previous requests
        cout << "The elevator system starts to execute the requests ! \n";
        while (elev.getStatus() != Status::kIdle)
        {
            elev.openGate(); // Open the elevator gate

            int int_req_floor = 0; // internal request floor #
                                   // Prompt user for the floor they plan to land on, based on the elevator's current direction
            if (elev.getStatus() == Status::kUp)
                cout << "Please give an input: which floor do you plan to land (from " << elev.getCurLevel() + 1 << " to " << N << "); \n";
            else
                cout << "Please give an input: which floor do you plan to land (from 1 to " << elev.getCurLevel() + 1 << "); \n";
            cout << "Or you can type in \"-1\" request to step out the elevator. \n";

            cin >> int_req_floor;

            // Handle internal request if the input floor is valid
            if (int_req_floor >= 0 && int_req_floor <= N)
                elev.handleInternalRequest(InternalRequest(int_req_floor));

            elev.closeGate(); // Close the elevator gate
        }
        // Indicate that all requests have been processed
        cout << "All the external & internal requests have been process!\n\n";
    }

    return 0;
}