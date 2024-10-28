#ifndef REQUEST_H // Include guard to prevent multiple inclusions of this header file
#define REQUEST_H
// Enum class representing the direction of a request (up or down)
enum class Direction
{
    kUp = 0,
    kDown = 1
};
// Class representing a general request with a specific level
class Request
{
private:
    int level; // The floor level associated with this request

public:
    Request(int l = 0) : level(l) {}       // Constructor with default level of 0
    int getLevel() const { return level; } // Accessor to get the level of the request
};
// Class representing an external request (from outside the elevator)
class ExternalRequest : public Request
{
private:
    Direction direction; // Direction of the external request

public:
    // Default constructor
    ExternalRequest() {};
    // Constructor to initialize level and direction
    ExternalRequest(int l, Direction d) : Request(l), direction(d) {}
    // Accessor to get the direction of the request
    Direction getDirection() const { return direction; }
};
// Class representing an internal request (from inside the elevator)
class InternalRequest : public Request
{
public:
    // Constructor with default level of 0
    InternalRequest(int l = 0) : Request(l) {}
};

#endif /* REQUEST_H */ // End of include guard