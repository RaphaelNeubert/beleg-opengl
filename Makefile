CXX=g++
CXXFLAGS=-Wall 
LDFLAGS=-lGL -lglut -lGLEW -I/usr/include/glm/ -I/usr/include/GL

ODIR = obj
SDIR = src

DEPS = $(wildcard $(SDIR)/*.hpp) 
SRC = $(wildcard $(SDIR)/*.cpp)
OBJ = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SRC))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS)

beleg: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(ODIR)/*.o
