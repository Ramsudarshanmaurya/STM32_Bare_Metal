/*
 * ============================================
 * Project  : LED Blink — Bare Metal STM32
 * MCU      : STM32F103C6/C8 (Blue Pill)
 * IDE      : Keil MDK uVision
 * Author   : Ramsudarshan Maurya
 * GitHub   : github.com/Ramsudarshanmaurya
 * ============================================
 *
 * Description:
 * Bare Metal LED Blink on PC13 (Built-in LED)
 * No HAL, No Library — Direct Register Access
 *
 * Connection:
 * PC13 → Built-in LED (Active LOW)
 * ============================================
 */

int main(void)
{
    /* ── RCC Clock Enable ─────────────────── */
    unsigned int *RCC_APB2ENR = (unsigned int *)(0x40021000 + 0x18);
    *RCC_APB2ENR |= (1 << 4); /* GPIOC Clock ON */

    /* ── PC13 → Output Push-Pull 2MHz ──────── */
    unsigned int *GPIOC_CRH = (unsigned int *)(0x40011000 + 0x04);
    unsigned int *GPIOC_ODR = (unsigned int *)(0x40011000 + 0x0C);

    *GPIOC_CRH &= ~(0xF << 20); /* Clear PC13 bits */
    *GPIOC_CRH |=  (0x2 << 20); /* Output 2MHz Push-Pull */

    /* ── LED Blink Loop ─────────────────────── */
    while(1)
    {
        *GPIOC_ODR &= ~(1 << 13); /* LED ON  (Active LOW) */
        for(volatile int i = 0; i < 500000; i++); /* ~500ms delay */

        *GPIOC_ODR |=  (1 << 13); /* LED OFF */
        for(volatile int i = 0; i < 500000; i++); /* ~500ms delay */
    }
}
