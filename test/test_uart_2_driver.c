///////////////////////////////////////////////////////////////////////////////
// Library test list
//
//  Initalising
//      Currently no real tests done on setup. Should decide which things should be tested
//
//  Sending a character
//      * The chacter should be stored in tx buffer at the end of the function - DONE
//      * is_tx_full should return true if tx buffer is full - DONE
//      * is_tx_full should return false if tx buffer has some spacNe in it - DONE
//
//  Receiving a character
//      * driver_get_rx_reg will return the current value in the rx reg - DONE
//      * if rx_reg is empty, driver_get_rx_reg will return 0x00 - DONE
//      * is_rx_empty will return true when ur2da is 0 - DONE
//      * is_rx_empty will return false when ur2da is 1 (i.e. there is something waiting to be read) - DONE
//      
//  Sending a string
//      * calling send_string will cause all bytes to be sent to tx2buf
//      * for each byte sent, tx full will be checked.
//          * if buffer is full, do nothing
//          * if buffer is not full, send byte to buf
//          


#include "unity.h"
#include "xc.h"
#include "uart_2_driver.h"
#include <stdbool.h>

// TODO: Go through and remove the commented code.

volatile uint16_t U2MODE;
volatile U2MODEBITS U2MODEbits;
volatile uint16_t U2STA;
volatile U2STABITS U2STAbits;
volatile uint16_t U2BRG;
volatile uint16_t U2RXREG;
volatile uint16_t U2TXREG;

static inline uint16_t set_bit(uint16_t value, uint8_t bit)
{
    value |= (1 << bit);
    return value;
}

static inline uint16_t clear_bit(uint16_t value, uint8_t bit)
{
    value &= ~(1 << bit);
    return value;
}

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

void setUp(void)
{
    uart_2_driver_init();
}

void tearDown(void)
{
}

///////////////////////////////////////////////////////////////////////////////
// Initializing
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Transmitting
///////////////////////////////////////////////////////////////////////////////

void test_put_c_moves_c_to_tx(void)
{
    uint8_t c = 'X';

    uart_2_driver_put_c(c);
    TEST_ASSERT_EQUAL_UINT8(c, U2TXREG);
}

void test_tx_is_full_returns_true_when_UTXBF_is_true(void)
{
    U2STAbits.UTXBF = 1;
    bool is_full = uart_2_driver_tx_buff_is_full();
    TEST_ASSERT(is_full);
}

void test_tx_is_full_returns_false_then_utxbf_is_0(void)
{
    U2STAbits.UTXBF = 0;
    bool is_full = uart_2_driver_tx_buff_is_full();
    TEST_ASSERT_FALSE(is_full);
}

//void test_send_string

///////////////////////////////////////////////////////////////////////////////
// Receiving
///////////////////////////////////////////////////////////////////////////////

void test_driver_get_rx_reg_returns_value_of_rxreg(void)
{
    U2STAbits.URXDA = 1;
    U2RXREG   = 'F';
    uint8_t c = uart_2_driver_get_rx_reg();
    TEST_ASSERT_EQUAL_UINT8(U2RXREG, c);
}

void test_driver_get_rx_reg_returns_0_when_buffer_is_empty(void)
{
    U2STAbits.URXDA = 0;
    U2RXREG = 'F';
    uint8_t c = uart_2_driver_get_rx_reg();
    TEST_ASSERT_EQUAL_UINT8(0x00, c);
}

void test_rx_is_empty_will_return_true_when_is_empty(void)
{
    U2STAbits.URXDA = 0;
    bool is_empty = uart_2_driver_rx_buff_is_empty();
    TEST_ASSERT(is_empty);
}

void test_rx_is_empty_will_return_false_when_is_not_empty(void)
{
    U2STAbits.URXDA = 1;
    bool is_empty = uart_2_driver_rx_buff_is_empty();
    TEST_ASSERT_FALSE(is_empty);
}
