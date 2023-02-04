#ifndef GUI_H
#define GUI_H

// button state
enum bs
{
  idle = 0,
  hovered,
  active
};

namespace GUI
{

  class max_press_time
  {
  public:
    max_press_time() = default;

    const bool pressable_button()
    {
      if (key_timer.getElapsedTime().asMilliseconds() >
          key_time_max_miliseconds)
      {
        key_timer.restart();
        return true;
      }

      return false;
    }

  private:
    static const sf::Int32 key_time_max_miliseconds = 330;
    sf::Clock key_timer;
  };

  class button
  {
  public:
    button(float x, float y, float width, float height, std::string _text,
           sf::Font *font, size_t _char_size, sf::Color _text_idle_color,
           sf::Color _text_hover_color, sf::Color _text_active_color,
           sf::Color _idle_color, sf::Color _hover_color, sf::Color _active_color,
           sf::Color _outline_idle_color = sf::Color::Transparent,
           sf::Color _outline_hover_color = sf::Color::Transparent,
           sf::Color _outline_active_color = sf::Color::Transparent,
           short unsigned id = 0);
    button();
    ~button();

    /*Updates the state for hovered and active button*/
    void update(const sf::Vector2f &mouse_pos);
    void render(sf::RenderTarget &target);

    const bool pressed() const;
    const sf::String get_text();
    const short unsigned get_id() const;
    const sf::FloatRect get_bounds() const;

    void set_id(const short unsigned id);
    void set_text(const sf::String _text);
    void set_pos(const GUI::button &_other);
    void set_pos(const float x, const float y);

  private:
    sf::RectangleShape shape;
    sf::Font *font;
    sf::Text text;
    size_t char_size;

    sf::Color text_idle_color;
    sf::Color text_hover_color;
    sf::Color text_active_color;

    sf::Color idle_color;
    sf::Color hover_color;
    sf::Color active_color;

    sf::Color outline_idle_color;
    sf::Color outline_hover_color;
    sf::Color outline_active_color;

    short unsigned button_state;
    short unsigned id;
  };

  class drop_down_box
  {
  public:
    drop_down_box(float x, float y, float width, float height, sf::Font &_font,
                  const std::vector<std::string> elem_list,
                  const unsigned default_index = 0);

    void update(const sf::Vector2f &mouse_pos);
    void render(sf::RenderTarget &target);

    const unsigned short get_active_elem_id() const;

    ~drop_down_box();

  private:
    void button_handler();

  private:
    GUI::button *active_elem;
    std::vector<GUI::button *> list;
    sf::Font &font;

    sf::RectangleShape list_box;

    GUI::max_press_time pt;
    bool show_menu;
  };
} // namespace GUI
#endif