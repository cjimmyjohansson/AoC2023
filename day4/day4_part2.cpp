#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <string_view>
#include <math.h>

using namespace std;


int main()
{
    string line;

    ifstream myfile1;
    //size_t found = string::npos;

    int sum = 0;
    int number = 0;
    int score = 0;
    int matches = 0;
    int cardNum = 0;
    int numTotalCopies = 0;

    bool afterCardRead = false;
    bool afterWinNum = false;

    vector<int> winningNum;
    vector<int> myNum;
    vector<string> vecCards;

    map<int, int> cardCopies;

    string tempString;

    myfile1.open("input1.txt");


    while (getline(myfile1, line))
    {   
        if(!line.empty())
        {
            vecCards.push_back(line);
        }
    }

    cout << "VecCards size: " << vecCards.size() << endl << endl;
    for(int i = 0; i < vecCards.size(); i++)
    {
        cardCopies[i] = 0;
        cout << "This is card " << i << endl;
    }

    for (int x = 0; x < vecCards.size(); x++)
    {   
        tempString = vecCards[x];

        cout << endl << "Checking Card no: " << x << endl;

        for (int i = 0; i <= tempString.size(); i++)
        {
            //cout << "char is: " << line[i] << endl;
            if (tempString[i] == ':') afterCardRead = true;
            if (tempString[i] == '|') afterWinNum = true;

            if(isdigit(tempString[i]) && afterCardRead )
            {   
                number = number*10 + (tempString[i] - '0');

            }
            else if (number > 0)
            {
                if (afterCardRead && !afterWinNum)
                {
                    winningNum.push_back(number);
                }
                else if(afterCardRead && afterWinNum)
                {
                    myNum.push_back(number);
                }

                number = 0;
            }
        }

        for (int i = 0; i < winningNum.size(); i++)
        {
            for (int j = 0; j < myNum.size(); j++)
            {
                if(winningNum[i] == myNum[j])
                {
                    cout << "Match! : " << winningNum[i] << " and mynum: " << myNum[j] << endl;
                    score = pow(2, matches);
                    //cout << "score :" << score << endl;
                    matches++;
                }
            }
        }

        for(int i = 0; i < matches; i++)
        {
            map<int, int>::iterator it = cardCopies.find(x+1+i);
            int value;
            int copiesOfCurrent = cardCopies[x];

            value = it->second;
            value++;
            it->second = value + copiesOfCurrent;
        }




        sum += score;
        myNum.clear();
        winningNum.clear();
        afterCardRead = false;
        afterWinNum = false;
        matches = 0;
        score = 0;
        
    }

 
//--------------  Check cardCopies Contents ---------------
    map<int, int>::iterator it = cardCopies.begin();
    while (it != cardCopies.end()) {
    cout << "Key: " << it->first << ", Value: " << it->second+1 << endl;

    numTotalCopies += it->second;
    ++it;
    }
//----------------------------------------------------------


    myfile1.close();
    cout << "Total Copies = " << numTotalCopies << endl ;
    cout << "Number of original cards " << vecCards.size() << endl;
    cout << endl << "The sum of cads: " << numTotalCopies + vecCards.size() << endl ;
    //cout << endl << "The sum for part 2 is: " << sum2 << endl << endl;

}