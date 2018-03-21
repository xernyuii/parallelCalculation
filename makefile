CXXFLAGS= -std=c++11 -static -O3

SRC = psort.cpp presort.cpp

OBJS = $(SRC:.cpp=.o)

TARGET = psort

all: $(TARGET)

clean: