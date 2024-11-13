#include <data_reader.hpp>
#include <iostream>
IDXstruct::IDXstruct(const std::string& data_path)
{
    std::ifstream file(data_path, std::ios::binary);
    if(!file.is_open()){
        throw std::runtime_error("Cannot open file: " + data_path);
    }
    int32_t magicNum;
    int32_t numImg;
    int32_t Row;
    int32_t Col;
    file.read(reinterpret_cast<char*>(&magicNum), 4);
    file.read(reinterpret_cast<char*>(&numImg), 4);
    file.read(reinterpret_cast<char*>(&Row), 4);
    file.read(reinterpret_cast<char*>(&Col), 4);
    num_images = std::byteswap(numImg);
    rows = std::byteswap(Row);
    cols = std::byteswap(Col);
    images.resize(num_images, std::vector<uint8_t>(rows * cols));
    for(int i=0; i<num_images; ++i){
        file.read(reinterpret_cast<char*>(images[i].data()), rows * cols);
    }
    
    file.close();
}

void
IDXstruct::show(int num)
{
    for(int i=0; i<rows; ++i){
        for(int j=0; j<cols; ++j)
        {
            std::cout << (images[num][i * cols + j] > 127 ? "#" : ".") << " ";
        }
        std::cout << std::endl;
    }
}