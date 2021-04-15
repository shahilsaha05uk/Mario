#include "HighScore.h"
//#include "MainGame.h"

HighScore::HighScore(SDL_Renderer* renderer, bool signal): GameScreen(renderer)
{
	m_renderer = renderer;

	//StoreScore(signal);

	Load();
}
HighScore::~HighScore()
{

}
void HighScore::Load()
{

	ReadInFile();
	WriteInFile();

	Score_infile.open("Score.txt");

	if (Score_infile.is_open())
	{
		if (tempStore.size() > 0 && tempStore.size() < 5)
		{
			for (int i = 0; i < tempStore.size(); i++)
			{
				_scoretext.push_back(new Text(m_renderer, "Fonts/BASTION_.TTF", tempStore.at(i), SMALLTEXTSIZE, { 225,225,225,225 }));
			}
		}
		if (tempStore.size() >= 5)
		{
			for (int i = 0; i < FileSize; i++)
			{
				_scoretext.push_back(new Text(m_renderer, "Fonts/BASTION_.TTF", tempStore.at(i), SMALLTEXTSIZE, { 225,225,225,225 }));
			}
		}

	}
	Score_infile.close();
}
void HighScore::Render()
{
	for (int i = 0; i < _scoretext.size(); i++)
	{
		SDL_Rect* rect = new SDL_Rect;
		rect->x = (SCREEN_WIDTH - SMALLTEXTSIZE) / 2; rect->y = 30*i;
		rect->w = 160; rect->h = 30;
		_scoretext.at(i)->Render(*rect, m_renderer);
	}
}




void HighScore::ReadInFile()
{
	Score_infile.open("Score.txt");

	string temptext;


	int count = 0;
	while (getline(Score_infile, temptext))
	{
		cout << "Score: " << temptext << endl;
		tempStore.push_back(temptext);
		count++;

		if (Score_infile.eof())
			break;
	}

	cout << "\nCount: " << count << "\n" << endl;
	Score_infile.close();

	FileSize = tempStore.size() - 5;
}
void HighScore::WriteInFile()
{
	Score_outfile.open("x.txt");

	if (Score_outfile.is_open())
	{
		if (tempStore.size() > 5)
		{
			cout << tempStore.size() << endl;
			for (int i = FileSize; i < tempStore.size(); i++)
			{
				cout << tempStore.at(i) << endl;
				Score_outfile << tempStore.at(i) << endl;
			}
		}
		else if(tempStore.size()<5)
		{
			cout <<"Temp size: "<< tempStore.size() << endl;

			for (int i = 0; i < tempStore.size(); i++)
			{
				cout << tempStore.at(i) << endl;
				Score_outfile << tempStore.at(i) << endl;
			}
		}
	}
	Score_outfile.close();


	if (FileSize > 5)
	{
		remove("Score.txt");
		rename("x.txt", "Score.txt");
	}
}
//void HighScore::StoreScore(bool b)
//{
//	int tempscore = 0;
//	if (b == true)
//	{
//		tempscore += ScoreRecord();
//		cout << "Scores are: " << tempscore;
//		b = false;
//
//	}
//	Score_outfile.open("Score.txt", ios::app);
//	if (tempscore > 0)
//	{
//		Score_outfile << "Score is: " << tempscore << endl;
//	}
//	Score_outfile.close();
//
//	if (!Score_outfile.is_open())
//	{
//		cout << "File successfully updated" << endl;
//	}
//}