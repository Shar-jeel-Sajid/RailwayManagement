#pragma once

// #include "backend.cpp"

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <conio.h>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

int ij =0;
void invert_colors(int t)
{
    ij =t;
}

Color colors[2] = {Color::Black,Color::White};

int station_page(RenderWindow&);
void new_page(RenderWindow &);
void admin_page(RenderWindow &);
int track_page(RenderWindow&);
int train_page(RenderWindow&);
void manage_schedule(RenderWindow&);
int select_class(RenderWindow&,string head);


class Button  {
protected:
    Text text;
    RectangleShape rect;

public:
    Button(Vector2f pos, string name, const Font &);
    void draw(RenderWindow &window);
    void setSize(Vector2f);
    void setText_size(int size) {text.setCharacterSize(size);}
    void setText(string str){text.setString(str);}
    bool pressed (RenderWindow& , Vector2f);   
    void highlight();
    void setPositon(Vector2f pos){text.setPosition(Vector2f(pos.x+25,pos.y+3));
    rect.setPosition(pos);}
    string get_text(){return text.getString();}
};
class Input_box : public Button
{
private:
    Text inner;
    string input;
    bool show;

public:
    Input_box(Vector2f, string, Font &);
    void take_input(RenderWindow &window);
    string get_input() { return input; }
    void draw(RenderWindow &);
    void selected(bool);
    void clear() { input.clear(); }
    void setInput(string a){input = a;}
    void show_pass() { show = !show; }
};
class Text_box : public Button
{
public:
    Text_box(Vector2f pos , string str ,const Font *font): Button (pos,str,*font){}
    void heading(int i){ text.setCharacterSize(i);text.Bold; }
    string gettext() { return text.getString();}
};










void Button::highlight(){
    text.setFillColor(Color::Blue);
    text.setStyle(text.Underlined);
}
bool Button::pressed(RenderWindow &window, Vector2f pos)
{
    if (rect.getGlobalBounds().contains(pos))
    {
        return true;
    }
    return false;
}
Button::Button(Vector2f pos, const string name,const Font &font)
{
    text.setFont(font);
    text.setPosition(Vector2f(pos.x + 25, pos.y + 3));
    text.setFillColor(colors[ij]);
    text.setString(name);
    text.setCharacterSize(20);
    rect.setSize(Vector2f(100, 30));
    rect.setPosition(pos);
    rect.setFillColor(Color::Transparent);
    rect.setOutlineColor(colors[ij]);
    rect.setOutlineThickness(1);
}
void Button::draw(RenderWindow &window)
{
    window.draw(rect);
    window.draw(text);
}
void Button::setSize(Vector2f size)
{
    rect.setSize(size);
}
Input_box::Input_box(Vector2f pos, const string before_text,Font &font) : Button(pos, before_text, font), inner(text)
{
    rect.setSize(Vector2f(300, 30));
    text.setPosition(Vector2f(pos.x - (before_text.length()) * (110 / 9), pos.y + 3));
    inner.setString(input);
    inner.setFillColor(colors[ij]);
    inner.setPosition(Vector2f(pos.x + 5, pos.y + 3));
    show = true;
}
void Input_box::draw(RenderWindow &Window)
{
    if (show)
        inner.setString(input);
    else
    {
        string tmp;
        for (int i = 0; i < input.length(); i++)
            tmp.push_back('*');
        inner.setString(tmp);
    }
    Button::draw(Window);
    Window.draw(inner);
}
void Input_box::take_input(RenderWindow &window)
{
    if (input.length() <= 20)
    {
        Event event;
        char c;
        while (!kbhit)
        {
        }
        if (window.pollEvent(event))
        {
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == ' ')
                    return;
                if (event.text.unicode == '\b')
                {
                    if (input.size())
                        input.pop_back();
                    return;
                }
                if (event.text.unicode < 128)
                    input += event.text.unicode;
            }
        }
    }
}
void Input_box::selected(bool selected)
{
    if (selected)
        rect.setOutlineThickness(3);
    else
        rect.setOutlineThickness(1);
}

