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
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;


int main()
{
    using namespace boost::multiprecision;
    string line;
    ifstream myfile1;

    myfile1.open("input1.txt");

    vector<int64_t> seeds;
    vector<vector<int64_t>> rawMaps;
    vector<map<int64_t, int64_t>> vectorMaps;
    vector<int64_t> dummy;

    vector<int64_t> tempVector;
    vector<vector<int64_t>> tempMatrix;
    
    int64_t number = -1;
    int64_t nextParse = 0;
    bool firstLine = true;
    int64_t mapNumber = 0;
    int64_t nextValue = 0;
    int64_t value = 0;

    int64_t minLocation = -1;
    int64_t dest;
    int64_t source;
    int64_t range;

    while (getline(myfile1, line))
    {      

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
            else if (number > -1)
            {
                dummy.push_back(number);
                number = -1;
            }           
        }

        if((line.find(":") != string::npos) && !firstLine && !dummy.empty())
        {        
            rawMaps.push_back(dummy);
            dummy.clear();
        }

        if((line.find(":") != string::npos) && firstLine)
        {
            seeds = dummy;
            dummy.clear();
            firstLine = false;
        }

        if(myfile1.eof())
        {
            rawMaps.push_back(dummy);
            dummy.clear();
            cout << "End of file!" << endl;
        } 

    }

    for(int64_t m = 0; m < seeds.size(); m++)
    {
        for(int64_t i = 0; i < rawMaps.size(); i++) //step through RawMaps
        {

            tempVector.clear();
            tempMatrix.clear();

            for (int64_t x = 0; x < rawMaps[i].size(); x += 3)
            {
                for(int64_t m=0; m < 3; m++)
                {
                    tempVector.push_back(rawMaps[i][x+m]);
                }

                tempMatrix.push_back(tempVector);
                tempVector.clear();
            }

            if(i == 0)
            {  
                value = 0;
                bool hit = false;
                for(int64_t x = 0; x < tempMatrix.size(); x++)
                {
                    tempVector = tempMatrix[x];
                    
                    dest = tempVector[0];
                    source = tempVector[1];
                    range = tempVector[2];
                    

                    if( (seeds[m] >= source) && (seeds[m] <= source + range-1))
                    {
                        value = (seeds[m] - source) + dest;
                        hit = true;
                    }
                    
                    if (!hit)
                    {
                        value = seeds[m];
                        hit = false;
                    }
                }
                nextValue = value;
                cout << "Seed: " << seeds[m] << " has soil = " << nextValue << endl;

            }
            else
            {
                value = 0;
                bool hit = false;
                for(int64_t x = 0; x < tempMatrix.size(); x++)
                {
                    tempVector = tempMatrix[x];

                    dest = tempVector[0];
                    source = tempVector[1];
                    range = tempVector[2];
                    

                    if( (nextValue >= source) && (nextValue <= source + range-1))
                    {
                        value = (nextValue - source) + dest;
                        hit = true;
                    }
                    
                    if (!hit)
                    {
                        value = nextValue;
                    }

                }
                nextValue = value;  
                cout << "Next Value is = " << nextValue << endl;           
            }
            
        }

        cout << "Location for seed: " << seeds[m] << " is = " << nextValue << " Seed:" << m <<endl;

        if(minLocation == -1) 
        {
            minLocation = nextValue;
        }
        else if (nextValue < minLocation)
        {
            minLocation = nextValue;
        }

        //cout << "Min location is :" << minLocation << endl;
        //cout << nextValue << endl;
        //cout << numeric_limits<int64_t>::max();
    }

    cout << "Min location is :" << minLocation << endl;
    myfile1.close();

    //cout << endl << "The sum for part 1 is: " << sum << endl ;


}