# Advanced Safety Helmet with Nestled Security & Communication Protocols

## Overview

Hello everyone! 👋 This is a small project developed during our university's **Computer Interfacing** course. Here we designed an **intelligent safety helmet** which enhances rider protection using modern sensors and communication technologies. It detects accidents, alcohol consumption, theft, and obstacles, and can send emergency alerts using Bluetooth communication. The helmet incorporates a combination of sensors, buzzers, LEDs, and buttons to provide real-time safety feedback. Arduino 2.3.6 was used to upload and compile the code for the Arduino Uno to run the project.

## Team Information

- [Md. Ratul Mushfique](https://www.facebook.com/ratul.mushfique/)
- [Farhan Labib](https://www.facebook.com/farhan.labib.913175)
- [Sakib Khan](https://www.facebook.com/shakib.parvez13)
- [Nowshin Sumaiya](https://www.facebook.com/nowshin.sumaiya.yen)
- [Most. Sumaiya Haque Subha](https://www.facebook.com/sumaiya.haque.subah)

## Hardware Components

| Component           | Type                      | Purpose                               |
|---------------------|---------------------------|----------------------------------------|
| Arduino Uno         | Microcontroller           | Core controller for all components     |
| MPU6050             | Gyroscope & Accelerometer | Crash and tilt detection               |
| MQ3 Sensor          | Alcohol Sensor            | Alcohol detection via breath           |
| IR Sensor           | Infrared Sensor           | Theft/unwanted access detection        |
| Ultrasonic Sensor   | HC-SR04                   | Obstacle detection                     |
| Touch Sensor        | Capacitive Sensor         | Helmet wear detection                  |
| LEDs                | Actuator                  | Visual alerts                          |
| Buzzer              | Actuator                  | Audio alerts                           |
| SOS Button          | Push Button               | Emergency alert trigger                |
| Kill Switch         | Toggle Switch             | Enable/disable crash detection system  |

## Software Requirements

- **Arduino IDE**: For programming and uploading code to the Arduino Uno.
### Libraries:
- **Wire.h** (for I2C communication with MPU6050)
- **SoftwareSerial.h** (for Bluetooth communication with HC-06)

## Communication Protocols

- **I2C**: For MPU6050 sensor (SDA/SCL)
- **UART**: For Bluetooth communication (TX/RX)
- **Digital/Analog I/O**: For other sensors, buzzers, and LEDs

## Setup Instructions

- Connect the MPU6050 to the Arduino Uno via I2C (SDA to A4, SCL to A5).
- Connect the MQ3 sensor to analog pin A0.
- Connect the IR sensor to digital pin 2.
- Connect the touch sensor to digital pin 6.
- Connect the ultrasonic sensor (HC-SR04) with Trig to pin 11 and Echo to pin 12.
- Connect LEDs to pins 7, 8, and 10.
- Connect buzzers to pins 9 and 13.
- Connect the SOS button to pin 4 and the kill switch to pin 5.
- Connect the HC-06 Bluetooth module to TX and RX pins for serial communication.

## Features

- **Crash Detection**: Triggered when pitch or roll exceeds 45°
- **Alcohol Detection**: Activates alerts if the alcohol level crosses a threshold
- **Helmet Detection**: Ensures the helmet is worn before operation
- **Theft Alert**: IR sensor triggers alert on unauthorized access
- **Obstacle Detection**: Ultrasonic sensor detects objects within 20cm
- **SOS Alert**: Emergency messages are sent with a button press

## Challenges & Solutions

- **MQ3 Sensor Noise**: Mitigated by using a threshold of >300
- **False Crash Detection**: Limited to >45° tilt to reduce false alerts
- **Sensor Inconsistencies**: Delays and flags used to debounce inputs
- **Power Consumption**: Buzzer/LEDs turned on only when needed

## Expected Outcomes

- Real-time alerts for crashes, alcohol detection, and theft
- Efficient, low-power consumption design
- Scalable and practical for commercial and personal use

## References

- [Fall Detection Using MPU6050 and Arduino](https://www.researchgate.net/publication/303404955_Design_and_Implementation_of_Fall_Detection_System_Using_MPU6050_Arduino)
- [Alcohol Detection System Integration](https://www.researchgate.net/publication/386234301_Deployment_of_Alcohol_Detection_System_in_the_Operations_of_Mechanical_Systems)
