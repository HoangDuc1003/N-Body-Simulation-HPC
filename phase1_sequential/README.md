# 🌌 N-Body Simulation - Phase 1: Sequential Baseline
> **The foundational physics engine for gravitational interaction.**

![C++](https://img.shields.io/badge/C++-17-blue?style=for-the-badge&logo=c%2B%2B)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

---

## 📖 Overview
This sub-project implements the core logic for simulating gravitational interactions between $N$ bodies in a 3D environment. It serves as the **Baseline** to verify mathematical accuracy before applying high-performance optimizations.

## 🛠 Technical Details
* **Algorithm:** Implements Newton's Law of Universal Gravitation with $O(N^2)$ time complexity.
* **Optimization:** Used Newton's 3rd Law to reduce force calculations by 50% for sequential execution.
* **Accuracy:** Features a `SOFTENING` constant to handle close-range interactions and prevent singularities.

## 📊 Benchmark
* **Dataset:** 10,000 bodies.
* **Execution Time:** ~5.0 seconds.
* **Performance:** Limited to a single CPU core execution.

> **Benchmark proof for Phase 1:**
> ![Benchmark Phase 1](docs/benchmark_p1_1.png)

## 🚀 How to Build & Run
```bash
# From this directory
mkdir build && cd build
cmake ..
make
./nbody_sim