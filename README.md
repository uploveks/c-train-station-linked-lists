# Train Station using Linked Lists
This is a program written in the C language that simulates a train station database. The purpose of this project is to simplify and condense information about a train station, and to make the job of its employees more manageable by implementing the most common station operations.

# Table of Contents
1. [About the project](#start-description)
2. [Functions](#functions-description)
3. [Building the Project](#build-description)
4. [Testing](#use-description)

<a name="start-description"></a>
## About the project

This project is designed to provide a simple solution to the problems faced by train station employees by implementing a train station database using linked lists in the C language. The project includes the most commonly used station operations to simplify and manage station data.

<a name="functions-description"></a>
## Functions
The program includes the following functions:

- **open_train_station**: Checks if the given number of platforms is a positive integer, allocates memory for the station and initializes each platform's train. If successful, returns the train station.
- **close_train_station**: Deallocates all allocated memory for the train station, including each train and platform.
- **show_existing_trains**: Prints the number of each platform and its locomotive power, as well as the weights of each car in the train.
- **arrive_train**: Allocates memory for a new train and sets its locomotive power to the given value. If successful, adds the train to the given platform.
- **leave_train**: Removes a train from a platform and deallocates its memory.
- **add_train_car**: Adds a car to a train on a given platform with the specified weight.
- **remove_train_cars**: Removes a car with a specific weight from a train on a given platform.
- **move_train_cars**: Moves a sequence of cars between two trains at different platforms.

<a name="build-description"></a>
## Building the project

To build the project, simply compile the main.c file using a C compiler. The project can be tested using gcc.
You can enter the following command in the terminal to compile the project:
```bash
    cd build
    make
```

<a name="use-description"></a>
## Testing

To get an idea of how to use the project functions, take a look at the station_run.c file. This file contains a set of tests designed to check each function, including corner cases such as null stations or trains, incorrect platform numbers, and more.

To run the tests and see which ones have passed, execute the following command:
```bash
    ./run.sh
```

To view the output, look in the THIS_FOLDER directory, and check station_run.c to see how the output is directed to your specific file.


---
