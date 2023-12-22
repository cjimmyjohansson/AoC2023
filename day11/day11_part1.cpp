#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <string_view>
#include <math.h>
#include <stdint.h>
#include <cctype>
#include <algorithm>
#include <cstdlib>

using namespace std;

vector<int> findEmptyspace(vector<vector<char>>& galaxy, int dir);

int main()
{
    string line;
    ifstream myfile1;
    string filename = "input1.txt";
    myfile1.open(filename);

    int64_t ans = 0;
    vector<vector<char>> galaxyMatrix;

    while (getline(myfile1, line))
    {
        vector<char> tempVector;
        for(int i = 0; i < line.size(); i++)
        {
            tempVector.push_back(line[i]);
        }

        galaxyMatrix.push_back(tempVector);
        tempVector.clear();
    }
    myfile1.close();

    vector<int> horizontalSpace = findEmptyspace(galaxyMatrix, 1); // 1 for horizontal
    vector<int> verticalSpace = findEmptyspace(galaxyMatrix, 2); // 2 for vertical

    vector<char> horizontalSpacefill (galaxyMatrix[0].size(), '.');

    //Expand empty space
    for(int i = 0; i < horizontalSpace.size(); i++)
    {
        galaxyMatrix.insert(galaxyMatrix.begin() + horizontalSpace[i] + i, horizontalSpacefill);
    }

    for(int i = 0; i < verticalSpace.size(); i++)
    {
        for(int m = 0; m < galaxyMatrix.size(); m++)
        {
            galaxyMatrix[m].insert(galaxyMatrix[m].begin() + verticalSpace[i] + i , '.');
        }
    }


    ofstream myfile;
    myfile.open ("space_after_spaceinsert.txt");
    for(int i = 0; i < galaxyMatrix.size(); i++)
    {

        for(int j = 0; j < galaxyMatrix[0].size(); j++)
        {
                myfile << galaxyMatrix[i][j];

        }

        if(i != galaxyMatrix.size()-1)
        {
            myfile << "\n";
        }
    }
    myfile.close();

    vector<vector<int>> starCoordinates;
    for(int i = 0; i < galaxyMatrix.size(); i++)
    {
        for(int j = 0; j < galaxyMatrix[0].size(); j++)
        {
            if(galaxyMatrix[i][j] == '#')
            {
                starCoordinates.push_back({j, i});
            }
        }
    }

    int sumPaths = 0;

    for(int i = 0; i < starCoordinates.size(); i++)
    {
        for(int j = i+1; j < starCoordinates.size(); j++)
        {

            int xpos = starCoordinates[i][0];
            int ypos = starCoordinates[i][1];

            int compxpos = starCoordinates[j][0];
            int compypos = starCoordinates[j][1];

            sumPaths += abs(xpos - compxpos) + abs(ypos - compypos);

        }
    }

    cout << "Total distance = " << sumPaths;
    cout << endl;

}

vector<int> findEmptyspace(vector<vector<char>>& galaxy, int dir)
{
    vector<int> result;

    if(dir == 1)
    {
        for(int i = 0; i < galaxy.size(); i++)
        {   
            bool allSpace = true;
            for(int j = 0; j < galaxy[0].size(); j++)
            {
                if(galaxy[i][j] != '.')
                {
                    allSpace = false;
                }
            }

            if (allSpace)
            {
                result.push_back(i);
            }
        }
    }
    else
    {
        for(int i = 0; i < galaxy[0].size(); i++)
        {   
            bool allSpace = true;
            for(int j = 0; j < galaxy.size(); j++)
            {
                if(galaxy[j][i] != '.')
                {
                    allSpace = false;
                }
            }

            if (allSpace)
            {
                result.push_back(i);
            }
        }

    }

    return result;
}

