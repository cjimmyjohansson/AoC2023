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


vector<int64_t> getDiff(vector<int64_t>& vect);
bool CheckIfZero(vector<int64_t>& vect);

int main()
{
    string line;
    ifstream myfile1;
    string filename = "input1.txt";
    int64_t sum = 0;
    vector<int> sol;

    vector<int64_t> vNextHistory;

    myfile1.open(filename);

    int lineCount = 0;
    int number = -1;

    while (getline(myfile1, line))
    {
        vector<int64_t> vDataset;
        vector<vector<int64_t>> vSetAndDiffs;
        vector<int64_t> vCurrDiff;
        vector<int64_t> vSequence;


        string tempString;
        stringstream ss(line);

        while(getline(ss, tempString, ' '))
        {
            vDataset.push_back(stoi(tempString));
        }

        /*for(int i = 0; i < line.size(); i++)
        {
                        
            if (isdigit(line[i]) &&  i != (line.size()-1))
            {   
                if(number == -1) number = 0;
                number =  number*10 + line[i]- '0';
            }
            else if (isdigit(line[i]) && i == (line.size()-1) )
            {
                if(number == -1) number = 0;
                number = number*10 + line[i] - '0';
                vDataset.push_back(number);
                number = -1;               
            }
            else if (number > -1)
            {
                vDataset.push_back(number);
                number = -1;
            } 
                      
        }*/

        vSetAndDiffs.push_back(vDataset);
        vSequence = vDataset;
        int diffSum = 1;
        
        sol.push_back(vSequence.back());
        while(!CheckIfZero(vSequence))
        {
            vCurrDiff = getDiff(vSequence);
            vSetAndDiffs.push_back(vCurrDiff);
            vSequence = vCurrDiff;
            sol.push_back(vSequence.back());
        }


        for(int i = vSetAndDiffs.size()-1; i >= 0 ; i--)
        {
            
            if(i == vSetAndDiffs.size()-1)
            {
                vSetAndDiffs[i].push_back(0);
                
            }
            else
            {
                int64_t pushValue;
                vector<int64_t> prevDiff = vSetAndDiffs[i+1];
                int prevLastValue = prevDiff[prevDiff.size()-1];
                int currLastValue = vSetAndDiffs[i][vSetAndDiffs[i].size()-1];

                pushValue = currLastValue + prevLastValue;
                //pushValue =  vSetAndDiffs[i][vSetAndDiffs[i].size()-1] + vSetAndDiffs[i+1][vSetAndDiffs[i+1].size()-1];

                vSetAndDiffs[i].push_back(pushValue);
            }
            
            //cout << vSetAndDiffs[i][0] << endl;
        }


        vNextHistory.push_back(vSetAndDiffs[0][vSetAndDiffs[0].size()-1]);
        //cout << "STOI = " << stoi("-54") << endl;
        lineCount++;
        //cout << endl;
        
    }
    myfile1.close();

    for(int i = 0; i < vNextHistory.size(); i++)
    {
        sum += vNextHistory[i];
    }
    
    cout << endl << "The sum is = " << sum << endl;
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

bool CheckIfZero(vector<int64_t>& vect)
{   
    bool isZero = true;
    for(int i = 0; i < vect.size(); i++)
    {
        if(vect[i]!=0)
        {
            isZero = false;
        }
    }

    return isZero;
}


vector<int64_t> getDiff(vector<int64_t>& vect)
{
    vector<int64_t> vtempDiff;
    int64_t elementDiff;

    for(int i = 0; i < vect.size()-1; i++)
    {
        elementDiff = vect[i+1] - vect[i];
        vtempDiff.push_back(elementDiff);
    }

    return vtempDiff;
}