#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

class animation_component
{
public:
    /* @brief Forces a sprite and a texture upon creating the class, because creating an animation without a sprite and a texture is pointless*/
    animation_component(sf::Sprite &_sprite, sf::Texture &_tex);

    /* @brief Plays the animation at the given key.*/
    const bool &play(const std::string key, const float &dt, const bool priority = false);

    /* @brief Changes the animation speed with a dynamic variable. If the entity's velocity is passed as a modifier,
    the animation speeds up as the entity's velocity increases.*/
    const bool &play(const std::string key, const float &dt, const float &modifier, const float &modifier_max, const bool priority = false);

    /* @brief Each animation needs a name, a timer (how fast the animation will run),
    a rectangle for each individual 'image', and the number of horizontal and vertical frames
    it needs.*/
    void add_animation(const std::string key, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

    /* @brief Returns true if a priority animation is done playing. */
    bool &is_done(const std::string key);

    ~animation_component();

private:
    class animation
    {
    public:
        animation(sf::Sprite &_sprite, sf::Texture &_sheet, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
            : sprite(_sprite), sheet(_sheet), animation_timer(animation_timer), width(width), height(height)
        {
            start_rect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
            current_rect = start_rect;
            end_rect = sf::IntRect(frames_x * width, frames_y * height, width, height);
            sprite.setTexture(sheet, true);
            sprite.setTextureRect(current_rect);

            timer = 0.f;
            done = false;
        }
        ~animation() = default;

        const bool &play(const float &dt)
        {
            // Update timer;
            done = false;
            timer += 100.f * dt;
            if (timer >= animation_timer)
            {
                // Reset timer;
                timer = 0.f;

                // Animate
                if (current_rect != end_rect)
                    current_rect.left += width;

                // Reset
                else
                {
                    done = true;
                    current_rect.left = start_rect.left;
                }

                sprite.setTextureRect(current_rect);
            }
            return done;
        }

        const bool &play(const float &dt, float mod_percent)
        {
            // Update timer;
            done = false;
            if (mod_percent < 0.5f)
                mod_percent = 0.5f;

            timer += mod_percent * 100.f * dt;
            if (timer >= animation_timer)
            {
                // Reset timer;
                timer = 0.f;

                // Animate
                if (current_rect != end_rect)
                    current_rect.left += width;

                // Reset
                else
                {
                    current_rect.left = start_rect.left;
                    done = true;
                }

                sprite.setTextureRect(current_rect);
            }
            return done;
        }

        void reset()
        {
            timer = animation_timer;
            current_rect = start_rect;
        }

        bool &is_done()
        {
            return done;
        }

        sf::Texture &sheet;
        sf::Sprite &sprite;

        float animation_timer;
        float timer;
        bool done;

        int width;
        int height;
        sf::IntRect start_rect;
        sf::IntRect current_rect;
        sf::IntRect end_rect;
    };
    sf::Sprite &sprite;
    sf::Texture &texture_sheet;
    animation *last_animation;
    animation *priority_animation;
    std::map<std::string, animation *> animations;
};

#endif