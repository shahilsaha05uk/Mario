#pragma once
#include "GameScreen.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "GameScreenManager.h"


class HighScore : public GameScreen
{
private:
	vector < Text*> _scoretext;
	vector<string> tempStore;

	int FileSize;
	int score;

	ifstream Score_infile;
	ofstream Score_outfile;
	string scores;
public:
	HighScore(SDL_Renderer *renderer, bool signal);
	~HighScore();

	void Load();
	void Update(SDL_Event e, float deltatime);
	void Render();

	void UpdateFile();
	void ReadInFile();
	void RenderScores();

};

