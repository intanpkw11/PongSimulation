class Score {

private:

	int PlayerXScore;
	int PlayerYScore;

public:

	Score(int px, int py) {

		PlayerXScore = px;
		PlayerYScore = py;

	}

	void theScore(int px, int py) {

		PlayerXScore += px;
		PlayerYScore += py;

	}

	int xScore() {

		return PlayerXScore;

	}

	int yScore() {

		return PlayerYScore;

	}

};
