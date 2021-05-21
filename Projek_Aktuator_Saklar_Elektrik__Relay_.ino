/*-----------------------------------------------
  IoT Smart Device Development Board
  by Dodit Suprianto | DSP-TECH

  Projek: Projek Aktuator Saklar Elektrik (Relay)

  Library:
  https://github.com/Simsso/ShiftRegister74HC595
  https://github.com/adafruit/Adafruit_SSD1306
  https://github.com/adafruit/Adafruit-GFX-Library
  -----------------------------------------------*/

/*-------------------------------------
  Menambahkan library yang diperlukan
  -------------------------------------*/
// library shift register 74HC595
#include <ShiftRegister74HC595.h>

// library OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

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
// pin relay shift register
#define pinRelay      10

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

// Konstruktor instance OLED 0.96"
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Status LED pertama adalah False
boolean statusRelay = false;

void setup() {
  /*----------------------------------------------------
    Mengatur baudrate serial MCU.
    Baurate disesuaikan dengan baudrate serial monitor)
    ----------------------------------------------------*/
  Serial.begin(115200);
  Wire.begin();

  /*---------------------------------------------
    Set seluruh kanal shift register menjadi OFF
    ---------------------------------------------*/
  srChannel.setAllLow();

  /*-------------------
    Inisialisasi OLED
    -------------------*/
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.setTextSize(1);
  display.setTextColor(WHITE);  
  display.clearDisplay();

  /*-----------------------------------
    Menampilkan pesan OLED pertamakali
    ------------------------------------*/
  display.setCursor(0, 0);
  display.println("Selamat datang...");
  display.setCursor(0, 12);
  display.println("Projek Relay");
  display.setCursor(0, 24);
  display.println("Aktif / Non Aktif");

  // menampilkan pesan string ke OLED
  display.display();

  // tunda tampilan selama 3 detik
  delay(3000);
}

void loop() {
  HidupMatiSemuaLED();
  statusOLED();
}

void statusOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  if (statusRelay == true) {
    display.setCursor(0, 0);
    display.println("Status Relay:");

    display.setTextSize(2);
    display.setCursor(0, 22);
    display.println("AKTIF");
  } else {
    display.setCursor(0, 0);
    display.println("Status Relay:");
    
    display.setTextSize(2);
    display.setCursor(0, 22);
    display.println("NON AKTIF");
  }
  display.display();
}

/*--------------------------------------
  Mematikan atau menghidupkan semua LED
  Menagkatifkan / menonaktifkan relay
  --------------------------------------*/
void HidupMatiSemuaLED() {
  if (statusRelay == true) {
    // Set channel shift register 0-8
    // atau LED 0 - LED 8 menjadi HIGH
    for (uint8_t i = 0; i <= 8; i++) {
      // semua LED hidup
      srChannel.set(i, HIGH);
    }

    // Relay aktif
    srChannel.set(pinRelay, HIGH);

    // ubah status led false
    statusRelay = false;
  } else {
    // Set channel shift register 0-8
    // atau LED 0 - LED 8 menjadi OFF
    for (uint8_t i = 0; i <= 8; i++) {
      // semua LED mati
      srChannel.set(i, LOW);
    }

    // Relay non aktif
    srChannel.set(pinRelay, LOW);

    // ubah status led true
    statusRelay = true;
  }

  // tunda 2 detik untuk setiap transisi
  delay (2000);
}
