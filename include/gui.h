#pragma once

#include "core.h"
#include "SFML/Graphics.hpp"

class UIElement : public Object
{
public:
    UIElement() = default;
    virtual ~UIElement() = default;

    virtual void Draw(sf::RenderWindow& window){}
    void OnStart() override{}
    void OnTick() override{}
};

class Box : public UIElement
{
protected:
    sf::RectangleShape box;
public:
    Box() = default;
    Box(sf::Vector2f pos, sf::Vector2f size);
    ~Box() override = default;

    void setColor(sf::Color c);
    void setPosition(float x, float y);
    void resize(float x, float y);
    void Draw(sf::RenderWindow& window) override;
};

template<typename FuncType>
class Button : public Box
{
private:
    FuncType func;
public:
    Button(sf::Vector2f pos, sf::Vector2f size,FuncType& func);
    ~Button() override = default;

    void OnClick() override;
};

class TextBox : public Box
{
private:
    sf::Text text;

public:
    TextBox(sf::Vector2f pos, sf::Vector2f size, std::string str);
    ~TextBox() override = default;

    void Draw(sf::RenderWindow& window) override;
};

class Canvas
{
private:
    std::vector<UIElement*> ui;
public:
    Canvas() = default;
    ~Canvas();

    void drawUI(sf::RenderWindow& window);

    template<typename T>
    void addElement(T* element);
};

class UI
{
private:
    Canvas* canvas = nullptr;
public:
    UI(Canvas* canvas) : canvas(canvas){}
    UI() = default;
    ~UI();

    void setCanvas(Canvas* c);
    void Draw(sf::RenderWindow& window);
};

class UIComponent : public Component
{
private:
    UI ui;
public:
    UIComponent(Canvas* canvas);
    ~UIComponent() override  = default;

    void Draw(sf::RenderWindow& window);
};