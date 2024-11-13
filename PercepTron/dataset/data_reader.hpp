#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <bit>
struct IDXstruct{
    int32_t num_images;
    int32_t rows;
    int32_t cols;
    std::vector<std::vector<u_int8_t>> images;

    IDXstruct(const std::string& dataset_path);
    void show(int num);
};

