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

using namespace std;

enum directions {LEFT, UP, RIGHT, DOWN};
vector<int> findS(vector<vector<char>>& vect);
vector<char> getStartPipes(vector<vector<char>>& sketch, vector<int>& vect);
directions nextDirection(vector<vector<char>>& sketch, vector<int> pos, directions dir);
char getSpipe(vector<int> first, vector<int> last);

int main()
{
    string line;
    ifstream myfile1;
    string filename = "input1.txt";
    myfile1.open(filename);
    int64_t ans = 0;
    int64_t totalPipelength = 0;

    vector<vector<char>> pipeSketch;
    vector<vector<int>> storeCoordinates;
    char sPipe;

    while (getline(myfile1, line))
    {
        vector<char> tempVector;
        for(int i = 0; i < line.size(); i++)
        {
            tempVector.push_back(line[i]);
        }

        pipeSketch.push_back(tempVector);
        tempVector.clear();
    }
    myfile1.close();

    vector<int> startPos = findS(pipeSketch); // Find start position, get coordinates  (x, y)
    vector<char> startPipes = getStartPipes(pipeSketch, startPos); //Get surrounding pipes

    directions nextStep;

    if((startPipes[0] == '-') || (startPipes[0] == 'F') || (startPipes[0] == 'L'))
    {
        nextStep = LEFT;
    }
    else if((startPipes[1] == '|') || (startPipes[1] == '7') || (startPipes[1] == 'F'))
    {
        nextStep = UP;
    }
    else if((startPipes[2] == '-') || (startPipes[2] == '7') || (startPipes[2] == 'J'))
    {
        nextStep = RIGHT;
    }
    else if((startPipes[3] == '|') || (startPipes[3] == 'L') || (startPipes[3] == 'J'))
    {
        nextStep = DOWN;
    }

    bool goalReached = false;
    vector<int> currPos = startPos;

    storeCoordinates.push_back(startPos);

    while(!goalReached)
    {
        switch (nextStep)
        {
        case LEFT:
            currPos = {currPos[0] - 1 , currPos[1]};
            nextStep = nextDirection(pipeSketch, currPos, nextStep);
            break;
        
        case UP:
            currPos = {currPos[0] , currPos[1] - 1};
            nextStep = nextDirection(pipeSketch, currPos, nextStep);
            break;

        case RIGHT:
            currPos = {currPos[0] + 1 , currPos[1]};
            nextStep = nextDirection(pipeSketch, currPos, nextStep);
            break;

        case DOWN:
            currPos = {currPos[0], currPos[1] + 1};
            nextStep = nextDirection(pipeSketch, currPos, nextStep);
            break;
        }

        if(pipeSketch[currPos[1]][currPos[0]] == 'S')
        {
            goalReached = true;
        }
        else
        {
            storeCoordinates.push_back(currPos);
        }

        
        //cout << "Current position(" << currPos[0] << ", " << currPos[1] << ")" << endl;
        totalPipelength++;
    }

    char firstPipe = pipeSketch[storeCoordinates[1][1]][storeCoordinates[1][0]];
    int sizeCoord = storeCoordinates.size()-1;
    char lastPipe = pipeSketch[storeCoordinates[sizeCoord][1]][storeCoordinates[sizeCoord][0]];

    vector<int> firstCoord = storeCoordinates[1];
    vector<int> lastCoord = storeCoordinates[sizeCoord];

    cout << "First pipe is: " << firstPipe << " and last pipe is: " << lastPipe << endl;

    cout << "First coord is: " << firstPipe << " and last pipe is: " << lastPipe << endl;
    sPipe = getSpipe(firstCoord, lastCoord);
    cout << "Spipe is: " << sPipe << endl;

    ans = totalPipelength/2;
    cout << endl << "The sum is = " << ans << endl;
    cout << endl;

    //Replace unconnected pipes replaced with '.' in pipeSketch and S with real pipe
    for(int i = 0; i < pipeSketch.size(); i++)
    {

        for(int j = 0; j < pipeSketch[0].size(); j++)
        {
            bool hit = false;

            for(int m = 0; m < storeCoordinates.size(); m++)
            {
                vector<int> tempVec = {j, i};
                
                if(storeCoordinates[m] == tempVec)
                {
                    hit=true;
                }
            }

            if(!hit)
            {
                pipeSketch[i][j] = '.';
            }

            if(pipeSketch[i][j] == 'S')
            {
                pipeSketch[i][j] = sPipe;
            }
        }
    }


    ofstream myfile;
    myfile.open ("pipeSketch_XandO_before.txt");
    for(int i = 0; i < pipeSketch.size(); i++)
    {

        for(int j = 0; j < pipeSketch[0].size(); j++)
        {
                myfile << pipeSketch[i][j];

        }

        if(i != pipeSketch.size()-1)
        {
            myfile << "\n";
        }
    }
    myfile.close();

    for(int i = 0; i < pipeSketch.size(); i++)
    {
        for(int j = 0; j < pipeSketch[0].size(); j++)
        {
            int hits = 0;
            bool cornerFJ = false;
            bool cornerL7 = false;
            
            if(pipeSketch[i][j] == '.')
            {
                for(int m = 0; m <= j; m++)
                {


                    if((pipeSketch[i][j-m] == '|'))
                    {
                        hits++;
                    }
                    else if((pipeSketch[i][j-m] == 'J'))
                    {
                        cornerFJ = true;
                    }
                    else if((pipeSketch[i][j-m] == 'F') && cornerFJ)
                    {
                        hits++;
                        cornerFJ = false;
                    }
                    else if((pipeSketch[i][j-m] == 'L') && cornerFJ)
                    {
                        cornerFJ = false;
                    }
                    else if((pipeSketch[i][j-m] == '7'))
                    {
                        cornerL7 = true;
                    }
                    else if((pipeSketch[i][j-m] == 'L') && cornerL7)
                    {
                        hits++;
                        cornerL7 = false;
                    }
                    else if((pipeSketch[i][j-m] == 'F') && cornerL7)
                    {
                        cornerL7 = false;
                    }
                }
            }

            //cout << "Hits: " << hits << " at (" << j << ", " << i << ")" <<  endl;
            if(pipeSketch[i][j] == '.')
            {
                if((((hits % 2) == 0) && hits != 0) || hits == 0)
                {
                    pipeSketch[i][j] = 'O';
                }
                else
                {
                    pipeSketch[i][j] = 'I';
                }
            }
        }
    }


    int totalI = 0;

    // Draw new txt file and count number of 'I's
    myfile.open ("pipeSketch_XandO_after.txt");
    for(int i = 0; i < pipeSketch.size(); i++)
    {

        for(int j = 0; j < pipeSketch[0].size(); j++)
        {
                myfile << pipeSketch[i][j];
            if(pipeSketch[i][j] == 'I')
            {
                totalI++;
            }
        }

        if(i != pipeSketch.size()-1)
        {
            myfile << "\n";
        }
    }
    myfile.close();

    cout << "Total I's = " << totalI << endl;


}

vector<int> findS(vector<vector<char>>& vect)
{
    vector<int> position;
    
    for(int i = 0; i < vect.size(); i++)
    {

        for(int j = 0; j < vect[i].size(); j++)
        {
            if(vect[i][j] == 'S')
            {
                position.push_back(j);
                position.push_back(i);
            }
        }
    }

    return position;
}

vector<char> getStartPipes(vector<vector<char>>& sketch, vector<int>& vect)
{
    vector<char> pipes;
    int posx = vect[0];
    int posy = vect[1];
    
    if(posx == 0){
        pipes.push_back('.');
    }
    else{
        pipes.push_back(sketch[posy][posx-1]); //LEFT
    }

    if(posy == 0){
        pipes.push_back('.');
    }
    else{
        pipes.push_back(sketch[posy-1][posx]); //UP
    }

    if(posx ==  sketch[0].size()-1){
        pipes.push_back('.');
    }
    else{
        pipes.push_back(sketch[posy][posx+1]); //RIGHT
    }

    if(posy == sketch.size()-1){
        pipes.push_back('.');
    }
    else{
        pipes.push_back(sketch[posy+1][posx]); //DOWN
    }

    return pipes;
}

directions nextDirection(vector<vector<char>>& sketch, vector<int> pos, directions dir)
{
    directions nextDir;
    
        switch (dir)
        {
        case LEFT:
            if(sketch[pos[1]][pos[0]] == '-')
            {
                nextDir = LEFT;
            }
            else if(sketch[pos[1]][pos[0]] == 'F')
            {
                nextDir = DOWN;
            }
            else if(sketch[pos[1]][pos[0]] == 'L')
            {
                nextDir = UP;
            }
            break;
        
        case UP:
            if(sketch[pos[1]][pos[0]] == '|')
            {
                nextDir = UP;
            }
            else if(sketch[pos[1]][pos[0]] == 'F')
            {
                nextDir = RIGHT;
            }
            else if(sketch[pos[1]][pos[0]] == '7')
            {
                nextDir = LEFT;
            }
            break;

        case RIGHT:
            if(sketch[pos[1]][pos[0]] == '-')
            {
                nextDir = RIGHT;
            }
            else if(sketch[pos[1]][pos[0]] == '7')
            {
                nextDir = DOWN;
            }
            else if(sketch[pos[1]][pos[0]] == 'J')
            {
                nextDir = UP;
            }
            break;

        case DOWN:
            if(sketch[pos[1]][pos[0]] == '|')
            {
                nextDir = DOWN;
            }
            else if(sketch[pos[1]][pos[0]] == 'L')
            {
                nextDir = RIGHT;
            }
            else if(sketch[pos[1]][pos[0]] == 'J')
            {
                nextDir = LEFT;
            }
            break;
        }

    return  nextDir;
}

char getSpipe(vector<int> first, vector<int> last)
{
    vector<int> firstCoord = first;
    vector<int> lastCoord = last;
    char tempChar;

    int diffy = 0;
    int diffx = 0;

    diffy = firstCoord[1] - lastCoord[1];
    diffx = firstCoord[0] - lastCoord[0];

    if((diffx == 1) && (diffy == 1))
    {
        tempChar = 'L';
    }

    if((diffx == 1) && (diffy == -1))
    {
        tempChar = 'F';
    }

    if((diffx == -1) && (diffy == 1))
    {
        tempChar = 'J';
    }

    if((diffx == -1) && (diffy == -1))
    {
        tempChar = '7';
    }

    if((diffx == -2) || (diffx == 2))
    {
        tempChar = '-';
    }

    if((diffy == -2) || (diffy == 2))
    {
        tempChar = '|';
    }

    return tempChar;
}

