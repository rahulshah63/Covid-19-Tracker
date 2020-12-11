#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>


using namespace std;

class Graph {
private:
    void DefaultText();//selecting default size and color while window is open
    void Display();
    void setData();
    void SetValues();//Setting of fonts, strings, style for text
    void loadFile(int);

public:
    Graph(sf::RenderWindow *window1, int data = 10);
    void draw(string, int);//for displaying and other purpose
    void combDisplay();


private:
    sf::RenderWindow *window;
    sf::RectangleShape *rectShape;//dynamic, defined at constructor
    sf::RectangleShape boundary;
    sf::Event event;
    sf::Font font;
    sf::Text title, countryName, countryData;

    const float xStart = 100;
    const float yStart = 100;
    float Ratio;

    const int width = 30;
    const int distance = 50;
    int noOfCountry;

    string titlestr;
    string **nameAndData;//dynamic, defined at constructor
};


