/*
 * ============================================
 * Project  : Seven Segment Display Counter
 * MCU      : STM32F103C6/C8 (Blue Pill)
 * IDE      : Keil MDK uVision
 * Author   : Ramsudarshan Maurya
 * GitHub   : github.com/Ramsudarshanmaurya
 * ============================================
 *
 * Description:
 * Auto counter 0-9 on Seven Segment Display
 * Common Cathode type
 * No HAL, No Library — Direct Register Access
 * PA0-PA7 → Segments a-g + DP
 *
 * Connection:
 * PA0 → segment a
 * PA1 → segment b
 * PA2 → segment c
 * PA3 → segment d
 * PA4 → segment e
 * PA5 → segment f
 * PA6 → segment g
 * PA7 → segment DP (optional)
 * GND → Common Cathode (GND pin)
 * ============================================
 */

int main(void)
{
    unsigned int *RCC_APB2ENR = (unsigned int *)(0x40021000 + 0x18);
    unsigned int *GPIOA_CRL   = (unsigned int *)(0x40010800 + 0x00);
    unsigned int *GPIOA_ODR   = (unsigned int *)(0x40010800 + 0x0C);

    /* Common Cathode segment codes 0-9 */
    unsigned char segment_codes[] = {
        0x3F, /* 0 — 0011 1111 */
        0x06, /* 1 — 0000 0110 */
        0x5B, /* 2 — 0101 1011 */
        0x4F, /* 3 — 0100 1111 */
        0x66, /* 4 — 0110 0110 */
        0x6D, /* 5 — 0110 1101 */
        0x7D, /* 6 — 0111 1101 */
        0x07, /* 7 — 0000 0111 */
        0x7F, /* 8 — 0111 1111 */
        0x6F  /* 9 — 0110 1111 */
    };

    /* GPIOA Clock Enable */
    *RCC_APB2ENR |= (1 << 2);

    /* PA0-PA7 → Output 2MHz Push-Pull */
    *GPIOA_CRL = 0x22222222;

    while(1)
    {
        for(int i = 0; i < 10; i++)
        {
            *GPIOA_ODR = segment_codes[i]; /* Display digit */
            for(volatile int d = 0; d < 5000000; d++); /* ~1 sec delay */
        }
    }
}
