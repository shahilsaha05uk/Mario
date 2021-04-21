#include "HighScore.h"
//#include "MainGame.h"

HighScore::HighScore(SDL_Renderer* renderer, bool signal): GameScreen(renderer)
{
	m_renderer = renderer;

	Load();
}
HighScore::~HighScore()
{

}
void HighScore::Load()
{
	game_manager = new GameScreenManager(m_renderer);

	UpdateFile();
	ReadInFile();
	RenderScores();

	Score_infile.open("Score.txt");
	Score_infile.close();
}


void HighScore::Render()
{
	for (int i = 0; i < _scoretext.size(); i++)
	{
		SDL_Rect* rect = new SDL_Rect;
		rect->x = (SCREEN_WIDTH - SMALLTEXTSIZE) / 2; rect->y = 30 * i;
		rect->w = 160; rect->h = 30;
		_scoretext.at(i)->Render(*rect, m_renderer);
	}
}


//1. read the lines to a vector
void HighScore::ReadInFile()
{
	Score_infile.open("Score.txt");

	string temptext;
	int count = 0;

	if (Score_infile.is_open())
	{
		while (getline(Score_infile, temptext))
		{
			tempStore.push_back(temptext);
			count++;

			if (Score_infile.eof())
			{
				break;
			}
		}
	}
	cout << "\nCount: " << count << "\n" << endl;
	Score_infile.close();

}

//2. Render the scores as text to the screen
void HighScore::RenderScores()
{
	for (int i = 0; i < tempStore.size(); i++)
	{
		_scoretext.push_back(new Text(m_renderer, game_manager->fontLoad[1], tempStore.at(i)));
	}
}

//Check if the file has more than 5 records
void HighScore::UpdateFile()
{
	vector<string> tempdata;
	int count = 0;
	//storing the lines to a vector string
	Score_infile.open("Score.txt");
	string temptext;
	if (Score_infile.is_open())
	{
		while (getline(Score_infile, temptext))
		{
			count++;
			if (Score_infile.eof())
				break;
		}
	}
	Score_infile.close();

	if (count >= 6)
	{
		remove("Score.txt");
		rename("temp.txt", "Score.txt");
	}

}
