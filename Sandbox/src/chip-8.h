#pragma once
#include "Sandbox.h"
#include <stack>

namespace CHIP8
{
  struct Spec
  {
    uint8_t ram[4096];
    uint8_t *IP;

    uint8_t delay_timer;
    uint8_t sound_timer;

    std::array<bool, 32> display_x;
    std::array<bool, 64> display_y;
    
    bool display[64*32];

    uint16_t address_register : 12;
    uint8_t registers[16]; // ranging from V0 to VF whereas VF should be avoided

    bool keys[16];

    std::stack<uint16_t*> stack;
  };

  void Init_Spec(Spec& spec);

};
