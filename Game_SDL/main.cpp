// Game_SDL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CommonFunc.h"
#include "BaseObject.h"
#include "PlayerObject.h"
#include "TimeFps.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 720

BaseObject g_background;
BaseObject g_background2;

BaseObject g_ground;
BaseObject g_ground2;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("            FLAPPY BIRD          ",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    
    if (g_window == NULL)
        success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            success = false;
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.loadImg("image//bg.png", g_screen);
    return ret;
}
void Ground_Move(int& ground_x_, int& ground_x2_)
{
   
    ground_x_ -= SPEED_GROUND;
    ground_x2_ -= SPEED_GROUND;
    if (ground_x_ < -GROUND_STRET)
    {
        ground_x_ = GROUND_STRET;
    }
    if (ground_x2_ < -GROUND_STRET)
    {
        ground_x2_ = GROUND_STRET;
    }
}
void close()
{
    g_background.Free();
    
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}
int main(int argc,char* argv[])
{
    if (InitData() == false)
    {
        return -1;
    }

    bool quite = false;
    if (!LoadBackground())
    {
        return -1;
    }
    
    TimeFps fps;
    bool ret = g_ground.loadImg("image//ground.png", g_screen);

    if (ret == false)
    {
        return -1;
    }

     ret = g_ground2.loadImg("image//ground.png", g_screen);
    if (ret == false)
    {
        return -1;
    }
     
    ret = g_background2.loadImg("image//bg.png", g_screen);
    if (ret == false)
    {
        return -1;
    }

    int ground_x_ = 1, ground_x2_ = GROUND_STRET;
    int bg_x_ = 1, bg_x2_ = 1000;
    
    PlayerObject Player;
    ret = Player.loadImg("image//mid_bird.png",g_screen);
    if (ret == false)
    {
        
        return - 1;
    }
    Player.SetRect(150, 200);
    
    //Vong lap Game
    while (!quite)
    {
        fps.start();
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                quite = true;
            }
            Player.HandleInputAction(g_event, g_screen);
        }
  
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        Ground_Move(bg_x_, bg_x2_);
        g_background.SetRect(bg_x_, 0);
        g_background2.SetRect(bg_x2_, 0);
        g_background.Render(g_screen, NULL);
        g_background2.Render(g_screen, NULL);


        bool falling = Player.GetFalling();
        Player.DoFalling(g_screen);
        Player.Show(g_screen);
        
        Ground_Move(ground_x_,ground_x2_);
        g_ground.SetRect(ground_x_, GROUND_MAP);
        g_ground2.SetRect(ground_x2_, GROUND_MAP);
        g_ground.Render(g_screen); 
        g_ground2.Render(g_screen);
       
        SDL_RenderPresent(g_screen);

        int real_time_ = fps.get_ticks();
        int time_one_frame = 1000 / FRAMES_PER_SECOND;   // ms
        if (real_time_ < time_one_frame)
        {
            int delay_time = time_one_frame - real_time_;
            if(delay_time>=0)
                SDL_Delay(delay_time);
        }
      

        bool gameOver = Player.GetIsDie();
        if (gameOver)
        {
            CommonFunction::loadAudio("audio//die.wav");
            SDL_Delay(2000);
            quite = true;
        }
    }
    close();
    return 0;
}


















// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and sele5ct the .sln file
