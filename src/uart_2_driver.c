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
    // *p_tx_reg = c;
    U2TXREG = c;
}

// TODO: Remmove function as no longer needed
void uart_2_driver_set_tx_reg_address(volatile uint16_t * p_address)
{
    //   p_tx_reg = p_address;
}

// TODO: Remove function as no longer needed
void uart_2_driver_set_uxsta_address(volatile uint16_t * p_address)
{
    //   p_uxsta_reg = p_address;
}

// TODO: Remove function as no longer needed
void uart_2_driver_set_rx_reg_address(volatile uint16_t * p_address)
{
    //   p_rx_reg = p_address;
}

bool uart_2_driver_tx_buff_is_full(void)
{
    bool is_full = U2STAbits.UTXBF;
    //   bool is_full = check_bit(*p_uxsta_reg, UTXBF);

    return is_full;
}

uint8_t uart_2_get_rx_reg(void)
{
    // return *p_rx_reg;
    return U2RXREG;
}

bool uart_2_driver_rx_buff_is_empty(void)
{
    //   bool is_empty = !check_bit(*p_uxsta_reg, URXDA);
    bool is_empty = !U2STAbits.URXDA;
    return is_empty;
}
