# CPU Scheduling Simulation using Binomial Heap

A CPU scheduling simulator implemented in C using a **Binomial Heap** priority queue.

The project simulates task scheduling, calculates waiting times, determines the optimal time quantum, and generates execution traces.

---

## Features

- CPU Scheduling Simulation
- Binomial Heap implementation
- Dynamic task insertion
- Waiting time calculation
- Average Waiting Time (AWT)
- Best Time Quantum selection
- Execution time trace
- Delay simulation

---

## Technologies Used

- C
- Data Structures
- Binomial Heap
- Operating Systems Concepts

---

## How to Run

Compile using GCC:

```bash
gcc secondPROJECT.c -o scheduler -lm
```

Run:

```bash
./scheduler
```

---

## Input Format

Each task is entered as:

```
Execution Time
Arrival Time
```

Enter **-1** to stop adding tasks.

---

## Example Output

- Best Time Quantum
- Waiting time for each task
- Average Waiting Time (AWT)
- CPU execution trace

---

## Academic Project

Developed as part of an Operating Systems / Data Structures university project.
