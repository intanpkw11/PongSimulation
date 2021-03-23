#include <iostream>
#include <stdlib.h>

using namespace std;

class Player {

private:

	enum player { PlayerX, PlayerY } playerReady;
	int Hits;

public:

	Player(int turn) {

		if (turn == 1) {

			playerReady = player::PlayerX;

		}

		else {

			playerReady = player::PlayerY;
		}

		Hits = 0;
	}

	Player(Player& turn) {

		if (turn.playerReady == player::PlayerX) {

			playerReady = player::PlayerY;

		}

		else {

			playerReady = player::PlayerX;
		}

		Hits = turn.Hits;
	}

	void setHits(int r) {
		Hits = r;
	}

	int getHits() {
		return Hits;
	}

	player getPlayer() {
		return playerReady;
	}
};