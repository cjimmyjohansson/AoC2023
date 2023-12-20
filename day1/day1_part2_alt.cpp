#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <string_view>

using namespace std;

int main()
{
    string line;
    int sum = 0;
    ifstream myfile1;
    size_t found = string::npos;
    size_t old_found = string::npos;

    map<string, int> numMap = {
        {"zero", '0'},
        {"one", '1'},
        {"two", '2'},
        {"three", '3'},
        {"four", '4'},
        {"five", '5'},
        {"six", '6'},
        {"seven", '7'},
        {"eight", '8'},
        {"nine", '9'}
    };

    string numbers[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};


    myfile1.open("input1.txt");

    while (getline(myfile1, line))
    {   
        vector<int> numVect;
        int lineLength = line.length();
        string tempLine; 

        for(int i = 0; i < line.size(); ++i)
        {
            if( isdigit(line[i]) ) 
            {
                numVect.push_back(line[i]-'0');
            }

            for(int x = 0; x <= 9; ++x)
            {
                tempLine = line.substr(i,lineLength);
                found = tempLine.find(numbers[x]);

                if(found != string::npos && found == 0)
                {
                    numVect.push_back(numMap[numbers[x]] - '0');
                }
            }
        }

       if(!numVect.empty())
       {
            if(numVect.size() > 1)
            {
                sum += ((numVect.front()*10) + numVect.back());
            }
            else if (numVect.size() == 1)
            {
                sum += (numVect.front()*10) + numVect.front();
            }
       }
    }
    myfile1.close();

    cout << endl << "The sum is: " << sum << endl << endl;
}