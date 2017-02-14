#pragma once
class ScoreBoard
{
	private:
		int points;
public:
	ScoreBoard();
	~ScoreBoard();

	void addPoints(int points);
	void draw();
};
