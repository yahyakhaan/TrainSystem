#pragma once
#include"Adult.h"
#include"kids.h"
#include"Person.h"
class Bogie
{
	int Bogie_ID;
	Person** Adults;
	Person** kids;
	//To store number of passengers in that Boggie
	int adlt_num;
	int kds_num;
public:
	string familyName;
	Bogie* next;//store the address of the next boggie
	//Constructor dynamically allocating memory and also asking info about passengers
	Bogie(int id)
	{
		Bogie_ID = id;
		next = nullptr;
		Adults = new Person*[6];
		kids = new Person * [4];
		familyName = "\0";
		for (int i= 0; i < 6; i++)
		{
			Adults[i] = nullptr;
		}
		for (int i= 0; i < 4; i++)
		{
			kids[i] = nullptr;
		}
		adlt_num = 0;
		kds_num = 0;
	}
	
	void book_bogie()//asking for number of passengers (kids and adults)
	{
		bool run = true;
		sf::RenderWindow window1(sf::VideoMode(600,600), "Input Data(MAX PASSENGERS 10)");
		//Button
	Label:
		Button adlt_btn;
		adlt_btn.set("Adults : ", { 170,50 }, { 60, 50 }, font, false);
		adlt_btn.setBackColor(sf::Color::Black);
		adlt_btn.setTextColor(sf::Color::Red);
		//Input Text Box for adults
		Textbox adlt_txt(20, sf::Color::Red, true);
		adlt_txt.setPosition({ 160, 55 });
		adlt_txt.setLimit(true, 10);
		adlt_txt.setFont(font);
		adlt_txt.Set_Secure();
		Button kds_btn;
		kds_btn.set("Kids : ", { 170,50 }, { 60, 120 }, font, false);
		kds_btn.setBackColor(sf::Color::Black);
		kds_btn.setTextColor(sf::Color::Red);
		//Input Text Box for kids
		Textbox kds_txt(20, sf::Color::Red, true);
		kds_txt.setPosition({ 130, 125 });
		kds_txt.setLimit(true, 10);
		kds_txt.setFont(font);
		kds_txt.Set_Secure();
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
						int adlt_num_f = 0;
						int  kids_num_f = 0;
						std::istringstream(adlt_txt.getText()) >> adlt_num_f;
						std::istringstream(kds_txt.getText()) >> kids_num_f;
						//logic checking if user enters more than 10 persons or entering in negative
						if ((adlt_num_f + kids_num_f +adlt_num + kds_num > 10) || 
							(adlt_num + kds_num +adlt_num_f + kids_num_f <= 0))
						{
							goto Label;
						}
						else if (adlt_num+adlt_num_f>6)//if more than 6 adults
						{
							goto Label;
						}
						else if (kids_num_f+kds_num>4)//if more than 4 kids
						{
							goto Label;
						}
						else
						{
							adlt_num += adlt_num_f;
							kds_num += kids_num_f;
							run = false;
							window1.close();
							AddPassengers(adlt_num_f, kids_num_f);
						}
					}
					break;
				}
				case sf::Event::TextEntered:
				{
					if (adlt_btn.isMouseOver(window1))
					{
						adlt_txt.typedOn(Event);
					}
					else if (kds_btn.isMouseOver(window1))
					{
						kds_txt.typedOn(Event);
					}
					break;
				}
				}
			}
			window1.clear();
			adlt_btn.drawTo(window1);
			kds_btn.drawTo(window1);
			adlt_txt.drawTo(window1);
			kds_txt.drawTo(window1);
			enter.drawTo(window1);
			window1.display();
		}
	}
	//getting data of passengers
	void AddPassengers(int adlt_num_f, int kds_num_f)// should add adults and kids information etc
	{
		int count = 0;
		if (adlt_num_f > 0)
		{
			while (count < adlt_num)
			{
				if (Adults[count] == nullptr)
				{
					Adults[count] = new Adult();//creating new Adult which asks for occupation,qualification and NIC
				}
				count++;
			}
		}
		if (kds_num_f > 0)
		{
			count = 0;
			while (count < kds_num)
			{
				if (kids[count] == nullptr)
				{
					kids[count] = new kid();//creating new Kid which asks for B-Form number
				}
				count++;
			}
		}
	}
	void Print()
	{
		int count = 0;
		while (count < adlt_num)
		{
			Adults[count++]->Print(familyName);
		}
		count = 0;
		while (count < kds_num)
		{
			kids[count++]->Print(familyName);
		}
	}
	//Deallocating memory
	~Bogie()
	{
		int count = 0;
		while (count < adlt_num)
		{
			delete Adults[count++];
		}
		delete[]Adults;
		count = 0;
		while (count < kds_num)
		{
			delete kids[count++];
		}
		delete[]kids;
		Adults = kids = nullptr;
	}
	int get_ID()//getter for Bogie ID
	{
		return Bogie_ID;
	}
};

