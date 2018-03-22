CXX = g++
CXXFLAGS = -std=c++11 -O3
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
	$(CXX) $(CXXFLAGS) $(SRC) $(LIBS) -o $(TARGET)

$(WRITETAR): $(WRITESRC)
	$(CXX) $(CXXFLAGS) $(WRITESRC) $(LIBS) -o $(WRITETAR)

$(READTAR): $(READSRC)
	$(CXX) $(CXXFLAGS) $(READSRC) $(LIBS) -o $(READTAR)