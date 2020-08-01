#pragma once
#include"Person.h"
class kid :public Person
{
	string B_form_number;
public:
	kid() :Person()
	{
		window2->setTitle("Kids Data");
		btn1.set("B-Form number : ", { 350,50 }, { 60, 50 }, font, false);
		btn1.setBackColor(sf::Color::Black);
		btn1.setTextColor(sf::Color::Red);
		//Input Text Box for Bform Number
		txt1 = Textbox(20, sf::Color::Red, true);
		txt1.setPosition({ 265, 55 });
		txt1.setLimit(true, 15);
		txt1.setFont(font);
		txt1.Set_Secure();
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
						B_form_number = txt1.getText();//convert string to int
						run = false;
					}
					break;
				}
				case sf::Event::TextEntered:
				{
					txt1.typedOn(Event);
					break;
				}
				}
				window2->clear();
				btn1.drawTo(*window2);
				txt1.drawTo(*window2);
				enter.drawTo(*window2);
				window2->display();
			}
		}
		Person::window2->close();
		delete Person::window2;
	}
	void Print(string familyName)
	{
		window2 = new sf::RenderWindow(sf::VideoMode(950, 550), "Kids Data");
		while (window2->isOpen())
		{
			sf::Event Event;
			while (window2->pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed:
				{
					window2->close();
				}
				}
			}
			window2->clear();
			Person::Print(familyName);
			btn1.set("B-Form Number : ", { 320,50 }, { 60, 330 }, font, false);
			btn1.setBackColor(sf::Color::Black);
			btn1.setTextColor(sf::Color::Red);
			sf::Text txt;
			txt.setCharacterSize(20);
			txt.setColor(sf::Color::Red);
			txt.setFont(font);
			txt.setString(B_form_number);
			txt.setPosition(260, 336);//print bform #
			btn1.drawTo(*window2);
			window2->draw(txt);
			window2->display();
		}
		delete Person::window2;//deallocate memory when window is closed

	}
	~kid()
	{

	}
};
