#include <iostream>
#include <string>
#include "Maze.hpp"

using namespace std;
int main(int argc, char* argv[])
{
	Maze test;
	//Reads file input from command line
	string output = argv[1];
	bool check = test.read(argv[1]);
	
	//Checks if file input is valid
	if (check)
	{
		//solves the maze if possible
		bool possible = test.solve();

		//If the maze was solved
		if (possible)
		{
			//removes .png from the end of the the input string
			int count = 4;
			while (!(count == 0))
			{
				output.pop_back();
				count--;
			}
			//Writes solved maze to file
			bool write = test.write(output + "_solved.png");
			
			//Check to see if maze was written to file
			if (write)
			{
				cout << "Maze Solved, solution saved as " + output +"_solved.png";
				return 0;
			}
			else
			{
				cout << "Could not write maze to file";
				return 1;
			}
		}
		//Maze isnt solvable
		else
		{
			cout << "Could not solve maze";
			return 1;
		}
	}
	//Input file could not be read
	else
	{
		cout << "Invalid maze file";
		return 1;
	}
}
