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
virtual bool make_trump(const Card &upcard, const Player &dealer,
                          int round, string &order_up_suit) const
{
	if (round == 1)
	{
		if (decision == "pass") 
		{
		   return false;
		}
		else
		{
			order_up_suit = decision;
			return true;
		}
		
	}
	else 
	{
		if (decision == "pass")
		{
			return false;
		}
		else 
		{
			order_up_suit = decision;
			return true;
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
	Card lead = hand.at(cardNumber);
	vector <Card> new_hand;
	for (unsigned int i=0; i < hand.size(); i++) 
	{
		if(i != cardNumber)
		{
			new_hand.push_back(hand.at(i));
		}
	}
	hand = new_hand;
	return lead;
}

//REQUIRES Player has at least one card
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
virtual Card play_card(const Card &led_card, const string &trump)
{
	Card play = hand.at(cardNumber);
	vector <Card> new_hand;
	for (unsigned int i=0; i < hand.size(); i++) 
	{
		if(i != cardNumber)
		{
			new_hand.push_back(hand.at(i));
		}
	}
	hand = new_hand;
	return play;
}
  // Needed to avoid some compiler errors
 // virtual ~Player() {}
private:
string name;
vector<Card> hand;
///////////INCOMPLETE FUNCTIONS 
string decision;
unsigned int cardNumber;
string get_decision()
{
	return decision;
}

int get_cardNumber()
{
	return cardNumber;
}

////////////////////////////////////
};
