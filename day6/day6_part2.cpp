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

using namespace std;


int main()
{
    string line;
    ifstream myfile1;

    myfile1.open("input1.txt");

    vector<int64_t> distance;
    vector<int64_t> time;
    vector<int64_t> wow;

    int64_t number =-1 ;
    bool firstLine = true;
    int64_t score = 1;

    while (getline(myfile1, line))
    {      
        vector<int64_t> dummy;

        for(int64_t i = 0; i < line.size(); i++)
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
                dummy.push_back(number);
                number = -1;               
            }
           /* else if (number > -1)
            {
                dummy.push_back(number);
                number = -1;
            }  */         
        }

        if((line.find(":") != string::npos) && firstLine)
        {
            time = dummy;
            dummy.clear();
            firstLine = false;
        }

        if((line.find(":") != string::npos) && !firstLine)
        {        
            distance = dummy;
            dummy.clear();
        }

    }


    for(int64_t i = 0; i < time.size(); i++)
    {
        int64_t tempTime =  time[i];
        int64_t tempDist =  distance[i];
        int64_t tryDist;
        int64_t wins = 0;

        for(int64_t j = 0; j <= tempTime; j++)
        {
            int64_t timeHold = tempTime - j;
            int64_t timeTravel = j;
            tryDist = timeTravel * timeHold;
            //cout << "time Travel = " << timeTravel << ", Time Hold = " << timeHold << endl;
            //cout << "Distance traveled = " << tryDist << endl << endl;
            if( tryDist > tempDist) wins++;
        }

        cout << "Wins : " << wins << endl;
        wow.push_back(wins);
    }


    for (int64_t i  = 0; i < wow.size(); i++)
    {
        score *= wow[i];
    }

    cout << "Score is :" << score << endl;
    myfile1.close();

    //cout << endl << "The sum for part 1 is: " << sum << endl ;


}