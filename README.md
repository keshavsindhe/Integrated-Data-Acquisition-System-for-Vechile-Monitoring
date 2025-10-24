# 📊 Data Acquisition System using LPC2129 (ARM7)

[![Platform](https://img.shields.io/badge/Platform-ARM7--LPC2129-blue.svg)]()  
[![Language](https://img.shields.io/badge/Language-Embedded%20C-green.svg)]()  
[![Tools](https://img.shields.io/badge/Tools-Keil%2C%20Proteus%2C%20FlashMagic-orange.svg)]()  
[![Status](https://img.shields.io/badge/Status-Working-success.svg)]()

---

## 📚 Table of Contents
1. [Overview](#overview)  
2. [Objective](#objective)  
3. [Components Used](#components-used)  
4. [Block Diagram](#block-diagram)  
5. [Flowchart](#flowchart)  
6. [Interfacing Summary](#interfacing-summary)  
7. [Software & Tools](#software--tools)  
8. [Code Structure](#code-structure)  
9. [Output](#output)  
10. [Future Improvements](#future-improvements)  
11. [Author](#author)

---

## 🧠 Overview
This project demonstrates a *Data Acquisition System (DAS)* built around the *LPC2129 ARM7 microcontroller*.  
The system continuously reads multiple sensors — *LDR, **Temperature (MCP9700), **Potentiometer, and **RTC (DS1307)* — and transmits processed data every second via *UART* to a PC terminal or LCD.

---

## 🎯 Objective
- To acquire and process real-time sensor data.  
- To interface multiple analog and digital sensors via *ADC, I2C, and UART*.  
- To update and display sensor values and time every 1 second.

---

## ⚙ Components Used
| Component | Function |
|------------|-----------|
| *LPC2129* | ARM7-based MCU for data processing |
| *MCP3204* | External 12-bit ADC for LDR input (SPI interface) |
| *MCP9700* | Temperature sensor (Analog output) |
| *DS1307* | Real-Time Clock (I2C communication) |
| *Potentiometer (10kΩ)* | Variable analog input |
| *16x2 LCD* | Displays sensor values |
| *UART Interface* | Sends sensor data to PC |
| *PSU* | Provides regulated power supply |

---

## 🧩 Block Diagram
![Block Diagram](<insert-your-block-diagram-image-link-here>)

*Explanation:*
- The *Power Supply Unit (PSU)* powers the *MCU* and connected sensors.  
- *LDR* connects to an external ADC (*MCP3204*) which interfaces with the MCU.  
- *Temperature Sensor, **Potentiometer, and **RTC (DS1307)* are read directly through the MCU’s inbuilt ADC and I2C modules.  
- The MCU sends processed data every second to *LCD* and *PC terminal* through *UART*.

---

## 🔁 Flowchart
![Flowchart](<insert-your-flowchart-image-link-here>)

*Process Description:*
1. *Timer Interrupt* triggers every 1 second.  
2. MCU reads sensor values from *LDR, **MCP9700, **DS1307, and **Potentiometer*.  
3. Raw ADC values are converted to readable units (e.g., °C, Lux, Voltage).  
4. Data is displayed on LCD and sent to the PC terminal via UART.  

---

## 🧮 Interfacing Summary

| Sensor/Module | Interface | MCU Peripheral Used |
|----------------|------------|----------------------|
| LDR (via MCP3204) | SPI | SPI0 |
| Temperature Sensor (MCP9700) | Analog | Inbuilt ADC |
| RTC (DS1307) | I2C | I2C0 |
| Potentiometer | Analog | Inbuilt ADC |
| LCD Display | GPIO | 4-bit mode |
| UART | Serial | UART0 |

---

## 💻 Software & Tools
- *Keil µVision* – For Embedded C programming  
- *Flash Magic* – For Flashing hex file to LPC2129  
- *Proteus / Multisim* – Circuit simulation and testing  
- *PuTTY / TeraTerm* – Serial monitoring  
- *Language:* Embedded C  

---

## 🧱 Code Structure
---

## 🧾 Output
*Example (PC Serial Terminal):*
*LCD Display Output:*
---

## 🚀 Future Improvements
- Add *SD Card* for data logging.  
- Include *Wi-Fi (ESP8266)* or *Bluetooth* for IoT integration.  
- Add *threshold-based alerts* (buzzer/LED) for specific conditions.  
- Display sensor graphs on PC using *Python GUI / ThingSpeak*.

---

## 👨‍💻 Author
*Keshav S. Sindhe*  
📧 [keshavsshinde5@gmail.com](mailto:keshavsshinde5@gmail.com)  
🔗 [LinkedIn](https://linkedin.com/in/keshav-sindhe5)  
💻 [GitHub](https://github.com/keshavsindhe)
