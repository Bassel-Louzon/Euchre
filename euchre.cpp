//Bassel Louzon  and Lucas Mata
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <cstring>
#include <vector>
#include <string>
#include "Player.h"
#include "Card.h"
#include "Pack.h"

using namespace std;

struct Game
{
	Pack euchre_pack;
	Player *players[4];
	string order_up_suit;
	int team1pts;
	int team2pts;
	int tricks1_won;
	int tricks2_won;
	int hand_tracker;
};

//Detemines which team won the trick. If team 1 wins, return true. If team 2 wins, return false
static bool trick(Game &game, int &player_index)
{
	int winner_index = player_index;
	const Card lead = game.players[player_index]->lead_card(game.order_up_suit);
	player_index = (player_index + 1) % 4;
	Card high = lead;
	for (int i = 0; i < 3; ++i) 
	{
		const Card current = game.players[player_index]->play_card(lead, game.order_up_suit);
		if (Card_less(high, current, lead, game.order_up_suit))
		{
			high = current;
			winner_index = player_index;
		}
		player_index = (player_index+1) % 4;
	}
	player_index = winner_index;
	if (winner_index == 0 || winner_index == 2) 
	{
		cout<<game.players[winner_index]->get_name()<<" takes the trick"<<endl;
		cout<<endl;
		return true;
	}
	else 
	{
		cout<<game.players[winner_index]->get_name()<<" takes the trick"<<endl;
		cout<<endl;
		return false;
	}
}

//Deals the cards to each player 3-2-3-2 then 2-3-2-3
static void deal_cards(Game &game, int player_index)
{
	for (int i = 0; i < 8; ++i) //Looping through each player getting cards twice
	{
		//Determining if current player gets 2 or 3 cars
		if(i == 0 || i == 2 || i == 5 || i == 7) //Gets three cards
		{
			game.players[player_index]->add_card(game.euchre_pack.deal_one());
			game.players[player_index]->add_card(game.euchre_pack.deal_one());
			game.players[player_index]->add_card(game.euchre_pack.deal_one());
		}
		else //Gets two cards
		{
			game.players[player_index]->add_card(game.euchre_pack.deal_one());
			game.players[player_index]->add_card(game.euchre_pack.deal_one());
		}
		player_index = (player_index + 1) % 4;
	}
}

//Determining who ordered up
static void making_trump(Game &game, const Card &upcard, int &dealer_index, int player_index, bool &ordered_up1, bool &ordered_up2)
{
	//Making trump round 1
	for (int i = 0; i < 4; ++i) 
	{
		if(game.players[player_index]->make_trump(upcard, *game.players[dealer_index], 1, game.order_up_suit))
		{
			if(player_index == 0 || player_index == 2)
			{
				ordered_up1 = true;
			}
			else 
			{
				ordered_up2 = true;
			}
			game.players[dealer_index]->add_and_discard(upcard);
			cout<<endl;
		    break;
		}
		player_index = (player_index + 1) % 4;
	}
	player_index = (dealer_index + 1) % 4;	
	//Making trump round 2
	if(ordered_up1 == false && ordered_up2 == false)
	{
		for (int i = 0; i < 3; ++i) 
		{
		 	if(game.players[player_index]->make_trump(upcard, *game.players[dealer_index], 2, game.order_up_suit))
			{
				if(player_index == 0 || player_index == 2)
				{
					ordered_up1 = true;
				}
				else 
				{
					ordered_up2 = true;
				}
				cout<<endl;
				break;
			}
		}
		player_index = (player_index + 1) % 4;
	}
	
	//screw the dealer	
	if (ordered_up1 == false && ordered_up2 == false)
	{
		game.order_up_suit = upcard.get_suit(upcard.get_suit());
		if(dealer_index == 0 || dealer_index == 2)
		{
			ordered_up1 = true;
		}
		else 
		{
			ordered_up2 = true;	
		}
		cout<<endl;
	}
}


int main(int argc, char *argv[]) 
{
	string filename;
	string shuffle_choice;
	Game game;
	game.team1pts = 0;
	game.team2pts = 0;
	game.hand_tracker = 0;
	int points_to_win = 0;
 	
	//Printing out error message if command arguments aren't 12
	if(argc != 12)
	{
		cout <<"Usage: euchre "<<argv[1]<<" "<<argv[2]<<" "<<
		argv[3]<<" "<<argv[4]<<" "<<argv[6]<<" "<<argv[8]<<" "<<argv[10]<<endl;
		exit(1);
	}
	
	//Printing out error message if points to win is not valid
	//Requires:  Points to win < 100 or Points to win < 1
	if(atoi(argv[3]) < 1 || atoi(argv[3]) > 100)
	{
		cout <<"Usage: euchre "<<argv[1]<<" "<<argv[2]<<" "<<
	    argv[3]<<" "<<argv[4]<<" "<<argv[6]<<" "<<argv[8]<<" "<<argv[10]<<endl;
		exit(1);
	}
	
	//Printing out error message if shuffle choice is invalid
	//Requires: Third command argument not be shuffle or noshuffle
	if (!strcmp(argv[2],"shuffle") && !strcmp(argv[2],"noshuffle"))
	{
		cout <<"Usage: euchre "<<argv[1]<<" "<<argv[2]<<" "<<
		argv[3]<<" "<<argv[4]<<" "<<argv[6]<<" "<<argv[8]<<" "<<argv[10]<<endl;
		exit(1);
	}
	
	//Printing out error message if player type is invalid
	//Requires: Fifth, Seventh, Ninth , or 11th command arguments are not Human or Simple
	if(!strcmp(argv[5],"Human") && !strcmp(argv[5],"Simple"))
	{
		cout <<"Usage: euchre "<<argv[1]<<" "<<argv[2]<<" "<<
		argv[3]<<" "<<argv[4]<<" "<<argv[6]<<" "<<argv[8]<<" "<<argv[10]<<endl;
		exit(1);
	}
	if(!strcmp(argv[7],"Human") && !strcmp(argv[7],"Simple"))
	{
		cout <<"Usage: euchre "<<argv[1]<<" "<<argv[2]<<" "<<
		argv[3]<<" "<<argv[4]<<" "<<argv[6]<<" "<<argv[8]<<" "<<argv[10]<<endl;
		exit(1);
	}
	if(!strcmp(argv[9],"Human") && !strcmp(argv[9],"Simple"))
	{
		cout <<"Usage: euchre "<<argv[1]<<" "<<argv[2]<<" "<<
		argv[3]<<" "<<argv[4]<<" "<<argv[6]<<" "<<argv[8]<<" "<<argv[10]<<endl;
		exit(1);
	}
	if(!strcmp(argv[11],"Human") && !strcmp(argv[11],"Simple"))
	{
		cout <<"Usage: euchre "<<argv[1]<<" "<<argv[2]<<" "<<
		argv[3]<<" "<<argv[4]<<" "<<argv[6]<<" "<<argv[8]<<" "<<argv[10]<<endl;
		exit(1);
	}
	for (int i = 0; i < 12; ++i) 
	{
		cout<<argv[i]<<" ";
	}
	cout<<endl;
	filename = argv[1];
	game.euchre_pack = Pack(filename);
	shuffle_choice = argv[2];
	points_to_win = atoi(argv[3]);
	
	game.players[0] = Player_factory(argv[4] , argv[5]);
	game.players[1] = Player_factory(argv[6], argv[7]);
	game.players[2] = Player_factory(argv[8], argv[9]);
	game.players[3] = Player_factory(argv[10], argv[11]);
	
	//Looping through the hands until a winner is decided
	while (game.team1pts < points_to_win && game.team2pts < points_to_win) 
	{
		bool ordered_up1 = false;
		bool ordered_up2 = false;
		game.tricks1_won = 0;
		game.tricks2_won = 0;
		
		if(shuffle_choice == "shuffle")
		{
			game.euchre_pack.reset();
			game.euchre_pack.shuffle();
		}
		
		if(shuffle_choice == "noshuffle")
		{
			game.euchre_pack.reset();
		}
		
		//Printing out current hand
		cout<<"Hand "<<game.hand_tracker<<endl;
		
		//Keeping track of dealer
		int dealer_index = game.hand_tracker % 4;
		
		string dealer = game.players[dealer_index]->get_name();
		cout<<dealer<<" deals"<<endl;
		
		//Starting at player to left of dealer
		int player_index = (dealer_index + 1) % 4;
		
		//Dealing cards to players
		deal_cards(game, player_index);
		
		//Setting upcard
		const Card upcard = game.euchre_pack.deal_one();
		cout<<upcard<<" turned up"<<endl;
		game.order_up_suit = upcard.get_suit();
		
		//Calling function to determine who ordered up
		making_trump(game, upcard, dealer_index, player_index, ordered_up1, ordered_up2);
				
		//Tricks for the current hand
		for (int i = 0; i < 5; ++i)
		{
			bool trick_winner = trick(game, player_index); 
			if(trick_winner == true)
			{
				game.tricks1_won = game.tricks1_won + 1;
			}
			if(trick_winner == false)
			{
				game.tricks2_won = game.tricks2_won + 1;
			}
			
		}
		
		//Adding up team points and printing up winner of hand
		
		//Team 1 winning and ordering up
		if(ordered_up1 == true) 
		{
			if(game.tricks1_won == 3 || game.tricks1_won == 4)
			{
				game.team1pts = game.team1pts + 1;
				cout<<game.players[0]->get_name()<<" and "<<game.players[2]->get_name()<<" win the hand"<<endl;
			}
			if(game.tricks1_won == 5)
			{
				game.team1pts = game.team1pts + 2;
				cout<<game.players[0]->get_name()<<" and "<<game.players[2]->get_name()<<" win the hand"<<endl;
				cout<<"march!"<<endl;
			}
		}
		
		//Team 2 winning hand and ordering up
		if(ordered_up2 == true) 
		{	
			if(game.tricks2_won == 3 || game.tricks2_won == 4)
			{
				game.team2pts = game.team2pts + 1;
				cout<<game.players[1]->get_name()<<" and "<<game.players[3]->get_name()<<" win the hand"<<endl;
			}
			if(game.tricks2_won == 5)
			{
				game.team2pts = game.team2pts + 2;
				cout<<game.players[1]->get_name()<<" and "<<game.players[3]->get_name()<<" win the hand"<<endl;
				cout<<"march!"<<endl;
			}
		}
		
		// Team 1 winning hand and not ordering up
		if(ordered_up1 == false) 
		{
			if(game.tricks1_won > 2)
			{
				cout<<game.players[0]->get_name()<<" and "<<game.players[2]->get_name()<<" win the hand"<<endl;
				game.team1pts = game.team1pts + 2;
				cout<<"euchred!"<<endl;
			}
		}
		
		//Team 2 winning hand and not ordering up
		if(ordered_up2 == false) 
		{
			if(game.tricks2_won > 2)
			{
				cout<<game.players[1]->get_name()<<" and "<<game.players[3]->get_name()<<" win the hand"<<endl;
				game.team2pts = game.team2pts + 2;
				cout<<"euchred!"<<endl;
			}			
		}
		
		//Printing out team points
		cout<<game.players[0]->get_name()<<" and "<<game.players[2]->get_name()<<" have "<<game.team1pts<<" points"<<endl;
		cout<<game.players[1]->get_name()<<" and "<<game.players[3]->get_name()<<" have "<<game.team2pts<<" points"<<endl;
		cout<<endl;
		++game.hand_tracker;
	}
	
	
	//Printing out the winner of the game
	//Team 1 wins
	if (game.team1pts >= points_to_win)
	{
		cout<<game.players[0]->get_name()<<" and "<<game.players[2]->get_name()<<" win!"<<endl;
	}
	
	//Team 2 wins
	if (game.team2pts >= points_to_win)
	{
		cout<<game.players[1]->get_name()<<" and "<<game.players[3]->get_name()<<" win!"<<endl;
	}
	
	//Deleting the dynamically allocated players
	for (int i = 0; i < 4; ++i) 
	{
		delete game.players[i];
		game.players[i] = 0;
	}
	
	return 0;
}
