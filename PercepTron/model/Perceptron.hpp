#pragma once

#include <thread>
#include <mutex>
#include <sstream>

#include <occa.hpp>

#include "data_reader.hpp"

struct Tron{
    std::vector<float> weights;
    std::vector<float> bias;
    occa::device dev;
    occa::memory W;
    occa::memory D;
    occa::memory L;
    occa::memory O;

    occa::kernel Inf;
    Tron(const IDXstruct& dataset);
    Tron(const std::string& weight_path, const IDXstruct& dataset, int threads = 10);
    void init(const std::string& mode, const IDXstruct& dataset, const std::string& OKLpath);
    int inference();
    void epoch();
};