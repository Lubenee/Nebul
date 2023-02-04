#include "../Headers/pch.h"
#include "../Headers/AnimationComponent.hpp"

animation_component::animation_component(sf::Sprite &_sprite, sf::Texture &_tex)
    : sprite(_sprite), texture_sheet(_tex), last_animation(nullptr), priority_animation(nullptr)
{
}

const bool &animation_component::play(const std::string key, const float &dt, const bool priority)
{

    /*
        In order to start each animation from it's first frame, the last played animation needs to be reset.
    */
    // If there is a priority animation ..
    if (priority_animation)
    {
        if (priority_animation == animations[key])
        {
            if (last_animation != animations[key])
            {
                if (last_animation == nullptr)
                    last_animation = animations[key];
                else
                {
                    last_animation->reset();
                    last_animation = animations[key];
                }
            }
            // If the priority animation is done, we remove it
            if (animations[key]->play(dt))
            {
                priority_animation = nullptr;
            }
        }
    }
    // Play animation if no other priority animation is set.
    else
    {
        if (priority)
            priority_animation = animations[key];
        if (last_animation != animations[key])
        {
            if (last_animation == nullptr)
                last_animation = animations[key];
            else
            {
                last_animation->reset();
                last_animation = animations[key];
            }
        }
        animations[key]->play(dt);
    }
    return animations[key]->is_done();
}

const bool &animation_component::play(const std::string key, const float &dt, const float &modifier, const float &modifier_max, const bool priority)
{
    if (priority_animation)
    {
        if (priority_animation == animations[key])
        {
            if (last_animation != animations[key])
            {
                if (last_animation == nullptr)
                    last_animation = animations[key];
                else
                {
                    last_animation->reset();
                    last_animation = animations[key];
                }
            }
            if (animations[key]->play(dt))
            {
                priority_animation = nullptr;
            }
        }
    }
    // Play animation if no other priority animation is set.
    else
    {
        if (priority)
            priority_animation = animations[key];

        if (last_animation != animations[key])
        {
            if (last_animation == nullptr)
                last_animation = animations[key];
            else
            {
                last_animation->reset();
                last_animation = animations[key];
            }
        }
        animations[key]->play(dt, abs(modifier / modifier_max));
    }
    return animations[key]->is_done();
}

void animation_component::add_animation(const std::string key, float animation_timer,
                                        int start_frame_x, int start_frame_y,
                                        int frames_x, int frames_y,
                                        int width, int height)
{
    animations[key] = new animation(this->sprite, this->texture_sheet, animation_timer, start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

bool &animation_component::is_done(const std::string key)
{
    return this->animations[key]->is_done();
}

animation_component::~animation_component()
{
    for (auto &i : this->animations)
        delete i.second;
}
