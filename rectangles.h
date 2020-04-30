#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
using namespace sf;
using namespace std;



class Rectangles
{
private:
	Texture pic;
	RenderWindow* app;
	
public:
	vector<vector<int>> figures =
	{
		{1,3,5,7},
		{0,2,3,5},
		{1,3,2,4},
		{1,3,2,5},
		{0,1,3,5},
		{1,3,5,4},
		{0,1,2,3}
	};
	struct Point
	{
		int x;
		int y;
	}a[4], acopy[4];
	Sprite s;
	int Dx = 0, ColorNum = 1;
	bool Rotate = false;
	float delay = 0.3;
	void setApp(RenderWindow* app);
	void setTexture(string s);
	void show();
	void show(int left, int i, int j);//show tied
	void getNewRectangle();
	void MoveLeftOrRight(vector<vector<int>>& field);
	void MoveRotate(vector<vector<int>>& field);
	void MoveDown(vector<vector<int>>& field);
	bool Check(vector<vector<int>> &field);
	bool isGameOver(vector<vector<int>>& field);
};

void Rectangles::setTexture(string s)
{
	this->pic.loadFromFile(s);
	this->s.setTexture(this->pic);
}

void Rectangles::setApp(RenderWindow* App)
{
	this->app = App;
}

void Rectangles::show(int left, int i, int j)
{
	this->s.setTextureRect(IntRect(left * 18, 0, 18, 18));
	this->s.setPosition(j * 18, i * 18);
	this->s.move(28, 31);
	app->draw(this->s);
}

void Rectangles::show()
{
	for (int i = 0; i < 4; i++)
	{
		this->s.setTextureRect(IntRect(ColorNum * 18, 0, 18, 18));
		this->s.setPosition(this->a[i].x * 18, a[i].y * 18);
		this->s.move(28, 31);
		app->draw(this->s);
	}
}

void Rectangles::getNewRectangle()
{
	ColorNum = 1 + rand() % 7;
	int n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2 + 3;
		a[i].y = figures[n][i] / 2;
		acopy[i] = a[i];
	}
}

void Rectangles::MoveDown(vector<vector<int>>& field)
{
	for (int i = 0; i < 4; i++)
	{
		acopy[i] = a[i];
		a[i].y += 1;
	}
	if (!Check(field))
	{
		for (int i = 0; i < 4; i++)
		{
			field[acopy[i].y][acopy[i].x] = this->ColorNum;
		}
		this->getNewRectangle();// getNewRectangle();
	}
	delay = 0.3;
}

bool Rectangles::Check(vector<vector<int>> &field)
{
	int M = field.size();
	int N = field[0].size();
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
			return false;
		else if (field[a[i].y][a[i].x])
			return false;
	}
	return true;
}

void Rectangles::MoveLeftOrRight(vector<vector<int>>& field)
{
	for (int i = 0; i < 4; i++)
	{
		acopy[i] = a[i];
		a[i].x += Dx;
	}
	if (!Check(field))
	{
		for (int i = 0; i < 4; i++)
			a[i] = acopy[i];
	}

	this->Dx = 0;
}

void Rectangles::MoveRotate(vector<vector<int>>& field)
{
	Point p = a[1];
	for (int i = 0; i < 4; i++)
	{
		acopy[i] = a[i];
		int x = a[i].y - p.y;
		int y = a[i].x - p.x;
		a[i].x = p.x - x;
		a[i].y = p.y + y;
	}
	if (!Check(field))
	{
		for (int i = 0; i < 4; i++)
			a[i] = acopy[i];
	}
	this->Rotate = false;
}

bool Rectangles::isGameOver(vector<vector<int>>& field)
{
	for (int i = 0; i < 4; i++)
	{
		if (field[a[i].y][a[i].x])
			return true;
	}
	return false;
}
