#include "Card.h"
#include <iostream>
#include <cassert>

using namespace std;

// ADD PROTOTYPES FOR YOU TEST FUNCTIONS HERE
void test_1();
void testJ_H();
void testled();
void test_suit_next();


int main() 
{
 
  test_1();
  testJ_H();
  testled();
  test_suit_next();
  
  cout << "PASS" << endl;
  return 0;
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
void test_1()
{
	
	Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
	Card test1 = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card test1copy = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card Led = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);	cout<< test1 << endl;
	
	assert(test1.get_rank() == Card::RANK_ACE);
	assert(test1.get_suit() == Card::SUIT_CLUBS);
	assert(test1.get_suit(Card::SUIT_HEARTS) == Card::SUIT_CLUBS);
	
	assert(test1.is_face());
	assert(!test1.is_right_bower(Card::SUIT_CLUBS));
	assert(!test1.is_left_bower(Card::SUIT_CLUBS));
	assert(test1.is_trump(Card::SUIT_CLUBS));
	
    assert((two_spades < test1));
    assert((test1 > two_spades));
    assert(two_spades == two_spades);
    assert(two_spades != test1);

    assert(!(test1copy < test1));
    assert(!(test1 > test1copy));
    assert(test1 == test1copy);
    
    assert(Card_less(two_spades, test1, Card::SUIT_CLUBS));
    assert(!Card_less(test1, two_spades, Led, Card::SUIT_CLUBS));
}

void testJ_H()
{
	
	Card test1 = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card Led = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
	Card Jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
	Card Jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
	
	cout<< Led << endl;
	cout<< Jack_hearts << endl;
	cout<< Jack_diamonds << endl;
	
    assert(Jack_hearts.get_rank() == Card::RANK_JACK);
	assert(Jack_hearts.get_suit() == Card::SUIT_HEARTS);
	assert(Jack_hearts.get_suit(Card::SUIT_CLUBS) == Card::SUIT_HEARTS);
	assert(Jack_hearts.get_suit(Card::SUIT_DIAMONDS) == Card::SUIT_DIAMONDS);
	
	assert(Jack_hearts.is_face());
    assert(!Jack_hearts.is_right_bower(Card::SUIT_DIAMONDS));
    assert(Jack_hearts.is_right_bower(Card::SUIT_HEARTS));
    assert(Jack_hearts.is_left_bower(Card::SUIT_DIAMONDS));
    assert(!Jack_hearts.is_trump(Card::SUIT_CLUBS));

    assert(Jack_hearts != test1);

    assert((Jack_hearts < test1));
    assert((Jack_hearts > Led));
    assert(Jack_hearts != Led);
	
    assert(Card_less(Led, Jack_hearts, Card::SUIT_CLUBS));
	assert(!Card_less(Led, Jack_hearts, Led, Card::SUIT_CLUBS));
	assert(Card_less(Led, Jack_hearts, Led, Card::SUIT_HEARTS));
    assert(Card_less(Led, Jack_hearts, Led, Card::SUIT_DIAMONDS));
	assert(Card_less(test1, Jack_hearts, Led, Card::SUIT_DIAMONDS));
	assert(Card_less(test1, Jack_hearts, Led, Card::SUIT_HEARTS));
	assert(Card_less(Jack_hearts, test1, Led, Card::SUIT_SPADES));
	assert(Card_less(Jack_hearts, Led, Led, Card::SUIT_SPADES));
	assert(Card_less(Jack_hearts, Jack_diamonds,Card::SUIT_DIAMONDS));
}

void testled()
{
	Card Led = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
	assert(Led.get_rank() == Card::RANK_NINE);
	assert(Led.get_suit() == Card::SUIT_DIAMONDS);
	assert(Led.get_suit(Card::SUIT_DIAMONDS) == Card::SUIT_DIAMONDS);
	
    assert(!Led.is_face());
	assert(!Led.is_right_bower(Card::SUIT_CLUBS));
	assert(!Led.is_left_bower(Card::SUIT_CLUBS));
	assert(!Led.is_trump(Card::SUIT_CLUBS));

}

void test_suit_next()
{
	assert(Suit_next(Card::SUIT_CLUBS) == Card::SUIT_SPADES);
	assert(Suit_next(Card::SUIT_DIAMONDS) == Card::SUIT_HEARTS);
	assert(Suit_next(Card::SUIT_SPADES) == Card::SUIT_CLUBS);
	assert(Suit_next(Card::SUIT_HEARTS) == Card::SUIT_DIAMONDS);
}
