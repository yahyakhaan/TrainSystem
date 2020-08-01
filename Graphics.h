// Header file for console graphics 
// Graphics for mouse buttons and mouse movements

#pragma once
#include"Train.h"
#include"Button.h"
#include"Textbox.h"
#include<iostream>
#include<SFML/Graphics.hpp>
class Graphics
{
private:
    int ID;
    //Object pointer for train
    Train *train_Obj;
    //Buttons
    Button enter;
    Button mainButton[8];// array for main menu buttons. The back button is at the zero index
    //Buttons For Display
    Button heading;
    //Variable for graphics
    sf::Font font;//variable for font
    sf::Sprite sprite;//sprite for background
    sf::Texture texture;//texture for background
    sf::RenderWindow* window;
    
public:
    bool ret;
    bool slct;//TO check which menu is select
    int btn_num;//Variable to check  button is selected or not
    Textbox id_Text;//To get input for ID
    Button id_Button;//TO display ID input box
private:
    //To load file(background image) and the font from the given folder
    int LoadFromFile()
    {
        //Loading Background Image
        if (!texture.loadFromFile("BackgroundImage.jpg"))
        {
            std::cout << "Background Image not found!\n";
            system("pause");
            return 0;
            exit(1);
        }
        //Loading font style
        if (!font.loadFromFile("Arial.ttf"))
        {
            std::cout << "Font File not found!\n";
            system("pause");
            return 0;
            exit(1);
        }
    }
    Graphics() :window(nullptr)
    {
        //Load Image
        if (!texture.loadFromFile("Extra/Inner.jpg"))
        {
            std::cout << "[ERROR]\nInner Image File not found!" << std::endl;
            system("pause");
            exit(1);
        }
        sprite.setTexture(texture);
       // enter = new Button[2];
    }
    //initializing buttons and background of console
    void Intialize()
    {
        ret = false;
        sprite.setTexture(texture);
        heading.Header("Fast Express", { 450,130 }, { 170, 55 }, font, true);//Header;
        //Initilizing main user console
        mainButton[1].set("Print Train", { 205,50 }, { 50,220 }, font,true);
        mainButton[2].set("Add a Bogie", { 205,50 }, { 50,290 }, font, true);
        mainButton[3].set("Remove a Bogie", { 205,50 }, { 50,360 }, font, true);
        mainButton[4].set("Reserve a Bogie", { 205,50 }, { 50,430 }, font, true);
        mainButton[5].set("Details of a Bogie", { 205,50 }, { 50,500 }, font, true);
        mainButton[6].set("Add Passengers", { 205,50 }, { 50,570 }, font, true);
        mainButton[7].set("Exit", { 205,50 }, { 50,640 }, font, true);
        //Back Button and Enter
        mainButton[0].set("Back", { 205,50 }, { 480,640 }, font, true);
        enter.set("Enter", { 205,50 }, { 150,640 }, font, true);
    }
    //Initializing the ID button
    void set()
    {
        //ID Button
        id_Button.set("ID:", { 170,50 }, { 50, 220 }, font, false);
        id_Button.setBackColor(sf::Color::Black);
        id_Button.setTextColor(sf::Color::Red);
       //Initializing Text Box to take input from user
        id_Text = Textbox(20, sf::Color::Red, true);
        id_Text.setPosition({ 85, 225 });
        id_Text.setLimit(true, 3);//setting a limit of max 3 integers
        id_Text.setFont(font);
        id_Text.Set_Secure();
    }
    //Clear/Erase The ID button
    void clear()
    {
        id_Button.setBackColor(sf::Color::Black);
        id_Button.setTextColor(sf::Color::Red);
        id_Text = Textbox(20, sf::Color::Black, true);
        id_Text.setPosition({ 85, 225 });
        id_Text.setLimit(true, 10);
        id_Text.setFont(font);
    }
public:
	//Default Constructor to intialize all created objects
	Graphics(sf::RenderWindow& window_p,Train& obj):ID(-1),slct(false),btn_num(-2),window(&window_p),train_Obj(&obj)
	{
       LoadFromFile();
       train_Obj->set_font(font);
       Intialize();//calling the initialize function
    }
    //When mouse is moved
    void MouseMoved()//function to detect mouse movement
    {
        if (train_Obj->getsize() > 0)
        {
            ID = -2;
        }
        else { ID = -1; }
        if (slct)
        {
            if (mainButton[0].isMouseOver(*window))
            {
                mainButton[0].setOutlineColor(sf::Color::Red);
            }
            else
            {
                mainButton[0].setOutlineColor(sf::Color::Black);
            }
      
            if (enter.isMouseOver(*window))
            {
                enter.setOutlineColor(sf::Color::Red);
            }
            else
            {
                enter.setOutlineColor(sf::Color::Black);
            }
        }
        else if (slct == false)
        {
            for (int i = 1; i < 8; i++)
            {
                if (mainButton[i].isMouseOver(*window))
                {
                    mainButton[i].setOutlineColor(sf::Color::Red);
                }
                else
                {
                    mainButton[i].setOutlineColor(sf::Color::Black);
                }
            }
        }
    }
    //When mouse is clicked
    void MouseButtonsPressed()
    {
        if (!slct)
        {
            for (int i = 1; i < 8; i++)
            {
                //If any of the buttons are pressed except the back button
                if (mainButton[i].isMouseOver(*window))
                {
                    btn_num = i;
                    slct = true;
                    set();
                    break;
                }
            }
            if (btn_num == 7)
            {
                //If exit button is pressed/clicked
                window->close();
            }
        }
        else if (slct == true)//Functionality of "back" button
        {
            if (mainButton[0].isMouseOver(*window))
            {
                btn_num = 0;
                slct = false;
                ret = false;
                enter.set("Enter", { 205,50 }, { 150,640 }, font, true);
            }
            else
            {
                std::istringstream(id_Text.getText()) >> ID;//converting string to int
                switch (btn_num)
                {
                case 1://Print Train
                {
                    break;
                }
                case 2://Add a Boggie
                {
                    if (enter.isMouseOver(*window))
                    {
                        if (train_Obj->addBogie(ID))//if same ID doesn't exist before
                        {
                            id_Button = Button("Bogie Added", { 250,50 }, { 50, 220 }, font, false);
                        }
                        else//if same ID already exists
                        {
                            id_Button = Button("Same Boggie Exists", { 250,50 }, { 50, 220 }, font, false);
                        }
                        ret= true;
                    }
                    break;
                }
                case 3://Remove Boggie
                {
                    if (enter.isMouseOver(*window))
                    {
                        if (train_Obj->removeBogie(ID))//if bogie found, bogie is removed
                        {
                            id_Button = Button("Bogie Removed", { 250,50 }, { 50, 220 }, font, false);
                        }
                        else// if bogie not found
                        {
                            id_Button = Button("Bogie Not Found", { 250,50 }, { 50, 220 }, font, false);
                        }
                        ret = true;
                    }
                    break;
                }
                case 4://reserve a boggie for family
                case 5://details of a bogie including adults and kids
                case 6://Add passengers
                {
                    if (enter.isMouseOver(*window))
                    {
                        if (!train_Obj->SearchBogie(ID))//if bogie entered is not created first using "Add Bogie" option
                        {
                            id_Button = Button("Bogie Not Found", { 250,50 }, { 50, 220 }, font, false);
                            ID = -2;
                        }
                    }
                }
                }
                clear();
            }
        }
    }
    //Draw the window in main loop
    void Draw()
    {
        window->draw(sprite);//Drawing background image
        heading.drawTo(*window);//Drawing header("FAST EXPRESS")
        if (!slct)//All the buttons except the "Back" and "Enter" buttons
        {
            mainButton[1].drawTo(*window);
            mainButton[2].drawTo(*window);
            mainButton[3].drawTo(*window);
            mainButton[4].drawTo(*window);
            mainButton[5].drawTo(*window);
            mainButton[6].drawTo(*window);
            mainButton[7].drawTo(*window);
        }
        else
        {
            mainButton[0].drawTo(*window);//Back Button
            switch (btn_num)
            {
            case 1://Printing data when buttons are clicked
            {
                if (train_Obj->getsize() == 0)//if no bogie is added i.e train is empty
                {
                    id_Button = Button("Empty Train", { 250,50 }, { 50, 220 }, font, false);
                    id_Button.drawTo(*window);
                    clear();
                }
                else//shows total number of bogies, bogie ID and their order, from front to end
                {
                    train_Obj->printTrain();
                }
                break;
            }
            case 2://Add a Boggie,jumping to case3 because they both have the same body
            case 3://Remove a boggie
            {
                id_Button.drawTo(*window);
                id_Text.drawTo(*window);
                if (!ret)
                {
                    enter.drawTo(*window);
                }
                break;
            }
            case 4://Reserve Bogge
            {
                if (ID != -1)//if a bogie is created
                {
                    enter.drawTo(*window);
                }
                if (ID >= 0)//if positive ID entered, that bogie is reserved under a family name
                {
                    train_Obj->reserve_Boggie(ID);
                    slct = false;
                    btn_num = 0;
                }
                else if (ID == -2)
                {
                    id_Button.drawTo(*window);
                    id_Text.drawTo(*window);
                }
                break;
            }
            case 5://Details of a boggie i.e data of adults and kids in a boogi
            {
                if (ID != -1)
                {
                    enter.drawTo(*window);
                }
                if (ID >= 0)
                {
                    train_Obj->bogie_details(ID);
                    slct = false;
                    btn_num = 0;
                }
                else if (ID == -2)
                {
                    id_Button.drawTo(*window);
                    id_Text.drawTo(*window);
                }
                break;
            }
            case 6://Add Passengers
            {
                if (ID != -1)
                {
                    enter.drawTo(*window);
                }
                if (ID >= 0)
                {
                    train_Obj->Addpassengers(ID);
                    slct = false;
                    btn_num = 0;
                }
                else if (ID == -2)
                {
                    id_Button.drawTo(*window);
                    id_Text.drawTo(*window);
                }
                break;
            }
            }
        }
    }
};

