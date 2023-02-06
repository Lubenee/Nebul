#include "../Headers/pch.h"
#include "../Headers/GUI.hpp"
using namespace GUI;

drop_down_box::drop_down_box(float x, float y, float width, float height,
                             sf::Font &_font,
                             const std::vector<std::string> elem_list,
                             const unsigned default_index)
    : font(_font), show_menu(false)
{

  for (size_t i = 0; i < elem_list.size(); ++i)
  {
    list.push_back(new button(
        x, y + (i + 1) * height, width, height, elem_list.at(i), &font, 22,
        sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255),
        sf::Color(40, 40, 40, 80), sf::Color(70, 71, 70, 200),
        sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
        sf::Color(150, 150, 150, 0), sf::Color(150, 150, 150, 0),
        sf::Color(150, 150, 150, 0), i));
  }
  active_elem =
      new button(x, y, width, height, elem_list.at(default_index), &font, 22,
                 sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200),
                 sf::Color(40, 40, 40, 80), sf::Color(100, 100, 100, 200),
                 sf::Color(200, 200, 200, 200), sf::Color(30, 30, 30, 200),
                 sf::Color(150, 150, 150, 0), sf::Color(150, 150, 150, 0),
                 sf::Color(150, 150, 150, 0), default_index);

  list_box.setSize(sf::Vector2f(width, elem_list.size() * height));
  list_box.setPosition(x, y);
  list_box.setFillColor(sf::Color(255, 100, 50, 20));
}

void drop_down_box::button_handler()
{
  // Show and hide the list
  if (active_elem->pressed() && pt.pressable_button())
    show_menu = show_menu ? false : true;
}

void drop_down_box::update(const sf::Vector2i &mouse_pos)
{
  button_handler();
  active_elem->update(mouse_pos);

  if (show_menu)
    for (auto &button : list)
    {
      button->update(mouse_pos);

      if (button->pressed() && pt.pressable_button())
      {
        show_menu = false;
        active_elem->set_text(button->get_text());
        active_elem->set_id(button->get_id());
        break;
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
          !list_box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
      {
        show_menu = false;
        break;
      }
    }
}

void drop_down_box::render(sf::RenderTarget &target)
{
  active_elem->render(target);
  if (show_menu)
    for (auto &i : list)
      i->render(target);

  // target.draw(list_box);
}

const unsigned short drop_down_box::get_active_elem_id() const
{
  return active_elem->get_id();
}

const bool drop_down_box::get_active() const
{
  return show_menu;
}

drop_down_box::~drop_down_box()
{
  delete active_elem;
  for (auto &i : list)
    delete i;
}
