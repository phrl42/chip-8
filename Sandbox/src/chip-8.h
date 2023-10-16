#pragma once
#include "Sandbox.h"

namespace CHIP8
{
  struct Spec
  {
    uint8_t ram[4096];
    bool *display; // points somewhere to ram
  };
};
