//g++ presort.cpp -ltbb -o presort
#include <iostream>
#include <cstdio>
#include <string>
#include <tbb/tbb.h>

class eachfile_sort{
public:
    eachfile_sort(){}
    void operator()(const tbb::blocked_range<int> &r) const{
        int a[10000];
        std::string fileback=".dat",  filefront="./data/";
        for(int i=r.begin();i!=r.end();i++){
            std::string filename = filefront + std::to_string(i) + fileback;
            FILE *fin=fopen(filename.c_str(),"rb+");
            fread(a, sizeof(int), 10000, fin);
            fclose(fin);
            std::sort(a,a+10000);
            // if(i==0)
            //     for(int i=0;i<10;i++){
            //         std::cout<<a[i]<<" ";
            //     }
            // if(i==0) std::cout<<"\n";
            FILE *fout=fopen(filename.c_str(),"wb");
            fwrite(a, sizeof(int), 10000, fout);
            fclose(fout);
        }
    }
};

void presort(){
    tbb::parallel_for(tbb::blocked_range<int>(0,16), eachfile_sort());
}
