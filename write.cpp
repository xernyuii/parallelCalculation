// g++ write.cpp -o write
#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>

void writefile(){
    int a[10000];
    std::string fileback=".dat",  filefront="./data/";
    for(int i=0;i<16;i++){
        for(int j=0;j<10000;j++){
            a[j]=rand();
        }
        std::string filename = filefront + std::to_string(i) + fileback;
        FILE *fout = fopen(filename.c_str(),"wb");
        fwrite(a, sizeof(int), 10000, fout);
        fclose(fout);
    }   
}

int main(){
    writefile();
    return 0;
}