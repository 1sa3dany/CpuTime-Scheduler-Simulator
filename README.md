# CpuTime-Scheduler-Simulator

A C++ simulation tool designed to model and compare classic Operating System CPU scheduling algorithms: **First-Come, First-Served (FCFS)** and **Round Robin (RR)**, built from scratch using core Data Structure principles.

## 📌 Project Overview
This simulator evaluates process management performance by calculating key execution metrics for both non-preemptive and preemptive CPU scheduling algorithms. It uses a custom linked-list queue structure to manage processes dynamically.

---

## 🚀 Key Features
* **First-Come, First-Served (FCFS):** Simulates non-preemptive scheduling based on process arrival order.
* **Round Robin (RR):** Implements preemptive scheduling using a **Time Quantum** (default: `2`) for dynamic process execution.
* **Custom Queue Implementation:** Built completely from scratch without using STL containers, demonstrating low-level queue operations.
* **Performance Analysis:** Automatically calculates and outputs essential process metrics:
  * **Completion Time (CT):** The time when a process finishes execution.
  * **Turnaround Time (TAT):** The total time taken from arrival to completion ($TAT = CT - AT$).
  * **Waiting Time (WT):** The total time a process spends waiting in the ready queue ($WT = TAT - BT$).

---

## 🛠️ Data Structures Implemented
* **Custom Linked-List Queue (`MajorQueue`):** Custom FIFO queue with processes sorted/inserted by arrival time (`insertByArrival`) to model the process queues.
* **Process Nodes (`ProcessNode`):** Dynamic structure containing process metadata (PID, Arrival Time, Burst Time, Remaining Time, Completion Time, Waiting Time, and pointers).
* **Dynamic Memory Management:** Custom destructor in `MajorQueue` to safely release allocated nodes and prevent memory leaks.

---

## ⚙️ How to Compile & Run

### 1. Compile the program
Open your terminal and run the following command:
```bash
g++ CpuTimeSchedulerSimulator.CPP -o scheduler
```

### 2. Run the simulator

* **On Windows (cmd / PowerShell):**
  ```cmd
  scheduler.exe
  ```
* **On Linux / macOS:**
  ```bash
  ./scheduler
  ```

---

## 📊 Sample Input & Output

### Input Example
```text
=======================================================
               CPU Scheduler Simulator                 
 GitHub: https://github.com/1sa3dany/CpuTime-Scheduler-Simulator 
=======================================================

Type The Number Of Processes : 3

--- Process 1 ---
Enter The Name Of Process (Char) : A
Type Burst Time : 5
Type Arrival Time : 0

--- Process 2 ---
Enter The Name Of Process (Char) : B
Type Burst Time : 3
Type Arrival Time : 1

--- Process 3 ---
Enter The Name Of Process (Char) : C
Type Burst Time : 1
Type Arrival Time : 2
```

### Output Example (Round Robin - Time Quantum: 2)
```text
 [Round Robin] Running Process ( A ) from 0 -> 2
 [Round Robin] Running Process ( B ) from 2 -> 4
==================================================
 [Round Robin] Process ( C ) Completed!
==================================================
  Running Time    : 4 -> 5
  Completion Time : 5
  Turnaround Time : 3
  Waiting Time    : 2 Time Cycles
==================================================
 [Round Robin] Running Process ( A ) from 5 -> 7
==================================================
 [Round Robin] Process ( B ) Completed!
==================================================
  Running Time    : 7 -> 8
  Completion Time : 8
  Turnaround Time : 7
  Waiting Time    : 4 Time Cycles
==================================================
==================================================
 [Round Robin] Process ( A ) Completed!
==================================================
  Running Time    : 8 -> 9
  Completion Time : 9
  Turnaround Time : 9
  Waiting Time    : 4 Time Cycles
==================================================
```

---

## 👤 Author
* **Abdulrahman Saadany** - [GitHub Profile](https://github.com/1sa3dany)
