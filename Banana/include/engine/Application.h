#pragma once

#include "glfw3.h"

namespace Banana
{
  class Application
  {
  public:
    Application();
    virtual ~Application();

    virtual void Run() = 0;
  };

  // definition is in client
  Application* CreateApplication();

};