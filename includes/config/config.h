#ifndef CONFIG_H
#define CONFIG_H
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include "system.h"


// TO SET PIC TO TEXTURE IN CONFIG.CPP
using namespace std;

class Config{
private:
    unordered_map<string, shared_ptr<sf::Texture>> _texture_map;
    unordered_map<int, shared_ptr<sf::Font>> _font_map;
    shared_ptr<sf::Font> _get_font(int key) {
        if(this->_font_map.find(key) != this->_font_map.end()){
            return this->_font_map.at(key);
        }
        return nullptr;
    }
    shared_ptr<sf::Texture> _get_texture(string key){
        if(this->_texture_map.find(key) != this->_texture_map.end()){
            return this->_texture_map.at(key);
        }
        return nullptr;
    }

    void _set_texture();
    void _set_font();

public:
    Config(){
        this->_texture_map = unordered_map<string, shared_ptr<sf::Texture>>();
        this->_font_map = unordered_map<int, shared_ptr<sf::Font>>();
        this->_set_texture();
        this->_set_font();
    }
    ~Config(){
        this->_texture_map.clear();
        this->_font_map.clear();
    }

    sf::Texture& get_texture(string index) {
        shared_ptr<sf::Texture> texture = this->_get_texture(std::move(index));
        assert(texture != nullptr && "Getting non existed texture");
        return *texture;
    }
    sf::Font& get_font(int index){
        shared_ptr<sf::Font> font = this->_get_font(index);
        assert(font != nullptr && "Getting non existed font");
        return *font;
    }
};


// global instance here
extern Config config;
#endif
