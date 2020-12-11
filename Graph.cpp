#include "Graph.h"
#include "Menu.h"
#include "MergeSort.h"
using namespace std;

Graph::Graph(sf::RenderWindow *window1, int data) {
    window = window1;

    int n = 1;
    char ch;
    FILE *infile = fopen("CovidData.txt", "r");


    while (EOF != (ch=getc(infile)))
        if ('\n' == ch)//last ko new line hudaina. So n = 1
            n++;

    if(data > n)
        noOfCountry = n;
    else
        noOfCountry = data;

    nameAndData = new string *[noOfCountry];
    for(int i = 0; i < noOfCountry; i++)
        nameAndData[i] = new string [2];

    rectShape = new sf::RectangleShape [noOfCountry];

    font.loadFromFile("cambria.ttc");
}

void Graph::combDisplay() {
    window->clear(sf::Color::White);

    window->draw(boundary);
    window->draw(title);

    for(int i = 0; i < noOfCountry; i++)
        window->draw(rectShape[i]);
}

void Graph::setData() {
    title.setFont(font);
    title.setPosition(255,30);
    title.setCharacterSize(30);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color(20, 100, 150));
    title.setString(titlestr);

    boundary.setSize(sf::Vector2f(898,668));
    boundary.setPosition(1,1);
    boundary.setOutlineThickness(1.f);
    boundary.setOutlineColor(sf::Color::Black);

    countryName.setFont(font);
    countryName.setCharacterSize(20);
    countryName.setFillColor(sf::Color::Black);

    countryData.setFont(font);
    countryData.setCharacterSize(20);
    countryData.setFillColor(sf::Color::Black);

    Ratio = 720/float(stoi(nameAndData[0][1]));

    for(int i = 0; i < noOfCountry; i++) {
        rectShape[i].setFillColor(sf::Color::Red);
        rectShape[i].setSize(sf::Vector2f(Ratio * stoi(nameAndData[i][1]), width));//setting size for graph rectangle 10 times
        rectShape[i].setPosition(xStart, yStart + distance * i);
    }
}

void Graph::loadFile(int option){
    linked_list CovidData;

    fstream file;
    string word[5], filename;
    filename = "CovidData.txt";
    file.open(filename.c_str());
    int i = 0;
    while (file >> word[i]){
        string country = word[0];
        string tcase = word[1];
        string tactive = word[2];
        string trecovery = word[3];
        string tdeath = word[4];
        i++;
        if( i == 5){
            int totalCase = stoi(tcase);
            int totalActive = stoi(tactive);
            int totalRecovery = stoi(trecovery);
            int totalDeath = stoi(tdeath);
            CovidData.add_node(country, totalCase, totalActive, totalRecovery, totalDeath);
            i = 0;
        }
    }
    file.close();

    CovidData.choice = option;
    CovidData.mergeSort(&globalHead);
    CovidData.reverseList();
    CovidData.display();
    CovidData.exchangeData(nameAndData, noOfCountry);
}

void Graph::draw(string title, int option) {
    titlestr = title;//setting the title above the graph as per selected choice
    loadFile(option);
    setData();
    while (window->isOpen()){
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.key.code == sf::Keyboard::Escape)
                return;
        }

        combDisplay();//draws boundary, title and rectangle for graph

        for (int i = 0; i < noOfCountry; i++){
            for (int j = 0; j < 2; j++){
                if(j == 0){
                    countryName.setString(nameAndData[i][j]);
                    countryName.setPosition(5, yStart + distance * i);
                    window->draw(countryName);
                }

                else{
                    countryData.setString(nameAndData[i][j]);
                    countryData.setPosition(xStart + Ratio * stoi(nameAndData[i][1]) + 5, yStart + distance * i + 2);
                    window->draw(countryData);
                }
            }
        }

    window->display();

    }
}



