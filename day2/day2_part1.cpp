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
    int sum = 0;
    ifstream myfile1;
    size_t found = string::npos;
    int bagRed = 12;
    int bagBlue = 14;
    int bagGreen = 13;
    int gameNumber = 0;

    map<string, int> numMap = {
        {"red", '0'},
        {"green", '1'},
        {"blue", '2'}
    };

    myfile1.open("input1.txt");

    while (getline(myfile1, line))
    {   
        int numbOfGrabs = 1;
        
        int lineLength = line.length();
        vector<string> wordsInLine;
        string tempLine = line;

        int maxRed = 0;
        int maxBlue = 0;
        int maxGreen = 0;

        istringstream iss(line);

        size_t startOfString = line.find(':');

        gameNumber +=1;

        while( getline(iss, word, ' '))
        {
            if (!word.empty())
            {
                wordsInLine.push_back(word);
            }
        }

        for(int i = 0; i < wordsInLine.size(); i++)
        {
            if( (wordsInLine[i].find("red") != string::npos) && stoi(wordsInLine[i-1]) > maxRed )
            {
                maxRed = stoi(wordsInLine[i-1]);
            }
            else if( (wordsInLine[i].find("blue") != string::npos) && stoi(wordsInLine[i-1]) > maxBlue )
            {
                maxBlue = stoi(wordsInLine[i-1]);
            }
            else if( (wordsInLine[i].find("green") != string::npos) && stoi(wordsInLine[i-1]) > maxGreen )
            {
                maxGreen = stoi(wordsInLine[i-1]);
            }
        }

        if((maxRed <= bagRed) && (maxBlue <= bagBlue) && (maxGreen <= bagGreen))
        {
            sum += gameNumber;
            cout << "Works!" << endl;
        }


/*//---------------------- Probably not needed  ---------------------------
        for(int i = 0; i < line.size(); ++i)
        {
            tempLine = line.substr(i,lineLength);
            found = tempLine.find(";");

            if( found != string::npos && found == 0)
            {
                numbOfGrabs++;
            }
        }
//-------------------------------------------------------------------------
*/

    }
    myfile1.close();

    cout << endl << "The sum is: " << sum << endl << endl;

}