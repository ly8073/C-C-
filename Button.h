#pragma once
#include<SFML/Graphics.hpp>
#include<string>
using namespace sf;
using namespace std;
class Button
{
private:
	Texture t;
	RenderWindow* app;
public:
	Button() :app(NULL), isActive(false) ,PreBeforeRealse(false){};
	bool isActive;
	Text text;
	Sprite s;
	bool isTest;
	bool PreBeforeRealse;
	void setTexture(string s);
	void setTexture(string s, Font font,int size);
	void setPosition(int x, int y);
	void setScale(float x, float y);
	void show();
	bool OnClick(Event& e);
	void setApp(RenderWindow* app);

};

void Button::setTexture(string s)
{
	this->t.loadFromFile(s);
	this->s.setTexture(this->t);
	this->isTest = false;
}

void Button::setTexture(string s, Font font,int size)
{
	this->text.setFont(font);
	this->text.setString(s);
	this->text.setCharacterSize(size);
	this->text.setFillColor(Color::Black);
	this->isTest = true;
}

void Button::setPosition(int x, int y)
{
	if(this->isTest)
		this->text.setPosition(x, y);
	else
	{
		this->s.setPosition(x, y);
	}
}

void Button::setScale(float x, float y)
{
	if (this->isTest)
		this->text.setScale(x, y);
	else
	{
		this->s.setScale(x, y);
	}
}

void Button::setApp(RenderWindow* App)
{
	this->app = App;
}

bool Button::OnClick(Event& e)
{
	if (!this->isActive)
		return false;
	bool flag = false;
	FloatRect ActiveArea = s.getGlobalBounds();
	Vector2i MousePosition = Mouse::getPosition(*app);
	if (MousePosition.x <= ActiveArea.left || MousePosition.x >= ActiveArea.left + ActiveArea.width || MousePosition.y <= ActiveArea.top || MousePosition.y >= ActiveArea.height + ActiveArea.top)
	{
		this->s.setColor(Color(255, 255, 255, 255));
		return false;
	}
	else
	{
		if (e.type == Event::MouseButtonReleased && e.key.code == Mouse::Left && PreBeforeRealse)
		{
			flag = true;
			this->PreBeforeRealse = false;
		}
		else
			flag = false;
		if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left)
		{
			this->s.setColor(Color(125, 125, 0, 255));
			this->PreBeforeRealse = true;
		}
		else
			this->s.setColor(Color(125, 125, 0, 100));

	}
	return flag;
}

void Button::show()
{
	this->isActive = true;
	if (this->isTest)
	{
		this->app->draw(text);
	}
	else
	{
		this->app->draw(this->s);
	}
}
