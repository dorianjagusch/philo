# Hive Helsinki Philosophers Project

## Table of Contents
- [Project Description](#project-description)
- [Project Requirements](#project-requirements)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)

## Project Description

This repository contains the solution for the Philosophers project at [Hive Helsinki](https://www.hive.fi/). The Philosophers project is designed to teach students about synchronization techniques in a multithreaded environment.

The project requires you to implement the "Dining Philosophers" problem. In this problem, a certain number of philosophers sit at a round table with a bowl of spaghetti in front of each philosopher. 
Philosophers alternate between thinking, eating and sleeping. To eat, a philosopher must pick up the two forks (one on the left and one on the right) of their place setting. 
Since there are only as many forks as there are philosophers, they must share forks and avoid deadlocks.

The goal is to create a program that simulates the behavior of philosophers, ensuring that they can do their actions without any conflicts, deadlocks, or starvation.

## Project Requirements

- Implements a simulation of the Dining Philosophers problem using threads.
- Manages the shared resources (forks) to avoid conflicts.
- Implements a time-limited simulation where philosophers think, pick up forks, eat, and sleep.
- Monitors and reports the status of the philosophers and their actions.

## Getting Started

Follow these instructions to get the project up and running on your local machine.

### Prerequisites

Before you start, ensure you have the following prerequisites:

- A Linux-based system (Linux/Unix).
- GNU Make.
- GCC compiler

### Installation

1. Clone this repository to your local machine:

   ```sh
   git clone https://github.com/yourusername/hive-helsinki-philosophers.git
   ```
2.  Compile the project:

    ```sh
    make
    ```
3. Run the program with appropriate arguments:

    ```sh
      ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
    ```

Replace the placeholders in square brackets with your desired values.

### Usage

The program will start running, simulating the behavior of philosophers. You can observe their actions, and the program will report the actions taken by the philosophers.

