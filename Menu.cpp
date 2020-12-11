#include "Menu.h"
#include "Graph.h"
#include "Tree.h"

BST start, temp, *root = NULL, *found = NULL;

Menu::Menu() {
    font.loadFromFile("cambria.ttc");

    virus.loadFromFile("corona.png");
    virus.setSmooth(true);
    gun.loadFromFile("gun.png");
    gun.setSmooth(true);

    backgnd[0].loadFromFile("first.jpg");
    backgnd[1].loadFromFile("second.jpg");
    backgnd[2].loadFromFile("third.jpg");
}

void Menu::SetValues() {
    background[0].setTexture(backgnd[0]);
    background[0].setScale(900 / background[0].getLocalBounds().width, 670 / background[0].getLocalBounds().height);

    background[1].setTexture(backgnd[1]);
    background[1].setScale(900 / background[1].getLocalBounds().width, 670 / background[1].getLocalBounds().height);

    background[2].setTexture(backgnd[2]);
    background[2].setScale(900 / background[2].getLocalBounds().width, 670 / background[2].getLocalBounds().height);

    rectShape1.setSize(sf::Vector2f(300.0f, 300.5f));//corona virus
    rectShape1.setTexture(&virus);
    rectShape1.setPosition(50, 50+65);

    rectShape2.setSize(sf::Vector2f(80.0f, 70.0f));//gun picture
    rectShape2.setTexture(&gun);
    rectShape2.setPosition(620, 50+30);

    first0.setFont(font);
    first0.setPosition(300, 50+30);
    first0.setCharacterSize(50);
    first0.setStyle(sf::Text::Bold);
    first0.setFillColor(sf::Color(20, 100, 150));
    first0.setString("Covid Tracker");

    first1.setFont(font);
    first1.setPosition(360, 50+100);
    //first1.setString("Top Total Cases");
    first1.setString(title[0]);

    first2.setFont(font);
    first2.setPosition(385, 50+140);
    //first2.setString("   Top Active Cases");
    first2.setString(title[1]);

    first3.setFont(font);
    first3.setPosition(393, 50+180);
    //first3.setString("    Top Cured Cases");
    first3.setString(title[2]);

    first4.setFont(font);
    first4.setPosition(385, 50+220);
    //first4.setString("    Top Deaths");
    first4.setString(title[3]);

    first5.setFont(font);
    first5.setPosition(350, 50+260);
    first5.setString("   Search & Update");

    first6.setFont(font);
    first6.setPosition(350, 50+300);
    first6.setString("Add to Database");
}

void Menu::DefaultText() {
    first1.setFillColor(sf::Color::Magenta);
    first1.setCharacterSize(30);

    first2.setFillColor(sf::Color::Magenta);
    first2.setCharacterSize(30);

    first3.setFillColor(sf::Color::Magenta);
    first3.setCharacterSize(30);

    first4.setFillColor(sf::Color::Magenta);
    first4.setCharacterSize(30);

    first5.setFillColor(sf::Color::Magenta);
    first5.setCharacterSize(30);

    first6.setFillColor(sf::Color::Magenta);
    first6.setCharacterSize(30);
}

void Menu::Display() {
    window.clear(sf::Color::White);

    window.draw(background[0]);
    window.draw(rectShape1);
    window.draw(rectShape2);
    window.draw(first0);
    window.draw(first1);
    window.draw(first2);
    window.draw(first3);
    window.draw(first4);
    window.draw(first5);
    window.draw(first6);
    //window.draw(background[0]);


    window.display();
}

void Menu::Create() {
    SetValues();//Setting of fonts, positions, strings, style for text
    window.create(sf::VideoMode(900, 670), "Covid Tracker");

    while (window.isOpen()){
        DefaultText();//selecting default size and color
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if (SelectedMenu < 6)
                SelectedMenu++;
            Sleep(150);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if (SelectedMenu > 1)
                SelectedMenu--;
            Sleep(150);
        }

        switch (SelectedMenu){//for change in color and increase in size
        case 1:
            first1.setFillColor(sf::Color(244, 42, 11));
            first1.setCharacterSize(34);
            break;

        case 2:
            first2.setFillColor(sf::Color(244, 42, 11));
            first2.setCharacterSize(34);
            break;

        case 3:
            first3.setFillColor(sf::Color(244, 42, 11));
            first3.setCharacterSize(34);
            break;

        case 4:
            first4.setFillColor(sf::Color(244, 42, 11));
            first4.setCharacterSize(34);
            break;

        case 5:
            first5.setFillColor(sf::Color(244, 42, 11));
            first5.setCharacterSize(34);
            break;

        case 6:
            first6.setFillColor(sf::Color(244, 42, 11));
            first6.setCharacterSize(34);
            break;
        }

        Display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){//if user hits enter then select based on SelectedMenu value
            Graph graph1(&window, 10);//no of countries to display in graph
            Sleep(150);
            switch (SelectedMenu){
            case 1:
                graph1.draw(title[0], SelectedMenu);
                break;

            case 2:
                graph1.draw(title[1], SelectedMenu);
                break;

            case 3:
                graph1.draw(title[2], SelectedMenu);
                break;

            case 4:
                graph1.draw(title[3], SelectedMenu);
                break;

            case 5:
                SearchCountry();
                break;

            case 6:
                userInput();
                Sleep(250);
                break;

            }
        }
    }
}

void Menu::LoadCountry() {
    show.setFont(font);
    show.setCharacterSize(30);
    SelectedMenu == 5?show.setPosition(550,100):show.setPosition(80,230);
    show.setFillColor(sf::Color::Black);

    read.setFont(font);
    read.setCharacterSize(30);
    read.setFillColor(sf::Color::Black);
}

void Menu::SearchCountry() {
    LoadCountry();
    LoadFromText();

    Displayed = 0;//Data is not displayed

    while (window.isOpen()){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::Escape) {
                while (userString.size() > 0){
                            userString.pop_back();//emptying all elements for next data
                }
                    return;
            }

            if (event.type == sf::Event::TextEntered && event.text.unicode < 128){
                if (event.text.unicode == 8){//if backspace removes last letter
                    if (userString.size() > 0){
                        userString.pop_back();
                    }
                }

                else if(event.text.unicode == 13){//for enter unicode
                    if (userString.size() > 0 || Displayed == 1){//change if not empty
                        if(Displayed == 1) {
                            while (userString.size() > 0)
                                userString.pop_back();//emptying string for next data

                            Update = true;
                            userInput(2);
                            return;
                        }

                        found=start.Search(root,userString);//searching the country by name

                        if(found==NULL){
                            while (userString.size() > 0)
                                userString.pop_back();//emptying the string for next input

                            cout<<"No data for the country"<<endl;
                            Sleep(150);
                            return;
                        }

                        start.Display(found);
                        Displayed ++;
                    }
                }

                else if(event.text.unicode >= 'a' && event.text.unicode <= 'z')
                    userString += static_cast<char>(event.text.unicode - 32); //converts the unicode into the typed character as input is in the form of unicode

                else if((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= '0' && event.text.unicode <= '9'))
                    userString += static_cast<char>(event.text.unicode); //converts the unicode into the typed character as input is in the form of unicode

            }
        }

        if(Displayed < 1)
            show.setString("Country Name:");
        else {
            show.setString(" Update the database?\n\t  Yes -> Enter\n\t\t\tNo -> Esc");
            show.setPosition(500, 250);
        }

        if(Displayed == 0) {
            read.setString(userString);
            read.setPosition(665, 130);
        }
        else {
            read.setString(retString(found));
            read.setPosition(550, 50);
        }

        window.clear();

        window.draw(background[1]);
        window.draw(show);
        window.draw(read);

        window.display();
    }
}

void Menu::LoadFromText() {
    ifstream infile;
    infile.open("CovidData.txt", ios::in);
    if(infile){
        while (infile >> temp){
            root = start.Insert(root,temp);
        }
        infile.close();
    }
    else
        cout << "File creation failed";
}

void Menu::userInput(int displayMenu) {
    LoadCountry();

    //displayMenu = 1; //for displaying among different texts
    while (window.isOpen()){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::Escape) {
                if (displayMenu == 1){//esc backs if only on initial state
                    while (userString.size() > 0){
                            userString.pop_back();//emptying all elements before going back
                    }
                    return;
                }
            }

            if (event.type == sf::Event::TextEntered && event.text.unicode < 128){
                if (event.text.unicode == 8){//if backspace removes last letter
                    if (userString.size() > 0){
                        userString.pop_back();
                    }
                }
                else if(event.text.unicode == 13)//for Enter unicode
                {
                    if (userString.size() > 0 || displayMenu == 6){//change if not empty
                        if(Update == true) {
                            switch(displayMenu) {
                            case 2://no case 1 because we need country name to update in file
                                found->TotalCase = stoi(userString);
                                break;
                            case 3:
                                found->TotalActive = stoi(userString);
                                break;
                            case 4:
                                found->TotalRecovery = stoi(userString);
                                break;
                            case 5:
                                found->TotalDeath = stoi(userString);
                                break;
                            case 6:
                                FileUpdate(found->Country, found);//updating the database
                                Update = false;
                                break;
                            }
                        }
                        else {
                            switch(displayMenu) {
                            case 1:
                                temp.Country = userString;
                                break;
                            case 2:
                                temp.TotalCase = stoi(userString);
                                break;
                            case 3:
                                temp.TotalActive = stoi(userString);
                                break;
                            case 4:
                                temp.TotalRecovery = stoi(userString);
                                break;
                            case 5:
                                temp.TotalDeath = stoi(userString);
                                break;
                            case 6:
                                AddCountry(temp);
                                break;
                            }
                        }

                        if (displayMenu == 6)
                            return;

                        displayMenu ++;

                        while (userString.size() > 0){
                            userString.pop_back();//emptying all elements for next data
                        }
                    }
                }

                else if(event.text.unicode >= 'a' && event.text.unicode <= 'z')
                    userString += static_cast<char>(event.text.unicode - 32); //converts the unicode into the typed character as input is in the form of unicode

                else if((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= '0' && event.text.unicode <= '9'))
                    userString += static_cast<char>(event.text.unicode); //converts the unicode into the typed character as input is in the form of unicode
            }
        }

        switch (displayMenu){
            case 1:
                show.setString("Country Name:");
                SelectedMenu == 5?read.setPosition(665, 130):read.setPosition(290, 230);
                break;
            case 2:
                show.setString("Total Cases:");
                SelectedMenu == 5?read.setPosition(635, 130):read.setPosition(250, 230);
                break;
            case 3:
                show.setString("Active Cases:");
                SelectedMenu == 5?read.setPosition(650, 130):read.setPosition(260, 230);
                break;
            case 4:
                show.setString("Cured Cases:");
                SelectedMenu == 5?read.setPosition(650, 130):read.setPosition(260, 230);
                break;
            case 5:
                show.setString("Total Deaths:");
                SelectedMenu == 5?read.setPosition(630,130):read.setPosition(260, 230);
                break;
            case 6:
                show.setString("Data input complete");
                break;
           }

        window.clear();

        SelectedMenu == 5? window.draw(background[1]): window.draw(background[2]);

        window.draw(show);
        read.setString(userString);
        window.draw(read);

        window.display();
    }
}

