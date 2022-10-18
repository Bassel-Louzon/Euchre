#include "Player.h"
#include "Card.h"
#include <iostream>
#include <cassert>
using namespace std;

// ADD PROTOTYPES FOR YOU TEST FUNCTIONS HERE
void human_basic_test();
void simple_basic_lead_card_test();
void simple_basic_play_card_test();
void simple_basic_make_trump_test();
void simple_basic_make_trump2_test();
void simple_trumps_lead_card_test();

int main() {

  // CALL YOUR TEST FUNCTIONS HERE
	//human_basic_test();
	//simple_basic_lead_card_test();
	//simple_basic_play_card_test();
	//simple_basic_make_trump_test();

	//tests add and discard, and lead card with a hand of all trumps
	//simple_trumps_lead_card_test();

	//tests that make trump works for round two
	simple_basic_make_trump2_test();

	
  cout << "Player_tests passed" << endl;
  return 0;
}
void simple_basic_lead_card_test()
{
	Player * chad = Player_factory("Chad", "Simple");
	
	Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  	Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  	Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
	Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  	Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
		
	chad->add_card(two_spades);
	chad->add_card(king_hearts);
	chad->add_card(two_spades);
	chad->add_card(king_diamonds);
	chad->add_card(two_spades);
	
	Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
        string trump = Card::SUIT_SPADES;

	chad->add_and_discard(jack_spades);
	Card card_led = chad->lead_card(trump);
	Card card_play = chad->play_card(card_led, trump);
  	assert(card_led == king_diamonds);	
	
}
void simple_basic_play_card_test()
{
	Player * chad = Player_factory("Chad", "Simple");
	
	Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  	Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  	Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
	Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  	Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
		
	chad->add_card(two_spades);
	chad->add_card(king_hearts);
	chad->add_card(two_spades);
	chad->add_card(king_diamonds);
	chad->add_card(two_spades);
	
	Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
        string trump = Card::SUIT_SPADES;

	Card card_led = chad->lead_card(trump);
	Card card_play = chad->play_card(card_led, trump);
	
  	assert(card_play == king_hearts);	
	
}
void simple_basic_make_trump_test()
{
	Player * chad = Player_factory("Chad", "Simple");
	
	Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  	Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  	Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
	Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
  	Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
		
	chad->add_card(two_spades);
	chad->add_card(king_spades);
	chad->add_card(jack_spades);
	chad->add_card(king_diamonds);
	chad->add_card(two_spades);

	string trump = Card::SUIT_SPADES;
	
	bool ou = chad->make_trump(two_spades, *chad, 1, trump);
	assert(ou == true);	
	
}
void simple_basic_make_trump2_test()
{
	Player * chad = Player_factory("Chad", "Simple");
	
	Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  	Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  	Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
	Card king_clubs = Card(Card::RANK_KING, Card::SUIT_CLUBS);
  	Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
		
	chad->add_card(two_spades);
	chad->add_card(king_clubs);
	chad->add_card(jack_spades);
	chad->add_card(king_diamonds);
	chad->add_card(two_spades);

	string trump = Card::SUIT_SPADES;
	
	bool ou = chad->make_trump(two_spades, *chad, 2, trump);
	assert(ou == true);	
	
}
void simple_trumps_lead_card_test()
{
	Player * chad = Player_factory("Chad", "Simple");
	
	Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  	Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
  	Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
	Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  	Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
		
	chad->add_card(two_spades);
	chad->add_card(three_spades);
	chad->add_card(two_spades);
	chad->add_card(king_diamonds);
	chad->add_card(king_diamonds);
	
	Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
        string trump = Card::SUIT_SPADES;

	chad->add_and_discard(nine_spades);
	Card card_led = chad->lead_card(trump);
	Card card_play = chad->play_card(card_led, trump);
  	//assert(card_led ==nine_spades);	
	card_play = chad->play_card(card_led,trump);
	card_play = chad->play_card(card_led,trump);
	card_play = chad->play_card(card_led,trump);
}
/*void human_basic_test()
{
	Player * chad = Player_factory("Chad", "Human");

	Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  	Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  	Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
	Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  	Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
	
	chad->add_card(two_spades);
	chad->add_card(king_hearts);
	chad->add_card(two_spades);
	chad->add_card(king_diamonds);
	chad->add_card(two_spades);
	
	Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
        string trump = Card::SUIT_SPADES;
	//bool ou = chad->make_trump(nine_spades, *chad, 1, trump);
	chad->add_and_discard(jack_spades);
	Card card_led = chad->lead_card(trump);
	Card card_play = chad->play_card(card_led, trump);
  	assert(card_led == jack_spades);
	

}*/

