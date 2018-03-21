//g++ read.cpp -o read
#include "sdk.h"
extern const int FILESIZE;
void pread(){
    int a[FILESIZE];
    std::string fileback=".dat",  filefront="./data/";
    std::string filename = filefront + std::to_string(2*FILENUM-1) + fileback;
    FILE *fin=fopen(filename.c_str(),"rb");
    fread(a, sizeof(int), FILESIZE, fin);
    fclose(fin);
    for(int i=0;i<100;i++){
        std::cout<<a[i]<<" ";
    }
    std::cout<<std::endl;
}

int main(){
     pread();
    return 0;
}