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
#include <bits/stdc++.h>

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

    int64_t sumPaths_task1 = 0;
    int64_t sumPaths_task2 = 0;

    for(int i = 0; i < starCoordinates.size(); i++)
    {
        for(int j = i+1; j < starCoordinates.size(); j++)
        {

            int xpos = starCoordinates[i][0];
            int ypos = starCoordinates[i][1];

            int compxpos = starCoordinates[j][0];
            int compypos = starCoordinates[j][1];

            int emptySpacecrossings = 0;
            for(int x = 0; x < horizontalSpace.size(); x++)
            {
                if((ypos < horizontalSpace[x] && horizontalSpace[x] < compypos) || ((ypos > horizontalSpace[x] && horizontalSpace[x] > compypos)))
                {
                    emptySpacecrossings++;
                }
            }

            for(int x = 0; x < verticalSpace.size(); x++)
            {
                if((xpos < verticalSpace[x] && verticalSpace[x] < compxpos) || ((xpos > verticalSpace[x] && verticalSpace[x] > compxpos)))
                {
                    emptySpacecrossings++;
                }
            }

            sumPaths_task1 += (abs(xpos - compxpos) + abs(ypos - compypos)) + emptySpacecrossings;
            sumPaths_task2 += (abs(xpos - compxpos) + abs(ypos - compypos)) + emptySpacecrossings * (1e6-1);

        }
    }
    cout << endl;
    cout << "Task 1 answer = " << sumPaths_task1 << endl;
    cout << "Task 2 answer = " << sumPaths_task2 << endl;
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

