#include <data_reader.hpp>
#include <iostream>
IDXstruct::IDXstruct(const std::string& data_path, const std::string& label_path)
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
    imgBin.resize(getDsize());
    file.read(reinterpret_cast<char*>(imgBin.data()), getDsize());
    file.close();

    std::ifstream labfile(label_path, std::ios::binary);
    if(!labfile.is_open()){
        throw std::runtime_error("Cannot open label");
    }
    int32_t numLabel;
    labfile.read(reinterpret_cast<char*>(&magicNum), 4);
    labfile.read(reinterpret_cast<char*>(&numLabel), 4);
    if(numLabel != numImg){
        throw std::runtime_error("image-label miss match");
    }
    labels.resize(numLabel);
    
    labfile.read(reinterpret_cast<char*>(labels.data()), sizeof(char) * numLabel);
    labfile.close();
}

void
IDXstruct::show(int num)
{
    for(int i=0; i<rows; ++i){
        for(int j=0; j<cols; ++j)
        {
            std::cout << (imgBin[(num * cols * rows) + (i * cols + j)] > 127 ? "#" : ".") << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "label: " << std::to_string(labels[num]) << std::endl;
}

int
IDXstruct::getWsize() const
{
    return rows * cols * 10;
}


int
IDXstruct::getDsize() const
{
    return rows * cols * num_images;
}