#pragma once
#include"Person.h"
class Adult :public Person
{
	string Occupation;
	string Qualification;
	string NIC;
public:
	Adult() :Person()
	{
		window2->setTitle("Adult Data");//new window asking info about adullt i.e qualification, occupation and NIC
		btn1.set("Occupation : ", { 280,50 }, { 60, 50 }, font, false);
		btn1.setBackColor(sf::Color::Black);
		btn1.setTextColor(sf::Color::Red);
		//Input Text Box for occupation
		txt1 = Textbox(20, sf::Color::Red, true);
		txt1.setPosition({ 220, 55 });
		txt1.setLimit(true, 15);
		txt1.setFont(font);

		btn2.set("Qualification : ", { 280,50 }, { 60, 120 }, font, false);
		btn2.setBackColor(sf::Color::Black);
		btn2.setTextColor(sf::Color::Red);
		//Input Text Box for qualification
		txt2 = Textbox(20, sf::Color::Red, true);
		txt2.setPosition({ 220, 125 });
		txt2.setLimit(true, 10);
		txt2.setFont(font);

		btn3.set("NIC : ", { 180,50 }, { 60, 190 }, font, false);
		btn3.setBackColor(sf::Color::Black);
		btn3.setTextColor(sf::Color::Red);
		//Input Text Box for NIC
		txt3 = Textbox(20, sf::Color::Red, true);
		txt3.setPosition({ 125, 195 });
		txt3.setLimit(true, 15);
		txt3.setFont(font);
		txt3.Set_Secure();
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
						NIC = txt3.getText();//converting string to int
						Occupation = txt1.getText();
						Qualification = txt2.getText();
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
		Person::window2->close();
		delete Person::window2;
	}
	void show()//displaying information
	{
		btn1.set("Occupation : ", { 280,50 }, { 60, 330 }, font, false);
		btn1.setBackColor(sf::Color::Black);
		btn1.setTextColor(sf::Color::Red);
		btn2.set("Qualification : ", { 280,50 }, { 60, 400 }, font, false);
		btn2.setBackColor(sf::Color::Black);
		btn2.setTextColor(sf::Color::Red);
		btn3.set("NIC : ", { 280,50 }, { 60, 470 }, font, false);
		btn3.setBackColor(sf::Color::Black);
		btn3.setTextColor(sf::Color::Red);
		btn1.drawTo(*window2);
		btn2.drawTo(*window2);
		btn3.drawTo(*window2);
		sf::Text txt;
		txt.setCharacterSize(20);
		txt.setColor(sf::Color::Red);
		txt.setFont(font);
		txt.setString(Occupation);
		txt.setPosition(220, 335);
		window2->draw(txt);
		txt.setString(Qualification);
		txt.setPosition(220, 405);
		window2->draw(txt);
		txt.setString(NIC);
		txt.setPosition(130, 475);
		window2->draw(txt);
	}
	void Print(string familyName)
	{
		window2 = new sf::RenderWindow(sf::VideoMode(950, 550), "Adult Data");
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
			show();
			window2->display();
		}
		delete Person::window2;
	}
	~Adult()
	{

	}
};

