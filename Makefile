.SUFFIXES: .cpp .x .o .h
DIR = `basename $(CURDIR)`

DT = TriangulationOutline
GENERATOR = Generator
RUN = run
TREE = DelaunayTree

EXEC_RUN = $(RUN).x
OBJS_RUN = $(RUN).o
LIBS_RUN = 

EXEC_TREE = $(TREE).x
OBJS_TREE = $(TREE).o
LIBS_TREE = 

EXEC_DT = $(DT).x
OBJS_DT = $(DT).o
LIBS_DT = 

CXXFLAGS = -std=c++14
LFLAGS = -std=c++14

CXX = g++
LD = $(CXX)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -lcairo

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -lcairo

.PHONY: all
all: $(EXEC_DT) $(EXEC_TREE) $(EXEC_RUN)

$(EXEC_RUN): $(OBJS_RUN)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC_TREE): $(OBJS_TREE)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC_DT): $(OBJS_DT)
	$(LD) -o $@ $(LFLAGS) $^ -lcairo

.PHONY: clean zip
clean:
	rm -f *.o *.x DelaunayTriangulation.pdf

zip: clean
	(cd ../; zip -r Vladyslav_Slovinskyi_$(DIR).zip  $(DIR) )

