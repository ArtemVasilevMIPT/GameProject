#include "gui.h"

Box::Box(sf::Vector2f pos, sf::Vector2f size)
{
    box.setSize(size);
    box.setPosition(pos.x, pos.y);
    position = pos;
}

void Box::setColor(sf::Color c)
{
    box.setFillColor(c);
}

void Box::setPosition(float x, float y)
{
    box.setPosition(x, y);
    position = sf::Vector2f(x, y);
}

void Box::resize(float x, float y)
{
    box.setSize(sf::Vector2f(x, y));
}

void Box::Draw(sf::RenderWindow &window)
{
    window.draw(box);
}

void Box::transform(sf::Transform &tr)
{
    UIElement::transform(tr);
    box.setPosition(position);
}

template<typename FuncType>
Button<FuncType>::Button(sf::Vector2f pos, sf::Vector2f size, FuncType &functor) : Box(pos, size)
{
    func = functor;
}

template<typename FuncType>
void Button<FuncType>::OnClick()
{
    func();
}


void TextBox::Draw(sf::RenderWindow &window)
{
    window.draw(box);
    window.draw(text);
}

TextBox::TextBox(sf::Vector2f pos, sf::Vector2f size, std::string str) : Box(pos, size)
{
    text.setString(str);
    text.setPosition(pos.x, pos.y);
}

void TextBox::transform(sf::Transform &tr)
{
    Box::transform(tr);
    text.setPosition(position);
}


Canvas::~Canvas()
{
    for(auto& elem : ui)
    {
        delete elem;
    }
}

void Canvas::drawUI(sf::RenderWindow &window)
{
    for(const auto& elem : ui)
    {
        elem->Draw(window);
    }
}

template<typename T>
void Canvas::addElement(T *element)
{
    ui.push_back(dynamic_cast<UIElement*>(element));
}

Canvas::Canvas()
{
    topRightCorner.x = 0.0f;
    topRightCorner.y = 0.0f;
    width = 100;
    height = 100;
    anchorPoint.x = 50;
    anchorPoint.y = 50;
}

void Canvas::transform(sf::Transform &tr)
{
    tr.transformPoint(topRightCorner);
    tr.transformPoint(anchorPoint);
    for(auto& uiElem : ui)
    {
        uiElem->transform(tr);
    }
}

Canvas::Canvas(const Canvas& other)
{
    topRightCorner = other.topRightCorner;
    width = other.width;
    height = other.height;
    anchorPoint = other.anchorPoint;
    state = other.state;

    for(const auto& elem : other.ui)
    {
        //TODO implement
    }
}

UI::~UI()
{
    delete canvas;
}

void UI::Draw(sf::RenderWindow &window)
{
    canvas->drawUI(window);
}

void UI::setCanvas(Canvas* c)
{
    canvas = c;
}

UIComponent::UIComponent(Canvas* canvas)
{
    ui.setCanvas(canvas);
}

void UIComponent::Draw(sf::RenderWindow &window)
{
    ui.Draw(window);
}

void UIElement::transform(sf::Transform &tr)
{
    tr.transformPoint(position);
}
