#include "LcdBuffers.h"
#include "daisy_ILI9341.h"

uint8_t DMA_BUFFER_MEM_SECTION frame_buffer[153600] = {0}; // DMA max (?) 65536 // full screen - 153600

uint8_t DSY_SDRAM_BSS color_mem[153600 / 2] = {0};

void ILI9341SpiTransport::TxCompleteCallback(void* context, SpiHandle::Result result)
{
    
}