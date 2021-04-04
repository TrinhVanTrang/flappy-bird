#include "PlayerObject.h"

PlayerObject::PlayerObject()
{
	y_val_ = 1;
    is_falling_ = false;
}

PlayerObject::~PlayerObject()
{
    Free();
}

bool PlayerObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::loadImg(path, screen);
    return ret;
}

void PlayerObject::Show(SDL_Renderer* des)
{
    BaseObject::Render(des);
}

void PlayerObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    {
        if (events.type == SDL_KEYDOWN)
        {
            switch (events.key.keysym.sym)
            {
            case SDLK_SPACE:
            {
                if (is_falling_ == false)
                {
                    LoadImg("image//down_bird.png", screen);
                    CommonFunction::loadAudio("audio//wing.wav");
                    y_val_ = -20;
                }
            }
            }
        }
        else if (events.type == SDL_KEYUP)
        {
            switch (events.key.keysym.sym)
            {
            case SDLK_SPACE:
            {
                LoadImg("image//up_bird.png", screen);
                y_val_ = 8;
            }
            break;
            }
        }
    }
}
void PlayerObject::DoFalling(SDL_Renderer* des)
{
    rect_.y += y_val_;
    if (rect_.y +rect_.h <= 0)
    {
        rect_.y -= y_val_;
    }
    if (((rect_.y + rect_.h) >= GROUND_MAP) )
    {
        CommonFunction::loadAudio("audio//hit.wav");
        is_falling_ = true;
        DoGround(des);
    }
}
void PlayerObject::DoGround(SDL_Renderer* screen)
{
    y_val_ = 0;
    rect_.y = GROUND_MAP - rect_.h;
    is_die_ = true;
}