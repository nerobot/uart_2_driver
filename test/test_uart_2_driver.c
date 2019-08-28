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

void setUp(void)
{
    uart_2_driver_create();
    // TODO: Check that the below is ok to remove

    // uart_2_driver_set_tx_reg_address(&virtual_tx_reg);
    // uart_2_driver_set_uxsta_address(&virtual_uxsta);
    // uart_2_driver_set_rx_reg_address(&virtual_rx_reg);
}

void tearDown(void)
{
}

void test_implement(void)
{
    // TEST_IGNORE_MESSAGE("To be implemented");
}

void test_put_c_moves_c_to_tx(void)
{
    uint8_t c = 'X';

    uart_2_driver_put_c(c);
    TEST_ASSERT_EQUAL_UINT8(c, U2TXREG);
}

void test_tx_is_full_returns_true_when_UTXBF_is_true(void)
{
    //   virtual_uxsta = set_bit(virtual_uxsta, UTXBF);
    U2STAbits.UTXBF = 1;
    bool is_full    = uart_2_driver_tx_buff_is_full();
    TEST_ASSERT(is_full);

    // virtual_uxsta = clear_bit(virtual_uxsta, UTXBF);
    U2STAbits.UTXBF = 0;
    is_full         = uart_2_driver_tx_buff_is_full();
    TEST_ASSERT_FALSE(is_full);
}

void test_get_rx_reg_returns_value_of_rxreg(void)
{
    U2RXREG   = 'F';
    uint8_t c = uart_2_get_rx_reg();
    TEST_ASSERT_EQUAL_UINT8(U2RXREG, c);
}

void test_rx_is_empty_will_return_true_when_is_empty(void)
{
    //   virtual_uxsta = clear_bit(virtual_uxsta, URXDA);
    U2STAbits.URXDA = 0;
    bool is_empty   = uart_2_driver_rx_buff_is_empty();
    // bool is_empty = U2STAbits.URXDA;
    TEST_ASSERT(is_empty);
}
