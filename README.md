# 🌌 High-Performance N-Body Simulation Engine

<div align="center">

![C++](https://img.shields.io/badge/C++-17%2F20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![OpenMP](https://img.shields.io/badge/Compute-OpenMP-FF9900?style=for-the-badge)
![MPI](https://img.shields.io/badge/Network-MPI-008000?style=for-the-badge)
![CUDA](https://img.shields.io/badge/Hardware-CUDA_GPU-76B900?style=for-the-badge&logo=nvidia&logoColor=white) <br>
![CMake](https://img.shields.io/badge/Build-CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![Linux](https://img.shields.io/badge/OS-Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)

</div>

## 📖 Executive Summary

This project is a high-performance physics engine designed to simulate the gravitational interactions of $N$ celestial bodies in a 3D space. 

Rather than a single monolithic script, this repository is architected as an **evolutionary study in High-Performance Computing (HPC)**. It systematically addresses the computational $O(N^2)$ bottleneck of the N-Body problem by scaling from a single-threaded baseline up to a distributed network cluster and GPU-accelerated environment.

---

## 🏗️ Architectural Evolution (The 4 Phases)

The simulation is strictly versioned into four distinct architectural phases, demonstrating progressive mastery over systems engineering, memory management, and parallel computing.

### 📍 [Phase 1: Sequential Baseline](./phase1_sequential)
* **Focus:** Algorithmic correctness and mathematical foundation.
* **Core Tech:** C++17, Newton's Law of Universal Gravitation, Euler Integration.
* **Achievement:** Established a mathematically stable baseline using a `SOFTENING` constant to prevent division-by-zero singularities during close-body encounters. Applied Newton's 3rd Law to halve the computational load for the sequential run.

### ⚡ [Phase 2: Shared-Memory Parallelization](./phase2_openmp)
* **Focus:** Multi-core CPU utilization and thread synchronization.
* **Core Tech:** OpenMP, Lock-free Data Structures, Cache Optimization.
* **Achievement:** Restructured the memory access pattern to eliminate Data Race conditions without the severe overhead of mutex locks. Achieved a significant linear speedup on a single machine utilizing dynamic thread scheduling.

### 🌐 [Phase 3: Distributed-Memory Compute](./phase3_mpi)
* **Focus:** Horizontal scaling, network topology, and Amdahl's Law.
* **Core Tech:** MPI (Message Passing Interface), Cluster Computing.
* **Achievement:** Successfully partitioned the universe domain across a 4-node cluster. Demonstrated and documented the "Network Latency Bottleneck", showing how communication overhead (`MPI_Allgather`) outweighs compute benefits for small datasets ($N=10,000$).

### 🚀 [Phase 4: Hardware Acceleration](./phase4_cuda)
* **Focus:** SIMT execution and Host-to-Device memory bandwidth limits.
* **Core Tech:** NVIDIA CUDA C++, GPU VRAM Management.
* **Achievement:** Offloaded massive floating-point operations to the GPU cores. Successfully simulated **1,000,000 bodies in 0.055 seconds**, demonstrating the astronomical throughput capabilities of GPU hardware over traditional CPU architecture.

---

## 📈 Observability & Performance Metrics

Performance is strictly benchmarked at each phase to track the architectural trade-offs between computation and communication.

### Global Benchmark Matrix

| Architecture | Compute Domain | Dataset Size (N) | Real Time | Status |
| :--- | :--- | :--- | :--- | :--- |
| **Phase 1 (Sequential)** | Single Core CPU | 10,000 | 2.772s | ✅ Completed |
| **Phase 2 (OpenMP)** | Multi-Core CPU | 10,000 | 0.620s | ✅ Completed |
| **Phase 3 (MPI)** | 4-Node Cluster | 10,000 | 1.531s | ✅ Completed |
| **Phase 4 (CUDA)** | GPU Cores | **1,000,000** | **0.055s** | ✅ Completed |

*Analytical Note: Phase 3 executes slower than Phase 2 on the 10,000 body dataset due to network communication overhead across distributed memory nodes. Phase 4 processes 100x the data volume in a fraction of the time by leveraging VRAM locality and thousands of parallel CUDA threads.*

---

## ⚙️ Build Instructions & Global Configuration

This repository uses a global `CMakeLists.txt` to manage all sub-projects efficiently, allowing you to compile all phases simultaneously.

### Prerequisites
* **Compiler:** GCC 9.0+ or Clang 10.0+
* **Build System:** CMake 3.18+
* **Libraries/Drivers:** OpenMP, OpenMPI, NVIDIA CUDA Toolkit

### 📂 Project Structure
```text
Distributed-N-Body-Simulation/
├── phase1_sequential/      # Baseline single-threaded implementation
├── phase2_openmp/          # Multi-threaded OpenMP optimization
├── phase3_mpi/             # Network distributed MPI implementation
├── phase4_cuda/            # GPU accelerated CUDA kernel
├── CMakeLists.txt          # Global build configuration
└── README.md               # Executive overview
```
### Quick Start
```bash
# 1. Clone the repository
git clone [https://github.com/HoangDuc1003/Distributed-N-Body-Simulation.git](https://github.com/HoangDuc1003/Distributed-N-Body-Simulation.git)
cd Distributed-N-Body-Simulation

# 2. Generate build files
mkdir build && cd build

# 3. Configure CMake with Release flag for maximum optimization
cmake -DCMAKE_BUILD_TYPE=Release ..

# 4. Compile all phases utilizing all available CPU cores
make -j$(nproc)
```
## 📧 Contact

- **Developer**: Hoang Duc
- **Specialization**: Backend Architecture, Systems Engineering, & High-Performance Computing
- **Email**: hhprolay@gmail.com
- **Project Link**: https://github.com/HoangDuc1003/N-Body-Simulation-HPC
