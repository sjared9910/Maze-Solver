#include "lodepng.h"
#include "Deque.hpp"
#include "Maze.hpp"

//Create a blank maze of size 0-by-0
Maze::Maze()
{
    rows = 0;
    cols = 0;
}

//Function to set the maze we want to solve, validate it, and set private variables appropriately
bool Maze::set(const std::vector<unsigned char>& maze, std::size_t rows)
{
    this->maze.clear();
    //make sure row input is valid, smaller than maze size
    if (rows < maze.size())
    {
        //checks to make sure maze can be divided to get columns
        if ((maze.size() % rows) == 0)
        {
            //variables to test if maze is valid
            int entrycount = 0;
            bool exittest = false;
            bool test = true;

            //goes through maze
            for (int i = 0; i < maze.size(); i++)
            {
                //checks to make sure maze variables are valid
                if (maze[i] != ' ' && maze[i] != '#' && maze[i] != 'B' && maze[i] != 'E')
                {
                    test = false;
                }
                //checks to make sure there is a start point
                if (maze[i] == 'B')
                {
                    entrycount++;
                }
                //check to make sure there is at least 1 exit
                if (maze[i] == 'E')
                {
                    exittest = true;
                }
            }

            //checks the test variables to make sure maze is valid
            if (entrycount == 1 && exittest == true && test == true)
            {
                //sets maze parameters
                cols = maze.size() / rows;
                this->rows = rows;
                this->maze = maze;
                return true;
            }
        }
        //if columns cant be calculated
        return false;
    }
    //if rows isnt valid
    return false;
}

//Return the maze
const std::vector<unsigned char>& Maze::get() const
{
    return maze;
}

//Find the (shortest) path from B to nearest E in the current maze and record the path in the maze
bool Maze::solve()
{
    //start and end values
    std::pair<int, int>start, goal;

    //goes through maze
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            //takes index of each variable in maze
            int index = j + (i * cols);

            //check for begining position
            if (maze[index] == 'B')
            {
                start.first = i;
                start.second = j;
            }
        }
    }

    //goes through maze
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            //takes index of each variable in maze
            int index = j + (i * cols);
            //checks for end index
            if (maze[index] == 'E')
            {
                goal.first = i;
                goal.second = j;
                break;
            }
        }
    }

    //pushes queue with start position
    Frontier.pushBack(start);
    //explored positions
    std::vector<std::pair<int, int>> explore;
    //pushing back parent vector with -1 to mark begining
    parent.push_back(-1);
    //start position;
    int found_At = -1;

    //while loop condition
    bool search = true;
    int l = 0;

    while (search)
    {
        //if frontier is empty then maze can't be solved
        if (Frontier.isEmpty())
        {
            return false;
        }

        //takes position
        std::pair<int, int> position = Frontier.front();
        //removes position from queue
        Frontier.popFront();
        //adds position to explored
        explore.push_back(position);

        //checks if position is less than width
        if (position.first + 1 < cols)
        {
            //takes index position to the right of original
            int right_index = position.second + ((position.first + 1) * cols);

            //makes pair with position
            std::pair<int, int> right;
            right.first = position.first + 1;
            right.second = position.second;

            //check to see if new position needs to be explored
            bool NeedsExplore = true;
            for (int i = 0; i < explore.size(); i++)
            {
                if (explore[i].first == right.first && explore[i].second == right.second)
                {
                    NeedsExplore = false;
                }
            }

            //if the position hasnt been explored and its a space
            if (NeedsExplore == true && maze[right_index] == ' ')
            {
                //pushes linear index to frontier
                Frontier.pushBack(right);
                //adds index to parent function
                parent.push_back(l);
            }

            //if the index is at the end point
            if (maze[right_index] == 'E')
            {
                //endpoint index assigned
                found_At = l;
                //while loop ended
                search = false;
            }
        }

        //checks if position is less than height
        if (position.second + 1 < rows)
        {
            //takes index position above original
            int above_index = position.second + 1 + (position.first * cols);

            //makes pair with position
            std::pair<int, int> above;
            above.first = position.first;
            above.second = position.second + 1;

            //check to see if new position needs to be explored
            bool NeedsExplore = true;
            for (int i = 0; i < explore.size(); i++)
            {
                if (explore[i].first == above.first && explore[i].second == above.second)
                {
                    NeedsExplore = false;
                }
            }

            //if the position hasnt been explored and its a space
            if (NeedsExplore == true && maze[above_index] == ' ')
            {
                //pushes linear index to frontier
                Frontier.pushBack(above);
                //adds index to parent function
                parent.push_back(l);
            }

            //if the index is at the end point
            if (maze[above_index] == 'E')
            {
                //endpoint index assigned
                found_At = l;
                //while loop ended
                search = false;
            }
        }

        //checks if position is greater than 0
        if (position.first - 1 >= 0)
        {
            //takes index position to the left of original
            int left_index = position.second + ((position.first - 1) * cols);

            //makes pair with position
            std::pair<int, int> left;
            left.first = position.first - 1;
            left.second = position.second;

            //check to see if new position needs to be explored
            bool NeedsExplore = true;
            for (int i = 0; i < explore.size(); i++)
            {
                if (explore[i].first == left.first && explore[i].second == left.second)
                {
                    NeedsExplore = false;
                }
            }

            //if the position hasnt been explored and its a space
            if (NeedsExplore == true && maze[left_index] == ' ')
            {
                //pushes linear index to frontier
                Frontier.pushBack(left);
                //adds index to parent function
                parent.push_back(l);
            }

            //if the index is at the end point
            if (maze[left_index] == 'E')
            {
                //endpoint index assigned
                found_At = l;
                search = false;
            }
        }

        //checks if position is greater than 0
        if (position.second - 1 >= 0)
        {
            //takes index position below original
            int below_index = position.second - 1 + (position.first * cols);

            //makes pair with position
            std::pair<int, int> below;
            below.first = position.first;
            below.second = position.second - 1;

            //check to see if new position needs to be explored
            bool NeedsExplore = true;
            for (int i = 0; i < explore.size(); i++)
            {
                if (explore[i].first == below.first && explore[i].second == below.second)
                {
                    NeedsExplore = false;
                }
            }

            //if the position hasnt been explored and its a space
            if (NeedsExplore == true && maze[below_index] == ' ')
            {
                //pushes linear index to frontier
                Frontier.pushBack(below);
                //adds index to parent function
                parent.push_back(l);
            }

            //if the index is at the end point
            if (maze[below_index] == 'E')
            {
                //endpoint index assigned
                found_At = l;
                //while loop ended
                search = false;
            }
        }
        l++;
    }

    //loops back through explored with end position set
    while (found_At != -1)
    {
        //if the position isnt the start point
        if (maze[explore[found_At].second + (explore[found_At].first * cols)] != 'B')
        {
            //sets position to *
            maze[explore[found_At].second + (explore[found_At].first * cols)] = '*';
        }
        //gets next position from parent function
        found_At = parent[found_At];
    }
    return true;
}

//Read a solved or unsolved maze from the PNG file
bool Maze::read(std::string filename)
{
    //check to make sure last 4 characters of input string are .png
    int length = filename.length();
    std::string fileTest = filename.substr((length - 4), length);

    //if the file is a png
    if (fileTest == ".png")
    {
        //reads input file
        bool flag = false;
        std::vector<std::uint8_t> pixels = std::vector<std::uint8_t>(4 * cols * rows);
        unsigned int w, h;

        //read png
        if (filename.empty())
            flag = lodepng::decode(pixels, w, h, "maze.png");
        else
            flag = lodepng::decode(pixels, w, h, filename);

        //sets row and columns to maze diminsions 
        rows = h;
        cols = w;

        //creates test variables
        bool entrytest = false;
        int entrycount = 0;
        bool exittest = false;

        //loops through pixel vector to set maze parameters
        for (int i = 0; i < pixels.size(); i = i + 4)
        {
            //if the pixels are black, wall is placed
            if (pixels[i] == 0 && pixels[i + 1] == 0 && pixels[i + 2] == 0 && pixels[i + 3] == 255)
            {
                maze.push_back('#');
            }
            //if pixels are white, blank is placed
            if (pixels[i] == 255 && pixels[i + 1] == 255 && pixels[i + 2] == 255 && pixels[i + 3] == 255)
            {
                maze.push_back(' ');
            }
            //if pixels are green, start is placed
            if (pixels[i] == 0 && pixels[i + 1] == 255 && pixels[i + 2] == 0 && pixels[i + 3] == 255)
            {
                maze.push_back('B');
                //start is set to true marking there is at least 1 start position
                entrytest = true;
                //check to see how many starts are placed
                entrycount++;
            }
            //if pixels are red, end is placed
            if (pixels[i] == 255 && pixels[i + 1] == 0 && pixels[i + 2] == 0 && pixels[i + 3] == 255)
            {
                maze.push_back('E');
                //sets end marker to true, there is at least 1 end
                exittest = true;
            }
            //if pixels are blue, path is placed
            if (pixels[i] == 0 && pixels[i + 1] == 0 && pixels[i + 2] == 255 && pixels[i + 3] == 255)
            {
                maze.push_back('*');
            }
        }

        //check to make sure there is at least 1 end and beginning 
        if (entrytest == false || exittest == false)
        {
            return false;
        }

        //check to see how many starting places, should be 1
        if (entrycount != 1)
        {
            return false;
        }

        //loops through maze to find any invalid characters
        for (int i = 0; i < maze.size(); i++)
        {
            if (maze[i] != ' ' && maze[i] != '#' && maze[i] != 'B' && maze[i] != 'E' && maze[i] != '*')
            {
                return false;
            }
        }
        return true;
    }
    //file input was not a png
    return false;
}

//Write the unsolved or solved mazed to a PNG file
bool Maze::write(std::string filename) const
{
    //Test to make sure last 4 characters in string are .png
    int length = filename.length();
    std::string fileTest = filename.substr((length - 4), length);

    //if the filename is a png
    if (fileTest == ".png")
    {
        //writes input image to file
        std::vector<unsigned char> raw(4 * cols * rows);

        //Puts image back into raw data
        std::size_t idx = 0;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
            {
                //if maze position was blanc, sets raw to white
                if (maze[j + (i * cols)] == ' ')
                {
                    raw[idx++] = 255;
                    raw[idx++] = 255;
                    raw[idx++] = 255;
                    raw[idx++] = 255;
                }
                //if maze position was wall, sets raw to black
                if (maze[j + (i * cols)] == '#')
                {
                    raw[idx++] = 0;
                    raw[idx++] = 0;
                    raw[idx++] = 0;
                    raw[idx++] = 255;
                }
                //if maze position was beginning, sets raw to green
                if (maze[j + (i * cols)] == 'B')
                {
                    raw[idx++] = 0;
                    raw[idx++] = 255;
                    raw[idx++] = 0;
                    raw[idx++] = 255;
                }
                //if maze position was end, sets raw to red
                if (maze[j + (i * cols)] == 'E')
                {
                    raw[idx++] = 255;
                    raw[idx++] = 0;
                    raw[idx++] = 0;
                    raw[idx++] = 255;
                }
                //if maze position is path, sets raw to blue
                if (maze[j + (i * cols)] == '*')
                {
                    raw[idx++] = 0;
                    raw[idx++] = 0;
                    raw[idx++] = 255;
                    raw[idx++] = 255;
                }
            }

        //encode the image
        unsigned error = lodepng::encode(filename.c_str(), raw, cols, rows);

        //If an error was found
        if (error)
        {
            return false;
        }
        return true;
    }
    //if output filename isnt a png
    return false;
}

//Operator to print maze to std::cout(useful for debugging)
std::ostream& operator<<(std::ostream& os, const Maze& m)
{
    for (int i = 0; i < m.rows * m.cols; i++)
    {
        if (i % m.cols == 0)
            os << std::endl;

        os << m.maze[i];
    }

    os << std::endl << std::endl;

    return os;
}

