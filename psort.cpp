//g++ psort.cpp -ltbb -o psort
#include <iostream>
#include <cstdio>
#include <string>
#include <tbb/tbb.h>
#include "presort.cpp"

std::string fileback =".dat",  filefront ="./data/";

int temp = 20;
const int BUFFSIZE = 10000;
int psort(int f_A, int f_B){
    int outnum=temp++;
    std::string outfile = "./data/" + std::to_string(outnum) + ".dat";
    // FILE* fc = fopen(outfile.c_str(), "wb");
    // _chsize_s(fileno(fc), BUFFSIZE * 2 * sizeof(int));
    std::string filenameA = filefront + std::to_string(f_A) + fileback;
    FILE* finA = fopen(filenameA.c_str(), "rb");
    std::string filenameB = filefront + std::to_string(f_B) + fileback;
    FILE* finB = fopen(filenameB.c_str(), "rb");
    FILE* fout = fopen(outfile.c_str(), "wb+");
    int *buf0 = new int [BUFFSIZE];
    int *buf1 = new int [BUFFSIZE];
    int *buf2 = new int [BUFFSIZE];
    int i = 0, j = 0, k = 0;
    fread(buf1, sizeof(int), BUFFSIZE, finA);
    fread(buf2, sizeof(int), BUFFSIZE, finB);
    long long all1 = ftell(finA)/sizeof(int), all2 = ftell(finA)/sizeof(int);
    // std::cerr<<all1<<" "<<all2<<"\n";
    // std::cerr<<buf1[1]<<" !"<<buf2[1]<<"\n";
    while(all1 > 0 && all2 > 0){
        // std::cerr<<"!!!!!"<<i<<" "<<j<<"\n";
        if(buf1[i] < buf2[j]){
            buf0[k++] = buf1[i++];
            all1--;
            if(i == BUFFSIZE){
                fread(buf1, sizeof(int), BUFFSIZE, finA);
                i=0;
            }
        }
        else{
            buf0[k++] = buf2[j++];
            all2--;
            if(j == BUFFSIZE){
                fread(buf2, sizeof(int), BUFFSIZE, finB);
                j=0;
            }
        }
        if(k == BUFFSIZE){
            fwrite(buf0, sizeof(int), BUFFSIZE, fout);
            k=0;
            
        }
    }
    while(all1 > 0){
        buf0[k++] = buf1[i++];
        all1--;
        if(i == BUFFSIZE){
            fread(buf1, sizeof(int), BUFFSIZE, finA);
            i=0;
        }
        if(k == BUFFSIZE){
            fwrite(buf0, sizeof(int), BUFFSIZE, fout);
            k=0;
        }
    }
    while(all2 > 0){
        buf0[k++] = buf2[i++];
        all2--;
        if(j == BUFFSIZE){
            fread(buf2, sizeof(int), BUFFSIZE, finB);
            j=0;
        }
        if(k == BUFFSIZE){
            fwrite(buf0, sizeof(int), BUFFSIZE, fout);
            k=0;
        }
    }
    fwrite(buf0, sizeof(int), k, fout);
    fclose(finA);
    fclose(finB);
    fclose(fout);
    delete [] buf0;
    delete [] buf1;
    delete [] buf2;
    system(("rm "+ filenameA).c_str());
    system(("rm "+ filenameB).c_str());
    return outnum;
}
int pmerge(int l, int r);
class pmfile{
    int *file1;
    int *file2;
    int l,r,mid;
public:
    pmfile(int *_file1, int *_file2, int _l, int _r, int _mid){
        file1=_file1;file2=_file2;
        l=_l;r=_r;mid=_mid;
        }
    void operator()(const tbb::blocked_range<int> &R) const{
        if (R.begin()==0) *file1 = pmerge(l, mid);
        else *file2 = pmerge(mid+1, r);
    }
};

int pmerge(int l, int r){
    if(l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    int file1, file2;
    tbb::parallel_for(tbb::blocked_range<int>(0,2), pmfile(&file1, &file2, l, r, mid));
    return psort(file1, file2);
}

int main(){
    presort();
    pmerge(0, 15);
    return 0;
}