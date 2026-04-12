#!/bin/bash

echo "========================================"
echo "BẮT ĐẦU BIÊN DỊCH DỰ ÁN N-BODY (PHASE 1)"
echo "========================================"

mkdir -p build
cd build
rm -f nbody_sim
cmake ..
make

if [ $? -eq 0 ]; then
    echo "----------------------------------------"
    echo "BIÊN DỊCH THÀNH CÔNG! ĐANG CHẠY MÔ PHỎNG..."
    echo "----------------------------------------"
    time ./nbody_sim
else
    echo "----------------------------------------"
    echo "LỖI BIÊN DỊCH! VUI LÒNG KIỂM TRA LẠI CODE C++."
    echo "----------------------------------------"
fi