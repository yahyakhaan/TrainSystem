//Header file for all textboxes

#pragma once
#include <iostream>
#include <sstream>//to convert string to int
#include <SFML/Graphics.hpp>

// Defining the delete,enter and escape keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox//textbox class to handle all textboxes in the console
{
private:
	sf::Text textbox;

	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 0;
	bool secure = false;
	void deleteLastChar()// Deleting the last character if backspace is pressed
	{
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str() + "_"); //adding "_" at the end so the user knows where the text is being typed
	}

	void inputLogic(int charTyped)//Getting input in textbox from user
	{
		// If the key pressed isn't delete,enter or escape, then append the text with the char
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) 
		{
			if (secure)
			{
				if (charTyped >= '0' && charTyped <= '9')
				{
					text << static_cast<char>(charTyped);//converting the keyboard input to char
				}
				
			}
			else
			{
				text << static_cast<char>(charTyped);//converting the keyboard input to char
			}
			
		}
		else if (charTyped == DELETE_KEY)// If the delete key is pressed, then delete the char
		{
			if (text.str().length() > 0) 
			{
				deleteLastChar();
			}
		}
		else if (charTyped == ENTER_KEY)
		{
			
		}
		// Set the textbox text
		textbox.setString(text.str() + "_");//adding "_" at the end so the user knows where the text is being typed
	}
public:
	void Set_Secure()//function checking if user doensn't enter an unwanted text. example entering non int in age or id boxes
	{
		secure = true;
	}
	Textbox() {}
	Textbox(int size, sf::Color color, bool sel) 
	{
		textbox.setCharacterSize(size);
		textbox.setColor(color);
		isSelected = sel;

		// Check if the textbox is selected and display "_" to know that textbox is selected
		if (isSelected)
			textbox.setString("_");
		else
			textbox.setString("");
	}

	
	void setFont(sf::Font& fonts)//settinng font of all textboxes and passing it by reference
	{
		textbox.setFont(fonts);
	}

	void setPosition(sf::Vector2f point)//setting the position of textboxes in the console
	{
		textbox.setPosition(point);
	}

	void setLimit(bool ToF)//boolean variable to check if textboxes have reached their limits
	{
		hasLimit = ToF;
	}

	void setLimit(bool ToF, int lim) //setting limit to the number of characters typed
	{
		hasLimit = ToF;
		limit = lim - 1;
	}

	// Change selected state:
	void setSelected(bool sel)//changing the selected stated i.e checking if the textbox is selected or not
	{
		isSelected = sel;
		if (!sel)//If textbox is not selected, remove the '_' at the end so the user knows that textbox is not selected
		{
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++)
			{
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	std::string getText()//getter for text
	{
		return text.str();
	}
	void setText(std::string ss)//setter for text
	{
		text.str() = ss;
	}
	void drawTo(sf::RenderWindow& window)//drawing a new window
	{
		window.draw(textbox);
	}

	void typedOn(sf::Event input)// Function for event loop
	{
		if (isSelected) 
		{
			int charTyped = input.text.unicode;
			if (charTyped < 128)// Only allow normal inputs
			{
				if (hasLimit) 
				{
					if (text.str().length() <= limit)//not exceeding the limit
					{
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit&& charTyped == DELETE_KEY)//deleting and adjusting the limit
					{
						deleteLastChar();
					}
				}
				else//if there is no limit
				{
					inputLogic(charTyped);
				}
			}
		}
	}
};
