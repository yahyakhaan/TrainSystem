#pragma once
#pragma once
#include"Textbox.h"
#include"Button.h"
#include<string>
//#include <sstream>
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
sf::Font font;
sf::Vertex line[2];

class Person
{
	string Name;
	int Age;
	string Gender;
protected:
	sf::RenderWindow* window2;
	sf::RectangleShape line;
	Button btn1;
	Button btn2;
	Button btn3;
	Textbox txt1;
	Textbox txt2;
	Textbox txt3;
public:
	Person()//default constructor asking name,age and gender
	{
		window2 = new sf::RenderWindow(sf::VideoMode(600, 500), "Input Data");
		btn1.set("Name : ", { 280,50 }, { 60, 50 }, font, false);
		btn1.setBackColor(sf::Color::Black);
		btn1.setTextColor(sf::Color::Red);
		//Input Text Box for name
		txt1 = Textbox(20, sf::Color::Red, true);
		txt1.setPosition({ 150, 55 });
		txt1.setLimit(true, 10);
		txt1.setFont(font);

		btn2.set("Age : ", { 170,50 }, { 60, 120 }, font, false);
		btn2.setBackColor(sf::Color::Black);
		btn2.setTextColor(sf::Color::Red);
		//Input Text Box for age
		txt2 = Textbox(20, sf::Color::Red, true);
		txt2.setPosition({ 130, 125 });
		txt2.setLimit(true, 10);
		txt2.setFont(font);
		txt2.Set_Secure();

		btn3.set("Gender : ", { 180,50 }, { 60, 190 }, font, false);
		btn3.setBackColor(sf::Color::Black);
		btn3.setTextColor(sf::Color::Red);
		//Input Text Box for gender
		txt3 = Textbox(20, sf::Color::Red, true);
		txt3.setPosition({ 163, 195 });
		txt3.setLimit(true, 10);
		txt3.setFont(font);
		Button enter("Enter", { 205,50 }, { 200,280 }, font, true);
		bool run = true;
		while (run)
		{
			sf::Event Event;
			//Event Loop:
			while (window2->pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed:
				{
					window2->close();
				}
				case sf::Event::MouseButtonPressed:
				{
					if (enter.isMouseOver(*window2))
					{
						istringstream(txt2.getText()) >> Age;//convert string to int
						Name = txt1.getText();
						Gender = txt3.getText();
						run = false;
					}
					break;
				}
				case sf::Event::TextEntered:
				{
					if (btn1.isMouseOver(*window2))
					{
						txt1.typedOn(Event);
					}
					else if (btn2.isMouseOver(*window2))
					{
						txt2.typedOn(Event);
					}
					else if (btn3.isMouseOver(*window2))
					{
						txt3.typedOn(Event);
					}
					break;
				}
				}
				window2->clear();
				btn1.drawTo(*window2);
				btn2.drawTo(*window2);
				btn3.drawTo(*window2);
				txt1.drawTo(*window2);
				txt2.drawTo(*window2);
				txt3.drawTo(*window2);
				enter.drawTo(*window2);
				window2->display();
			}
		}
		
	}
	virtual void Print(string familyName)
	{
		btn1.set("Name : ", { 280,50 }, { 60, 120 }, font, false);
		btn1.setBackColor(sf::Color::Black);
		btn1.setTextColor(sf::Color::Red);
		btn2.set("Age : ", { 170,50 }, { 60, 190 }, font, false);
		btn2.setBackColor(sf::Color::Black);
		btn2.setTextColor(sf::Color::Red);
		btn3.set("Gender : ", { 180,50 }, { 60, 260 }, font, false);
		btn3.setBackColor(sf::Color::Black);
		btn3.setTextColor(sf::Color::Red);
		btn1.drawTo(*window2);
		btn2.drawTo(*window2);
		btn3.drawTo(*window2);
		//Text Box
		sf::Text txt;
		txt.setCharacterSize(20);
		txt.setColor(sf::Color::Red);
		txt.setFont(font);
		txt.setString(Name);//Name
		txt.setPosition(160, 125);
		window2->draw(txt);
		stringstream ss;
		ss << Age;
		txt.setString(ss.str());//Age
		txt.setPosition(120, 195);
		window2->draw(txt);
		txt.setString(Gender);//Gender
		txt.setPosition(160, 266);
		window2->draw(txt);
		if (familyName[0] != '\0')
		{
			btn1.set("Family Name : ", { 280,50 }, { 60, 50 }, font, false);
			btn1.setBackColor(sf::Color::Black);
			btn1.setTextColor(sf::Color::Red);
			btn1.drawTo(*window2);
			txt.setString(familyName);//familyName
			txt.setPosition(225, 55);
			window2->draw(txt);
		}
	}
	virtual ~Person() {}
};

