# CpuTime-Scheduler-Simulator

A C++ simulation tool designed to model and compare classic Operating System CPU scheduling algorithms: **First-Come, First-Served (FCFS)** and **Round Robin (RR)**, built using core Data Structure principles.

## 📌 Project Overview
This simulator evaluates process management performance by calculating key execution metrics for both non-preemptive and preemptive CPU scheduling algorithms.

## 🚀 Key Features
* **First-Come, First-Served (FCFS):** Simulates non-preemptive scheduling based on process arrival order.
* **Round Robin (RR):** Implements preemptive scheduling using a configurable **Time Quantum** for dynamic process execution.
* **Performance Analysis:** Automatically calculates and outputs essential process metrics:
  * Completion Time (CT)
  * Turnaround Time (TAT)
  * Waiting Time (WT)

## 🛠️ Data Structures Implemented
* **Queues (FIFO):** Used to manage ready queues and process execution state.
* **Structs & Dynamic Memory:** Encapsulated process data and parameters.

## ⚙️ How to Compile & Run
