#pragma once
#include "Sandbox.h"
#include <stack>

#define CHIP8_LOG(x) std::cout << "[CHIP-8] " << x << std::endl;

namespace CHIP8
{
  const uint32_t entry = 0x200; // chip8 starts loading roms at 0x200

  enum State
  {
    RUN = 0, PAUSE, QUIT
  };
  
  struct Spec
  {
    State state;           // Declare current chip-8 state

    uint8_t ram[4096];     // Emulate chip-8 original ram size

    uint8_t I;             // Index register
    uint16_t PC;           // Program Counter
    uint16_t AR[12];       // Subroutine stack

    uint8_t delay_timer;   // Decrements at 60hz > 0
    uint8_t sound_timer;   // Decrements at 60hz > 0 and plays sound

    bool key[16];          // Keys 0x0 - 0xF

    uint8_t registers[16]; // Data registers V0 - VF

    const char *rom;             // Running rom

    // screen values
    std::array<bool, 64> display_x;
    std::array<bool, 32> display_y;

    std::stack<uint16_t*> stack;
  };

  void Load_Font(Spec &spec);
  bool Load_Rom(Spec &spec, const char* rom_path);
  
  void Init_Spec(Spec &spec, const char* rom_path);

};
