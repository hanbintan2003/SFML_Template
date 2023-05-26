#include "config.h"

#include <utility>
Config config = Config();

void Config::_set_texture(){
    // set texture example
    auto t1 = make_shared<sf::Texture>();
    t1->loadFromFile("../assets/error.png");
    this->_texture_map.insert({"0",t1});
}

void Config::_set_font(){
    // set font example
    auto f1 = make_shared<sf::Font>();
    f1->loadFromFile("../assets/arial.ttf");
    this->_font_map[ARIAL] = f1;
}
