#include <bits/stdc++.h>
using namespace std;


// So First of all i have created Point class to represent coordinates (x, y)
class Point {
public:
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {} // Parametrized constructor
};

// Then i have created a simple Obstacle class to represent obstacles
class Obstacle {
public:
    Point position;
    Obstacle(int x, int y) : position(x, y) {} // Parametrized constructor
};

// Direction enum for rover's direction
enum class Direction { N, S, E, W };

// Command interface for the Command Pattern
class Command {
public:
    virtual void execute(Point& position, Direction& direction) = 0;
};

// MoveCommand to move the rover forward
class MoveCommand : public Command {                // Used Inheritance 
public:
    void execute(Point& position, Direction& direction) override {
        // If an obstacle is detected, throw an exception
        if (obstacleDetected(position, direction)) {
            throw runtime_error("Obstacle detected. Rover cannot move.");
        }

        // Implemented moving forward logic based on the current direction
        switch (direction) {
            case Direction::N:
                position.y++;
                break;
            case Direction::S:
                position.y--;
                break;
            case Direction::E:
                position.x++;
                break;
            case Direction::W:
                position.x--;
                break;
        }
    }

private:
    bool obstacleDetected(const Point& position, const Direction& direction) {
        return false;  
    }
};

// LeftTurnCommand to turn the rover left
class LeftTurnCommand : public Command {
public:
    void execute(Point& position, Direction& direction) override {
        // Implemented turning left logic based on the current direction
        switch (direction) {
            case Direction::N:
                direction = Direction::W;
                break;
            case Direction::S:
                direction = Direction::E;
                break;
            case Direction::E:
                direction = Direction::N;
                break;
            case Direction::W:
                direction = Direction::S;
                break;
        }
    }
};

// RightTurnCommand to turn the rover right
class RightTurnCommand : public Command {
public:
    void execute(Point& position, Direction& direction) override {
        // Implemented the turning right logic based on the current direction
        switch (direction) {
            case Direction::N:
                direction = Direction::E;
                break;
            case Direction::S:
                direction = Direction::W;
                break;
            case Direction::E:
                direction = Direction::S;
                break;
            case Direction::W:
                direction = Direction::N;
                break;
        }
    }
};

// Created the Mars Rover Class 
class MarsRover {
public:
    Point getPosition() const { return position; }
    Direction getDirection() const { return direction; }

    MarsRover(int startX, int startY, Direction startDirection)
        : position(startX, startY), direction(startDirection) {}

    void executeCommands(const vector<Command*>& commands, const vector<Obstacle>& obstacles) {
        for (const auto& command : commands) {
            // Check if the next position after moving contains any obstacles
            Point nextPosition = position;
            Direction nextDirection = direction;
            command->execute(nextPosition, nextDirection);


             // Check if there is an obstacle in the next position
            if (!obstacleDetected(nextPosition, obstacles)) {
                // Update rover's position and direction only if no obstacle is detected
                position = nextPosition;
                direction = nextDirection;
            }
        }
    }

    // For rover's current position and facing direction
    string getStatusReport(const vector<Obstacle>& obstacles) const {
        string directionStr;
        switch (direction) {
            case Direction::N:
                directionStr = "North";
                break;
            case Direction::S:
                directionStr = "South";
                break;
            case Direction::E:
                directionStr = "East";
                break;
            case Direction::W:
                directionStr = "West";
                break;
        }
        string statusReport = "Rover is at (" + to_string(position.x) + ", " + to_string(position.y) + ") facing " + directionStr + ". No obstacles detected.";
        
        // Check for obstacles to update the status report
        bool obstacleDetected = false;
        for (const Obstacle& obstacle : obstacles) {
            if (obstacle.position.x == position.x && obstacle.position.y == position.y) {
                obstacleDetected = true;
                break;
            }
        }
        
        if (!obstacleDetected) {
            statusReport += ". No obstacles detected.";
        } else {
            statusReport += ". Obstacle detected.";
        }
        
        return statusReport;

    }

private:
    Point position;
    Direction direction;
    bool obstacleDetected(const Point& nextPosition, const vector<Obstacle>& obstacles) const {
        // Check if the next position contains any obstacles
        for (const Obstacle& obstacle : obstacles) {
            if (obstacle.position.x == nextPosition.x && obstacle.position.y == nextPosition.y) {
                return true; // Obstacle detected
            }
        }
        return false;
    }

};

int main() {
    try {
        // User input for grid size
        int gridSizeX, gridSizeY;
        cout << "Enter grid size (X Y e.g: 10 10): ";
        cin >> gridSizeX >> gridSizeY;

        // User input for starting position and direction
        int startX, startY;
        char startDirectionChar;
        cout << "Enter starting position (x y direction(N/S/E/W)): ";
        cin >> startX >> startY >> startDirectionChar;

        Direction startDirection;      // Created object of Direction class
        switch (startDirectionChar) {  // O(1)
            case 'N':
                startDirection = Direction::N;
                break;
            case 'S':
                startDirection = Direction::S;
                break;
            case 'E':
                startDirection = Direction::E;
                break;
            case 'W':
                startDirection = Direction::W;
                break;
            default:
                throw invalid_argument("Invalid starting direction.");
        }

        // User input for commands
        string commandsStr;
        cout << "Enter commands (e.g: MMRMLM): ";
        cin >> commandsStr;

        vector<Command*> commands;
        for (char commandChar : commandsStr) {
            switch (commandChar) {
                case 'M':
                    commands.push_back(new MoveCommand());
                    break;
                case 'L':
                    commands.push_back(new LeftTurnCommand());
                    break;
                case 'R':
                    commands.push_back(new RightTurnCommand());
                    break;
                default:
                    throw invalid_argument("Invalid command.");
            }
        }

        // User input for obstacles
        vector<Obstacle> obstacles;
        int obstacleCount;
        cout << "Enter the number of obstacles: ";
        cin >> obstacleCount;
        for (int i = 0; i < obstacleCount; ++i) {
            int obstacleX, obstacleY;
            cout << "Enter obstacle position (x y): ";
            cin >> obstacleX >> obstacleY;
            obstacles.push_back(Obstacle(obstacleX, obstacleY));
        }

        // Created a Mars Rover with the user-defined initial position and direction
        MarsRover rover(startX, startY, startDirection);

        // then excecuted user-defined commands
        rover.executeCommands(commands, obstacles);

        // The final position and status report

        string finalPosition = "(" + to_string(rover.getPosition().x) + ", " + to_string(rover.getPosition().y) + ", ";
        string directionStr;
        switch (rover.getDirection()) {
            case Direction::N:
                directionStr = "N";
                break;
            case Direction::S:
                directionStr = "S";
                break;
            case Direction::E:
                directionStr = "E";
                break;
            case Direction::W:
                directionStr = "W";
                break;
        }
        finalPosition += directionStr + ")";
        
        string statusReport = "Rover is at " + finalPosition + " facing " + directionStr;

        // Check for obstacles and update status report
        for (const Obstacle& obstacle : obstacles) {
            if (obstacle.position.x == rover.getPosition().x && obstacle.position.y == rover.getPosition().y) {
                statusReport += ". Obstacle detected.";
                break;
            }
        }

        // Printed final position and status report which will be our final answer
        cout << "Final Position: " << finalPosition << endl;
        cout << "Status Report: " << statusReport << endl;

        // At last i Clean up the memory by deleting command objects
        for (const auto& command : commands) {
            delete command;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}