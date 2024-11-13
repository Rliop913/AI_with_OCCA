#pragma once

#include <string>
#include <fstream>


#include <occa.hpp>

struct Tron{

    std::vector<float> weights;
    Tron(int rows, int cols);
    Tron(int rows, int cols, const std::string& weight_path);
    int inference();
    int epoch();
};