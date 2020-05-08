#include "cpu.h"
#include "ppu.h"

//TODO: Make a Vulkan renderer
//TODO: Finish SDL renderer

#include <SDL2/SDL.h>
//Screen dimension constants
const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 144;

void SETUP()
{
  //The window we'll be rendering to
  SDL_Window* window = NULL;

  //The surface contained by the window
  SDL_Surface* screenSurface = NULL;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  }
  else
  {
    //Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
  }
}