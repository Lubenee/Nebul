#include "../Headers/pch.h"
#include "../Headers/SettingsState.hpp"

settings_state::settings_state(state_data *_state_data) : state(_state_data)
{
  init_keybinds();
  init_fonts();
  init_background();
  init_gui();
  init_text();
  check = new GUI::check_box(400.f, 210.f, 50, 50,
                             sf::Color(250, 50, 100, 150),
                             sf::Color(50, 150, 50, 50),
                             sf::Color(50, 250, 100, 150));
}

void settings_state::init_text()
{
  options_text.setFont(font);
  options_text.setPosition(130, 145);
  options_text.setCharacterSize(30);
  options_text.setFillColor(sf::Color(255, 155, 55, 255));
  options_text.setString("Resolution \n\nFullscreen");
  // options_text.setString("Resolution \n\nFullscreen \n\nAntialiasing
  // \n\nVsync \n\n");
}

void settings_state::init_gui()
{
  buttons["APPLY"] = new GUI::button(
      p2p_x(65.f), p2p_y(80.f),
      p2p_x(10.f), p2p_y(6.4f),
      "Apply", &font, 30,
      sf::Color(150, 150, 150, 200), sf::Color(250, 250, 250, 250), sf::Color(40, 40, 40, 80),
      sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

  buttons["BACK"] = new GUI::button(
      p2p_x(80.f), p2p_y(80.f),
      p2p_x(10.f), p2p_y(6.4f),
      "Back", &font,
      30, sf::Color(150, 150, 150, 200), sf::Color(250, 250, 250, 250),
      sf::Color(40, 40, 40, 80), sf::Color(70, 70, 70, 0),
      sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

  std::vector<std::string> list;
  vms = sf::VideoMode::getFullscreenModes();
  size_t current_resolution_index = 0;

  // TODO /7 bug. GetFullscreenModes returns all modes but adds them 7 times
  // each
  for (size_t i = 0; i < vms.size() / 7; ++i)
  {
    list.push_back(std::to_string(vms[i].width) + 'x' +
                   std::to_string(vms[i].height));
    if (vms[i].width == state_details->window->getSize().x &&
        vms[i].height == state_details->window->getSize().y)
      current_resolution_index = i;
  }

  drop_lists["RESOLUTION"] = new GUI::drop_down_box(
      400, 137, 200, 50, font, list, current_resolution_index);
}

void settings_state::init_keybinds()
{
  std::ifstream ifs;
  ifs.open("../Config/settingsState_keybinds.ini", std::ios::in);
  if (ifs.is_open())
  {
    std::string key = "";
    std::string key_value = "";
    while (ifs >> key >> key_value)
      keybinds[key] = supported_keys->at(key_value);
  }
  ifs.close();
}

void settings_state::init_fonts()
{
  if (!font.loadFromFile("../Fonts/pixelfont.TTF"))
    throw("ERROR::SETTINGS_STATE_H::COULD NOT LOAD FONT");
}

void settings_state::init_background()
{
  if (!background_texture.loadFromFile(
          "../Assets/Images/Backgrounds/bckgr1.jpg"))
    throw("ERROR::SETTINGS_STATE::FAILED TO LOAD BACKGROUND TEXTURE.");
  background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x),
                                  static_cast<float>(window->getSize().y)));

  background.setTexture(&background_texture);
}

void settings_state::update_gui()
{
  if (!drop_lists["RESOLUTION"]->get_active())
    for (auto &i : buttons)
      i.second->update(mouse_pos_window);
  for (auto &i : drop_lists)
    i.second->update(mouse_pos_window);
}

void settings_state::update_collision_timer()
{
  if (drop_lists["RESOLUTION"]->get_active())
    button_collision_timer.restart();
}

void settings_state::update_input(const float &dt) { update_mouse_pos(); }

void settings_state::button_handler()
{
  if (buttons["BACK"]->pressed() && valid_button_collision())
    end_state();

  else if (buttons["APPLY"]->pressed() && valid_button_collision())
  {
    if (state_details->gfx_settings->resolution.width !=
            vms[drop_lists["RESOLUTION"]->get_active_elem_id()].width &&
        state_details->gfx_settings->resolution.height !=
            vms[drop_lists["RESOLUTION"]->get_active_elem_id()].height)
    {

      state_details->gfx_settings->resolution =
          vms[drop_lists["RESOLUTION"]->get_active_elem_id()];
      if (check->get_active())
      {
        window->create(state_details->gfx_settings->resolution,
                       state_details->gfx_settings->title, sf::Style::Fullscreen,
                       state_details->gfx_settings->cs);
      }
      else
      {
        window->create(state_details->gfx_settings->resolution,
                       state_details->gfx_settings->title, sf::Style::Close,
                       state_details->gfx_settings->cs);
      }
      window->setVerticalSyncEnabled(state_details->gfx_settings->vsync);
      window->setFramerateLimit(state_details->gfx_settings->framerate_limit);
      background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x),
                                      static_cast<float>(window->getSize().y)));
      buttons["APPLY"]->set_pos(p2p_x(65.f), p2p_y(80.f));
      buttons["BACK"]->set_pos(p2p_x(80.f), p2p_y(80.f));
    }
  }
}

void settings_state::update(const float &dt)
{
  update_collision_timer();
  update_input(dt);
  update_gui();
  button_handler();
  check->update(mouse_pos_view);
}

void settings_state::render_gui(sf::RenderTarget &target)
{

  for (auto &i : buttons)
    i.second->render(target);

  for (auto &i : drop_lists)
    i.second->render(target);

  check->render(target);

  target.draw(options_text);
}

void settings_state::render(sf::RenderTarget *target)
{
  if (!target)
    target = window;
  target->draw(background);

  render_gui(*target);

  sf::Text t;
  t.setPosition(mouse_pos_view.x - 60, mouse_pos_view.y - 30);
  t.setFont(font);
  t.setCharacterSize(10);
  std::stringstream ss;
  ss << mouse_pos_view.x << ' ' << mouse_pos_view.y;
  t.setString(ss.str());
  target->draw(t);
}

bool settings_state::valid_button_collision()
{
  return button_collision_timer.getElapsedTime().asMilliseconds() > this->key_time_max_miliseconds + 50 ? true : false;
}

settings_state::~settings_state()
{
  for (auto &i : buttons)
    delete i.second;

  for (auto &i : drop_lists)
    delete i.second;

  delete check;
}