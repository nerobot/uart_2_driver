# UART_2_DRIVER

Module to init and driver the uart 2 module. The module contains the code for direct control of the uart hardware, including setting up the module and reading / setting registers.

Details such as sending / reading strings are controlled in the uart_controller module instead.

## Installation

Copy git folder into required mplab source folder.

## Documentation

To build documentation, call doxygen from project folder.

## Usage

### Testing

To test module, ceedling and gcc need to install.

```
ceedling test:all
```

All tests should pass before adding to project.

