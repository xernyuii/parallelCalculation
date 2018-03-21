//g++ read.cpp -o read
#include <iostream>
#include <cstdio>

void pread(){
    int a[10000];
    std::string fileback=".dat",  filefront="./data/";
    std::string filename = filefront + std::to_string(34) + fileback;
    FILE *fin=fopen(filename.c_str(),"rb");
    fread(a, sizeof(int), 10000, fin);
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