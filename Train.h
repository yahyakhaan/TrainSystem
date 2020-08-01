#pragma once
#include"Bogie.h"
class Train
{
	int count;
	Bogie* engine;//Engine is already attached
	sf::RenderWindow* window;
public:
	void set_font(sf::Font& font_p)
	{
		font = font_p;
	}
	//Default constructor while initializing engine to NULL
	Train(sf::RenderWindow* window) :engine(nullptr), count(0), window(window) {}
	int getsize()//getter for number of bogies
	{
		return count;
	}
	void printTrain()//when first button("Print train") is clicked which prints total number of bogies and their ID from start to end
	{
		if (engine != nullptr)
		{
			Button display;
			std::stringstream ss;//stringstream to convert string to int
			Bogie* temp = engine;
			sf::Text text;
			text.setFont(font);
			text.setCharacterSize(20);
			text.setColor(sf::Color::Red);
			ss << getsize();
			display.set("Total Boggies : ", { 450,450 }, { 20,200 }, font, false);
			display.setBackColor(sf::Color::Black);
			display.setTextColor(sf::Color::Red);
			display.drawTo(*window);
			display.set("ID:-", { 450,450 }, { 20,230 }, font, false);
			display.setBackColor(sf::Color::Black);
			display.setTextColor(sf::Color::Red);
			display.drawTo(*window);
			text.setString(ss.str());
			text.setPosition(190, 200);
			window->draw(text);
			int x = 20;
			int y = 260;
			while (temp != nullptr)
			{
				std::stringstream ss;
				ss << temp->get_ID();
				text.setString(ss.str());
				text.setPosition(x, y);
				window->draw(text);
				if (x >= 440)
				{
					y += 20;
					x = 20;
				}
				else
				{
					x += 50;
				}
				text.setPosition(x, y);
				text.setString(",");
				window->draw(text);
				temp = temp->next;
				if (x == 440)
				{
					y += 20;
					x = 50;
				}
				else
				{
					x += 20;
				}
			}
		}
	}
	bool SearchBogie(int ID)//searching if the Bogie is present in train
	{
		if (engine != nullptr)
		{
			Bogie* temp = engine;
			while (temp != nullptr)
			{
				if (temp->get_ID() == ID)
				{
					return true;
				}
				temp = temp->next;
			}
		}
		return false;
	}
	bool removeBogie(int ID)//searching the bogie and delete if found
	{
		if (engine != nullptr)
		{
			Bogie* found = engine;//storing the address of the previous boggie
			if (found->get_ID() == ID)
			{
				engine = found->next;//storing address of next bogie in the "next" pointer
				delete found;//now safely deleting the previous bogie
				found = nullptr;//assining to nullptr to avoid dangling pointer
				--count;//decrementing total number of bogies in train
				return true;
			}
			Bogie* current = engine->next;//stores the address of the boggie to be deleted
			while (current != nullptr)
			{
				if (current->get_ID() == ID)
				{
					found->next = current->next;
					delete current;
					current = nullptr;
					--count;
					return true;
				}
				found = current;
				current = current->next;
			}
		}
		return false;
	}
	bool addBogie(int ID)//adding bogie at the end of the train
	{
		if (engine)
		{
			if (engine->get_ID() == ID) { return false; }//if already present with same ID
			Bogie* temp = engine;
			while (temp != nullptr)
			{
				if (temp->get_ID() == ID) { return false; }
				else if (temp->next == nullptr)
				{
					temp->next = new Bogie(ID);//creating new bogie with ID
					break;
				}
				temp = temp->next;
			}
			temp = new Bogie(ID);
		}
		else
		{
			engine = new Bogie(ID);
		}
		++count;
		return true;
	}
	void Addpassengers(int ID)
	{
		Bogie* temp = engine;
		while (temp->get_ID() != ID)
		{
			temp = temp->next;
		}
		if (temp->familyName == "\0")
		{
			//If bogie is not already booked
			temp->book_bogie();
		}
	}
	void reserve_Boggie(int ID)//reserving a bogie under a family name
	{
		Bogie* temp = engine;
		while (temp->get_ID() != ID)
		{
			temp = temp->next;
		}
		if (temp->familyName == "\0")
		{
			bool run = true;
			sf::RenderWindow window1(sf::VideoMode(500, 400), "Input Data(MAX PASSENGERS 10)");
		Label:
			Button fmly_btn;
			fmly_btn.set("Family Name : ", { 300,50 }, { 60, 50 }, font, false);
			fmly_btn.setBackColor(sf::Color::Black);
			fmly_btn.setTextColor(sf::Color::Red);
			//Input Text Box for family name
			Textbox fmly_txt(20, sf::Color::Red, true);
			fmly_txt.setPosition({ 235, 52 });
			fmly_txt.setLimit(true, 10);
			fmly_txt.setFont(font);
			Button enter("Enter", { 205,50 }, { 180,250 }, font, true);
			while (run)
			{
				sf::Event Event;
				//Event Loop:
				while (window1.pollEvent(Event))
				{
					switch (Event.type)
					{
					case sf::Event::Closed:
					{
						window1.close();
						run = false;
						break;
					}
					case sf::Event::MouseButtonPressed:
					{
						if (enter.isMouseOver(window1))
						{
							window1.close();
							run = false;
							temp->familyName = fmly_txt.getText();
							temp->book_bogie();
						}
						break;
					}
					case sf::Event::TextEntered:
					{
						fmly_txt.typedOn(Event);
					}
					}
				}
				window1.clear();
				fmly_btn.drawTo(window1);
				fmly_txt.drawTo(window1);
				enter.drawTo(window1);
				window1.display();
			}
		}
	}
	void bogie_details(int ID)//display data of persons in bogie
	{
		Bogie* temp = engine;
		while (temp->get_ID() != ID)
		{
			temp = temp->next;
		}
		temp->Print();
	}
	~Train()//destructor
	{
		if (engine)
		{
			Bogie* temp = engine;
			Bogie* current = engine;
			while (current != nullptr)
			{
				temp = temp->next;
				delete current;
				current = temp;
			}
			engine = nullptr;
		}
	}
};
