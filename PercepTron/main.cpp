#include <iostream>
#include <data_reader.hpp>

#include <occa.hpp>

int main(){
    std::string datapath = "../dataset/t10k-images.idx3-ubyte";
    std::string labelpath= "../dataset/t10k-labels.idx1-ubyte";
    IDXstruct idx(datapath, labelpath);
    std::cout << "numImages: " << idx.num_images << std::endl;
    std::cout << "rows: " << idx.rows << std::endl;
    std::cout << "cols: " << idx.cols << std::endl;
    idx.show(0);
    occa::device dev;
    occa::json jj;
    jj["mode"] = "openmp";
    
    dev.setup(jj);
    unsigned long num = 30;
    unsigned long EXP = 1 << num;
    occa::memory test_data = dev.malloc<float>(EXP);
    occa::memory out_data = dev.malloc<float>(EXP);


    std::vector<float> test(EXP);
    
    for(unsigned long i=0; i < EXP; ++i){
        test[i] = 1;
    }
    
    test_data.copyFrom(test.data());
    occa::kernel transer = dev.buildKernel("../model/Dot.okl", "T");
    transer(test_data, out_data, num, num);
    
    occa::kernel dotter = dev.buildKernel("../model/Dot.okl", "DOT_front");
    occa::kernel dotback = dev.buildKernel("../model/Dot.okl", "DOT_back1024");
    
    occa::memory Dout = dev.malloc<float>(num * num * num);
    std::vector<float> Dtest(num * num);
    occa::memory resul= dev.malloc<float>(num * num);
    resul.copyFrom(Dtest.data());
    dotter(
        test_data, num, num,
        out_data, num,
        Dout);
    dotback(
        Dout,
        resul,
        static_cast<unsigned int>(num * num), 
        static_cast<unsigned int>(num)
        );
    // std::vector<float> Ttest(EXP);
    // out_data.copyTo(Ttest.data());
    test_data.free();
    out_data.free();
    resul.copyTo(Dtest.data());
    for(int i=0;i<num;++i){
        for(int j=0; j<num; ++j){
            std::cout << Dtest[j + num*i] << ", ";
        }
        std::cout << "----" << std::endl;
    }
    // std::cout<< Dtest[0] << std::endl;
}
