#include "Card.h"
#include "Pack.h"
#include <string>
#include <cassert>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

//EFFECTS Creates an empty pack
Pack::Pack() : next(0) {}

//MODIFIES stdout
//EFFECTS  Initializes Pack by reading from pack_filename.
//  If file IO fails, prints an error message and calls exit(EXIT_FAILURE).
Pack::Pack(const std::string &pack_filename) :next(0)
{
    ifstream fin;	
	fin.open(pack_filename.c_str());
	/*	if (!fin.is_open()) 
	{						
		cout << "Error opening: " << pack_filename << endl;
		exit(EXIT_FAILURE);
		}*/
	string tmpRank;
	string tmpSuit;
	string tmp;
	
	
	for(int i = 0; i < PACK_SIZE; ++i)
	{
		fin >> tmpRank;
		fin >> tmp;
		fin >> tmpSuit;
		Card tmpCard(tmpRank, tmpSuit);
		cards.push_back(tmpCard);
		
		
	}
	fin.close();
}

//REQUIRES cards remain in the Pack
//EFFECTS  Returns the next card in the pack and increments the next pointer
Card Pack::deal_one()
{
	assert(next >= 0 && next < PACK_SIZE);
	next += 1;
	return (cards.at(next - 1));
}

//EFFECTS Resets next pointer to first card in the Pack
void Pack::reset()
{
	next = 0;
}
//EFFECTS  Shuffles the Pack and resets the next pointer.  See the project
// spec for a description of the shuffling procedure
void Pack::shuffle()
{
	std::vector<Card> tmpCards;
	std::vector<Card> newCards;	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 17; j < 24; j++)
		{
			newCards.push_back(cards.at(j));
		}
		for (int q = 0; q < 17; q++)
		{
			newCards.push_back(cards.at(q));
		}
		cards = newCards;
		newCards = tmpCards;		
	}
	reset();
	
}
//EFFECTS returns true if there are no more cards left in the pack
bool Pack::empty() const
{
	if (next == PACK_SIZE)	
		return true;
	else
		return false;
}


