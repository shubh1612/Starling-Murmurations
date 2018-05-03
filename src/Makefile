CXX = g++
IDIR = ../include
CXXFLAGS = -I$(IDIR) -w -std=c++11
ODIR = ../bin

LIBS = -lGL -lGLU -lglut -fopenmp

DEPS = physics.cpp simulation.cpp

all: $(ODIR)/App
	chmod +x ../bin/*

$(ODIR)/App: main.cpp
	$(CXX) -o $@ $^ $(DEPS) $(CXXFLAGS) $(LIBS)

clean:
	rm -f ../bin/*