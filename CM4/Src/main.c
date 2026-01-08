#include "main.h" // Includes the device header (stm32h745xx.h)

int main(void)
{
  // 1. Enable the Clock for GPIO Port J
  // On the STM32H7, GPIOs are on the AHB4 bus.
  // We need to set Bit 9 (corresponding to Port J) in the AHB4ENR register.
  RCC->AHB4ENR |= (1 << 9);

  // 2. Configure PJ2 as Output
  // The MODER (Mode Register) controls the direction.
  // Each pin uses 2 bits. Pin 2 uses bits [5:4].
  // 00 = Input, 01 = Output, 10 = Alternate Function, 11 = Analog
  // We want "01".

  // First, clear the bits for Pin 2 to be safe (make them 00)
  GPIOJ->MODER &= ~(0x3 << (2 * 2));

  // Now, set the bits to 01 (Output)
  GPIOJ->MODER |= (0x1 << (2 * 2));

  /* Infinite loop */
  while (1)
  {
      // 3. Toggle the LED
      // ODR (Output Data Register) controls the High/Low state.
      // We flip Bit 2 using an XOR operation.
      GPIOJ->ODR ^= (1 << 2);

      // 4. Dirty Delay
      // Since we aren't using HAL_Delay, we just burn CPU cycles.
      // 1,000,000 iterations is roughly visible on the default clock.
      for (volatile int i = 0; i < 1000000; i++);
  }
}
