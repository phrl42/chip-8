#pragma once
#include "Sandbox.h"
#include <stack>

#define CHIP8_LOG(x) std::cout << "[CHIP-8] " << x << std::endl;

// this is haunting me in my dreams
#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15

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

    uint16_t I;             // Index register
    uint16_t PC;           // Program Counter

    uint8_t delay_timer;   // Decrements at 60hz > 0
    uint8_t sound_timer;   // Decrements at 60hz > 0 and plays sound

    bool key[16];          // Keys 0x0 - 0xF

    uint8_t registers[16]; // Data registers V0 - VF

    const char *rom;             // Running rom

    // screen values are saved at 'I'
    //bool display[32][64];

    std::stack<uint16_t*> stack; // Subroutine stack
  };

  void Load_Font(Spec *spec);
  bool Load_Rom(Spec *spec, const char* rom_path);

  uint16_t Combine(uint8_t first, uint8_t second);
  uint16_t Get_Value_N(uint16_t opcode, uint8_t n);
  
  void Init_Spec(Spec *spec, const char* rom_path);

  void Validate_Opcode(Spec *spec);
  void Update(Spec *spec);
  
};
