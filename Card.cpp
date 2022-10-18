#include "Card.h"
#include <string>
#include <cassert>
using namespace std;

const string Card::RANK_TWO = "Two";
const string Card::RANK_THREE = "Three";
const string Card::RANK_FOUR = "Four";
const string Card::RANK_FIVE = "Five";
const string Card::RANK_SIX = "Six";
const string Card::RANK_SEVEN = "Seven";
const string Card::RANK_EIGHT = "Eight";
const string Card::RANK_NINE = "Nine";
const string Card::RANK_TEN = "Ten";
const string Card::RANK_JACK = "Jack";
const string Card::RANK_QUEEN = "Queen";
const string Card::RANK_KING = "King";
const string Card::RANK_ACE = "Ace";

const string Card::SUIT_SPADES = "Spades";
const string Card::SUIT_HEARTS = "Hearts";
const string Card::SUIT_CLUBS = "Clubs";
const string Card::SUIT_DIAMONDS = "Diamonds";

////////////////////////////////////////////////////////////////////////////////
// Suits in order from lowest suit to highest suit.
static const string SUIT_NAMES_BY_WEIGHT[] = {
  Card::SUIT_SPADES,
  Card::SUIT_HEARTS,
  Card::SUIT_CLUBS,
  Card::SUIT_DIAMONDS
};
static const int NUM_SUITS = 4;

// Ranks in order from lowest rank to highest rank.
static const string RANK_NAMES_BY_WEIGHT[] = {
  Card::RANK_TWO,
  Card::RANK_THREE,
  Card::RANK_FOUR,
  Card::RANK_FIVE,
  Card::RANK_SIX,
  Card::RANK_SEVEN,
  Card::RANK_EIGHT,
  Card::RANK_NINE,
  Card::RANK_TEN,
  Card::RANK_JACK,
  Card::RANK_QUEEN,
  Card::RANK_KING,
  Card::RANK_ACE
};
static const int NUM_RANKS = 13;


//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"  
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const string &rank_in, const string &suit_in) : rank(rank_in), suit(suit_in)
{
	int i=0;
	while((rank_in != RANK_NAMES_BY_WEIGHT[i]) && (i != 13)) 
	{
		i+=1;
	}
	int j=0;
	while((suit_in != SUIT_NAMES_BY_WEIGHT[j]) && (j != 4))
	{
		j+=1;
	}
	assert(suit_in == SUIT_NAMES_BY_WEIGHT[j]);
	assert(rank_in == RANK_NAMES_BY_WEIGHT[i]);
}

//EFFECTS Returns the rank 
string Card::get_rank() const
{
  return rank;
}

//EFFECTS Returns the suit.  Does not consider trump. 
string Card::get_suit() const
{
	return suit;
}

//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
string Card::get_suit(const string &trump) const
{
	if(is_left_bower(trump))
	{
		return trump;
	}
	else 
	{
		return get_suit();
	}
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const
{
	if (rank == Card::RANK_JACK || rank == Card::RANK_QUEEN || rank == Card::RANK_KING 
	|| rank == Card::RANK_ACE)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const string &trump) const
{
	if(rank == Card::RANK_JACK && suit == trump)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const string &trump) const
{
	if (rank != Card::RANK_JACK)
	{
		return false;
	}
	else //if (rank == Card::RANK_JACK)
	{
		if(trump == Card::SUIT_SPADES && suit == Card::SUIT_CLUBS)
		{
			return true;
		}
		else if (trump == Card::SUIT_SPADES && suit != Card::SUIT_CLUBS) 
		{
			return false;
		}
		if(trump == Card::SUIT_CLUBS && suit == Card::SUIT_SPADES)
		{
			return true;
		}
		else if (trump == Card::SUIT_CLUBS && suit != Card::SUIT_SPADES)
		{
			return false;
		}
		if(trump == Card::SUIT_HEARTS && suit == Card::SUIT_DIAMONDS)
		{
			return true;
		}
		else if (trump == Card::SUIT_HEARTS && suit != Card::SUIT_DIAMONDS) 
		{
			return false;
		}
		if (trump == Card::SUIT_DIAMONDS && suit == Card::SUIT_HEARTS) 
		{
			return true;
		}
		else //if(trump == Card::SUIT_DIAMONDS && suit != Card::SUIT_HEARTS)
		{
			return false;
		}
		
	}
}

//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const string &trump) const
{
	if(suit == trump)
	{
		return true;
	}
	else if(is_left_bower(trump))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs)
{
	int i=0;
	int j=0;
	int x=0;
	int y=0;
	
	while (lhs.get_rank() != RANK_NAMES_BY_WEIGHT[i]) 
	{
		++i;
	}
	
	while (rhs.get_rank() != RANK_NAMES_BY_WEIGHT[j]) 
	{
		++j;
	}
	
	while (lhs.get_suit() != SUIT_NAMES_BY_WEIGHT[x])
	{
		++x;
	}
	
	while (rhs.get_suit() != SUIT_NAMES_BY_WEIGHT[y])
	{
		++y;
	}
	
    if (i < j)
	{
		return true;
	}
	
	else if (i == j) 
	{
		if (x < y)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	else 
	{
		return false;
	}
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs)
{
	int i=0;
	int j=0;
	int x=0;
	int y=0;
	
	while (lhs.get_rank() != RANK_NAMES_BY_WEIGHT[i]) 
	{
		++i;
	}
	
	while (rhs.get_rank() != RANK_NAMES_BY_WEIGHT[j]) 
	{
		++j;
	}
	
	while (lhs.get_suit() != SUIT_NAMES_BY_WEIGHT[x])
	{
		++x;
	}
	
	while (rhs.get_suit() != SUIT_NAMES_BY_WEIGHT[y])
	{
		++y;
	}
	
	if (i > j)
	{
		return true;
	}
	
	else if(i == j)
	{
		if (x > y)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	
	else
	{
		return false;
	}

}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs)
{
	if((lhs.get_suit() == rhs.get_suit()) && (lhs.get_rank() == rhs.get_rank()))
	{
		return true;
	}
	
	else
	{
		return false;
	}

}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs)
{
	if((lhs.get_suit() != rhs.get_suit()) || (lhs.get_rank() != rhs.get_rank()))
	{
		return true;
	}
	
	else
 	{
		return false;
	}
}

//EFFECTS returns the next suit, which is the suit of the same color
string Suit_next(const string &suit)
{
	if (suit == Card::SUIT_SPADES)
	{
		return Card::SUIT_CLUBS;
	}
	
	else if (suit == Card::SUIT_CLUBS)
	{
		return Card::SUIT_SPADES;
	}
	
	else if (suit == Card::SUIT_HEARTS)
	{
		return Card::SUIT_DIAMONDS;
	}
	
	else 
	{
		return Card::SUIT_HEARTS;
	}
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
ostream & operator<<(ostream &os, const Card &card)
{
   os<< card.get_rank() << " of " << card.get_suit();
   return os;
}

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const string &trump)
{
	if (a.is_right_bower(trump))
	{
		return false;
	}
		
	else if (b.is_right_bower(trump))
	{
		return true;
	}
		
	else if(a.is_left_bower(trump))
	{
		return false;
	}
		
	else if(b.is_left_bower(trump))
	{
		return true;
	}

	else if ((a < b) && (a.get_suit() != trump) && (b.get_suit() != trump)) 
	{
		return true;
	}
	
	else if ((a > b) && (a.get_suit() != trump) && (b.get_suit() != trump)) 
	{
		return false;
	}
	
	else if (a.get_suit() == trump && b.get_suit() != trump)
	{
		return false;
	}
	
	else if (a.get_suit() != trump && b.get_suit() == trump)
	{
		return true;
	}
	
	else if (a.get_suit() == trump && b.get_suit() == trump && a < b)
	{
		return true;
	}
	
	else 
	{
		return false;
	}
	
}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, const string &trump)
{
	if (a.is_right_bower(trump))
	{
		return false;
	}
		
	else if (b.is_right_bower(trump))
	{
		return true;
	}
		
	else if(a.is_left_bower(trump))
	{
		return false;
	}
		
	else if(b.is_left_bower(trump))
	{
		return true;
	}

	else if (a < b && a.get_suit() != trump && b.get_suit() != trump 
		&& a.get_suit() != led_card.get_suit() && b.get_suit() != led_card.get_suit() ) 
	{
		return true;
	}
	
	else if(a > b && a.get_suit() != trump && b.get_suit() != trump 
	   && a.get_suit() != led_card.get_suit() && b.get_suit() != led_card.get_suit() ) 
	{
			return false;
	}
	
	else if (a.get_suit() == trump && b.get_suit() != trump)
	{
		return false;
	}
	
	else if (a.get_suit() != trump && b.get_suit() == trump)
	{
		return true;
	}
	
	else if (a.get_suit() == trump && b.get_suit() == trump && a < b)
	{
		return true;
	}
		
	else if (a.get_suit() == trump && b.get_suit() == trump && a > b)
	{
		return false;
	}
	
	else if (a.get_suit() == led_card.get_suit() && b.get_suit() == led_card.get_suit() && a < b) 
	{
		return true;
	}
	
	else if (a.get_suit() == led_card.get_suit() && b.get_suit() == led_card.get_suit() && a > b) 
	{
		return false;
	}
	
	else if(a.get_suit() == led_card.get_suit() && b.get_suit() != led_card.get_suit() && a.get_suit() != trump && b.get_suit() != trump)
	{
		return false;
	}
	else if (a == b)
	{
		return false;
	}
	else 
	{
		return true;
	}

}
