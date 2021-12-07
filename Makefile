CXX=clang++
CXX_FLAGS=-std=c++11 -stdlib=libc++ -g -O0 -Wall -Wextra -Werror -Iincludes/

.PHONY: test clean

test: test/test.cc src/Graph.cc src/Graph.hpp src/Airport.hpp;
	${CXX} ${CXX_FLAGS} src/Graph.cc test/test.cc -o bin/test

clean:
	rm bin/test
