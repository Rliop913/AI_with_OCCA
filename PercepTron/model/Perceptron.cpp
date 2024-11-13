#include "Perceptron.hpp"


Tron::Tron(const IDXstruct& dataset)
{
    weights.resize(dataset.getWsize());
    bias.resize(10);
}

Tron::Tron(const std::string& weight_path, const IDXstruct& dataset, int threads)
{
    std::ifstream file(weight_path);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open Weight");
    }
    weights.resize(dataset.getWsize());
    bias.resize(10);
    std::vector<std::thread> workers;
    std::mutex datalocker;
    for(int i=0; i<threads; ++i){
        workers.emplace_back([&datalocker, &file, this](){
            std::string line;
            while (true)
            {
                datalocker.lock();
                if(std::getline(file, line)){
                    std::istringstream strm(line);
                    std::vector<std::string> tokens;
                    std::string token;

                    while(std::getline(strm, token, ',')){
                        tokens.push_back(token);
                    }
                    if(tokens.back() == " "){
                        tokens.pop_back();
                    }
                    int row = std::stoi(tokens.back());
                    tokens.pop_back();
                    if(row < 0){
                        float* Bp = this->bias.data();
                        for(auto i : tokens){
                            *(Bp++) = std::stof(i);
                        }
                    }
                    else{
                        float* Wp = this->weights.data();
                        Wp += 100 * row;
                        for(auto i : tokens){
                            *(Wp++) = std::stof(i);
                        }
                    }
                    datalocker.unlock();
                }
                else{
                    datalocker.unlock();
                    break;
                }
            }
        });
    }
    for(int i=0; i<threads; ++i){
        workers[i].join();
    }
    file.close();
}

void
Tron::init(const std::string& mode, const IDXstruct& dataset, const std::string& OKLpath)
{
    occa::json initJson;
    initJson["mode"] = mode;
    dev.setup(initJson);
    W = dev.malloc<float>(weights.size());
    D = dev.malloc<uint8_t>(dataset.getDsize());
    O = dev.malloc<float>(10);
    L = dev.malloc<int8_t>(dataset.num_images);
    W.copyFrom(weights.data());
    D.copyFrom(dataset.imgBin.data());
    L.copyFrom(dataset.labels.data());

    Inf = dev.buildKernel(OKLpath, "inference");
}