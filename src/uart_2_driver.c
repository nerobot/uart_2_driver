#include "uart_2_driver.h"
#include "xc.h"

// Remove the commented code below

static inline bool check_bit(uint16_t value, uint8_t bit)
{
    if (value & (1 << bit))
    {
        return true;
    }
    return false;
}

void uart_2_driver_init(void)
{
    U2MODEbits.UARTEN =
        1; // Enable uart ready for use. Needs enabling before UTXEN

    U2STAbits.UTXEN = 1; // Transmit enabled
    U2STAbits.URXEN = 1; // Receive enabled
    U2MODEbits.BRGH = 0;

    U2BRG = 207; // 9600 baud-rate
}

void uart_2_driver_put_c(uint8_t c)
{
    U2TXREG = c;
}

bool uart_2_driver_tx_buff_is_full(void)
{
    bool is_full = U2STAbits.UTXBF;
    return is_full;
}

uint8_t uart_2_get_rx_reg(void)
{
    if (true == uart_2_driver_rx_buff_is_empty())
    {
        return 0x00;
    }
    return U2RXREG;
}

bool uart_2_driver_rx_buff_is_empty(void)
{
    bool is_empty = !U2STAbits.URXDA;
    return is_empty;
}
