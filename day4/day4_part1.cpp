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
    string line2;
    string word;

    ifstream myfile1;
    size_t found = string::npos;

    int sum = 0;
    int number = 0;

    bool afterCardRead = false;
    bool afterWinNum = false;

    vector<string> wordsInLine;

    vector<int> winningNum;
    vector<int> myNum;

    int score = 0;
    int matches = 0;

    myfile1.open("input1.txt");

    while (getline(myfile1, line))
    {   

        for (int i = 0; i <= line.size(); i++)
        {
            //cout << "char is: " << line[i] << endl;
            if (line[i] == ':') afterCardRead = true;
            if (line[i] == '|') afterWinNum = true;

            if(isdigit(line[i]) && afterCardRead )
            {   
                number = number*10 + (line[i] - '0');

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
                        cout << "score :" << score << endl;
                        matches++;
                    }

                }

            }
        sum += score;
        myNum.clear();
        winningNum.clear();
        afterCardRead = false;
        afterWinNum = false;
        matches = 0;
        score = 0;
        

    }

    myfile1.close();

    cout << endl << "The sum for part 1 is: " << sum << endl ;
    //cout << endl << "The sum for part 2 is: " << sum2 << endl << endl;

}