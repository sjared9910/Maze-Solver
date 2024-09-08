#ifndef _MAZE_HPP_
#define _MAZE_HPP_

#include <iostream>
#include <stdexcept>
#include <vector>
#include "Deque.hpp"
#include "lodepng.h"

class Maze
{
private:
	//size of maze
	std::size_t rows;
	std::size_t cols;
	//maze is stored internally as one-dimensional array
	std::vector<unsigned char> maze;
	//queue frontier
	Deque <std::pair<int, int>> Frontier;
	//parent vector to hold path positions
	std::vector<int>parent;

public:
	//Create a blank maze of size 0-by-0
	Maze();
	//set the maze to solve, validate it
	bool set(const std::vector<unsigned char>& maze, std::size_t rows);
	//Return the maze
	const std::vector<unsigned char>& get() const;
	//Solves the maze
	bool solve();
	//Reads maze from PNG file
	bool read(std::string filename);
	//Writes solved maze to PNG file
	bool write(std::string filename) const;
	//Prints maze to cout
	friend std::ostream& operator<<(std::ostream& os, const Maze& m);
};
#endif
