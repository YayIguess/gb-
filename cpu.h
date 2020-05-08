#ifndef CPU
#define CPU

#include <stdint.h>
#include <fstream>

#define CARRY_FLAG 4 //'C'
#define HALFCARRY_FLAG 5 //'H'
#define SUBTRACT_FLAG 6 //'N'
#define ZERO_FLAG 7 //'Z'

#define VBLANK_INTERRUPT 0
#define LCD_STAT_INTERRUPT 1
#define TIMER_INTERRUPT 2
#define SERIAL_INTERRUPT 3
#define JOYPAD_INTERRUPT 4

using namespace std;

#define WORD uint16_t
#define BYTE uint8_t

#define CPU_FREQ 4194304
#define DIV_FREQ 16384

#define HBlank_FREQ 204 //GPU_MODE 0
#define SCANLINE_OAM_FREQ 80 //GPU_MODE 2
#define SCANLINE_VRAM_FREQ 80 //GPU_MODE 3
#define ONELINE_FREQ 456
#define VBlank_FREQ 4560 //GPU_MODE 1
#define FULL_FRAME_FREQ 70224

union AddressSpace {
    BYTE Space[0x10000];

    struct {
        BYTE ROM_BANK1[0x4000];//mapped to 0x0000
        BYTE ROM_BANK_SWITCH[0x4000]; //mapped to 0x4000
        BYTE VRAM[0x2000]; //mapped to 0x8000
        BYTE RAM_BANK_SWITCH[0x2000]; //mapped to 0xA000
        BYTE MB1[0x1000]; //mapped to 0xC000
        BYTE MB2[0x1000]; //mapped to 0xD000
        BYTE EMPTY[0x1E00]; //mapped to 0xE000 NOT USED
        BYTE SPRITE_ATTRIBUTE_TABLE[0x100]; //mapped to 0xFE00
        BYTE IO[0x80]; //mapped to 0xFF00, 0xFF0F is interrupt flag
        BYTE SPECIAL_RAM[0x7F]; //mapped to 0xFF80
        BYTE INTERUPT_ENABLE_REG; //mapped to 0xFFFF
    };
};

union RegisterPair {
    WORD reg; //register.reg == (hi << 8) + lo. (high is more significant than lo)

    struct {
        BYTE lo;
        BYTE hi;
    };
};

class CPU_ {
 private:

  int cycles;

  WORD address_bus;
  BYTE data_bus;

  RegisterPair AF;

  //general purpose registers
  RegisterPair BC;
  RegisterPair DE;
  RegisterPair HL;

  WORD SP; //stack pointer
  WORD PC; //program counter

  AddressSpace Space;

  BYTE* IF = &Space.Space[0xFF0F];
  BYTE* LCD_CONTROL = &Space.Space[0xFF40];
  BYTE* TIMER_COUNTER = &Space.Space[0xFF05];
  BYTE* TIMER_MODULO = &Space.Space[0xFF06];
  BYTE* TIMER_CONTROL = &Space.Space[0xFF07];

  BYTE* DIV_REGISTER = &Space.Space[0xFF04];
  int previous_cycle_count = 0;
  int div_count = 0;

  bool IME = true;

  //PPU stuff
  BYTE* LCDC = &Space.Space[0xFF40];
  BYTE* STAT = &Space.Space[0xFF41];
  BYTE* SCY = &Space.Space[0xFF42];
  BYTE* LY = &Space.Space[0xFF44];
  BYTE* LYC = &Space.Space[0xFF45];
  BYTE* WY = &Space.Space[0xFF4A];
  BYTE* WX = &Space.Space[0xFF4B];
  BYTE* BGP = &Space.Space[0xFF47];
  BYTE* OBP0 = &Space.Space[0xFF48];
  BYTE* OBP1 = &Space.Space[0xFF49];
  BYTE* DMA = &Space.Space[0xFF46];

 public:

  void INIT_PC();

  void OPCODE_HANDLER();

  static void LOAD_BOOTROM(ifstream &FILE, int FILE_SIZE);

  void RUN();

  void INTERRUPT_HANDLER();

  void SET_FLAG(BYTE bit);
  void RESET_FLAG(BYTE bit);
  bool GET_FLAG(BYTE bit);

  WORD GET_WORD();

  BYTE GET_BYTE();

  //OPCODE FUNCTIONS
  template<typename T>
  void LD(T &DEST, T SRC);
  template<typename T>
  void XOR(T &DEST, T SRC);
  template<typename T>
  void BIT(T, T);
  template<typename T>
  void JP(T);
  template<typename T>
  bool JR_NZ(T);
  template<typename T>
  void INC(T &REG);
  template<typename T>
  void CALL(T);
  void HALT();
  void STOP();
  template<typename T>
  void LD_W(T, T);
  template<typename T>
  void CP(T);
  template<typename T>
  void DEC(T &REG);
  template<typename T>
  bool JR_Z(T);
  template<typename T>
  void SUB(T);
  template<typename T>
  void JR(T);
  template<typename T>
  void PUSH(T);
  template<typename T>
  void RL(T &REG);
  template<typename T>
  void POP(T &REG);
  template<typename T>
  void RLA(T &REG);
  void RET();
  template<typename T>
  void ADD(T &REG, T VALUE);

  void VBLANK_HANDLE();
  void LCD_STAT_HANDLE();
  void TIMER_HANDLE();
  void SERIAL_HANDLE();
  void JOYPAD_HANDLE();

  bool TEST_INTERRUPT_ENABLED(BYTE INTERRUPT);

  void TIMING();

  void RESET_INTERRUPT(BYTE INTERRUPT);
};


#endif //CPU
