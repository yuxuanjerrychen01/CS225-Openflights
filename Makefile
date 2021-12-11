# Executable names:
EXE = graph
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = Graph.o main.o Draw.o 

# Use the cs225 makefile template:
include cs225/make/cs225.mk