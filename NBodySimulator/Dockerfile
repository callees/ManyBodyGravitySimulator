FROM gcc:14.1
COPY "./makefile" /usr/src
COPY "./NBodySimulator/*.cpp" /usr/src/NBodySimulator/
COPY "./NBodySimulator/*.h" /usr/src/NBodySimulator/
COPY "./SimulationProgram/main.cpp" /usr/src/SimulationProgram/
WORKDIR /usr/src/
RUN make VERBOSE=1
CMD ["./nbodysimapp"]