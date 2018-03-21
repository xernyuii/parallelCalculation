//g++ merge.cpp -ltbb -o merge
#include <iostream>
#include <cstdio>
#include <ctime>
#include <tbb/tbb.h>

void merge(int* a, int low, int mid, int high){
    int i=low;
    int j=mid+1;
    int size=0; //temp的下标
    int *temp = new int [high - low +1]; //创建临时空间
    while((i <= mid) && (j <= high)){
        if(a[i] < a[j]){
            temp[size] = a[i++];
        }
        else{
            temp[size] = a[j++];
        }
        size++;
    }
    while(i <= mid){
        temp[size++] = a[i++];
    }
    for(int i=0; i < size; i++){
        a[low + i] = temp[i];
    }
    delete [] temp;
}
int dx=10;

void merge_sort(int* a, int low, int high);
class parallel_srt{
    int* a;
    int low;
    int high;
    int mid;
public:
    parallel_srt(int* _a, int _low, int _mid, int _high){
        a=_a;low=_low;mid=_mid;high=_high;
    }
    void operator()(const tbb::blocked_range<int> &r) const{
         if(r.begin()==0){
            merge_sort(a, low, mid);
         }
         else{
            merge_sort(a, mid+1, high);
         }
    }
};
// 优化，间距>dx的时候才进行并行的归并，否则为串行的归并
void merge_sort(int* a, int low, int high){
    if(low >= high) return;
    int mid = (low + high)>>1;
    if(high - low > dx){
        tbb::parallel_for(tbb::blocked_range<int>(0,2), parallel_srt(a, low, mid, high));
    }
    else{
        merge_sort(a, low, mid);
        merge_sort(a, mid+1, high);
    }
    merge(a, low, mid, high);
}

void solve(){
    int n=100;
    int a[1000];
    for(int i=0; i<n; i++){
        a[i]=rand();
    }
    merge_sort(a, 0, n-1);
    for(int i=0;i<n;i++){
        std::cout<<a[i]<<std::endl;
    }
}

int main(){
    solve();
    return 0;
}