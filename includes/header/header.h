#ifndef HEADER_H
#define HEADER_H
#include <SFML/Graphics.hpp>
using namespace std;


class Header{
public:
    Header(){}
    Header(std::string headerText, sf::Vector2f headerSize,
           sf::Vector2f headerPos, int charSize, sf::Color bgColor, sf::Color textColor){
        _header.setSize(headerSize);
        _header.setFillColor(bgColor);
        _header.setPosition(headerPos);
        _text.setPosition(headerPos);


        _text.setString(headerText);
        _text.setCharacterSize(charSize);
        _text.setFillColor(textColor);
    }
    ~Header(){}


    string getHeaderText(){return this->_text.getString();}
    void setHeaderText(const string& text){_text.setString(text);}

    void setFont(sf::Font &fonts){
        _text.setFont(fonts);
    }
    void drawTo(sf::RenderWindow &window){
        window.draw(_header);
        window.draw(_text);
    }

private:
    sf::RectangleShape _header;
    sf::Text _text;
};

#endif