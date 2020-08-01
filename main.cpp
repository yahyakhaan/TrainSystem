#include"Train.h"
#include"Graphics.h"
#include<SFML/Graphics.hpp>
void main()
{ 
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Fast Express");
    Train train_Obj(&window);
    Graphics handle(window,train_Obj);
   while (window.isOpen())
    {
        sf::Event Event;
       //Event Loop:
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                }
                case sf::Event::MouseMoved://when mouse is moved
                {
                    handle.MouseMoved();
					break;
                }
                case sf::Event::MouseButtonPressed://when mouse button is pressed
                {
                    handle.MouseButtonsPressed();
                    break;
                }
                case sf::Event::TextEntered://when text is entered. This also checks a few conditions 
                 {
                     if ((handle.btn_num > 1) && (handle.btn_num < 8))//if buttons from 2 to 7 are selected
                      {
                         if (!handle.ret)
                         {
                             handle.id_Text.typedOn(Event);//if text is typed on the space
                         }
                         else
                         {
                             handle.id_Text.setSelected(false);
                         }
                      }
                      break;
                 }
            }
            window.clear();
            handle.Draw();
            window.display();
        }
    }
}