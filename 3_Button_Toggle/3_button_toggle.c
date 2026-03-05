/*
 * ============================================
 * Project  : Button Toggle LED
 * MCU      : STM32F103C6/C8 (Blue Pill)
 * IDE      : Keil MDK uVision
 * Author   : Ramsudarshan Maurya
 * GitHub   : github.com/Ramsudarshanmaurya
 * ============================================
 *
 * Description:
 * 1st Press → LED ON
 * 2nd Press → LED OFF
 * Software Debounce implemented
 * XOR Toggle Logic used
 * No HAL, No Library — Direct Register Access
 *
 * Connection:
 * PA0 → Button → GND
 * PA1 → External LED → GND
 * PC13 → Built-in LED (Active LOW)
 * ============================================
 */

int main(void)
{
    /* ── RCC Clock Enable ─────────────────── */
    unsigned int *RCC_APB2ENR = (unsigned int *)(0x40021000 + 0x18);
    *RCC_APB2ENR |= (1 << 2); /* GPIOA Clock ON */
    *RCC_APB2ENR |= (1 << 4); /* GPIOC Clock ON */

    /* ── PC13 → Output Push-Pull (Built-in LED) ─ */
    unsigned int *GPIOC_CRH = (unsigned int *)(0x40011000 + 0x04);
    *GPIOC_CRH &= ~(0xF << 20);
    *GPIOC_CRH |=  (0x2 << 20);

    /* ── PA0 → Input Pull-up (Button) ────────── */
    /* ── PA1 → Output Push-Pull (External LED) ─ */
    unsigned int *GPIOA_CRL = (unsigned int *)(0x40010800 + 0x00);
    unsigned int *GPIOA_ODR = (unsigned int *)(0x40010800 + 0x0C);
    unsigned int *GPIOA_IDR = (unsigned int *)(0x40010800 + 0x08);
    unsigned int *GPIOC_ODR = (unsigned int *)(0x40011000 + 0x0C);

    /* PA0 → Input Pull-up */
    *GPIOA_CRL &= ~(0xF << 0);
    *GPIOA_CRL |=  (0x8 << 0);
    *GPIOA_ODR |=  (1 << 0);

    /* PA1 → Output Push-Pull 2MHz */
    *GPIOA_CRL &= ~(0xF << 4);
    *GPIOA_CRL |=  (0x2 << 4);

    /* Both LEDs OFF initially */
    *GPIOC_ODR |=  (1 << 13);
    *GPIOA_ODR &= ~(1 << 1);

    unsigned int led_state = 0; /* LED state: 0=OFF, 1=ON */

    /* ── Main Loop ──────────────────────────── */
    while(1)
    {
        if(!(*GPIOA_IDR & (1 << 0)))       /* Button pressed */
        {
            /* Software Debounce — 50ms */
            for(volatile int i = 0; i < 50000; i++);

            if(!(*GPIOA_IDR & (1 << 0)))   /* Confirm press */
            {
                led_state ^= 1;             /* XOR Toggle */

                if(led_state)
                {
                    *GPIOC_ODR &= ~(1 << 13); /* Built-in LED ON  */
                    *GPIOA_ODR |=  (1 << 1);  /* External LED ON  */
                }
                else
                {
                    *GPIOC_ODR |=  (1 << 13); /* Built-in LED OFF */
                    *GPIOA_ODR &= ~(1 << 1);  /* External LED OFF */
                }

                /* Wait for button release */
                while(!(*GPIOA_IDR & (1 << 0)));
            }
        }
    }
}
