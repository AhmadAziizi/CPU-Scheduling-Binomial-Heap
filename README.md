# CPU Scheduling Simulator using Binomial Heap

This project is a CPU scheduling simulator written in C.  
It is designed to simulate how a processor chooses which task should run next when multiple tasks arrive at different times and have different execution times.

The program uses a **Binomial Heap** as a priority queue to manage tasks efficiently and select the next process based on a calculated priority level.

---

## Project Idea

In operating systems, CPU scheduling is used to decide which process should be executed by the CPU at each moment.

This project simulates that idea by:

- Accepting multiple tasks with execution time and arrival time
- Managing ready tasks using a Binomial Heap
- Testing different time quantum values
- Calculating waiting time for each task
- Finding the best quantum that gives the lowest average waiting time
- Showing a time trace of how tasks are executed

---

## Possible Real-World Use Cases

Although this is an academic simulation, the same idea can be related to systems where many jobs must be scheduled efficiently, such as:

- Operating system process scheduling
- Print queue management in printers or copy centers
- Task scheduling in servers
- Job scheduling in production systems
- Background task management in applications

---

## Features

- Custom Binomial Heap implementation
- Priority-based task scheduling
- Dynamic task insertion based on arrival time
- Best time quantum calculation
- Waiting time and average waiting time calculation
- CPU idle time detection
- Simulation with and without context-switch delay
- Detailed execution trace

---

## Technologies Used

- C
- Data Structures
- Binomial Heap
- Priority Queue
- Operating Systems Concepts
- Scheduling Algorithms

---

## How It Works

Each task has:

- Process ID
- Execution time
- Arrival time
- Remaining execution time
- Priority level

The simulator inserts tasks into a Binomial Heap when they arrive.  
At each step, the task with the highest scheduling priority is selected, executed for a time quantum, and either completed or reinserted into the heap with updated remaining time.

The program tests different quantum values and chooses the one that results in the lowest average waiting time.

---

## Input Format

The user enters tasks in this format:

```text
Execution Time
Arrival Time
```

Enter `-1` to stop adding tasks.

Example:

```text
6 0
4 1
8 2
-1
```

---

## Example Output

The program displays:

- The best time quantum
- Waiting time for each process
- Average Waiting Time
- CPU execution trace
- Heap status during scheduling

---

## How to Run

Compile:

```bash
gcc cpu_scheduler.c -o scheduler -lm
```

Run:

```bash
./scheduler
```

---

## Academic Project

This project was developed as a university project to practice data structures and operating system scheduling concepts.
