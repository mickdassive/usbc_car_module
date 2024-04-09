# USB 3.1x1 Hub with USB-C and USB-A Ports

This project is a USB 3.1x1 hub designed with KiCad 7.0 and developed with PlatformIO. It features two USB-C ports (one downstream and one upstream) capable of delivering up to 100W power, along with four regular downstream USB-A ports.

## Features

- USB 3.1x1 hub with USB-C and USB-A ports
- Supports up to 100W power delivery per port
- Onboard UART transceiver for programming the main MCU (ESP-12F)
- Onboard CAN bus transceiver for automotive applications
- Utilizes USB5926C hub chip from Microchip
- USB PD PHYs (PTN110N) from NXP
- Includes a display and ADC for power monitoring:
  - Monitor individual power consumption of USB-C ports (upstream and downstream)
  - Monitor combined total power consumption of USB-A ports
  - Monitor total system power consumption


## Contributors

- [Tokyo Andreana](https://github.com/mickdassive)

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).
