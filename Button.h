#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape button;
	sf::CircleShape circle1;
	sf::CircleShape circle2;
	sf::Text text;
	//dimensions i.e height and width of buttons
	int btnWidth;
	int btnHeight;
	bool circle;
public:
	//Default constructor
	Button():btnHeight(250),btnWidth(60)//setting default height and width
	{
		circle = false;
	}
	//parametrized constructor setting the text,size,position and font of button
	Button(std::string btnText, sf::Vector2f buttonSize, sf::Vector2f buttonPos,sf::Font& font,bool circle)
	{
		this->circle = circle;
		set(btnText, buttonSize,buttonPos,font,circle);
	}
	//graphics for setting the header i.e "FAST EXPRESS"
	void Header(std::string btnText, sf::Vector2f buttonSize, sf::Vector2f buttonPos, sf::Font& font,bool circle)
	{
		this->circle = circle;
		btnWidth = buttonSize.x;
		btnHeight = buttonSize.y;
		button.setPosition(buttonPos);
		//Set Rectangle
		button.setSize(buttonSize);
		button.setFillColor(sf::Color::Black);
		circle1.setFillColor(sf::Color::Black);
		circle2.setFillColor(sf::Color::Black);
		text.setString(btnText);
		text.setColor(sf::Color::Red);
		text.setCharacterSize(70);
		text.setStyle(sf::Text::Style::Italic);
		text.setOutlineColor(sf::Color::Yellow);
		text.setOutlineThickness(2);
		//Set Text
		setFont(font);
		setText(buttonPos);
		//Setting circles on both ends
		circle1.setRadius(btnHeight / 2);
		circle1.setPosition(btnWidth - 340, buttonPos.y);
		circle2.setRadius(btnHeight / 2);
		circle2.setPosition(btnWidth + 90, buttonPos.y);

	}
	// set function for graphics of buttons i.e their font, color, size and texts
	void set(std::string btnText,sf::Vector2f buttonSize,sf::Vector2f buttonPos, sf::Font& font,bool circle)
	{
		this->circle = circle;
		btnWidth = buttonSize.x;
		btnHeight = buttonSize.y;
		button.setPosition(buttonPos);
		//Set Rectangle
		button.setSize(buttonSize);	
		button.setFillColor(sf::Color::Black);
		//Setting Text
		text.setString(btnText);
		text.setColor(sf::Color::Red);
		text.setCharacterSize(25);
		setFont(font);
		setText(buttonPos);
		//Setting Circle
		setCircle(buttonPos);
	}
	//set function for curve at each end of buttons
	void setCircle(sf::Vector2f buttonPos)
	{
		circle1.setFillColor(sf::Color::Black);
		circle2.setFillColor(sf::Color::Black);
		circle1.setOutlineThickness(2);
		circle1.setOutlineColor(sf::Color::Black);
		circle1.setRadius(btnHeight/2);
		circle1.setPosition(buttonPos.x-28, buttonPos.y);
		circle2.setRadius(btnHeight / 2);
		circle2.setPosition(buttonPos.x+180, buttonPos.y);

	}	
	void setOutlineColor(sf::Color color)//setter for outline color
	{
		circle1.setOutlineColor(color);
	}
	void setSize(sf::Vector2f buttonSize)//setter for size
	{
		btnHeight = buttonSize.y;
		btnWidth = buttonSize.x;
		button.setSize(buttonSize);
		circle1.setRadius(btnWidth / 2);
		circle2.setRadius(btnWidth / 2);
	}
	void setFont(sf::Font& fonts)//setter for font
	{
		text.setFont(fonts);
	}
	void setBackColor(sf::Color color)//setter for main back color
	{
		button.setFillColor(color);
	}
	void setTextColor(sf::Color color)//setter for text color of button
	{
		text.setColor(color);
	}
	void setText(sf::Vector2f point)//setter for position of text in a button
	{
		float xPos = point.x;
		float yPos = point.y;
		text.setPosition(xPos, yPos);
	}
	void setPosition(sf::Vector2f point)//setter for position of button in the console
	{
		button.setPosition(point);
		// Logic to place text in the middle of the button by getting its boundary coordinates
		float xPos = (point.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
		float yPos = (point.y + btnHeight / 2.2) - (text.getLocalBounds().height / 2);
		text.setPosition(xPos, yPos);
	}
	void drawTo(sf::RenderWindow& window)
	{
		if (circle==true)
		{
			window.draw(circle1);
			window.draw(circle2);
		}
		window.draw(button);
		window.draw(text);
	}
	//Check if the mouse is within the boundary of the button i.e if mouse is clicking ON the button
	bool isMouseOver(sf::RenderWindow& window)
	{
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		int btnPosX = button.getPosition().x;
		int btnPosY = button.getPosition().y;

		int btnxPosWidth = button.getPosition().x + btnWidth;
		int btnyPosHeight = button.getPosition().y + btnHeight;

		if (mouseX < btnxPosWidth && mouseX > btnPosX&& mouseY < btnyPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;
	}
};