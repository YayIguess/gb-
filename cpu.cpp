#include "cpu.h"
#include <iostream>
#include <bitset>
#include <iomanip>
#include <cstdio>

extern CPU_ Z80;

void CPU_::INIT_PC()
{
  PC = 0x0000;
}

void CPU_::LOAD_BOOTROM(ifstream &FILE, int FILE_SIZE)
{
  FILE.read(reinterpret_cast<char *>(Z80.Space.ROM_BANK1), FILE_SIZE);
}

void CPU_::RUN()
{
  for(int i = 0; i < 24604; i++)
  {
    OPCODE_HANDLER();
    INTERRUPT_HANDLER();
    TIMING();
  }
  for(int i = 0; i < 30000; i++)
  {
    OPCODE_HANDLER();
    INTERRUPT_HANDLER();
    TIMING();
  }
}

void CPU_::SET_FLAG(BYTE bit)
{
  AF.lo |= (1 << bit);
}

void CPU_::RESET_FLAG(BYTE bit)
{
  AF.lo &= ~(1 << bit);
}

bool CPU_::GET_FLAG(BYTE bit)
{
  return (AF.lo >> bit) & 1;
}

WORD CPU_::GET_WORD()
{
  //probably not the best way to do this, but it works for now
  RegisterPair WORD_TO_RETURN;

  //remember little endianness
  WORD_TO_RETURN.lo = Space.Space[PC + 1];
  WORD_TO_RETURN.hi = Space.Space[PC + 2];

  return WORD_TO_RETURN.reg;

}

BYTE CPU_::GET_BYTE()
{
  return Space.Space[PC + 1];
}

void CPU_::INTERRUPT_HANDLER()
{
  if(!IME)
    return;

  if(*IF & (BYTE) (1 << VBLANK_INTERRUPT)
    && TEST_INTERRUPT_ENABLED(VBLANK_INTERRUPT))
      VBLANK_HANDLE();
  if(*IF & (BYTE) (1 << LCD_STAT_INTERRUPT)
    && TEST_INTERRUPT_ENABLED(LCD_STAT_INTERRUPT))
      LCD_STAT_HANDLE();
  if(*IF & (BYTE) (1 << TIMER_INTERRUPT)
    && TEST_INTERRUPT_ENABLED(TIMER_INTERRUPT))
      TIMER_HANDLE();
  if(*IF & (BYTE) (1 << SERIAL_INTERRUPT)
    && TEST_INTERRUPT_ENABLED(SERIAL_INTERRUPT))
      SERIAL_HANDLE();
  if(*IF & (BYTE) (1 << JOYPAD_INTERRUPT)
    && TEST_INTERRUPT_ENABLED(JOYPAD_INTERRUPT))
      JOYPAD_HANDLE();

}

void CPU_::VBLANK_HANDLE()
{

}

void CPU_::LCD_STAT_HANDLE()
{

}
void CPU_::TIMER_HANDLE()
{

}
void CPU_::SERIAL_HANDLE()
{

}
void CPU_::JOYPAD_HANDLE()
{

}

bool CPU_::TEST_INTERRUPT_ENABLED(BYTE INTERRUPT)
{
  return Space.INTERUPT_ENABLE_REG & (BYTE) (1 << INTERRUPT);
}

void CPU_::RESET_INTERRUPT(BYTE INTERRUPT)
{
  *IF &= ~(1 << INTERRUPT);
}

void CPU_::TIMING()
{
  div_count = cycles - previous_cycle_count;

  if(div_count >= (CPU_FREQ / DIV_FREQ))
  {
    *DIV_REGISTER += 1;
    previous_cycle_count = div_count;
  }

  if(cycles >= CPU_FREQ)
  {
    cycles = 0;
    previous_cycle_count = 0;
  }
}
