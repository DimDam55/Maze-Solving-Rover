# Maze-Solving-Rover
## Maze Solving Rover using Arduino Uno

Created by: Damianos Dimitrios, Larisis Konstantinos

Duration: October-November 2022

This is our submission for the 2022 Workshop of NTUA Microprocessors Laboratory & Digital Systems Laboratory (MICROLAB)

## Possible applications of a maze solving rover

- Detection of victims trapped under collapsed buildings
- Exploration of inaccessibe areas (e.g. caves)

## The implementation

Our rover uses the [Left Wall Follower algorithm](https://en.wikipedia.org/wiki/Maze-solving_algorithm) to find the exit from the maze, given that the rover begins at its entrance.

## Algorithm's Flowchart 

![alt text](https://github.com/DimDam55/Maze-Solving-Rover/blob/main/maze-rover-flowchart.drawio.png?raw=true)

## Components
- Arduino Uno x1
- Mini Breadboards x2
- HC-SR04 ultrasonic sensor x2
- 9V battery x1
- Dual Motor Driver Module L298N x1
- Car Chassis x1
- Gear Motor x2
- Car Tire x2
- Universal Wheel x1
- Buzzer x1

## Schematic 

![alt text](https://github.com/DimDam55/Maze-Solving-Rover/blob/main/schematic.png?raw=true)

## Photos of the rover

![alt text](https://github.com/DimDam55/Maze-Solving-Rover/blob/main/photo_rover1.jpg?raw=true)

![alt text](https://github.com/DimDam55/Maze-Solving-Rover/blob/main/photo_rover2.jpg?raw=true)

![alt text](https://github.com/DimDam55/Maze-Solving-Rover/blob/main/photo_rover3.jpg?raw=true)

## Implementation issues

- Course correction (driving in a straight line)
- Reflection of sound waves, when the sensor is in a non-perpenticular position from the left wall ,which results to inaccurate measurements of the distance.

## Solutions to the above issues

- Use of [PD controller](https://en.wikipedia.org/wiki/PID_controller) for course correction
- Left Sensor placed on a 45 degrees angle with respect to the rover's greatest dimension axis , as shown on the above photos

