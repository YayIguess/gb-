#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <string>

#include "cpu.h"
#include "ppu.h"
#include <SDL2/SDL.h>

using namespace std;
namespace fs = std::filesystem;

string path;
CPU_ Z80;

int main(int argc, char *argv[]) {
  Z80.INIT_PC();
  SETUP();

  path = "../games/tetris.gb";
//path = "../bootroms/dmg_boot.bin";

  ifstream BootRom;
  BootRom.open(path, ios::binary);
  int size = fs::file_size(path);
  //if(size == 256)
  //{
    Z80.LOAD_BOOTROM(BootRom, size);
  //}
  //else
  //{
 //   cout << "Bootrom was an unexpected size!\nQuitting!" << endl;
 //   exit(1);
  //}
  //BootRom.close();

  Z80.RUN();

  return 0;
}

/*
 * 16 bit address bus
 * 8 bit data bus
 * potential 64k of memory
 * registers included
 *      8 bit accumulator                       (A)
 *      8 bit status register                   (F)
 *      six 8 bit general purpose registers     (B, C, D, E, H, L)
 *      16 bit stack pointer                    (AP)
 *      16 bit program counter                  (PC)
 * general purpose registers could be used in pairs for some 16 bit instructions
 * H+L = HL and could be used as a pointer
 * HL could also be used for arithmetic
 * could add a pair (BC, DE, HL, SP) to HL
 * could also load them with 16-bit values and increment or decrement them by 1
 * F register stores the results from the last executed instruction
 * each bits of the F register were used as flags (zero, carry, sign, half-carry, parity)
 *      bits 0-3 not used
 *      bit 4 carry flag - set when a carry from bit 7 is produced in arithmetical instructions.  Otherwise it is cleared.
 *      bit 5 half-carry flag - set when a carry from bit 3 is produced in arithmetical instructions.  Otherwise it is cleared.
 *      bit 6 subtract flag - when the instruction is a subtraction this bit is set.  Otherwise (the instruction is an addition) it is cleared.
 *      bit 7 zero flag - set when the instruction results in a value of 0.  Otherwise (result different to 0) it is cleared.
 * writing to memory address 0xFF00 -> 0xFF7F reserved for device mapping
 * OPCODE 0xCB was a opcode extender
 * 4194304Hz CPU
 *
 * 8k byte work ram
 * 8k video ram
 * 160x144 (20x18 tiles)
 * max 40 sprites per screen, 10 per line
 * 8x8 or 8x16 sprites
 * 4 shades or gray
 * 9198KHz horizontal sync
 * 59.73 Hz vertical sync
 * 4 channels with stereo sound
 *
 * 16 bit address bus and one address space so max 64kb of memory
 * everything was accessed through memory, everything
 * memory banks 16kb in size
 * first bank was always mapped to 0x0000-0x3FFF (first 16kb of address space)
 * rest of the banks could be swapped between the last 48kb of address space (0x4000-0xFFFF)
 * because of this the size of the game didn't matter as parts could be swapped in and out
 * bank switching was done in software not hardware
 *
 * (ROM banks are 16kb in size)
 * 0x0000-0x3FFF - permanently mapped ROM bank 1
 * 0x4000-0x7FFF - area for switchable ROM banks (ROM banks 2 - 255)
 * 0x8000-0x9FFF - VRAM
 * 0xA000-0xBFFF - area for switchable external RAM banks
 * 0xC000-0xCFFF - working RAM bank 1
 * 0xD000-0xDFFF - working RAM bank 2
 * 0xFE00-0xFEFF - sprite attribute table
 * 0xFF00-0xFF7F - IO devices
 * 0xFF80-0xFFFE - high ram area
 * 0xFFFF          interrupt enable register
 *
 * 0x0000-0x7FFF would be mapped to the ROM
 * 0xA000-0xBFFF used for cartridge RAM banks (each 8KB big), cartridges had up to 32kb of RAM and this ram was non-volatile
 * 0x8000-0x9FFF used to hold the pixels to display
 * 0xC000-0xCFFF and 0xD000-0xDFFF internal gameboy RAM, two permanently mapped 4KB banks
 * 0xFE00-0xFEFF used by the LCD to draw sprites
 * 0xFF00-0xFF7F used to access display, 4 sound channels, link cable, internal timers, joypad, and interrupt system
 * 0xFF80-0xFFFE used as a special working RAM by games
 * 0xFFFF interrupt enable register, used to enable/disable interrupts
 *
 * hardware interrupts trigger interrupt handler
 * interrupt handlers are part of the cartridge ROM
 * when one interrupt occurs the CPU disabled further interrupts
 * then the address to the next instruction is pushed onto the stack
 * then a call is made to the interrupt handler
 * once finished, a special return instruction pops the return address from the stack onto the PC
 * interrupts would be enabled again and execution would continue
 * interrupts can be re-enabled while handling an interrupt which allows nested interrupts
 * this system was driven by two special memory-mapped registers
 *
 * (interrupts can be disabled)
 * 0xFFFF – IE – Interrupt Enable (R/W)
 *  Bit 0: V-Blank  Interrupt Enable  (INT 40h)  (1=Enable)
 *  Bit 1: LCD STAT Interrupt Enable  (INT 48h)  (1=Enable)
 *  Bit 2: Timer    Interrupt Enable  (INT 50h)  (1=Enable)
 *  Bit 3: Serial   Interrupt Enable  (INT 58h)  (1=Enable)
 *  Bit 4: Joypad   Interrupt Enable  (INT 60h)  (1=Enable)
 *
 * (interrupts can be requested)
 * 0xFF0F – IF – Interrupt Flag (R/W)
 *  Bit 0: V-Blank  Interrupt Request (INT 40h)  (1=Request)
 *  Bit 1: LCD STAT Interrupt Request (INT 48h)  (1=Request)
 *  Bit 2: Timer    Interrupt Request (INT 50h)  (1=Request)
 *  Bit 3: Serial   Interrupt Request (INT 58h)  (1=Request)
 *  Bit 4: Joypad   Interrupt Request (INT 60h)  (1=Request)
 *
 * interrupts have priorities, with lower bits being serviced first
 *
 *
 */