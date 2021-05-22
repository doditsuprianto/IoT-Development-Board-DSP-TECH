/*-----------------------------------------------
  IoT Smart Device Development Board
  by Dodit Suprianto | DSP-TECH

  Projek: Sensor Intesitas Cahaya

  Library:
  https://github.com/Simsso/ShiftRegister74HC595
  https://github.com/kiryanenko/SimpleTimer
  -----------------------------------------------*/

/*-------------------------------------
  Menambahkan library yang diperlukan
  -------------------------------------*/
// library shift register 74HC595
#include <ShiftRegister74HC595.h>

// library timer (millis)/thread
#include <SimpleTimer.h>

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

/*------------------------------
  Pin Microcontroller NodeMCU
  ------------------------------*/
#define pinData       16 // pin D0
#define pinClock       2 // pin D4
#define pinLatch       0 // pin D3
#define pinLDR        A0 // pin A0

/*------------------------------
  Inisialisasi instance/object &
  Deklarasi varibale global
  -------------------------------*/
// Konstruktor instance Shift register
ShiftRegister74HC595<2> srChannel(pinData, pinClock, pinLatch);

// Konstruktor instance OLED 0.96"
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Varibale simpletimer (Timer interval)
// SimpleTimer semacam thread yang membentuk session
// tanpa mengganggu session program utama
SimpleTimer TimerLDR;

int validGauge = 0;

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

  /*-----------------------------------
    Atur interval pemvacaan sensor LDR
    -----------------------------------*/
  // interval 300 mili detik
  TimerLDR.setInterval(300);

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
  display.println("Projek Membaca LDR");
  display.setCursor(0, 24);
  display.println("Intensitas Cahaya");

  // menampilkan pesan string ke OLED
  display.display();

  // tunda tampilan selama 5 detik
  delay(5000);
}

void loop() {
  /*----------------------------------
      pembacaan sensor cahaya LDR
      sesuai interval yang ditentukan,
      yitu setiap 300 mili detik
      ---------------------------------*/
  if (TimerLDR.isReady()) {
    // update tampilan ke OLED setelah
    // membaca sensor LDR hasil perubahan nilai
    updateOLED();

    // Memanggil fungsi LEDProgress()
    // untuk memberi efek gauge gerakan LED
    LEDProgress();

    // reset counter ulang
    TimerLDR.reset();
  }
}

/*------------------------------------------
  Fungsi untuk menghitung intensitas cahaya
  dengan sensor LDR secara analog
  ------------------------------------------*/
int SensorLDR() {
  // Membaca sensor LDR mode Analog
  // yang bernilai antara 0 sampai 1023
  int nilaiAnalogLDR = analogRead(pinLDR);

  /*--------------------------------------------------------------------------------
    Referensi perhitung Lux
    https://arduinodiy.wordpress.com/2013/11/03/measuring-light-with-an-arduino/
    https://emant.com/316002
    VOut = nilaiAnalogLDR * (3.3 / 1023) = nilaiAnalogLDR * ‭‭0.0032258064516129‬
    ----------------------------------------------------------------------------------*/
  // Konversi nilai menjadi satuan LUX
  // Perhitungan ini belum tentu valid karena
  // tidak belum dikalibrasi
  double Vout = nilaiAnalogLDR * 0.0032258064516129;
  int lux = 330 / (10 * ((3.3 - Vout) / Vout));
  Serial.println("Nilai LDR Analog = " + String(int(Vout)));

  // nilai balik lux ke fungsi SensorLDR()
  return lux;
}

/*---------------------------------------
  Menampilkan data terbaru ke layar OLED
  ---------------------------------------*/
void updateOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);    display.print("Light");
  display.setCursor(75, 0);   display.print(String(SensorLDR()));
  display.setCursor(100, 0);  display.print("Lux");

  // mapping LUX menjadi gauge ke layar OLED
  // x = 0, y = 0, tinggi = 10 piksel dan
  // lebar = sesuai nilai mapping gaugeOLED, maks 127 piksel
  int gaugeOLED = map(validGauge, 0, 1000, 0, 127);
  display.fillRect(0, 14, gaugeOLED, 10, SSD1306_INVERSE);

  // membuat klasifikasi intensitas cahaya
  // menjadi gelap, redup, terang dan sangat terang
  display.setCursor(0, 28);  display.print("Grade LDR");
  
  if (validGauge >= 0 && validGauge < 50) {    
    display.setCursor(75, 28); display.print("GELAP");
  } else if (validGauge >= 50 && validGauge < 200) {    
    display.setCursor(75, 28); display.print("SEDANG");
  } else if (validGauge >= 200) {    
    display.setCursor(75, 28); display.print("TERANG");
  }

  display.display();
}

/*--------------------------------------
  Gauge LED mengikuti besar kecil nilai
  LUX intensitas cahaya dari sensor LDR
  --------------------------------------*/
void LEDProgress() {
  // set semua LED menjadi mati (LOW)
  for (uint8_t i = 0; i <= 8; i++) {
    srChannel.set(i, LOW);
  }

  // Membatasi nilai agar gauge tidak lebih dari 1000
  if (SensorLDR() > 1000) {
    validGauge = 1000;
  } else {
    validGauge = SensorLDR();
  }

  // Memetakan nilai antara LUX dari fungsi SensorLDR()
  // dengan sejumlah 9 LED (ch 0-8 shift register)
  // kemudian menset menjadi hidup (HIGH)
  int gauge = map(validGauge, 0, 1000, 0, 8);
  Serial.println("Lux Meter: " + String(SensorLDR()));
  Serial.println("Gauge: " + String(gauge));

  // Set channel shift register 0-8 sesuai nilai gauge
  // menjadi hidup (HIGH)
  for (uint8_t i = 0; i <= gauge; i++) {
    // semua LED hidup
    srChannel.set(i, HIGH);
  }
}
