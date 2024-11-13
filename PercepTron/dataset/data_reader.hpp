#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <bit>
struct IDXstruct{
    int32_t num_images;
    int32_t rows;
    int32_t cols;
    std::vector<uint8_t> imgBin;
    std::vector<int8_t> labels;
    IDXstruct(const std::string& dataset_path, const std::string& label_path);
    void show(int num);
    int getWsize() const;
    int getDsize() const;
};

