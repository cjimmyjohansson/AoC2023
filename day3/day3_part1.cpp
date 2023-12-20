#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <string_view>

using namespace std;

int main()
{
    string line;
    string word;

    ifstream myfile1;
    size_t found = string::npos;

    int sum = 0;
    int sum2 = 0;
    int numberValue = 0;

    vector<string> wordsInLine;
    vector<string> vecLines;

    vector<vector<int>> gearCoord;

    bool isPartnumber = false;

    bool firstRow = false;
    bool lastRow = false;
    bool firstChar = false;
    bool lastChar = false;

    map< vector<int> , vector<int> > gearMap;

    vector<int> tempVector;

    myfile1.open("input1.txt");

    while (getline(myfile1, line))
    {   
        if(!line.empty())
        {
            vecLines.push_back(line);
        }
        istringstream iss(line);

    }

    myfile1.close();

        for(int i = 0; i < vecLines.size(); i++)
        {
            //cout <<"Lines " << i << ": " << vecLines[i] << endl;
            string tempLine = vecLines[i];

            for(int x = 0; x < tempLine.size(); x++)
            {

                if (isdigit(tempLine[x]))
                {
                    numberValue = numberValue*10 + (tempLine[x] - '0');

                    for (int ii = -1; ii <=1; ii++ )
                    {
                        for(int xx = -1; xx <= 1; xx++)
                        {
                            if( (x+xx > 0) && (x+xx < tempLine.size()) && (i+ii > 0) && (i+ii < vecLines.size()))
                            {
                                if( (!isdigit(vecLines[i+ii][x+xx]))  && (vecLines[i+ii][x+xx] != '.') )
                                {
                                    isPartnumber = true;
                                }

                                if ( vecLines[i+ii][x+xx] == '*' && gearCoord.empty())
                                {
                                    gearCoord.push_back({i+ii, x+xx});
                                }
                            }

                        }
                    }
                }
                else if (numberValue > 0)
                {

                    for (int z = 0; z < gearCoord.size() ; z++)
                    {
                        tempVector = gearMap[gearCoord[z]];
                        tempVector.push_back(numberValue);
                        gearMap[gearCoord[z]] = tempVector;
                    }
                    

                    if(isPartnumber)
                    {
                        //cout << "NumberValue is: " << numberValue << endl << endl;
                        sum += numberValue;
                    }
                    numberValue = 0;
                    isPartnumber = false;
                    gearCoord.clear();
                }

            }
        }

    map< vector<int> , vector<int> >::iterator it = gearMap.begin();
    while (it != gearMap.end()) {
        if ( it->second.size() == 2)
        {
            sum2 += it->second[0] * it->second[1];
        }
        ++it;
    }
    cout << endl << "The sum for part 1 is: " << sum << endl ;
    cout << endl << "The sum for part 2 is: " << sum2 << endl << endl;

}