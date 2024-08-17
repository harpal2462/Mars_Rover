# Mars Rover Simulation
Welcome to the Mars Rover Simulation project! This program simulates the movement of a Mars Rover on a grid-based terrain, following specific commands while avoiding obstacles. The code adheres to Object-Oriented Programming principles and design patterns.

## Table of Contents
- Introduction
- How It Works
- Project Structure
- Command Patterns

## Introduction
The Mars Rover Simulation project allows you to control a Mars Rover's movement on a grid. It is equipped with the following features:

- Forward movement ('M') in the direction the rover is facing.
- Left turn ('L') to change the rover's direction counterclockwise.
- Right turn ('R') to change the rover's direction clockwise.
- Obstacle detection to prevent the rover from colliding with obstacles.
- Optional: Status report indicating the rover's final position, facing direction, and obstacles encountered.

## How It Works
1. Initialize the grid with a specific size (e.g., 10x10).
2. Add obstacles to the grid as needed.
3. Initialize the starting position and direction of the rover.
4. Specify a sequence of commands for the rover.
5. The program processes each command, moving the rover and updating its status.
6. Obstacles are detected and reported.
7. The program displays the final position and facing direction of the rover.

## Project Structure
The project consists of the following classes:
- Client: The main class that initializes the grid, adds obstacles, and executes rover commands.
- Command: An abstract superclass for rover movement commands.
- Forward: A class that handles forward movement ('M') of the rover.
- Left: A class that handles left turns ('L') of the rover.
- Right: A class that handles right turns ('R') of the rover.
- Grid: Represents the grid and handles obstacle management.
- Rover: Represents the Mars Rover, its coordinates, direction, and status

## Command Patterns
The code employs the Command Pattern to encapsulate movement commands ('M', 'L', 'R') as objects. This design promotes flexibility and extensibility in handling rover actions.
