#include <switch.h>

#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* image;
SDL_Texture* texture;

Mix_Music* music;

void initAudio()
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) SDL_Quit();
  music = Mix_LoadMUS("audio.mp3");
}

void initImage()
{
  window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, SDL_WINDOW_FULLSCREEN);
  if(!window) SDL_Quit();

  renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_SOFTWARE);
  if(!renderer) SDL_Quit();

  image = SDL_LoadBMP("image.bmp");
  texture = SDL_CreateTextureFromSurface(renderer, image);

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void initJoycons()
{
  for(int i = 0; i < 2; i++)
  {
    if(!SDL_JoystickOpen(i))
    {
      printf("%s Joycon is disconnected, quitting in 5...\n", i ? "Right" : "Left");
      SDL_Delay(5000);
      SDL_Quit();
    }
  }
}

int main(int argc, char **argv)
{
  int done = 0;

  SDL_Init(SDL_INIT_EVERYTHING);

  initImage();
  initJoycons();
  initAudio();

  while(!done)
  {
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
      switch (event.type) {
        case SDL_JOYBUTTONDOWN:
          if(event.jbutton.which == 0 && event.jbutton.button == 10)
            done = 1;
          else if(event.jbutton.which == 0 && event.jbutton.button == 0)
            Mix_PlayMusic(music, 1);
          break;
      }
    }
  }

  SDL_Quit();
  return 0;
}
