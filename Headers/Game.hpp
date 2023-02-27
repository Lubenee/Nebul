#ifndef GAME_H
#define GAME_H
#include "MainMenuState.hpp"
#include "GraphicsSettings.hpp"

class main_menu_state;
class graphics_settings;

class game
{
public:
  game();

  /* Core */
  void run();

  ~game();

private:
  /*Update*/
  void process_events();
  void update_delta_time();
  void update();

  /*Render*/
  void render();

  /*Initializers*/
  void init_window();
  void init_states();
  void init_keys();
  void init_state_data();

  /* Exit */
  void exit_window();

private:
  /* Window */
  sf::RenderWindow *window;

  /* Settings */
  graphics_settings gfx;
  state_data state_details;

  /* PollEvents */
  sf::Event event;

  /* Delta time */
  sf::Time time_per_frame;

  /* Stack */
  std::stack<state *> states;
  const float grid_size;

  /* Keyboard */
  std::map<std::string, int> supported_keys;
};

#endif