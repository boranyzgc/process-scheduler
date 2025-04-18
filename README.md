# Process Scheduler Simulation

A simple C++ console application to simulate basic CPU scheduling algorithms, developed as a part of Operating Systems coursework.

## 🧠 Algorithms Implemented

- **First-Come-First-Served (FCFS)**  
  Non-preemptive algorithm that schedules processes based on their arrival time.

- **Round Robin (RR)**  
  Preemptive algorithm that assigns a fixed time quantum to each process.

## 📋 Features

- User-defined number of processes with custom arrival and burst times
- Option to choose scheduling algorithm (FCFS or Round Robin)
- Calculates and displays:
  - Waiting Time
  - Turnaround Time
  - Average metrics
- Simple command-line interface

## 🛠️ Technologies

- Language: C++
- Concepts: CPU Scheduling, Queues, Process Management

## 🚀 Usage

```bash
g++ process_scheduler.cpp -o scheduler
./scheduler

Process   Arrival Time   Burst Time   Waiting Time   Turnaround Time
P1        0              4            0              4
P2        1              3            3              6
...
Average Waiting Time: 2.67
Average Turnaround Time: 5.33

