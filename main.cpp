
#include<SFML/Graphics.hpp>
#include<time.h>
#include<vector>
#include<string>
#include "Button.h"
#include "Rectangles.h"
using namespace sf;

const int M = 20;
const int N = 10;

vector<vector<int>> field;

void CheckLines()
{
	int k = M - 1;
	for (int i = k; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			if (field[i][j])
				count++;
			field[k][j] = field[i][j];
		}
		if (count < N)
			k--;
	}
}

int main()
{
	for (int i = 0; i < M; i++)
	{
		vector<int> tmp(N, 0);
		field.push_back(tmp);
	}
	srand(time(0));
	RenderWindow MainWindow(VideoMode(320, 480), "The Game!");
	//加载纹理
	Texture frame,bg;
	bg.loadFromFile("images/background.png");
	frame.loadFromFile("images/frame.png");
	Rectangles rectangs,tied;
	rectangs.setTexture("images/tiles.png");
	rectangs.setApp(&MainWindow);
	rectangs.getNewRectangle();
	tied.setTexture("images/tiles.png");
	tied.setApp(&MainWindow);
	//rectangs.getNewRectangle();
	//rectangs.show();
	//生成背景精灵
	Sprite background(bg), fr(frame);

	Font font;
	if (!font.loadFromFile("ttf/arial.ttf"))
	{
		return 0;
	}
	Text GameOver;
	GameOver.setFont(font);
	GameOver.setString("Game Over");
	GameOver.setCharacterSize(24);
	GameOver.setFillColor(Color::Black);
	float timer = 0;

	Clock clock;

	while (MainWindow.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event User;
		while (MainWindow.pollEvent(User))
		{
			if (User.type == Event::Closed)
				MainWindow.close();
			if (User.type == Event::KeyPressed)
			{
				if (User.key.code == Keyboard::Up)
					rectangs.Rotate = true;
				else if (User.key.code == Keyboard::Left)
					rectangs.Dx = -1;
				else if (User.key.code == Keyboard::Right)
					rectangs.Dx = 1;
				else if (User.key.code == Keyboard::R)
				{
					for (int i = 0; i < M; i++)
					{
						for (int j = 0; j < N; j++)
						{
							field[i][j] = 0;
						}
					}
					rectangs.getNewRectangle();
				}
			}
		}
		if (User.key.code == Keyboard::Down)
			rectangs.delay = 0.1;

		rectangs.MoveLeftOrRight(field);
		if (rectangs.Rotate)
		{
			rectangs.MoveRotate(field);
		}
		//rectangs.MoveDown(timer, field);
		if (timer > rectangs.delay)
		{
			rectangs.MoveDown(field);
			timer = 0;
		}
		CheckLines();

		//updata
		MainWindow.clear(Color::White);
		MainWindow.draw(background);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0)
					continue;
				tied.show(field[i][j], i, j);
			}
		}
		rectangs.show();
		//GameOver
		if (rectangs.isGameOver(field))//判断是否满
		{
			RenderWindow Notice(VideoMode(200, 100), "Notice");
			Button Restart, Quit;
			Restart.setApp(&Notice);
			Quit.setApp(&Notice);
			Restart.setTexture("images/restart.png");
			Quit.setTexture("images/quit.png");
			Restart.setPosition(40, 70);
			Quit.setPosition(110, 70);
			Notice.clear(Color::White);
			Restart.show();
			Quit.show();
			GameOver.setPosition(25, 25);
			Notice.draw(GameOver);
			Notice.display();
			while (Notice.isOpen())
			{
				Event Close;
				while (Notice.pollEvent(Close))
				{
					if (Restart.OnClick(Close))
					{
						for (int i = 0; i < M; i++)
						{
							for (int j = 0; j < N; j++)
							{
								field[i][j] = 0;
							}
						}
						Notice.close();
					}
					if (Quit.OnClick(Close))
					{
						Notice.close();
						MainWindow.close();
					}
				}
			}
		}
		MainWindow.draw(fr);
		MainWindow.display();
	}
}
