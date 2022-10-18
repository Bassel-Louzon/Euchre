#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <cstring>
#include <vector>
#include <string>
#include "Player.h"
#include "Card.h"
#include <algorithm>

using namespace std;

class SimplePlayer : public Player { 
public:
//Initializing Player name
SimplePlayer(string name_in) : name(name_in){}
//EFFECTS returns player's name
virtual const string & get_name() const 
{
	return name;
}

//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
virtual void add_card(const Card &c)
{ 
	assert(hand.size() < MAX_HAND_SIZE);
	hand.push_back(c);
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
virtual bool make_trump(const Card &upcard, const Player &dealer, int round, string &order_up_suit) const
{
	assert(round == 1 || round == 2);
	if(round == 1)
	{
		int numTFC = 0;
		for(unsigned int i = 0; i < hand.size();i++)
		{
			if(hand.at(i).is_face() && hand.at(i).is_trump(upcard.get_suit()))
			{
				++numTFC;
			}
		}
		if (numTFC >= 2) 
		{
			order_up_suit = upcard.get_suit();
			cout << get_name() << " orders up " << order_up_suit << endl;
			return true;
		}
		else
	    {
			cout << get_name() << " passes" << endl;			
			return false;
		}
	}
	else 
	{
		int numTFC = 0;
		string same_color_suit = upcard.get_suit(upcard.get_suit());
		for(unsigned int i = 0; i < hand.size(); i++)
		{
			if(hand.at(i).is_face() && hand.at(i).get_suit() == same_color_suit)
			{
				++numTFC;
			}
		}
		
		if(numTFC >= 1)
		{
			order_up_suit = same_color_suit;
			cout << get_name() << " orders up " << order_up_suit << endl;
			return true;
		}
		else 
		{
			cout << get_name() << " passes" << endl;			
			return false;
		}
	}
}

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
virtual void add_and_discard(const Card &upcard)
{
	assert(hand.size() > 0);
	Card low_card = hand.at(0);
	int lowIndex = 0;
	for(unsigned int i = 1; i < hand.size(); i++)
	{
		if(Card_less(hand.at(i), low_card, upcard.get_suit()))
		{
			low_card = hand.at(i);
			lowIndex = i;
		}
	}
	if(Card_less(low_card, upcard, upcard.get_suit()))
	{
		hand.at(lowIndex) = upcard;
	}
}

//REQUIRES Player has at least one card
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
virtual Card lead_card(const string &trump)
{
	assert(hand.size() > 0);
	bool allTrumps = true;
	unsigned int high_index;
	vector<Card> new_hand;
	for (unsigned int i = 0; i < hand.size(); i++)
	{
		if (hand.at(i).get_suit() != trump)
		{
			allTrumps = false;			
			high_index = i;
			break;
			
		}
	}
	
	if (allTrumps == false)
	{
		Card high_card = hand.at(high_index);
		for (unsigned int j = 0; j < hand.size(); j++)
		{
			if (hand.at(j).get_suit() != trump && hand.at(j) > high_card) 
			{
				 high_card = hand.at(j);
				 high_index = j;
			}
		}
		
		//removing card from hand
		for (unsigned int cnt = 0; cnt < hand.size(); cnt++)
		{
			if (cnt != high_index)
			{
				new_hand.push_back(hand.at(cnt));
			}			
		}
		
		hand = new_hand;
		cout << high_card << " led by " << get_name() << endl;
		
		return high_card;
	}
	//allTrumps is true
	else
	{
		Card high_card = hand.at(0);
		high_index = 0;
		
		for (unsigned int k = 0; k < hand.size(); k++)
		{
			if(Card_less(high_card, hand.at(k), trump))			{
				high_card = hand.at(k);
				high_index = k;
			}
		}
		
		//removing card from hand
		for (unsigned int cnt = 0; cnt < hand.size(); cnt++)
		{
			if (cnt != high_index)
			{
				new_hand.push_back(hand.at(cnt));
			}			
		}
		
		hand = new_hand;
		cout << high_card << " led by " << get_name() << endl;	
		return high_card;
	}
	
	
}

//REQUIRES Player has at least one card
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
virtual Card play_card(const Card &led_card, const string &trump)
{
	unsigned int high_index = 0;
	unsigned int low_index = 0;
	bool sameSuit = false;
	vector<Card> new_hand;

	for (unsigned int i = 0; i < hand.size(); i++)
	{
		if (hand.at(i).get_suit() == led_card.get_suit())
		{
			sameSuit = true;			
			high_index = i;
			break;
			
		}
	}
	if (sameSuit == true && led_card.get_suit() != trump)
	{
		Card high_card = hand.at(high_index);	
		for (unsigned int i = 0; i < hand.size(); i++)
		{
			if (Card_less(high_card, hand.at(i), trump) && hand.at(i).get_suit() == led_card.get_suit())
			{
				high_card = hand.at(i);
				high_index = i;
			}
		}
		
		for (unsigned int cnt = 0; cnt < hand.size(); cnt++)
		{
			if (cnt != high_index)
			{
				new_hand.push_back(hand.at(cnt));
			}			
		}
		
		hand = new_hand;
		cout << high_card << " played by " << get_name() << endl;
		
		return high_card;
	}
	else if (sameSuit == true && led_card.get_suit() == trump) 
	{
		Card high_card = hand.at(high_index);	
		for (unsigned int i = 0; i < hand.size(); i++)
		{
			if (Card_less(high_card, hand.at(i), trump))
			{
				high_card = hand.at(i);
				high_index = i;
			}
		}
		
		for (unsigned int cnt = 0; cnt < hand.size(); cnt++)
		{
			if (cnt != high_index)
			{
				new_hand.push_back(hand.at(cnt));
			}			
		}
		
		hand = new_hand;
		cout << high_card << " played by " << get_name() << endl;
		
		return high_card;

	}
	else
	{
		Card low_card = hand.at(0);
		for (unsigned int i = 0; i < hand.size(); i++)
		{
			if (low_card.is_trump(trump) && !hand.at(i).is_trump(trump))
			{
				low_card = hand.at(i);
				low_index = i;
			}
			else if (low_card > hand.at(i) && !hand.at(i).is_trump(trump))
			{
				low_card = hand.at(i);
				low_index = i;
			}
			else if (Card_less(hand.at(i), low_card, trump))			{
				low_card = hand.at(i);
				low_index = i;				
			}	
		}
		for (unsigned int cnt = 0; cnt < hand.size(); cnt++)
		{
			if (cnt != low_index)
			{
				new_hand.push_back(hand.at(cnt));
			}			
		}
		hand = new_hand;
		cout << low_card << " played by " << get_name() << endl;
		return low_card;		
	}
}

private:
string name;
vector<Card> hand;
};

class HumanPlayer : public Player {

public:

//Initializing Player name

HumanPlayer(string name_in) : name(name_in){}

//EFFECTS returns player's name
virtual const string & get_name() const
{
	return name;
}

//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
virtual void add_card(const Card &c)
{
	assert(hand.size() < MAX_HAND_SIZE);
	hand.push_back(c);
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
virtual bool make_trump(const Card &upcard, const Player &dealer, int round, string &order_up_suit) const
{
	string decision;	
	assert( round == 1 || round == 2);	
	vector<Card> copyHand;	
	
	for(int i = 0; i < (int) hand.size() ; i++)
	{
		copyHand.push_back(hand.at(i));	
	}	
	copyHand = sortHand(copyHand);
	
	for (int i = 0; i < (int) hand.size(); i++)
	{
		cout << "Human player " << get_name() << "'s hand: [" << i << "] " << copyHand.at(i) << endl;
	}
	
	cout << "Human player " << get_name() << ", please enter a suit, or \"pass\":"<<endl;
	cin >> decision;	
	
	if (decision == "pass") 
	{
		cout << get_name() << " passes" << endl;   
		return false;
	}
	
	else
	{
		order_up_suit = decision;
		cout << get_name() << " orders up " << order_up_suit << endl;
		//cout << endl;
		return true;
	}
	
	return true;

}

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
virtual void add_and_discard(const Card &upcard)
{
	string decision;
	int cardNumber;	
	assert(hand.size() > 0);
	vector<Card> copyHand;
	
	for(int i = 0; i < (int) hand.size(); i++)
	{
		copyHand.push_back(hand.at(i));	
	}	
	
	copyHand = sortHand(copyHand);
	hand = copyHand;
		
	for (int i = 0; i < (int) hand.size(); i++)
	{
		cout << "Human player " << get_name() << "'s hand: [" << i << "] " << hand.at(i)<< endl;
	}
	
	cout << "Discard upcard:  [-1]" << endl;
	cout << "Human player " << get_name() << ", please select a card to discard:";
	cin >> cardNumber;
	
	if (cardNumber != -1)
	{
		hand.at(cardNumber) = upcard;
	}
}

//REQUIRES Player has at least one card
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
virtual Card lead_card(const string &trump)
{
	string decision;
	int cardNumber;	
	vector<Card> copyHand;
	
	for(int i = 0; i < (int) hand.size(); i++)
	{
		copyHand.push_back(hand.at(i));	
	}
		
	copyHand = sortHand(copyHand);
	hand = copyHand;
		
	for (int i = 0; i < (int) hand.size(); i++)
	{
		cout << "Human player " << get_name() << "'s hand: [" << i << "] " << hand.at(i).get_rank() << " of " <<
	    hand.at(i).get_suit() << endl;
	}
	
	cout << "Human player " << get_name() << ", please select a card:"<<endl;
	cin >> cardNumber;	
	
	Card lead = hand.at(cardNumber);
	vector <Card> new_hand;
	
	for (int i=0; i < (int) hand.size(); i++) 
	{
		if(i != cardNumber)
		{
			new_hand.push_back(hand.at(i));
		}
	}
	
	hand = new_hand;
	cout << lead.get_rank() << " of " << lead.get_suit() << " led by " << get_name() << endl;
	
	return lead;
}

//REQUIRES Player has at least one card
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
virtual Card play_card(const Card &led_card, const string &trump)
{	
	string decision;
	int cardNumber;	
	vector<Card> copyHand;
	
	for(int i = 0; i < (int) hand.size(); i++)
	{
		copyHand.push_back(hand.at(i));	
	}
		
	copyHand = sortHand(copyHand);
	hand = copyHand;
		
	for (int i = 0; i < (int) hand.size(); i++)
	{
		cout << "Human player " << get_name() << "'s hand: [" << i << "] " << hand.at(i).get_rank() << " of " << 
		hand.at(i).get_suit() << endl;
	}
	
	cout << "Human player " << get_name() << ", please select a card:"<<endl;
	cin >> cardNumber;
	Card play = hand.at(cardNumber);
	vector <Card> new_hand;
	
	for (int i=0; i < (int) hand.size(); i++) 
	{
		if(i != cardNumber)
		{
			new_hand.push_back(hand.at(i));
		}
	}
	
	hand = new_hand;
	cout << play << " played by " << get_name() << endl;
	
	return play;
	
}

private:
static vector<Card> sortHand (vector<Card> in_hand)
{
	sort(in_hand.begin(), in_hand.end());	
	return in_hand;
}
string name;
vector<Card> hand;
};
//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* at the end of Game::play
Player * Player_factory(const string &name, const string &strategy)
{
	if(strategy == "Simple")
	{
		return new SimplePlayer(name);
	}
	
	else if(strategy == "Human")
	{
		return new HumanPlayer(name);
	}
	
	else 
	{
		assert(false);
		exit(1);
	}
}

//EFFECTS: Prints player's name to os
ostream & operator<<(ostream &os, const Player &p)
{
	os << p.get_name();
	return os;
}
