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

struct Hand {
    int bid = -1;
    string cards = "";
    int rank = -1;
    int type = -1;
    vector<int> noOfCards;
    Hand(): noOfCards(15, 0){}
};

bool my_comp(const Hand& a, const Hand& b);

int main()
{
    vector<int> noOfCards(15, 0);
    string line;
    ifstream myfile1;
    string filename = "input1.txt";
    int winnings = 0;

    map<char, int> cardValues = 
    {
        {'A', 14},
        {'K', 13},
        {'Q', 12},
        {'J', 11},
        {'T', 10},
        {'9', 9},
        {'8', 8},
        {'7', 7},
        {'6', 6},
        {'5', 5},
        {'4', 4},
        {'3', 3},
        {'2', 2}
    };


    vector<Hand> hands;

    myfile1.open(filename);
    while (getline(myfile1, line))
    {   
        Hand tempHand;
        hands.push_back(tempHand);
    }  
    myfile1.close();

    myfile1.open(filename);

    int number =-1 ;
    bool nextParse = false;

    int lineCount = 0;

    while (getline(myfile1, line))
    {     
        for(int i = 0; i < line.size(); i++)
        {
            if (isspace(line[i])) nextParse = true;

            if(nextParse)
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
                    hands[lineCount].bid = number;
                    number = -1;               
                }
                else if (number > -1)
                {
                    hands[lineCount].bid = number;
                    number = -1;
                } 
            }
            else
            {
                hands[lineCount].cards += line[i];
                hands[lineCount].noOfCards[cardValues[line[i]]]++;         
            }

                      
        }
    
        lineCount++;
        nextParse = false;
    }
    myfile1.close();

    // All hands gets a Type
    for (int i = 0; i < hands.size(); i++)
    {   
        int threeofakind = 0;
        int twoofakind = 0; 
        int fourofakind = 0;
        int fiveofakind = 0;

        for(int j = 0; j < hands[i].noOfCards.size(); j++)
        {
            if(hands[i].noOfCards[j] == 5)
            {
                fiveofakind++;
            }
            else if(hands[i].noOfCards[j] == 4)
            {
                fourofakind++;
            }
            else if (hands[i].noOfCards[j] == 3)
            {
                threeofakind++;
            }
            else if (hands[i].noOfCards[j] == 2)
            {
                twoofakind++;
            }
        }

        if(fiveofakind == 1)
        {
            hands[i].type = 7;
        }
        else if(fourofakind == 1)
        {
            hands[i].type = 6;
        }
        else if (threeofakind == 1 && twoofakind == 1)
        {
            hands[i].type = 5;
        } 
        else if (threeofakind == 1 && twoofakind != 1)
        {
            hands[i].type = 4;
        } 
        else if (twoofakind == 2)
        {
            hands[i].type = 3;
        } 
        else if (twoofakind == 1)
        { 
            hands[i].type = 2;
        } 
        else 
        {
            hands[i].type = 1;
        }

    }

    /*r (int i = 0; i < hands.size(); i++)
    { 
        hands[i].type 
    }*/

    cout << endl;
    std::sort(hands.begin(), hands.end(), my_comp);
    cout << endl;

    for (int i = 0; i < hands.size(); i++)
    {
        int rank = i+1;
        cout << "Hand " << i << " bid = " << hands[i].bid << " Rank = " << rank << endl;
        winnings += hands[i].bid * rank;
        
    }



    cout << endl << "Total winnings = " << winnings << endl ;
    cout << endl;

}


bool my_comp(const Hand& a, const Hand& b)
{     
        map<char, int> cardValues = 
    {
        {'A', 14},
        {'K', 13},
        {'Q', 12},
        {'J', 11},
        {'T', 10},
        {'9', 9},
        {'8', 8},
        {'7', 7},
        {'6', 6},
        {'5', 5},
        {'4', 4},
        {'3', 3},
        {'2', 2}
    };

    if (a.type == b.type)
    {   
        if (cardValues[a.cards[0]] == cardValues[b.cards[0]])
        {
            if (cardValues[a.cards[1]] == cardValues[b.cards[1]])
            {
                if (cardValues[a.cards[2]] == cardValues[b.cards[2]])
                {
                    if (cardValues[a.cards[3]] == cardValues[b.cards[3]])
                    {
                        return cardValues[a.cards[4]] < cardValues[b.cards[4]];

                    } else return cardValues[a.cards[3]] < cardValues[b.cards[3]];
                } else return cardValues[a.cards[2]] < cardValues[b.cards[2]];
            } else return cardValues[a.cards[1]] < cardValues[b.cards[1]];
        } else return cardValues[a.cards[0]] < cardValues[b.cards[0]];
        
        
        //cout << "hej " << cardValues[a.cards[0]] << endl;
        //a.cards[0]
    }    
    return a.type < b.type;
}