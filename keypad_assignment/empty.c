#include "ti_msp_dl_config.h"
#include <stdio.h> // Include for printf
#include <stdint.h>

#define ROWS 5
#define COLUMNS 4

// Define GPIO pins for rows and columns
uint32_t rowPins[ROWS] = {GPIO_PORT_B_PIN_0_PIN, GPIO_PORT_B_PIN_1_PIN, GPIO_PORT_B_PIN_2_PIN, GPIO_PORT_B_PIN_3_PIN, GPIO_PORT_B_PIN_4_PIN};
uint32_t colPins[COLUMNS] = {GPIO_PORT_A_PIN_5_PIN, GPIO_PORT_A_PIN_6_PIN, GPIO_PORT_A_PIN_7_PIN, GPIO_PORT_A_PIN_8_PIN};

// Keypad layout (example)
char keys[ROWS][COLUMNS] = {
    {'A', 'B', 'C', 'D'},
    {'1', '2', '3', 'H'},
    {'4', '5', '6', 'G'},
    {'7', '8', '9', 'F'},
    {'*', '0', '#', 'E'}
};


// Initialize GPIOs
void keypad_init(void)
{
    // Configure rows as outputs
    for (int i = 0; i < ROWS; i++)
    {
        // Ensure GPIO_CFG_OUTPUT is defined in your library or use appropriate output configuration


        DL_GPIO_setPins(GPIO_PORT_B_PORT, rowPins[i]); // Set HIGH
    }

    // Configure columns as inputs with pull-ups
    for (int i = 0; i < COLUMNS; i++)
    {
        // Ensure GPIO_CFG_INPUT | GPIO_CFG_PULLUP is defined in your library

    }
}

// Read keypad
char keypad_getKey(void)
{
    for (int row = 0; row < ROWS; row++)
    {
        // Set all rows HIGH
        for (int i = 0; i < ROWS; i++)
        {
            DL_GPIO_setPins(GPIO_PORT_B_PORT, rowPins[i]);
        }

        // Set current row LOW
        DL_GPIO_clearPins(GPIO_PORT_B_PORT, rowPins[row]);

        // Check each column
        for (int col = 0; col < COLUMNS; col++)
        {
            if (!DL_GPIO_readPins(GPIO_PORT_A_PORT, colPins[col]))
            {
                delay_ms(50);// Debounce delay


                // Confirm key press
                if (!DL_GPIO_readPins(GPIO_PORT_A_PORT, colPins[col]))
                {
                    // Reset the current row before returning
                    DL_GPIO_setPins(GPIO_PORT_B_PORT, rowPins[row]);
                    return keys[row][col]; // Return the key value
                }
            }
        }

        // Reset the current row to HIGH after scanning
        DL_GPIO_setPins(GPIO_PORT_B_PORT, rowPins[row]);
    }
    return '\0'; // No key pressed
}

int main()
{
    SYSCFG_DL_init();

    for (int i = 0; i < 5; i++) {
                       DL_GPIO_setPins(GPIO_PORT_B_PORT, row[i]);  // Set all rows to high
                   }

        while(1){

                for (int i = 0; i < 5; i++) {
                    DL_GPIO_clearPins(GPIO_PORT_B_PORT, row[i]); // Set current row to low

                    for (int j = 0; j < 4; j++) {  // Check each column

                            if (!(DL_GPIO_readPins(GPIO_PORT_A_PORT, col[j]))) {

                                printf(" Key pressed: %c \n", key[i][j]);  // Print the key

                                while (!(DL_GPIO_readPins(GPIO_PORT_A_PORT, col[j])) );

                                delay_cycles(DELAY);

                            }
                        }
                    DL_GPIO_setPins(GPIO_PORT_PORT, row[i]);  // Set row back to high
                    }
        }
}
