#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <tbb/tbb.h>

static std::string fileback =".dat";
static std::string filefront ="./data/";

extern const int BUFFSIZE = 10000;
extern const int FILENUM = 16;
extern const int FILESIZE = 10000;