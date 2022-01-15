CXX=g++
CXXFLAGS=-Wall -g
LDFLAGS=-lGL -lglut -lGLEW -I/usr/include/glm/ -I/usr/include/GL -lfreeimage

ODIR = obj
SDIR = src

DEPS = $(wildcard $(SDIR)/*.hpp) 
SRC = $(wildcard $(SDIR)/*.cpp)
OBJ = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SRC))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(ODIR)/*.o
