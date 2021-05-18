/*-----------------------------------------------
  IoT Smart Device Development Board
  by Dodit Suprianto | DSP-TECH

  Projek: Pergerakkan LED

  Library:
  https://github.com/Simsso/ShiftRegister74HC595
  -----------------------------------------------*/

/*-------------------------------------
  Menambahkan library yang diperlukan
  -------------------------------------*/
#include <ShiftRegister74HC595.h>   // library shift register 74HC595

/*-------------------------------
  Alamat Kanal Shift Register:
  -------------------------------
  Kanal  0 = LED 1
  Kanal  1 = LED 2
  Kanal  2 = LED 3
  Kanal  3 = LED 4
  Kanal  4 = LED 5
  Kanal  5 = LED 6
  Kanal  6 = LED 7
  Kanal  7 = LED 8
  Kanal  8 = LED 9
  Kanal  9 = Buzz Piezo Speaker
  Kanal 10 = Relay
  Kanal 11 - 15 = Kanal expansi
  -------------------------------*/

/*------------------------------
  Pin Microcontroller NodeMCU
  ------------------------------*/
#define pinData       16 // pin D0
#define pinClock       2 // pin D4
#define pinLatch       0 // pin D3

/*------------------------------
  Inisialisasi instance/object &
  Deklarasi varibale global
  -------------------------------*/
// Konstruktor instance Shift register
ShiftRegister74HC595<2> srChannel(pinData, pinClock, pinLatch);

/*-----------------------------------
  Mode Running LED dengan type enum
  -----------------------------------*/
typedef enum {
  AnimKiriKanan,
  AnimKiriKananSendirian,
  AnimTengahSamping,
  AnimSampingTengah
} animLED;

void setup() {
  /*----------------------------------------------------
    Mengatur baudrate serial MCU.
    Baurate disesuaikan dengan baudrate serial monitor)
    ----------------------------------------------------*/
  Serial.begin(115200);

  /*---------------------------------------------
    Set seluruh kanal shift register menjadi OFF
    ---------------------------------------------*/
  srChannel.setAllLow();
}

void loop() {
  Serial.println("Animasi LED dari kiri ke kanan");
  runningLED(AnimKiriKanan, 100);
  delay(1000);

  Serial.println("Animasi LED dari kiri ke kanan satu per satu");
  runningLED(AnimKiriKananSendirian, 100);
  delay(1000);

  Serial.println("Animasi LED dari tengah ke samping");
  runningLED(AnimTengahSamping, 100);
  delay(1000);

  Serial.println("Animasi LED dari samping ke tengah");
  runningLED(AnimSampingTengah, 100);
  delay(1000);
}

/*----------------------
  Function Running LED
  -----------------------*/
void runningLED(animLED al, int tunda) {
  MematikanSemuaLED();
  switch (al) {
    //LED hidup dari kiri ke kanan
    case AnimKiriKanan:
      for (uint8_t i = 0; i <= 8; i++) {
        srChannel.set(i, HIGH);       // LED ke-i hidup
        delay(tunda);                 // tuda 100 ms
      }
      break;

    //LED hidup dari kanan ke kiri
    case AnimKiriKananSendirian:
      for (uint8_t i = 0; i <= 8; i++) {
        if (i > 0) srChannel.set(i - 1, LOW);
        srChannel.set(i, HIGH);
        delay(tunda);
      }
      break;

    case AnimTengahSamping:
      srChannel.set(4, HIGH);
      delay(tunda);

      srChannel.set(3, HIGH);
      srChannel.set(5, HIGH);
      delay(tunda);

      srChannel.set(2, HIGH);
      srChannel.set(6, HIGH);
      delay(tunda);

      srChannel.set(1, HIGH);
      srChannel.set(7, HIGH);
      delay(tunda);

      srChannel.set(0, HIGH);
      srChannel.set(8, HIGH);
      delay(tunda);
      break;

    //LED hidup dari samping ke tengah
    case AnimSampingTengah:
      srChannel.set(0, HIGH);
      srChannel.set(8, HIGH);
      delay(tunda);

      srChannel.set(1, HIGH);
      srChannel.set(7, HIGH);
      delay(tunda);

      srChannel.set(2, HIGH);
      srChannel.set(6, HIGH);
      delay(tunda);

      srChannel.set(3, HIGH);
      srChannel.set(5, HIGH);
      delay(tunda);

      srChannel.set(4, HIGH);
      delay(tunda);
      break;
  }

  MematikanSemuaLED();
}

/*--------------------
  Mematikan semua LED
  ---------------------*/
void MematikanSemuaLED() {
  //Set seluruh kanal LED 0 - LED 8 menjadi OFF
  for (uint8_t i = 0; i <= 8; i++) {
    srChannel.set(i, LOW);
  }
}
