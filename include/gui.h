#pragma once

#include "core.h"
#include "SFML/Graphics.hpp"

class UIElement
{
public:
    sf::Vector2f position;//Position of top left corner
    UIElement() = default;
    UIElement(const UIElement& other) = default;
    virtual ~UIElement() = default;

    virtual void Draw(sf::RenderWindow& window){}
    virtual void transform(sf::Transform& tr);
};

class Box : public UIElement
{
protected:
    sf::RectangleShape box;
public:
    Box() = default;
    Box(sf::Vector2f pos, sf::Vector2f size);
    Box(const Box& other) = default;
    ~Box() override = default;

    void setColor(sf::Color c);
    void setPosition(float x, float y);
    void resize(float x, float y);
    void Draw(sf::RenderWindow& window) override;
    void transform(sf::Transform& tr) override;
};

template<typename FuncType>
class Button : public Box
{
private:
    FuncType func;
public:
    Button(sf::Vector2f pos, sf::Vector2f size,FuncType& func);
    Button(const Button& other) = default;
    ~Button() override = default;

    void OnClick();
};

class TextBox : public Box
{
private:
    sf::Text text;

public:
    TextBox(sf::Vector2f pos, sf::Vector2f size, std::string str);
    TextBox(const TextBox& other) = default;
    ~TextBox() override = default;

    void Draw(sf::RenderWindow& window) override;
    void transform(sf::Transform& tr) override;
};

class Canvas
{
private:
    std::vector<UIElement*> ui;
    std::string state = "STATIC";//STATIC - will be moved with the view
                                 //DYNAMIC - will not be moves with the view
public:
    sf::Vector2f topRightCorner;
    size_t width;
    size_t height;
    sf::Vector2f anchorPoint;

    Canvas();
    Canvas(const Canvas& other);
    ~Canvas();

    void drawUI(sf::RenderWindow& window);

    const std::string& getState()
    {
        return state;
    }
    void setState(const std::string& st)
    {
        state = st;
    }

    void transform(sf::Transform& tr);

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
    explicit UIComponent(Canvas* canvas);
    ~UIComponent() override  = default;

    void Draw(sf::RenderWindow& window);
};

/*
class UIManager
{
private:
    std::vector<
};
*/