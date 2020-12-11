#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>//for sleep function
#include <string>

using namespace std;

class Menu {
private:
    void SetValues();//Setting of fonts, strings, style for text
    void SearchCountry();
    void DefaultText();//selecting default size and color while window is open
    void Display();
    void userInput(int displayMenu = 1);
    void LoadCountry();
    void LoadFromText();

public:
    Menu();
    void Create();//for displaying and other purpose

private:
    sf::RenderWindow window;
    sf::RectangleShape rectShape1, rectShape2;
    sf::Event event;
    sf::Font font;
    sf::Sprite background[3];
    sf::Text first0, first1, first2, first3, first4, first5, first6;//first main menu
    sf::Text show, read;//for input from user
    sf::Texture virus, backgnd[3], gun;

    bool Update = false;

    string userString;
    string title[4]= {"Top Total Cases", "Top Active Cases",  "Top Cured Cases", "Top Deaths"};

    int Displayed;//for search country one, if displayed and esc then ... if not ...
    int SelectedMenu = 1;//which menu user is in (first menu)
    //int displayMenu;


};




