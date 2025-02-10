COMPILER = g++
COMPILER_FLAG = -lstdc++ -std=c++20

LIB_SRCS=$(wildcard NBodySimulator/*.cpp)
LIB_OBJS=$(LIB_SRCS:.cpp=.o)

nbodysimapp: SimulationProgram/main.o $(LIB_OBJS)
	$(COMPILER) $(COMPILER_FLAG) $(LIB_OBJS) SimulationProgram/main.o -o nbodysimapp

SimulationProgram/main.o: SimulationProgram/main.cpp
	$(COMPILER) $(COMPILER_FLAG) -c SimulationProgram/main.cpp -o SimulationProgram/main.o
	
$(LIB_OBJS) : %.o : %.cpp
	$(COMPILER) $(COMPILER_FLAG) -c $< -o $@