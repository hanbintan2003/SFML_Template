#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button()= default;
    Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor){
        button.setSize(buttonSize);
        button.setFillColor(bgColor);

        // Get these for later use:
        btnWidth = buttonSize.x;
        btnHeight = buttonSize.y;

        text.setString(btnText);
        text.setCharacterSize(charSize);
        text.setFillColor(textColor);
    }
    void setFont(sf::Font &fonts){
        text.setFont(fonts);
    }
    void setBackColor(sf::Color color){
        button.setFillColor(color);
    }

    void setPosition(sf::Vector2f point){
        button.setPosition(point);

        // Center text on button:
        float div = 2.0 + btnHeight / btnWidth;

        float xPos = (point.x + btnWidth / div) - (text.getLocalBounds().width / 2);
        float yPos = (point.y + btnHeight / div) - (text.getLocalBounds().height / 2);
        text.setPosition(xPos, yPos);
    }
    void drawTo(sf::RenderWindow &window){
        window.draw(button);
        window.draw(text);
    }
    // Check if the mouse is within the bounds of the button:
    bool isMouseOver(sf::RenderWindow &window){
        sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x,
                                   sf::Mouse::getPosition(window).y });

        sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

        float mouseX = realCoords.x;
        float mouseY = realCoords.y;

        int btnPosX = button.getPosition().x;
        int btnPosY = button.getPosition().y;

        int btnxPosWidth = button.getPosition().x + button.getGlobalBounds().width;
        int btnyPosHeight = button.getPosition().y + button.getGlobalBounds().height;

        if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
            return true;
        }
        return false;
    }

private:
    sf::RectangleShape button;
    sf::Text text;

    float btnWidth{};
    float btnHeight{};
};

#endif // !BUTTON_H