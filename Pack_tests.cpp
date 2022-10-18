#include "Pack.h"
#include <iostream>
#include <cassert>
using namespace std;

// ADD PROTOTYPES FOR YOU TEST FUNCTIONS HERE

int main() {

  // CALL YOUR TEST FUNCTIONS HERE
  Pack pack("pack.in");

  Card first_card = pack.deal_one();
  assert(first_card == Card(Card::RANK_NINE, Card::SUIT_SPADES));

  assert(!pack.empty());

  pack.reset();

  first_card = pack.deal_one();
  assert(first_card == Card(Card::RANK_NINE, Card::SUIT_SPADES));

  pack.shuffle();

  first_card = pack.deal_one();
  assert(first_card == Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  cout << "Pack_tests passed" << endl;
  return 0;
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
