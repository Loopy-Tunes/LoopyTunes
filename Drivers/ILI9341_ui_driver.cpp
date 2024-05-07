#include "daisy_ILI9341.hpp"

uint8_t DMA_BUFFER_MEM_SECTION
    frame_buffer[ILI9341SpiTransport::buffer_size]
    = {0}; // DMA max (?) 65536 // full screen - 153600

uint8_t DSY_SDRAM_BSS
    color_mem[ILI9341SpiTransport::buffer_size / 2]
    = {0};

UiDriver lcd;