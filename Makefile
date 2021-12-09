CXX=clang++
CXX_FLAGS=-std=c++20 -stdlib=libc++ -g -O0 -Wall -Wextra -Werror -Iincludes/

.PHONY: test clean

test: test/test.cpp src/Graph.cpp src/Graph.hpp src/Airport.hpp src/Draw.cpp src/Draw.hpp cs225/HSLAPixel.cpp cs225/HSLAPixel.h cs225/PNG.cpp cs225/PNG.h cs225/RGB_HSL.h cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h;
	${CXX} ${CXX_FLAGS} cs225/lodepng/lodepng.cpp src/Graph.cpp src/Draw.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp test/test.cpp -o bin/test

clean:
	rm bin/test
