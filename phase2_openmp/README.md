# N-Body Simulation - Phase 2: Parallel Computing with OpenMP

## 📌 Giới thiệu
Phiên bản này nâng cấp từ Phase 1, tập trung vào việc tối ưu hóa hiệu năng bằng cách tận dụng sức mạnh đa nhân của CPU hiện đại. Đây là bước nhảy vọt về tốc độ xử lý cho các bài toán tính toán lớn.

## 🛠 Công nghệ sử dụng
* **Parallel API:** OpenMP
* **Optimization:** Compiler Flags `-O3`, `-fopenmp`
* **Ngôn ngữ:** C++17

## 🚀 Các cải tiến cốt lõi
1. **Multi-threading:** Sử dụng `#pragma omp parallel for` để chia sẻ khối lượng tính toán cho toàn bộ nhân CPU.
2. **Race Condition Handling:** Tái cấu trúc logic để đảm bảo an toàn bộ nhớ khi nhiều luồng cùng ghi dữ liệu (Data Integrity).
3. **Load Balancing:** Sử dụng `schedule(dynamic)` để phân phối công việc linh hoạt cho các core.

## 📈 Kết quả vượt trội (Benchmark)
| Thông số | Phase 1 (Sequential) | Phase 2 (OpenMP) |
| :--- | :--- | :--- |
| **Số vật thể** | 10,000 | 10,000 |
| **Thời gian** | ~5.0s | **0.62s** |
| **Speedup** | 1x | **8.06x** |

**⚡ Hiệu năng tăng trưởng: ~700%**

## 🔨 Cách chạy
1. Truy cập thư mục: `cd phase2_openmp`
2. Biên dịch thủ công (để tối ưu tốt nhất):
   ```bash
   g++ -O3 -fopenmp src/main.cpp -o nbody_omp