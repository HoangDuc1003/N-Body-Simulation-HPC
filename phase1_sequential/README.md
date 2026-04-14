# N-Body Simulation - Phase 1: Sequential Version

## 📌 Giới thiệu
Đây là bước đầu tiên trong dự án mô phỏng chuyển động của các vật thể trong không gian dựa trên định luật vạn vật hấp dẫn của Newton. Phiên bản này tập trung vào việc thiết lập thuật toán cơ bản và cấu trúc dữ liệu chính xác.

## 🛠 Công nghệ sử dụng
* **Ngôn ngữ:** C++17
* **Trình biên dịch:** GCC/Clang
* **Hệ thống Build:** CMake

## 🚀 Tính năng
* Khởi tạo ngẫu nhiên vị trí, khối lượng và vận tốc cho $N$ vật thể.
* Tính toán lực hấp dẫn giữa từng cặp vật thể với độ phức tạp $O(N^2)$.
* Cập nhật vị trí dựa trên thuật toán tích phân Euler cơ bản.
* **Tối ưu hóa toán học:** Sử dụng định luật 3 Newton để giảm 50% số phép tính tương tác lực.

## 📊 Kết quả (Benchmark)
* **Số lượng vật thể:** 10,000
* **Thời gian thực thi:** ~5 giây (trên 1 luồng CPU duy nhất).

## 🔨 Cách chạy
1. Truy cập thư mục: `cd phase1_sequential`
2. Tạo thư mục build: `mkdir build && cd build`
3. Biên dịch: `cmake .. && make`
4. Chạy: `./nbody_sim`