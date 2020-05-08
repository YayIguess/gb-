#include "cpu.h"
#include <cstdio>

void CPU_::OPCODE_HANDLER()
{
  bool jumped;

  if(Space.Space[PC] != 0xCB)
  {
    printf("0x%.2x\n", Space.Space[PC]);

    switch(Space.Space[PC])
    {
      case 0x00:
        //NOP
        PC += 1;
        cycles += 4;
        break;

      case 0x01:
        LD(BC.reg, GET_WORD());
        PC += 3;
        cycles += 12;
        break;

      case 0x02:
        LD(Space.Space[BC.reg], AF.hi);
        PC += 1;
        cycles += 8;
        break;

      case 0x03:
        BC.reg += 1;
        PC += 1;
        cycles += 8;
        break;

      case 0x04:
        INC(BC.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x05:
        DEC(BC.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x06:
        LD(BC.hi, GET_BYTE());
        PC += 2;
        cycles += 8;
        break;

      case 0x08:
        LD_W(GET_WORD(), SP);
        PC += 3;
        cycles += 20;
        break;

      case 0x09:
        ADD(HL.reg, BC.reg);
        PC += 1;
        cycles += 8;
        break;

      case 0x0A:
        LD(AF.hi, Space.Space[BC.reg]);
        PC += 1;
        cycles += 8;
        break;

      case 0x0B:
        BC.reg -= 1;
        PC += 1;
        cycles += 8;
        break;

      case 0x0C:
        INC(BC.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x0D:
        DEC(BC.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x0E:
        LD(BC.lo, GET_BYTE());
        PC += 2;
        cycles += 8;
        break;

      case 0x10:
        STOP();
        PC += 2;
        cycles += 4;
        break;

      case 0x11:
        LD(DE.reg, GET_WORD());
        PC += 3;
        cycles += 12;
        break;

      case 0x12:
        LD(Space.Space[BC.reg], AF.hi);
        PC += 1;
        cycles += 8;
        break;

      case 0x13:
        DE.reg++; //no flags change no just inc it manually
        PC += 1;
        cycles += 8;
        break;

      case 0x14:
        INC(DE.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x15:
        DEC(DE.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x16:
        LD(DE.hi, GET_BYTE());
        PC += 2;
        cycles += 8;
        break;

      case 0x17:
        RLA(AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x18:
        JR(GET_BYTE());
        PC += 1;
        cycles += 4;
        break;

      case 0x19:
        ADD(HL.reg, BC.reg);
        PC += 1;
        cycles += 8;
        break;

      case 0x1A:
        LD(AF.hi, Space.Space[DE.reg]);
        PC += 1;
        cycles += 8;
        break;

      case 0x1B:
        DE.reg -= 1;
        PC += 1;
        cycles += 8;
        break;

      case 0x1C:
        INC(DE.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x1D:
        DEC(DE.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x1E:
        LD(DE.lo, GET_BYTE());
        PC += 2;
        cycles += 8;
        break;

      case 0x20:
        jumped = JR_NZ(GET_BYTE());
        if(jumped)
        {
          cycles += 12;
        }
        else
        {
          PC += 2;
          cycles += 8;
        }
        break;

      case 0x21:
        LD(HL.reg, GET_WORD());
        PC += 3;
        cycles += 12;
        break;

      case 0x22:
        LD(Space.Space[HL.reg], AF.hi);
        HL.reg++;
        PC += 1;
        cycles += 8;
        break;

      case 0x23:
        INC(HL.reg);
        PC += 1;
        cycles += 8;
        break;

      case 0x28:
        jumped = JR_Z(GET_BYTE());
        if(jumped)
        {
          cycles += 12;
        }
        else
        {
          PC += 2;
          cycles += 8;
        }
          break;

      case 0x2A:
        LD(AF.hi, Space.Space[HL.reg]);
        HL.reg += 1;
        PC += 1;
        cycles += 8;
        break;

      case 0x2E:
        LD(HL.lo, GET_BYTE());
        PC += 2;
        cycles += 8;
        break;

      case 0x31:
        LD(SP, GET_WORD());
        PC += 3;
        cycles += 12;
        break;

      case 0x32:
        LD(Space.Space[HL.reg], AF.hi);
        HL.reg--;
        PC += 1;
        cycles += 8;
        break;

      case 0x33:
        SP += 1;
        PC += 1;
        cycles += 8;
        break;

      case 0x34:
        INC(Space.Space[HL.reg]);
        PC += 1;
        cycles += 12;
        break;

      case 0x35:
        DEC(Space.Space[HL.reg]);
        PC += 1;
        cycles += 12;
        break;

      case 0x36:
        LD(Space.Space[HL.reg], GET_BYTE());
        PC += 2;
        cycles += 12;
        break;

      case 0x39:
        ADD(HL.reg, SP);
        PC += 1;
        cycles += 8;
        break;

      case 0x3A:
        LD(AF.hi, Space.Space[HL.reg]);
        HL.reg -= 1;
        PC += 1;
        cycles += 8;
        break;

      case 0x3B:
        SP--;
        PC += 1;
        cycles += 8;
        break;

      case 0x3C:
        INC(AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x3D:
        DEC(AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x3E:
        LD(AF.hi, GET_BYTE());
        PC += 2;
        cycles += 8;
        break;

      case 0x40:
        LD(BC.hi, BC.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x41:
        LD(BC.hi, BC.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x42:
        LD(BC.hi, DE.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x43:
        LD(BC.hi, DE.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x44:
        LD(BC.hi, HL.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x45:
        LD(BC.hi, HL.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x46:
        LD(BC.hi, Space.Space[HL.reg]);
        PC += 1;
        cycles += 8;
        break;

      case 0x47:
        LD(BC.hi, AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x48:
        LD(BC.lo, BC.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x49:
        LD(BC.lo, BC.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x4A:
        LD(BC.lo, DE.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0xBC:
        LD(BC.lo, DE.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x4C:
        LD(BC.lo, HL.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x4D:
        LD(BC.lo, HL.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x4E:
        LD(BC.lo, Space.Space[HL.reg]);
        PC += 1;
        cycles += 8;
        break;

      case 0x4F:
        LD(BC.lo, AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x50:
        LD(DE.hi, BC.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x51:
        LD(DE.hi, BC.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x52:
        LD(DE.hi, DE.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x53:
        LD(DE.hi, DE.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x54:
        LD(DE.hi, HL.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x55:
        LD(DE.hi, HL.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x56:
        LD(DE.hi, Space.Space[HL.reg]);
        PC += 1;
        cycles += 8;
        break;

      case 0x57:
        LD(DE.hi, AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x58:
        LD(DE.lo, BC.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x59:
        LD(DE.lo, BC.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x5A:
        LD(DE.lo, DE.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x5B:
        LD(DE.lo, DE.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x5C:
        LD(DE.lo, HL.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x5D:
        LD(DE.lo, HL.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x5E:
        LD(DE.lo, Space.Space[HL.reg]);
        PC += 1;
        cycles += 8;
        break;

      case 0x5F:
        LD(DE.lo, AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x60:
        LD(HL.hi, BC.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x61:
        LD(HL.hi, BC.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x62:
        LD(HL.hi, DE.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x63:
        LD(HL.hi, DE.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x64:
        LD(HL.hi, HL.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x65:
        LD(HL.hi, HL.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x66:
        LD(HL.hi, Space.Space[HL.reg]);
        PC += 1;
        cycles += 8;
        break;

      case 0x67:
        LD(HL.hi, AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x68:
        LD(HL.lo, BC.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x69:
        LD(HL.lo, BC.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x6A:
        LD(HL.lo, DE.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x6B:
        LD(HL.lo, DE.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x6C:
        LD(HL.lo, HL.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x6D:
        LD(HL.lo, HL.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x6E:
        LD(HL.lo, Space.Space[HL.reg]);
        PC += 1;
        cycles += 8;
        break;

      case 0x6F:
        LD(HL.lo, AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x70:
        LD(Space.Space[HL.reg], BC.hi);
        PC += 1;
        cycles += 8;
        break;

      case 0x71:
        LD(Space.Space[HL.reg], BC.lo);
        PC += 1;
        cycles += 8;
        break;

      case 0x72:
        LD(Space.Space[HL.reg], DE.hi);
        PC += 1;
        cycles += 8;
        break;

      case 0x73:
        LD(Space.Space[HL.reg], DE.lo);
        PC += 1;
        cycles += 8;
        break;

      case 0x74:
        LD(Space.Space[HL.reg], HL.hi);
        PC += 1;
        cycles += 8;
        break;

      case 0x75:
        LD(Space.Space[HL.reg], HL.lo);
        PC += 1;
        cycles += 8;
        break;

      case 0x76:
        HALT();
        PC += 1;
        cycles += 4;
        break;

      case 0x77:
        LD(Space.Space[HL.reg], AF.hi);
        PC += 1;
        cycles += 8;
        break;

      case 0x78:
        LD(AF.hi, BC.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x79:
        LD(AF.hi, BC.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x7A:
        LD(AF.hi, DE.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x7B:
        LD(AF.hi, DE.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x7C:
        LD(AF.hi, HL.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x7D:
        LD(AF.hi, HL.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x7E:
        LD(AF.hi, Space.Space[HL.reg]);
        PC += 1;
        cycles += 8;
        break;

      case 0x7F:
        LD(AF.hi, AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x80:
        ADD(AF.hi, BC.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x81:
        ADD(AF.hi, BC.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x82:
        ADD(AF.hi, DE.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x83:
        ADD(AF.hi, DE.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x84:
        ADD(AF.hi, HL.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0x85:
        ADD(AF.hi, HL.lo);
        PC += 1;
        cycles += 4;
        break;

      case 0x86:
        ADD(AF.hi, Space.Space[HL.reg]);
        PC += 1;
        cycles += 8;
        break;

      case 0x87:
        ADD(AF.hi, AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0xAF:
        XOR(AF.hi, AF.hi);
        PC += 1;
        cycles += 4;
        break;

      case 0xC1:
        POP(BC.reg);
        PC += 1;
        cycles += 12;
        break;

      case 0xC3:
        JP(GET_WORD());
        cycles += 16;
        break;

      case 0xC5:
        PUSH(BC.reg);
        PC += 1;
        cycles += 16;
        break;

      case 0xC9:
        RET();
        cycles += 16;
        break;

      case 0xCD:
        CALL(GET_WORD());
        cycles += 8;
        break;

      case 0xD5:
        PUSH(DE.reg);
        PC += 1;
        cycles += 16;
        break;

      case 0xE0:
        LD(Space.Space[0xFF00 + GET_BYTE()], AF.hi);
        PC += 2;
        cycles += 8;
        break;

      case 0xE1:
        POP(HL.reg);
        PC += 1;
        cycles += 12;
        break;

      case 0xE2:
        LD(Space.Space[BC.lo + 0xFF00], AF.hi);
        PC += 1;
        cycles += 8;
        break;

      case 0xE9:
        JP(HL.reg);
        cycles += 16;
        break;

      case 0xEA:
        LD(Space.Space[GET_WORD()], AF.hi);
        PC += 3;
        cycles += 16;
        break;

      case 0xF0:
        LD(AF.hi, Space.Space[0xFF00 + GET_BYTE()]);
        PC += 2;
        cycles += 12;
        break;

      case 0xF3:
        IME = 0;
        PC += 1;
        cycles += 4;
        break;

      case 0xFB:
        IME = 1;
        PC += 1;
        cycles += 4;
        break;

      case 0xFE:
        CP(GET_BYTE());
        PC += 2;
        cycles += 8;
        break;

    }

  }
  else //extension
  {
    printf("0x%x%.2x\n", Space.Space[PC], Space.Space[PC + 1]);

    PC += 1;

    //extension handler
    switch(Space.Space[PC])
    {
      case 0x11:
        RL(BC.lo);
        PC += 1;
        cycles += 8;
        break;

      case 0x7C:
        BIT((BYTE) 7, HL.hi);
        PC += 1;
        cycles += 8;
        break;

    }
  }
};

void CPU_::RET()
{
  POP(PC);
}

template<typename T>
void CPU_::LD(T &DEST, T SRC)
{
  DEST = SRC;
}

template<typename T>
void CPU_::LD_W(T DEST, T SRC)
{

  if(sizeof(SRC) == sizeof(WORD))
  {
    Space.Space[DEST] = (BYTE) (SRC & 0xFF00) >> 8;
    Space.Space[DEST + 1] = (BYTE) (SRC & 0xFF);
  }
}
template<typename T>
void CPU_::RLA(T &REG)
{
  //printf("0x%.2x\n", REG);
  //printf("%d\n", GET_FLAG(CARRY_FLAG));
  bool carry;

  //printf("\n0x%x\n", REG);
  //printf("0x%x\n\n", REG & ((T)1 << 7));

  if(REG & (1 << 7))
  {
    carry = true;
  }
  else
  {
    carry = false;
  }

  REG <<= 1;

  if(GET_FLAG(CARRY_FLAG))
    REG += 1;

  if(carry)
  {
    SET_FLAG(CARRY_FLAG);
  }
  else
  {
    RESET_FLAG(CARRY_FLAG);
  }

  RESET_FLAG(ZERO_FLAG);
  RESET_FLAG(SUBTRACT_FLAG);
  RESET_FLAG(HALFCARRY_FLAG);
}

template<typename T>
void CPU_::ADD(T &REG, T VALUE)
{

   if(sizeof(REG) == sizeof(BYTE))
   {
     if((((VALUE & 0xF) + (REG & 0xF)) & 0x10)
        == 0x10) //halfcarry test https://robdor.com/2016/08/10/gameboy-emulator-half-carry-flag/
       SET_FLAG(HALFCARRY_FLAG);
     else
       RESET_FLAG(HALFCARRY_FLAG);
     if((((VALUE & 0xFF) + (REG & 0xFF)) & 0x100)
        == 0x100) //halfcarry test https://robdor.com/2016/08/10/gameboy-emulator-half-carry-flag/
       SET_FLAG(CARRY_FLAG);
     else
       RESET_FLAG(CARRY_FLAG);
   }

  if(sizeof(REG) == sizeof(WORD))
  {
    if((((VALUE & 0xFFF) + (REG & 0xFFF)) & 0x1000)
       == 0x1000) //halfcarry test https://robdor.com/2016/08/10/gameboy-emulator-half-carry-flag/
      SET_FLAG(HALFCARRY_FLAG);
    else
      RESET_FLAG(HALFCARRY_FLAG);
    if((((VALUE & 0xFFFF) + (REG & 0xFFFF)) & 0x10000)
       == 0x10000) //halfcarry test https://robdor.com/2016/08/10/gameboy-emulator-half-carry-flag/
      SET_FLAG(CARRY_FLAG);
    else
      RESET_FLAG(CARRY_FLAG);
  }

  REG += VALUE;

  if(REG == 0)
    SET_FLAG(ZERO_FLAG);
  else
    RESET_FLAG(ZERO_FLAG);

  RESET_FLAG(SUBTRACT_FLAG);

}

template<typename T>
void CPU_::XOR(T &DEST, T SRC)
{
  DEST ^= SRC;

  if(DEST == 0)
  {
    SET_FLAG(ZERO_FLAG);
  }
  RESET_FLAG(SUBTRACT_FLAG);
  RESET_FLAG(CARRY_FLAG);
  RESET_FLAG(HALFCARRY_FLAG);
}

template<typename T>
void CPU_::BIT(T TEST_BIT, T REG)
{
  BYTE result = REG & (T) (1 << TEST_BIT);

  if(result == 0)
  {
    SET_FLAG(ZERO_FLAG);
  }
  else
  {
    RESET_FLAG(ZERO_FLAG);
  }
  SET_FLAG(HALFCARRY_FLAG);
  RESET_FLAG(SUBTRACT_FLAG);

}

template<typename T>
bool CPU_::JR_NZ(T OFFSET)
{
  bool jumped = false;
  if(!GET_FLAG(ZERO_FLAG)) //if not set
  {
    PC += (int8_t) OFFSET + 2; //PC moves 2 from the original instruction
    jumped = true;
  }

  return jumped;
}

template<typename T>
void CPU_::INC(T &REG)
{
  REG++;

  if(sizeof(REG) == sizeof(BYTE))
  {
    if(REG == 0)
      SET_FLAG(ZERO_FLAG);
    else
      RESET_FLAG(ZERO_FLAG);

    RESET_FLAG(SUBTRACT_FLAG);

    if(((((REG - 1) & 0xf) + (REG & 0xf)) & 0x10)
       == 0x10) //halfcarry test https://robdor.com/2016/08/10/gameboy-emulator-half-carry-flag/
      SET_FLAG(HALFCARRY_FLAG);
    else
      RESET_FLAG(HALFCARRY_FLAG);

  }
}

template<typename T>
void CPU_::CALL(T ADDR)
{
  PUSH(PC + 3);
  PC = ADDR;
}

template<typename T>
void CPU_::CP(T VALUE) //compare
{
  if(AF.hi < VALUE)
  {
    SET_FLAG(CARRY_FLAG);
    RESET_FLAG(ZERO_FLAG);
  }
  else if(AF.hi == VALUE)
  {
    SET_FLAG(ZERO_FLAG);
    RESET_FLAG(CARRY_FLAG);
  }

  SET_FLAG(SUBTRACT_FLAG);

  if(0 > (((AF.hi) & 0xf) - (VALUE & 0xf))) //halfcarry test https://www.reddit.com/r/EmuDev/comments/4clh23/trouble_with_halfcarrycarry_flag/
    SET_FLAG(HALFCARRY_FLAG);
  else
    RESET_FLAG(HALFCARRY_FLAG);

}

template<typename T>
void CPU_::DEC(T &REG)
{
  REG -= 1;

  if(sizeof(REG) == sizeof(BYTE))
  {
    if(REG == 0)
      SET_FLAG(ZERO_FLAG);
    else
      RESET_FLAG(ZERO_FLAG);

    SET_FLAG(SUBTRACT_FLAG);

    if(0 > (((REG + 1) & 0xf) - (REG & 0xf))) //halfcarry test https://www.reddit.com/r/EmuDev/comments/4clh23/trouble_with_halfcarrycarry_flag/
      SET_FLAG(HALFCARRY_FLAG);
    else
      RESET_FLAG(HALFCARRY_FLAG);

  }

}

template<typename T>
bool CPU_::JR_Z(T OFFSET)
{
  bool jumped = false;
  if(GET_FLAG(ZERO_FLAG)) //if not set
  {
    PC += (int8_t) OFFSET + 2; //PC moves 2 from the original instruction
    jumped = true;
  }

  return jumped;
}

void CPU_::HALT()
{

}

template<typename T>
void CPU_::SUB(T VALUE)
{
  if(AF.hi < VALUE)
  {
    SET_FLAG(CARRY_FLAG);
    RESET_FLAG(ZERO_FLAG);
  }
  else if(AF.hi == VALUE)
  {
    SET_FLAG(ZERO_FLAG);
    RESET_FLAG(CARRY_FLAG);
  }

  AF.hi -= VALUE;

  SET_FLAG(SUBTRACT_FLAG);

  if(0 > (((AF.hi) & 0xf) - (VALUE & 0xf))) //halfcarry test https://www.reddit.com/r/EmuDev/comments/4clh23/trouble_with_halfcarrycarry_flag/
    SET_FLAG(HALFCARRY_FLAG);
  else
    RESET_FLAG(HALFCARRY_FLAG);

}

template<typename T>
void CPU_::JR(T OFFSET)
{
  PC += (int8_t) OFFSET + 2; //PC moves 2 from original instruction
}

template<typename T>
void CPU_::RL(T &REG)
{
  //printf("0x%.2x\n", REG);
  //printf("%d\n", GET_FLAG(CARRY_FLAG));
  bool carry;

  //printf("\n0x%x\n", REG);
  //printf("0x%x\n\n", REG & ((T)1 << 7));

  if(REG & (1 << 7))
  {
    carry = true;
  }
  else
  {
    carry = false;
  }

  REG <<= 1;

  if(GET_FLAG(CARRY_FLAG))
    REG += 1;

  if(carry)
  {
    SET_FLAG(CARRY_FLAG);
  }
  else
  {
    RESET_FLAG(CARRY_FLAG);
  }

  if(REG == 0)
    SET_FLAG(ZERO_FLAG);


  RESET_FLAG(SUBTRACT_FLAG);
  RESET_FLAG(HALFCARRY_FLAG);
}

template<typename T>
void CPU_::POP(T &REG)
{
  RegisterPair temp;
  temp.lo = Space.Space[SP++];
  temp.hi = Space.Space[SP++];

  REG = temp.reg;
}

template<typename T>
void CPU_::PUSH(T REG)
{
  //little endian
  RegisterPair temp;
  temp.lo = REG & 0xFF;
  temp.hi = REG >> 8;
  SP--;
  Space.Space[SP] = temp.hi;
  SP--;
  Space.Space[SP] = temp.lo;
}

template<typename T>
void CPU_::JP(T ADDR)
{
  PC = ADDR;
}

void CPU_::STOP()
{

}