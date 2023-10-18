#include "chip-8.h"

namespace CHIP8
{
  void Load_Font(Spec &spec)
  {
    // put font into memory

    // 0
    spec.ram[0] = 0xF0;
    spec.ram[1] = 0x90;
    spec.ram[2] = 0x90;
    spec.ram[3] = 0x90;
    spec.ram[4] = 0xF0;

    // 1 
    spec.ram[5] = 0x20;
    spec.ram[6] = 0x60;
    spec.ram[7] = 0x20;
    spec.ram[8] = 0x20;
    spec.ram[9] = 0x70;

    // 2
    spec.ram[10] = 0xF0;
    spec.ram[11] = 0x10;
    spec.ram[12] = 0xF0;
    spec.ram[13] = 0x80;
    spec.ram[14] = 0xF0;

    // 3
    spec.ram[15] = 0xF0;
    spec.ram[16] = 0x10;
    spec.ram[17] = 0xF0;
    spec.ram[18] = 0x10;
    spec.ram[19] = 0xF0;

    // 4
    spec.ram[20] = 0x90;
    spec.ram[21] = 0x90;
    spec.ram[22] = 0xF0;
    spec.ram[23] = 0x10;
    spec.ram[24] = 0x10;

    // 5
    spec.ram[25] = 0xF0;
    spec.ram[26] = 0x80;
    spec.ram[27] = 0xF0;
    spec.ram[28] = 0x10;
    spec.ram[29] = 0xF0;

    // 6
    spec.ram[30] = 0xF0;
    spec.ram[31] = 0x80;
    spec.ram[32] = 0xF0;
    spec.ram[33] = 0x90;
    spec.ram[34] = 0xF0;

    // 7
    spec.ram[35] = 0xF0;
    spec.ram[36] = 0x10;
    spec.ram[37] = 0x20;
    spec.ram[38] = 0x40;
    spec.ram[39] = 0x40;

    // 8
    spec.ram[40] = 0xF0;
    spec.ram[41] = 0x90;
    spec.ram[42] = 0xF0;
    spec.ram[43] = 0x90;
    spec.ram[44] = 0xF0;

    // 9
    spec.ram[45] = 0xF0;
    spec.ram[46] = 0x90;
    spec.ram[47] = 0xF0;
    spec.ram[48] = 0x10;
    spec.ram[49] = 0xF0;

    // A
    spec.ram[50] = 0xF0;
    spec.ram[51] = 0x90;
    spec.ram[52] = 0xF0;
    spec.ram[53] = 0x90;
    spec.ram[54] = 0x90;

    // B
    spec.ram[55] = 0xE0;
    spec.ram[56] = 0x90;
    spec.ram[57] = 0xE0;
    spec.ram[58] = 0x90;
    spec.ram[59] = 0xE0;

    // C
    spec.ram[60] = 0xF0;
    spec.ram[61] = 0x80;
    spec.ram[62] = 0x80;
    spec.ram[63] = 0x80;
    spec.ram[64] = 0xF0;

    // D
    spec.ram[65] = 0xE0;
    spec.ram[66] = 0x90;
    spec.ram[67] = 0x90;
    spec.ram[68] = 0x90;
    spec.ram[69] = 0xE0;

    // E
    spec.ram[70] = 0xF0;
    spec.ram[71] = 0x80;
    spec.ram[72] = 0xF0;
    spec.ram[73] = 0x80;
    spec.ram[74] = 0xF0;

    // F
    spec.ram[75] = 0xF0;
    spec.ram[76] = 0x80;
    spec.ram[77] = 0xF0;
    spec.ram[78] = 0x80;
    spec.ram[79] = 0x80;

  }

  bool Load_Rom(Spec &spec, const char* rom_path)
  {
    std::ifstream file(rom_path);

    // properly load byte by byte?
 
  }

  void Init_Chip8(Spec &spec, const char* rom_path)
  {
    const uint32_t entry = 0x200; // chip8 starts loading roms at 0x200

    Load_Font(spec);

    if(!Load_Rom(spec, rom_path))
    {
      LOG("Could not load rom at: " + std::to_string(rom_path));
    }
    
    spec->state = State::RUN;
    spec->PC = entry; // set Program Counter to entry
    spec->rom = rom_path;
  }
  
};
