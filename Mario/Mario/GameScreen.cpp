#include "GameScreen.h"
#include "HighScore.h"
#include "GameScreenManager.h"
#include "HealthBar.h"
GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer= renderer;
}
GameScreen::~GameScreen()
{
	m_renderer = nullptr;

}

void GameScreen::Render()
{
}
void GameScreen::Update(float deltaTime, SDL_Event e)
{

}

int GameScreen::ScoreRecord(int score)
{
	static int totalpoint;
	totalpoint += score;

	cout << totalpoint << endl;
	return totalpoint;
}

void GameScreen::WriteToScoreFile()
{
	int tempscore = ScoreRecord();
	ofstream outfile;
	outfile.open("Score.txt", ios::app);
	outfile <<"Score is: "<< tempscore << endl;
	outfile.close();

	ScoreRecord(-tempscore);
}