# Specify compiler
CC=g++.exe
  
# Specify linker
LINK=g++.exe
  
# Build all target
.PHONY : all
all : app
  
# Link the object files and dependent libraries into a binary
app : server.o $(LINK) -o server server.o -lstdc++
  
# Compile the source files into object files
server.o : server.cpp $(CC) -c server.cpp -o server.o
  

