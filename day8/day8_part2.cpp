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
#include <numeric>

using namespace std;

/*
struct Node {
    string element = "";
    string left = "";
    string right = "";
};
*/

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    return a * b / gcd(a, b);
}


int main()
{
    string line;
    ifstream myfile1;
    string filename = "input1.txt";

    int steps = 0;


    //vector<Node> nodes;
    vector<char> instructions;

    myfile1.open(filename);

    int lineCount = 0;

    bool firstLine = true;
    bool parseLeft = false;
    bool parseRight = false;
    bool parseElement = true;

    string startPoint = "";
    vector<string> startingPoints;

    map<string, vector<string>> mapNodes;

    while (getline(myfile1, line))
    {
        //Node tempNode;
        string tempLeft = "";
        string tempRight = "";
        string tempElemement = "";
        vector<string> tempVector;
        


        for(int i = 0; i < line.size(); i++)
        {

            if(firstLine)
            {
                instructions.push_back(line[i]);
            }
            else if(!firstLine)
            {
                switch (line[i])
                {
                case '(':
                    parseLeft = true;
                    break;

                case '=':
                    parseElement = false;
                    break;

                case ',':
                    parseRight = true;
                    parseLeft = false;
                    break;

                case ')':
                    parseRight = false;
                    break;
                
                default:
                    break;
                }
                

                if(parseElement && !(line[i] == ' '))
                {
                    tempElemement += line[i];
                }
                else if (parseLeft && !(line[i] == '('))
                {
                    tempLeft += line [i];
                }
                else if (parseRight && !(line[i] == ' ') && !(line[i] == ','))
                {
                    tempRight += line[i];
                }
                
            }

                      
        }

        if(lineCount>1)
        {
            //nodes.push_back(tempNode);
            tempVector.push_back(tempLeft);
            tempVector.push_back(tempRight);
            mapNodes[tempElemement] = tempVector;
            if(tempElemement[2] == 'A')
            {
                startingPoints.push_back(tempElemement);
            }
        }

        parseLeft = false;
        parseRight = false;
        parseElement = true;
        firstLine = false;
        lineCount++;
    }
    myfile1.close();

    vector<string> nextElements;
    vector<bool> startingPointsGoalReached(startingPoints.size(), false);
    nextElements = startingPoints;
    vector<int> stepsToGoal(startingPoints.size(), 0);


    for(int i = 0; i < instructions.size(); i++)
    {
        if(instructions[i] == 'R')
        {
            steps++;
            for(int j = 0; j < startingPoints.size(); j++)
            {
                nextElements[j] = mapNodes[nextElements[j]][1];
                if(nextElements[j][2] == 'Z')
                {
                    startingPointsGoalReached[j] = true;
                    stepsToGoal[j] = steps;
                    cout << nextElements[j][0] << nextElements[j][1] << nextElements[j][2] << endl;
                }
                //startingPointsGoalReached[j] = (nextElements[j][2] == 'Z') ? true : false;
            }
            
        }
        else if (instructions[i] == 'L')
        {
            steps++;
            for(int j = 0; j < startingPoints.size(); j++)
            {
                nextElements[j] = mapNodes[nextElements[j]][0];
                if(nextElements[j][2] == 'Z')
                {
                    startingPointsGoalReached[j] = true;
                    stepsToGoal[j] = steps;
                    cout << nextElements[j][0] << nextElements[j][1] << nextElements[j][2] << endl;
                }
                //startingPointsGoalReached[j] = (nextElements[j][2] == 'Z') ? true : false;
            } 
        }


        if(std::find(begin(startingPointsGoalReached), end(startingPointsGoalReached), false) == end(startingPointsGoalReached))
        {
            break;
        }
        else if (i == instructions.size()-1)
        {
            i = -1;
            //cout << "Steps :" << steps << '\r';
        }
    }
    
    int64_t multiple = 1;


    for (int i = 0; i < stepsToGoal.size(); i++){
        multiple = std::lcm(multiple, stepsToGoal[i]);

    }

    cout << "Steps : " << multiple << endl;

}