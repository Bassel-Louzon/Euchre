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
