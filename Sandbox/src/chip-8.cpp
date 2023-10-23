#include "chip-8.h"
#include <cstring>
#include <sstream>

namespace CHIP8
{
  void Load_Font(Spec *spec)
  {
    // put font into memory

    // 0
    spec->ram[0] = 0xF0;
    spec->ram[1] = 0x90;
    spec->ram[2] = 0x90;
    spec->ram[3] = 0x90;
    spec->ram[4] = 0xF0;

    // 1 
    spec->ram[5] = 0x20;
    spec->ram[6] = 0x60;
    spec->ram[7] = 0x20;
    spec->ram[8] = 0x20;
    spec->ram[9] = 0x70;

    // 2
    spec->ram[10] = 0xF0;
    spec->ram[11] = 0x10;
    spec->ram[12] = 0xF0;
    spec->ram[13] = 0x80;
    spec->ram[14] = 0xF0;

    // 3
    spec->ram[15] = 0xF0;
    spec->ram[16] = 0x10;
    spec->ram[17] = 0xF0;
    spec->ram[18] = 0x10;
    spec->ram[19] = 0xF0;

    // 4
    spec->ram[20] = 0x90;
    spec->ram[21] = 0x90;
    spec->ram[22] = 0xF0;
    spec->ram[23] = 0x10;
    spec->ram[24] = 0x10;

    // 5
    spec->ram[25] = 0xF0;
    spec->ram[26] = 0x80;
    spec->ram[27] = 0xF0;
    spec->ram[28] = 0x10;
    spec->ram[29] = 0xF0;

    // 6
    spec->ram[30] = 0xF0;
    spec->ram[31] = 0x80;
    spec->ram[32] = 0xF0;
    spec->ram[33] = 0x90;
    spec->ram[34] = 0xF0;

    // 7
    spec->ram[35] = 0xF0;
    spec->ram[36] = 0x10;
    spec->ram[37] = 0x20;
    spec->ram[38] = 0x40;
    spec->ram[39] = 0x40;

    // 8
    spec->ram[40] = 0xF0;
    spec->ram[41] = 0x90;
    spec->ram[42] = 0xF0;
    spec->ram[43] = 0x90;
    spec->ram[44] = 0xF0;

    // 9
    spec->ram[45] = 0xF0;
    spec->ram[46] = 0x90;
    spec->ram[47] = 0xF0;
    spec->ram[48] = 0x10;
    spec->ram[49] = 0xF0;

    // A
    spec->ram[50] = 0xF0;
    spec->ram[51] = 0x90;
    spec->ram[52] = 0xF0;
    spec->ram[53] = 0x90;
    spec->ram[54] = 0x90;

    // B
    spec->ram[55] = 0xE0;
    spec->ram[56] = 0x90;
    spec->ram[57] = 0xE0;
    spec->ram[58] = 0x90;
    spec->ram[59] = 0xE0;

    // C
    spec->ram[60] = 0xF0;
    spec->ram[61] = 0x80;
    spec->ram[62] = 0x80;
    spec->ram[63] = 0x80;
    spec->ram[64] = 0xF0;

    // D
    spec->ram[65] = 0xE0;
    spec->ram[66] = 0x90;
    spec->ram[67] = 0x90;
    spec->ram[68] = 0x90;
    spec->ram[69] = 0xE0;

    // E
    spec->ram[70] = 0xF0;
    spec->ram[71] = 0x80;
    spec->ram[72] = 0xF0;
    spec->ram[73] = 0x80;
    spec->ram[74] = 0xF0;

    // F
    spec->ram[75] = 0xF0;
    spec->ram[76] = 0x80;
    spec->ram[77] = 0xF0;
    spec->ram[78] = 0x80;
    spec->ram[79] = 0x80;

    CHIP8_LOG("Loaded custom font");
  }

  bool Load_Rom(Spec *spec, const char* rom_path)
  {
    std::ifstream file(rom_path);
    
    if(!file)
    {
      return false;
    }

    int length = 0;
    file.seekg(0, file.end);
    length = file.tellg();
    file.seekg(0, file.beg);
      
    // put all 4096 bytes into ram
    //file.read((char*)(spec->ram + entry), length);
    char byte = 0;
    uint16_t index = entry;
    while(file.get(byte))
    {
      spec->ram[index] = byte;
      index += 1;
    }
    CHIP8_LOG("Loaded " + std::to_string(length) + " bytes");

    file.close();
    return true;
  }

  uint16_t Combine(uint8_t first, uint8_t second)
  {
    uint16_t first_16 = (uint16_t) first; 
    uint16_t second_16 = (uint16_t) second;

    first_16 = first_16 << 8;

    uint16_t val = first_16 | second_16;

    return val;
  }

  uint16_t Get_Value_N(uint16_t opcode, uint8_t n)
  {
    if(n > 3)
    {
      CHIP8_LOG("Cannot get " + std::to_string(n) + ". Opcode is 16-bit only: 0-3 MAX");
      return 0;
    }
    opcode = opcode << (n * 4);
    opcode = opcode >> 12;

    return opcode;
  }
  
  void Init_Spec(Spec *spec, const char* rom_path)
  {
    // zero all arrays
    memset(spec->ram, 0, sizeof(spec->ram) / sizeof(spec->ram[0]));
    memset(spec->key, 0, sizeof(spec->key) / sizeof(spec->key[0]));
    memset(spec->registers, 0, sizeof(spec->registers) / sizeof(spec->registers[0]));

    for(int y = 0; y < 32; y++)
    {
      for(int x = 0; x < 64; x++)
      {
	spec->display[y][x] = 0;
      }
    }

    Load_Font(spec);

    if(!Load_Rom(spec, rom_path))
    {
      CHIP8_LOG("Could not load ROM at: " + std::string(rom_path));
    }
    
    CHIP8_LOG("Loaded ROM '" + std::string(rom_path) + "'");
    
    spec->state = State::RUN;
    spec->PC = entry; // set Program Counter to entry
    spec->rom = rom_path;
  }

  void Validate_Opcode(Spec *spec)
  {
    uint16_t opcode = Combine(spec->ram[spec->PC], spec->ram[spec->PC+1]);
    uint16_t prefix = opcode >> 12;
    std::cout << "[" << std::hex << spec->PC << "] " << std::hex << opcode << "(" << std::to_string(prefix) << ")"<< std::endl;
    switch(prefix)
    {

    case 0:
    {
      // clear screen
      if(opcode == 0x00E0)
      {
	for(int y = 0; y < 32; y++)
	{
	  for(int x = 0; x < 64; x++)
	  {
	    spec->display[y][x] = 0;
	  }
	}
      }

      // return from subroutine
      if(opcode == 0x00EE)
      {
	spec->PC = spec->stack.top();
	spec->stack.pop();
      }
      break;
    }

    case 1:
    {
      // jump to address NNN
      uint16_t address = opcode;

      address = address << 4;
      address = address >> 4;

      spec->PC = address - 2;
      break;
    }

    case 2:
    {
      // call to subroutine at NNN
      // and save current address in stack
      // so it can be used when returning from subroutine
      uint16_t address = opcode;

      address = address << 4;
      address = address >> 4;

      spec->stack.push(spec->PC);

      spec->PC = address - 2;
      break;
    }

    case 3:
    {
      // skips next instruction if VX is NN
      uint16_t index = opcode;
      index = index << 4;
      index = index >> 12;

      uint16_t value = opcode;
      value = value << 8;
      value = value >> 8;
      // side note: lol, so every chip-8's if statement content is a subroutine, so you can easily skip it 
      if(spec->registers[index] == value)
      {
	spec->PC += 2;
      }
      break;
    }

    case 4:
    {
      // skips next instruction if VX is not NN
      uint16_t index_X = Get_Value_N(opcode, 1);
      //index_X = index_X << 4;
      //index_X = index_X >> 12;

      uint16_t value = opcode;
      value = value << 8;
      value = value >> 8;

      if(spec->registers[index_X] != value)
      {
	spec->PC += 2;
      }
      break;
    }

    case 5:
    {
      // skips next instruction if VX is VY
      uint16_t index_X = Get_Value_N(opcode, 1);
      //index_X = index_X << 4;
      //index_X = index_X >> 12;

      uint16_t index_Y = Get_Value_N(opcode, 2);
      //index_Y = index_Y << 8;
      //index_Y = index_Y >> 12;
      
      if(spec->registers[index_X] == spec->registers[index_Y])
      {
	spec->PC += 2;
      }

      break;
    }
    
    case 6:
    {
      // set VX to NN
      uint16_t index_X = Get_Value_N(opcode, 1);
      //index_X = index_X << 4;
      //index_X = index_X >> 12;

      uint16_t value = opcode;
      value = value << 8;
      value = value >> 8;

      spec->registers[index_X] = value;
      break;
    }
    case 7:
    {
      // add NN to VX
      uint16_t index_X = Get_Value_N(opcode, 1);
      //index_X = index_X << 4;
      //index_X = index_X >> 12;

      uint16_t value = opcode;
      value = value << 8;
      value = value >> 8;

      spec->registers[index_X] += value;
      break;
    }

    case 8:
    {
      // operations
      uint16_t operation = Get_Value_N(opcode, 3);
      uint16_t index_X = Get_Value_N(opcode, 1);
      uint16_t index_Y = Get_Value_N(opcode, 2);
      switch(operation)
      {
	// VX = VY
      case 0:
      {
	spec->registers[index_X] = spec->registers[index_Y];
	break;
      }

      // bitwise OR
      case 1:
      {
	spec->registers[index_X] |= spec->registers[index_Y];
	break;
      }

      // bitwise AND
      case 2:
      {
	spec->registers[index_X] &= spec->registers[index_Y];
	break;
      }

      // bitwise XOR
      case 3:
      {
	spec->registers[index_X] ^= spec->registers[index_Y];
	break;
      }
      
      // add
      case 4:
      {
	spec->registers[index_X] += spec->registers[index_Y];
	break;
      }

      // subtract
      case 5:
      {
	spec->registers[index_X] -= spec->registers[index_Y];
	break;
      }

      // store lsb at VF and rshift VX by 1
      case 6:
      {
	uint16_t lsb_vx = spec->registers[index_X];
	lsb_vx = lsb_vx << 15;
	lsb_vx = lsb_vx >> 15;
	spec->registers[15] = lsb_vx;

	spec->registers[index_X] >>= 1;
	break;
      }

      // VX = VY - VX
      case 7:
      {
	spec->registers[index_X] = spec->registers[index_Y] - spec->registers[index_X];
	break;
      }

      // inverse instruction of 6: store msb at VF and lshift VX by 1 
      case E:
      {
	uint16_t msb_vx = spec->registers[index_X];
	msb_vx = msb_vx >> 15;
	spec->registers[15] = msb_vx;

	spec->registers[index_X] <<= 1;
	break;
      }
    
      default:
      {
	std::ostringstream stream;
	stream << std::hex << opcode;
	CHIP8_LOG("Instruction '" + stream.str() + "' unknown.");
	break;
      }
      }
    }
    case 9:
    { 
      break;
    }

    // set I (Index Register) to NNN
    case A:
    {
      uint16_t val = opcode;
      val = val << 4;
      val = val >> 4;
      spec->I = val;
      break;
    }

    case B:
    {
      break;
    }

    case C:
    {
      break;
    }

    // DXYN
    // draw at (VX, VY) with (8, N) 
    case D:
    {
      uint16_t x = spec->registers[Get_Value_N(opcode, 1)];
      uint16_t y = spec->registers[Get_Value_N(opcode, 2)];
      uint16_t n = Get_Value_N(opcode, 3);
      bool collided = false;

      for(uint16_t h = 0; h < n; h++)
      {
	for(uint8_t w = 0; w < 8; w++)
	{
	  uint8_t row = spec->ram[spec->I + h];
	  row = row << w;
	  row = row >> (7 - w);
	  if(spec->display[y+h][x+w]) collided = true;
	  spec->display[y+h][x+w] = row;
	}
      }

      spec->registers[15] = collided;
      break;
    }
    
    case E:
    {
      break;
    }

    case F:
    {
      break;
    }
    
    default:
    {
      std::ostringstream stream;
      stream << std::hex << opcode;
      CHIP8_LOG("Instruction '" + stream.str() + "' unknown.");
      break;
    }
    }
    spec->PC += 2;
  }
  
  void Update(Spec *spec)
  {
    Validate_Opcode(spec);
  }
  
};
