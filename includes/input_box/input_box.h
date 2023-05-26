#ifndef INPUT_BOX_H
#define INPUT_BOX_H
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
// Define keys:

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
using namespace std;

class InputBox {
public:
    InputBox()= default;

    InputBox(int font_size, sf::Vector2f box_size, sf::Vector2f position,
             sf::Color text_color, sf::Color box_color, bool sel, string text_str=""){
        isSelected = false;
        rect.setSize(box_size);
        rect.setFillColor(box_color);
        rect.setPosition(position);
        textbox.setCharacterSize(font_size);
        textbox.setFillColor(text_color);
        textbox.setPosition(position);
        isSelected = sel;

        text = std::move(text_str);
        init_text_len = text.length();

        // Check if the textbox is selected upon creation and display it accordingly:
        if(isSelected)
            textbox.setString(text + "|");
        else
            textbox.setString(text);
    }

    // Make sure font is passed by reference:
    void setFont(sf::Font &fonts){
        textbox.setFont(fonts);
    }

    void setPosition(sf::Vector2f point){
        textbox.setPosition(point);
    }


    // Change selected state:
    void setSelected(bool sel){
        isSelected = sel;

        // If not selected, remove the '_' at the end:
        std::string newT = "";
        if (!sel) {
            std::string t = text;
            for (int i = 0; i < t.length(); i++) {
                newT += t[i];
            }
            textbox.setString(newT);
            return;
        }
    }

    std::string getText(){
        return text;
    }

    sf::Text& get_text_box(){return this->textbox;}
    void drawTo(sf::RenderWindow &window){
        window.draw(rect);
        window.draw(textbox);
    }

    // Function for event loop:
    void typedOn(sf::Event &input){
        if (isSelected) {
            int charTyped = input.text.unicode;
            // Only allow normal inputs:
            if (charTyped < 128) inputLogic(charTyped);
        }
    }

    void update_input_box(sf::RenderWindow &window, sf::Event& event){
        sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });

        sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

        float mouseX = realCoords.x;
        float mouseY = realCoords.y;

        int boxPosX = rect.getPosition().x;
        int boxPosY = rect.getPosition().y;

        int boxXPosWidth = rect.getPosition().x + rect.getGlobalBounds().width;
        int boxYPosHeight = rect.getPosition().y + rect.getGlobalBounds().height;

        bool clicked = event.type == sf::Event::MouseButtonPressed;
        if (mouseX < boxXPosWidth && mouseX > boxPosX && mouseY < boxYPosHeight && mouseY > boxPosY) {

            if(clicked){
                this->setSelected(true);
                this->textbox.setString(this->getText() + "|");
                return;
            }
        }
        if(clicked || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->setSelected(false);
    }

private:
    sf::Text textbox;
    string text;
    int init_text_len{};
    bool isSelected{};
    sf::RectangleShape rect;

    // Delete the last character of the text:
    void deleteLastChar(){
        if(text.length() == init_text_len) return;
        std::string t = text;
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++) {
            newT += t[i];
        }
        text = newT;
        textbox.setString(text + "|");
        //std::cout << text.str() << std::endl;
    }

    // Get user input:
    void inputLogic(int charTyped){
        // If the key pressed isn't delete, or the two selection keys, then append the text with the char:
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text += static_cast<char>(charTyped);
            if((text.length() + 1) % (int(rect.getSize().x / 15)) == 0) text += '\n';
        }
        // If the key is delete, then delete the char:
        if (charTyped == DELETE_KEY) {
            if (text.length() > 0) {
                deleteLastChar();
            }
        }
        // Set the textbox text:
        string str = text + "|";
        textbox.setString(str);
        //std::cout << text.str() << std::endl;
    }
};


#endif