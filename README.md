
I give the circuit connections in writing:

circuit elemans:
-Arduino UNO
-RFID okuyucu (MFRC522)
-Load Cell ve HX711 module
-LCD screen (16x2)
-LED
-Buzzer

RFID (MFRC522):

-SDA -> Arduino Pin 10
-SCK -> Arduino Pin 13
-MOSI -> Arduino Pin 11
-MISO -> Arduino Pin 12
-RST -> Arduino Pin 9
-3.3V -> 3.3V
-GND -> GND

Load Cell, HX711 Module:

-Load Cell -> HX711
-HX711 DT -> Arduino Pin A1
-HX711 SCK -> Arduino Pin A0
-HX711 VCC -> 5V
-HX711 GND -> GND

LCD Screen:

-RS -> Arduino Pin 7
-E -> Arduino Pin 6
-D4 -> Arduino Pin 5
-D5 -> Arduino Pin 4
-D6 -> Arduino Pin 3
-D7 -> Arduino Pin 2
-VSS -> GND
-VDD -> 5V
-V0 -> Potansiyometre (kontrast ayarı için)

LED:

-Anot -> Arduino Pin 8
-Katot -> GND

Buzzer:

-Pozitif -> Arduino Pin 7
-Negatif -> GND
