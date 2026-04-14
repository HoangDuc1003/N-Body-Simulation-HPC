# 🌌 High-Performance Distributed N-Body Simulation

![C++](https://img.shields.io/badge/C++-17/20-blue?style=for-the-badge&logo=c%2B%2B)
![OpenMP](https://img.shields.io/badge/Compute-OpenMP-orange?style=for-the-badge)
![MPI](https://img.shields.io/badge/Network-MPI-green?style=for-the-badge)
![CUDA](https://img.shields.io/badge/Hardware-CUDA_GPU-76B900?style=for-the-badge&logo=nvidia)
![Build](https://img.shields.io/badge/Build-CMake-lightgrey?style=for-the-badge&logo=cmake)

## 📖 Executive Summary
This project is a comprehensive physics engine designed to simulate the gravitational interactions of $N$ celestial bodies in a 3D space. 

Rather than a single script, this repository is architected as an **evolutionary study in High-Performance Computing (HPC)**. It systematically addresses the computational $O(N^2)$ bottleneck of the N-Body problem by scaling from a single-threaded baseline up to a distributed, GPU-accelerated cluster environment.

---

## 🏗️ Architectural Evolution (The 4 Phases)

The simulation is strictly versioned into four distinct architectural phases, each demonstrating mastery over a specific domain of computer science and systems engineering.

### [Phase 1: Sequential Baseline](./phase1_sequential)
* **Focus:** Algorithmic correctness and mathematical foundation.
* **Core Tech:** C++17, Newton's Law of Universal Gravitation, Euler Integration.
* **Achievement:** Established a mathematically stable environment using a `SOFTENING` factor to prevent collision singularities. Applied Newton's 3rd Law to halve the baseline computational load.

### [Phase 2: Shared-Memory Parallelization](./phase2_openmp)
* **Focus:** Multi-core CPU utilization and thread synchronization.
* **Core Tech:** OpenMP, Lock-free Data Structures, Cache Optimization.
* **Achievement:** Restructured the memory access pattern to eliminate Race Conditions without the overhead of mutex locks. Achieved an **8.06x linear speedup** (0.62s vs 5.0s) on 10,000 bodies via dynamic thread scheduling.

### [Phase 3: Distributed-Memory Compute (In Progress) ](./phase3_mpi)
* **Focus:** Horizontal scaling, network topology, and data serialization.
* **Core Tech:** MPI (Message Passing Interface), Cluster Computing.
* **Objective:** Partition the universe domain across multiple physical servers. Overcome network latency bottlenecks using asynchronous collective communications (`MPI_Isend` / `MPI_Irecv` / `MPI_Allgather`).

### [Phase 4: Hardware Acceleration (Planned) ](./phase4_cuda)
* **Focus:** SIMT (Single Instruction, Multiple Threads) execution and Host-to-Device memory bandwidth.
* **Core Tech:** NVIDIA CUDA C++, GPU VRAM Management.
* **Objective:** Offload the massive floating-point operations to the GPU. Target: Simulating **1,000,000+ bodies** in real-time by minimizing PCIe bus transfers and maximizing block/grid utilization.

---

## 📊 Global Performance Matrix

| Architecture | Compute Domain | Max Bodies (Real-time) | Speedup vs Baseline | Status |
| :--- | :--- | :--- | :--- | :--- |
| **Phase 1 (Sequential)** | Single Core CPU | 10,000 | 1.0x (5.0s) | ✅ Completed |
| **Phase 2 (OpenMP)** | Multi-Core CPU | 50,000 | **8.06x** (0.62s) | ✅ Completed |
| **Phase 3 (MPI)** | Multi-Node Cluster | *Pending* | *Pending* | 🚧 WIP |
| **Phase 4 (CUDA)** | GPU Cores | **1,000,000+** | *Target: >500x* | 📅 Planned |

---

## ⚙️ System Requirements & Build Instructions

This repository uses a global `CMakeLists.txt` to manage all sub-projects efficiently.

### Prerequisites
* **Compiler:** GCC 9.0+ or Clang 10.0+ (Must support C++17)
* **Build System:** CMake 3.10+
* **Libraries:** OpenMP, MPICH/OpenMPI (for Phase 3), CUDA Toolkit (for Phase 4)

### Global Build
```bash
# Clone the repository
git clone [https://github.com/HoangDuc1003/N-Body-Simulation-HPC.git](https://github.com/HoangDuc1003/N-Body-Simulation-HPC.git)
cd N-Body-Simulation-HPC

# Generate build files and compile all phases
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
