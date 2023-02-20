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
    void update(const sf::Vector2i &mouse_pos);
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

    void update(const sf::Vector2i &mouse_pos);
    void render(sf::RenderTarget &target);

    const unsigned short get_active_elem_id() const;
    const bool get_active() const;

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

  class texture_selector
  {
  public:
    texture_selector(const float _x, const float _y, const float _width, const float _height, const float grid_size, const sf::Texture &texture_sheet, sf::Font &font);

    void update(const sf::Vector2i &mouse_pos_window);
    void render(sf::RenderTarget &target);

    const bool get_active() const;
    const bool get_hidden() const;
    void set_hidden(bool _state);
    const sf::IntRect &get_texture_rect() const;

    ~texture_selector();

  private:
    sf::RectangleShape bounds;
    sf::Sprite sheet;
    float grid_size;

    bool active;
    bool hidden;
    button *hide_button;

    sf::RectangleShape selector;
    sf::IntRect texture_rect;
    sf::Vector2u mouse_pos_grid;

    max_press_time pt;
  };

  class check_box
  {
  public:
    check_box(float x, float y,
              float width, float height,
              sf::Color inactive_color,
              sf::Color hover_color,
              sf::Color active_color);
    void update(const sf::Vector2f mouse_pos);
    void render(sf::RenderTarget &target);

    void set_active();

    const bool get_active() const;
    ~check_box();

  private:
    sf::RectangleShape shape;
    short unsigned button_state;
    bool active;

    sf::Color hover_color;
    sf::Color inactive_color;
    sf::Color active_color;

    max_press_time pt;
  };

  /*
    * @brief
        Converts a percentage value to pixels relative to the current resolution on the x-axis.
      @param        float percent       The percentage value.
      @retval       const float         The calculated pixel value.
    */
  const float p2p_x(const float _percent, const sf::VideoMode &vm);

  /*
  * @brief
      Converts a percentage value to pixels relative to the current resolution on the y-axis.
    @param        float percent       The percentage value.
    @retval       float pixels         Returns the calculated pixel value.
  */
  const float p2p_y(const float _percent, const sf::VideoMode &vm);

  /*
  * @brief
      Calculates the character size for text using the current resolution and a constant (100).
    @retval       unsigned            Returns the calculated character size value.
  */
  const unsigned calc_char_size(const sf::VideoMode &vm);
} // namespace GUI

#endif