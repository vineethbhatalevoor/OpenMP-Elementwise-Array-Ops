# Multi-Core Performance Analysis: Element-Wise Array Operations using OpenMP

This repository contains the benchmarking suite and performance analysis report for parallelizing element-wise array operations using **OpenMP** in C. 


## 📌 Problem Statement
High-performance computing and data science applications frequently process massive array grids. Given two dense 1D vectors, $A$ and $B$, this project evaluates the performance of computing three simultaneous element-wise operations:
1. **Addition:** `Add[i] = A[i] + B[i]`
2. **Subtraction:** `Sub[i] = A[i] - B[i]`
3. **Multiplication:** `Mul[i] = A[i] * B[i]`

We analyze execution timelines and multi-core scalability across increasing array boundaries up to $10,000,000$ elements.

---

## 📁 Repository Structure
* **`Serial_Execution.c`**: Sequential implementation running synchronously down a single CPU thread pipeline ($\mathcal{O}(N)$ complexity).
* **`Parallel_Execution.c`**: Multi-threaded variant using OpenMP loop work-sharing directives ($\mathcal{O}(N/P)$ complexity).
* **`Performance_Benchmark.c`**: A unified test harness executing both workloads back-to-back under uniform system conditions to calculate live speedup data.

---

## 🚀 How to Run the Code

### Method 1: Using an Online Compiler (Recommended Quick Setup)
To run these scripts in web environments like **OnlineGDB** or **Tutorialspoint Coding Ground**:
1. Copy the code from `Performance_Benchmark.c`.
2. Select **C** as the language interface.
3. **CRITICAL STEP:** Look for the compiler options panel or flag dropdown and explicitly ensure that **`GCC (with OpenMP support)`** is selected, or add the flag **`-fopenmp`** to your execution arguments. Without this, OpenMP loops will fallback to slow, single-threaded execution.
4. Click **Run**.

### Method 2: Offline Compilation via Windows/Linux Terminal
Open your terminal and use the following compilation and execution sequences:

```bash
# Compile the unified benchmark script with flags enabled
gcc -O3 -fopenmp Performance_Benchmark.c -o Performance_Benchmark

# Run the executable (Linux/MacOS)
./Performance_Benchmark

# Run the executable (Windows)
.\Performance_Benchmark.exe
