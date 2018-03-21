// g++ write.cpp -o write
#include "sdk.h"
class pfilewrite{
public:
    pfilewrite(){}
    void operator()(const tbb::blocked_range<int> &r) const{
        int a[FILESIZE];
        for(int i=r.begin();i!=r.end();i++){
            for(int j=0;j<FILESIZE;j++){
                a[j]=rand();
            }
            std::string filename = filefront + std::to_string(i) + fileback;
            FILE *fout = fopen(filename.c_str(),"wb");
            fwrite(a, sizeof(int), FILESIZE, fout);
            fclose(fout);
        }
    }
};
void writefile(){
    
    tbb::parallel_for(tbb::blocked_range<int>(0,FILENUM), pfilewrite());
}

int main(){
    writefile();
    return 0;
}