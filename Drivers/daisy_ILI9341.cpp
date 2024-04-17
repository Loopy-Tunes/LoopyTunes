#include "LcdBuffers.h"
#include "daisy_ILI9341.h"

static uint8_t DMA_BUFFER_MEM_SECTION frame_buffer[153600]; // DMA max (?) 65536 // full screen - 153600
static uint8_t DSY_SDRAM_BSS color_mem[153600 / 2];

void ILI9341SpiTransport::TxCompleteCallback(void* context, SpiHandle::Result result)
{
        if(result == SpiHandle::Result::OK)
        {
            auto transport     = static_cast<ILI9341SpiTransport*>(context);
            auto transfer_size = transport->GetTransferSize();
            transport->remaining_buff -= transfer_size;
            if(transport->remaining_buff > 0)
            {
                uint8_t* next_buffer_ptr = frame_buffer + (transport->buffer_size - transport->remaining_buff);  // potential issue
                transport->SendDataDMA(
                   &frame_buffer[buffer_size - transport->remaining_buff],
                    transfer_size);
                    

                // 16bit transfer             uncommented
                // transport->SendDataDMA(
                  //   &frame_buffer[2 * transport->buf_chunk_size],
                    // transport->buf_chunk_size);
            }
            else
            {
                //System::Delay(120);
                transport->dma_busy = false;
                

                // 8 bit transfer
                // auto* spi_h = transport->spi_.GetHandle();
                // spi_h->Instance->CFG1 &= ~SPI_CFG1_DSIZE_3;
                // spi_h->Instance->CFG2 &= ~SPI_CFG2_LSBFRST;
                // spi_h->Init.DataSize = SPI_DATASIZE_8BIT;
            }
        }
}

SpiHandle::Result ILI9341SpiTransport::SendDataDMA()
{
    remaining_buff = buffer_size;
    //System::Delay(120);
    dma_busy       = true;
        

    // auto* spi_h = spi_.GetHandle();
    // spi_h->Instance->CFG1 |= SPI_CFG1_DSIZE_3;
    // spi_h->Instance->CFG2 |= SPI_CFG2_LSBFRST;
    // spi_h->Init.DataSize = SPI_DATASIZE_16BIT; // 15;

    return SendDataDMA(frame_buffer, buf_chunk_size);
}

void ILI9341SpiTransport::PaintPixel(uint32_t id, uint8_t color_id, uint8_t alpha) const
{
    auto color = tftPalette[color_id];

    if(alpha != 255)
    {
        auto bg_color = tftPalette[color_mem[id]];
        color         = Blend565(color, bg_color, alpha);
    }

    color_mem[id] = color_id; 

    frame_buffer[id]     = color >> 8;
    frame_buffer[id + 1] = color & 0xFF;
}

uint16_t ILI9341SpiTransport::GetPixel(uint32_t id)
{
    return color_mem[id];
}