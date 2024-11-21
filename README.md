Introduction
The Philosophers project is a key part of the 42 curriculum, designed to introduce students to the world of concurrent programming. Inspired by the famous "Dining Philosophers Problem" conceptualized by Edsger Dijkstra, this project challenges students to implement solutions for managing multiple threads or processes that share resources.

Purpose
The primary goal of the Philosophers project is to deepen students' understanding of concurrency, synchronization, and resource management. It provides an opportunity to work with multithreading, mutexes, semaphores, and other tools essential for solving real-world problems in parallel computing. This project is also crucial for honing debugging and analytical skills when dealing with deadlocks, race conditions, and other concurrency-related challenges.

Features
Thread/Process Management

Implementation of philosophers as independent threads or processes that act concurrently.
Handling interactions between threads/processes to avoid conflicts and ensure proper synchronization.
Resource Sharing

Use of mutexes or semaphores to manage access to shared resources (e.g., forks).
Prevention of resource starvation and deadlocks through optimized solutions.
Simulation

Accurate simulation of the dining philosophers' behavior, including thinking, eating, and sleeping states.
Customizable rules such as time limits and philosopher count.
Error Handling

Proper validation of input parameters.
Graceful handling of errors and edge cases like insufficient resources or invalid configuration.
How to Use
Compilation
The project can be compiled using the provided Makefile. Run the following command in the project’s root directory to generate the executable:

bash
Kodu kopyala
make
Execution
Run the program with the following syntax:

bash
Kodu kopyala
./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]
Example:

bash
Kodu kopyala
./philosophers 5 800 200 200
Inputs

number_of_philosophers: Total number of philosophers participating.
time_to_die: Maximum time (in milliseconds) a philosopher can live without eating.
time_to_eat: Time (in milliseconds) a philosopher spends eating.
time_to_sleep: Time (in milliseconds) a philosopher spends sleeping.
number_of_times_each_philosopher_must_eat (optional): If specified, the simulation ends when each philosopher has eaten at least this many times.
