#include "presort.cpp"
extern std::string fileback;
extern std::string filefront;

extern const int BUFFSIZE;
extern int pmerge(int l, int r);
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