#include "../Headers/pch.h"
#include "../Headers/GUI.hpp"
using namespace GUI;

button::button(float x, float y,
               float width, float height,
               std::string _text, sf::Font *font,
               size_t _char_size,
               sf::Color _text_idle_color,
               sf::Color _text_hover_color,
               sf::Color _text_active_color,
               sf::Color _idle_color,
               sf::Color _hover_color,
               sf::Color _active_color,
               sf::Color _outline_idle_color,
               sf::Color _outline_hover_color,
               sf::Color _outline_active_color,
               short unsigned id)
{
  this->id = id;
  font = font;
  char_size = _char_size;

  text_idle_color = _text_idle_color;
  text_hover_color = _text_hover_color;
  text_active_color = _text_active_color;

  idle_color = _idle_color;
  hover_color = _hover_color;
  active_color = _active_color;

  outline_idle_color = _outline_idle_color;
  outline_hover_color = _outline_hover_color;
  outline_active_color = _outline_active_color;

  shape.setPosition(x, y);
  shape.setSize(sf::Vector2f(width, height));
  shape.setFillColor(idle_color);
  shape.setOutlineThickness(1.f);
  shape.setOutlineColor(outline_idle_color);

  text.setFont(*font);
  text.setString(_text);
  text.setFillColor(text_idle_color);
  text.setCharacterSize(char_size);
  text.setPosition(shape.getPosition().x + shape.getGlobalBounds().width / 2.f -
                       text.getGlobalBounds().width / 2.f,
                   shape.getPosition().y +
                       shape.getGlobalBounds().height / 2.f -
                       text.getGlobalBounds().height / 4.f);

  button_state = bs::idle;
}

button::button() {}

void button::update(const sf::Vector2f &mouse_pos)
{
  button_state = bs::idle;
  if (shape.getGlobalBounds().contains(mouse_pos))
  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      button_state = bs::active;
    else
      button_state = bs::hovered;
  }

  switch (button_state)
  {
  case bs::idle:
    shape.setFillColor(idle_color);
    text.setFillColor(text_idle_color);
    shape.setOutlineColor(outline_idle_color);
    break;
  case bs::hovered:
    shape.setFillColor(hover_color);
    text.setFillColor(text_hover_color);
    shape.setOutlineColor(outline_hover_color);
    break;
  case bs::active:
    shape.setFillColor(active_color);
    text.setFillColor(text_active_color);
    shape.setOutlineColor(outline_active_color);
    break;
  default:
    shape.setFillColor(sf::Color::Red);
    text.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Green);
    break;
  }
}

void button::render(sf::RenderTarget &target)
{
  target.draw(shape);
  target.draw(text);
}

const bool button::pressed() const
{
  return (button_state == bs::active ? true : false);
}

const sf::String button::get_text()
{
  return text.getString();
}

const short unsigned button::get_id() const
{
  return id;
}

const sf::FloatRect button::get_bounds() const
{
  return shape.getGlobalBounds();
}

void button::set_id(const short unsigned id)
{
  this->id = id;
}

void button::set_text(const sf::String _text)
{
  text.setString(_text);
}

void button::set_pos(const button &other)
{
  this->shape.setPosition(other.shape.getPosition().x,
                          other.shape.getPosition().y);
  text.setPosition(shape.getPosition().x + shape.getGlobalBounds().width / 2.f -
                       text.getGlobalBounds().width / 2.f,
                   shape.getPosition().y +
                       shape.getGlobalBounds().height / 2.f -
                       text.getGlobalBounds().height / 4.f);
}

void button::set_pos(const float x, const float y)
{
  shape.setPosition(x, y);
  text.setPosition(shape.getPosition().x + shape.getGlobalBounds().width / 2.f -
                       text.getGlobalBounds().width / 2.f,
                   shape.getPosition().y +
                       shape.getGlobalBounds().height / 2.f -
                       text.getGlobalBounds().height / 4.f);
}
button::~button() {}
