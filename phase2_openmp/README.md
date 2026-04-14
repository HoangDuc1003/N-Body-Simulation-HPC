# ⚡ N-Body Simulation - Phase 2: OpenMP Parallelization
> **Achieving massive speedup through Multi-Core Parallel Computing.**

![C++](https://img.shields.io/badge/C++-17-blue?style=for-the-badge&logo=c%2B%2B)
![OpenMP](https://img.shields.io/badge/OpenMP-Enabled-orange?style=for-the-badge)
![Speed](https://img.shields.io/badge/Performance-8x_Faster-red?style=for-the-badge)

---

## 🚀 Performance Breakthrough
This version optimizes the simulation by leveraging **OpenMP** to distribute the heavy computational workload across all available CPU cores. 
> **Performance Breakthrough Proof for Phase 2:**
> <div align="center">
>   <img src="docs/benchmark_p2_1.png" alt="Benchmark Phase 2 - 1" width="48%" />
>   <img src="docs/benchmark_p2_2.png" alt="Benchmark Phase 2 - 2" width="48%" />
> </div>
### 🛠 Optimization Highlights
* **Parallelization:** Utilizes `#pragma omp parallel for` with `dynamic` scheduling for optimal load balancing.
* **Race Condition Avoidance:** Implements a thread-safe accumulation model to maintain data integrity without performance-killing locks.
* **Zero-Overhead Scaling:** Designed to scale linearly with the number of CPU threads.
* **Compiler-Level Tuning:** Leverages `-O3` and `-fopenmp` flags for maximum throughput.

## 📊 Performance Comparison
| Metric | Sequential (Phase 1) | OpenMP (Phase 2) | Speedup |
| :--- | :--- | :--- | :--- |
| **Execution Time** | ~5.0s | **0.62s** | **8.06x** |
| **Efficiency** | Baseline | **High Performance** | **+706%** |

## 🔨 Compilation for Maximum Speed
To get the best performance out of your hardware, use this command:
```bash
g++ -O3 -fopenmp src/main.cpp -o nbody_omp
./nbody_omp
