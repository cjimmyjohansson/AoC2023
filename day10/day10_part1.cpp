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

vector<int> findS(vector<vector<char>>& vect);
vector<char> getStartPipes(vector<vector<char>>& sketch, vector<int>& vect);

int main()
{
    string line;
    ifstream myfile1;
    string filename = "input2.txt";

    int64_t ans = 0;

    vector<vector<char>> pipeSketch;

    myfile1.open(filename);

    int lineCount = 0;
    int number = -1;

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

    vector<int> startPos = findS(pipeSketch); // position (x, y)
    vector<char> startPipes = getStartPipes(pipeSketch, startPos);

    //Solution suggestion goLeft, goRight, goUp and goDown functions? which returns next move?



    cout << "Position is at (" << startPos[0] << ", " << startPos[1] << ")" << endl;

    cout << endl << "The sum is = " << ans << endl;
    cout << endl;
/*
    ofstream myfile;
    myfile.open ("example_mine.txt");
    for(int i = 0; i < vNextHistory.size(); i++)
    {
        myfile << vNextHistory[i] << "\n";
    }
    myfile.close();
*/

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
