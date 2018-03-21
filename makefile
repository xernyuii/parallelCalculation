CXX = g++
CXXFLAGS = -std=c++11 -static -O3
LIBS = -ltbb
SRC = psort.cpp
WRITESRC = write.cpp
READSRC = read.cpp

TARGET = psort 
WRITETAR = write
READTAR = read
DATA = ./data/*
all: $(TARGET) $(WRITETAR) $(READTAR)

clean:
	-rm -f  $(TARGET) $(WRITETAR) $(READTAR) $(DATA)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(LIBS) -o $(TARGET)

$(WRITETAR): $(WRITESRC)
	$(CXX) $(WRITESRC) $(LIBS) -o $(WRITETAR)

$(READTAR): $(READSRC)
	$(CXX) $(READSRC) $(LIBS) -o $(READTAR)