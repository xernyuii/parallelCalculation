//g++ psort.cpp -ltbb -o psort
#include "psort.h"
#include <unistd.h>
int temp = FILENUM+1;

int psort(const int &f_A, const int &f_B){
    int outnum=temp++;
    std::string outfile = "./data/" + std::to_string(outnum) + ".dat";
    // FILE* fc = fopen(outfile.c_str(), "wb");
    // _chsize_s(fileno(fc), BUFFSIZE * 2 * sizeof(int));
    
    std::string filenameA = filefront + std::to_string(f_A) + fileback;
    FILE* finA = fopen(filenameA.c_str(), "rb");
    std::string filenameB = filefront + std::to_string(f_B) + fileback;
    FILE* finB = fopen(filenameB.c_str(), "rb");

    FILE* fn = fopen(outfile.c_str(),"ab+");
    fseek(finA, 0L, SEEK_END);  
    long long filesizeA = ftell(finA);
    fseek(finB, 0L, SEEK_END);  
    long long filesizeB = ftell(finB);  
    ftruncate(fileno(fn), filesizeA + filesizeB);
    fclose(fn);
    FILE* fout = fopen(outfile.c_str(), "rb+");


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

int pmerge(const int l, const int r){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int file1, file2;

    tbb::parallel_for(tbb::blocked_range<int>(0,2), pmfile(&file1, &file2, l, r, mid));
    return psort(file1, file2);
}

int main(){
    presort();
    pmerge(0, FILENUM-1);
    return 0;
}