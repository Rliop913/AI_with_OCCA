#include <iostream>
#include <data_reader.hpp>

int main(){
    std::string datapath = "../dataset/t10k-images.idx3-ubyte";
    IDXstruct idx(datapath);
    std::cout << "numImages: " << idx.num_images << std::endl;
    std::cout << "rows: " << idx.rows << std::endl;
    std::cout << "cols: " << idx.cols << std::endl;
    idx.show(3);
}
