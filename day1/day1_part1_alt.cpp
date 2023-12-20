#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    string line;
    int sum = 0;
    ifstream myfile1;



    myfile1.open("input1_small.txt");

    while (getline(myfile1, line))
    {   
        vector<int> numVect;

        for(int i = 0; i < line.size(); ++i)
        {
            if( isdigit(line[i]) ) 
            {
                numVect.push_back(line[i]-'0');
            }
        }
       sum += ((numVect.front()*10) + numVect.back());

       cout << "Line: " << line << endl;
    }


    myfile1.close();

    cout << "The sum is: " << sum << endl;
}