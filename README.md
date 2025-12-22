# ssd1306-emulator
Library for emulating the SSD1306 OLED display in the terminal.

> [!NOTE]
> Right now tests work only on POSIX-compliant systems (Linux/macOS) as they use POSIX
replacements for HAL library functions. Windows support is planned in the future.

Functionality can be tested by compiling the program `test_all.c` with the following command:
```
gcc -lm test_all.c ssd1306.c ssd1306_tests.c ssd1306_fonts.c
```
or with `clang`:
```
clang -lm test_all.c ssd1306.c ssd1306_tests.c ssd1306_fonts.c
```

Based on [STM32 SSD1306 library](https://github.com/afiskon/stm32-ssd1306) written by Aleksander Alekseev (afiskon)
