#include "ppu.h"

#include <iostream>

//TODO: Make a Vulkan renderer

using namespace std;

void PPU::RUN()
{
  initWindow();
  initVk();
  mainLoop();
  cleanup();
}

void PPU::mainLoop()
{
  double time = glfwGetTime();

  while(!glfwWindowShouldClose(window))
  {
    // Keep running
    glfwPollEvents();
    drawFrame();
  }

  vkDeviceWaitIdle(device);
}
