# 🌌 N-Body Simulation - Phase 1: Sequential Baseline
> **Cấu trúc nền tảng cho mô phỏng vật lý thiên văn.**

![C++](https://img.shields.io/badge/C++-17-blue?style=for-the-badge&logo=c%2B%2B)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

---

## 📖 Giới thiệu
Dự án này mô phỏng tương tác trọng lực giữa $N$ vật thể trong không gian 3D. Đây là phiên bản **Sequential (Tuần tự)**, đóng vai trò là cột mốc (Baseline) để đo lường hiệu năng cho các giải pháp tối ưu hóa sau này.

## 🛠 Đặc tính kỹ thuật
* **Cấu trúc dữ liệu:** Sử dụng `struct Body` tối ưu để quản lý tọa độ $(x, y, z)$, vận tốc và khối lượng.
* **Thuật toán:** Tính toán lực Newton $F = G \frac{m_1 m_2}{r^2}$ với độ phức tạp $O(N^2)$.
* **Xử lý số học:** Sử dụng hệ số `SOFTENING` để tránh lỗi chia cho 0 khi các vật thể va chạm.

## 🐢 Kết quả Benchmark
* **Số lượng:** 10,000 vật thể.
* **Thời gian:** ~5.0 giây.
* **Đặc điểm:** Chỉ sử dụng 1 nhân duy nhất của CPU, chưa tận dụng hết phần cứng.

## 🚀 Hướng dẫn cài đặt
```bash
# Di chuyển vào thư mục
cd phase1_sequential

# Biên dịch dự án
mkdir build && cd build
cmake ..
make

# Khởi chạy
./nbody_sim