# Aplikasi IoT & C#.NET Desktop

Pengembangan aplikasi IoT juga dapat memanfaatkan aplikasi dekstop winform semacam C#.NET. Berikut ini akan kami demonstrasikan bagaimana mengambangkan aplikasi IoT yang mengkomunikasi antara Smart IoT Development Board dengan Bahasa pemrograman C#,NET Winform Desktop.

## Aplikasi Sisi IoT Development Board

Seperti yang telah kita kerjakan sebelumnya pada bagian https://dsp-tech.gitbook.io/internet-of-things/membangun-aplikasi-iot-create-from-scratch/mengkomunikasikan-antara-iot-development-board-dengan-message-broker-mosquitto. Kode program tetap sama seperti contoh, yaitu sebagai berikut:

```javascript
/*-----------------------------------------------
  IoT Smart Device Development Board
  by Dodit Suprianto | DSP-TECH
  https://doditsuprianto.blogspot.com/
  https://doditsuprianto.gitbook.io/dsp-tech/
  https://github.com/doditsuprianto
  Email: doditsuprianto@gmail.com

  Library Link & Credit:
  1. https://github.com/bblanchon/ArduinoJson
  2. https://github.com/Simsso/ShiftRegister74HC595
  3. https://github.com/winlinvip/SimpleDHT
  4. https://github.com/adafruit/Adafruit_SSD1306
  5. https://github.com/adafruit/Adafruit-GFX-Library
  6. https://github.com/crankyoldgit/IRremoteESP8266
  7. https://github.com/kiryanenko/SimpleTimer
  8. https://github.com/knolleary/pubsubclient
  --------------------------------------------------------*/

/*------------------------
  Library yang diperlukan
  ------------------------*/
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>            // library ESP8266 Wifi
#include <PubSubClient.h>           // library MQTT Message
#include <ShiftRegister74HC595.h>   // library shift register 74HC595
#include <SimpleDHT.h>              // library sensor suhu & kelembaban DHT
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>           // library OLED
#include <Adafruit_SSD1306.h>       // library font OLED
#include <IRremoteESP8266.h>        // library remote infrared
#include <IRrecv.h>
#include <IRutils.h>
#include <SimpleTimer.h>            // library timer (milles) / thread

/*-------------------------------------
   Buffering memory untuk
   Serialisasi String ke JSON Library
  --------------------------------------*/
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
DynamicJsonDocument dhtData(1024);

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

/*-----------------------------------------
  Mendefinisikan pin kanal shift register
  -----------------------------------------*/
#define pinBuzz        9
#define pinRelay      10

/*------------------------------
  Pin Microcontroller NodeMCU
  ------------------------------*/
#define pinDHT        10 // pin SDD3
#define pinEcho       12 // pin D6
#define pinTrigger    14 // pin D5
#define pinLDR        A0 // pin A0
#define pinFan        15 // pin D8
#define pinIR         13 // pin D7
#define pinData       16 // pin D0
#define pinClock       2 // pin D4
#define pinLatch       0 // pin D3

/*---------------------------------------------------
  Login dan Password Access Point jaringan internet
  Sesuaikan nama WIFI dan PASSWORD Access Point Anda
  ----------------------------------------------------*/
const char* wifiName = "Tenda";
const char* wifiPass = "88888888";

/*------------------------------------------------------------------------------
  Login dan Password ke Message Broker Mosquitto
  User dan Password harus sesuai dengan setting pada Mosquitto
  Alamat IP Message Broker harus disesuaikan, di sini menggunakan 192.168.0.101
  ------------------------------------------------------------------------------*/
const char* brokerUser = "AdminMQTT";
const char* brokerPass = "pwd123";
const char* brokerHost = "192.168.0.103";

/*----------------------------------------------------
  Daftar nama Topic MQTT sebagai Publisher:
  1. Sebagai Publisher DHT11: Suhu & Kelembaban
  2. Sebagai Publisher LDR: Intensitas Cahaya
  3. Sebagai Publisher HC-SR04: Proximity Ultrasonic
  ----------------------------------------------------*/
const char* outTopicDHT  = "/dht";  // pub suhu dan kelembaban
const char* outTopicLDR  = "/ldr";  // pub intensitas cahaya
const char* outTopicSR04 = "/sr04"; // pub jarak penghalang dengan ultrasonic
const char* outTopicIR   = "/remoteir"; // pub remote IR

/*---------------------------------------------
  Daftar nama Topic MQTT sebagai Subscriber:
  1. Sebagai Subscriber FAN PWM
  2. Sebagai Subscriber Relay
  3. Sebagai Subscriber LED
  4. Sebagai Subscriber Buzzer / SPK Piezo
  ---------------------------------------------*/
const char* inTopicFAN   = "/fanpwm";
const char* inTopicRelay = "/relay";
const char* inTopicLED   = "/ledanim";
const char* inTopicPiezo = "/piezo";

/*------------------------------
  Inisialisasi instance/object &
  Deklarasi varibale global
  -------------------------------*/
// OLED 0.96"
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Konstruktor instance Shift register
ShiftRegister74HC595<2> srChannel(pinData, pinClock, pinLatch);

// Konstruktor instance Sensor DHT11
SimpleDHT11 dht11(pinDHT);

// Konstruktor instance Sensor IR Remote
IRrecv PenerimaIR(pinIR);
decode_results hasil;

// Varibale simpletimer / Timer interval
SimpleTimer TimerDHT, TimerLDR, TimerSR04;

// Deklarasi variable suhu dan kelembaban
byte humValid, tempValid;

// Deklarasi kode tombol remote
unsigned int KodeTombolRemote;

// Deklaasi client wifi
WiFiClient espClient;

// Deklarasi MQTT Client
PubSubClient client(espClient);
long lastReconnectAttempt = 0;

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
  Wire.begin();

  /*-------------------------
    Inisialisasi layar OLED
    -------------------------*/
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();

  /*------------------------------------------------
    Membentuk koneksi ke jaringan WIFI Access Point
    ------------------------------------------------*/
  KoneksiWIFI();

  /*--------------------------------
    Koneksi TCP ke Broker MQTT
    port message broker adalah 1883
    --------------------------------*/
  client.setServer(brokerHost, 1883);
  client.setCallback(callback);

  // Mengaktifkan infra red receiver
  // kondisi listen
  PenerimaIR.enableIRIn();

  /*---------------------------------
    Mode pin sensor jarak ultrasonic
    ---------------------------------*/
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);

  /*-------------------
    Mode pin fan/kipas
    -------------------*/
  pinMode(pinFan, OUTPUT);

  /*-------------------
    Mode pin sensor DHT
    -------------------*/
  pinMode(pinDHT, INPUT);

  /*---------------------------------------------
    Set seluruh kanal shift register menjadi OFF
    ---------------------------------------------*/
  srChannel.setAllLow();

  /*----------------------------------------------------
    Atur interval pengecekan LDR, DHT, Jarak Ultrasonic
    ----------------------------------------------------*/
  TimerDHT.setInterval(1500);   // interval 1,5 detik
  TimerLDR.setInterval(300);    // interval 300 mili detik
  TimerSR04.setInterval(500);   // interval 0,5 detik
}

void loop() {
  /*---------------------------------------
    Koneksi ulang ke broker jika terputus
    ---------------------------------------*/
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  /*-------------------------------
    Publish kode keypad Remote IR
    -------------------------------*/
  BacaKodeRemoteIR();

  /*--------------------------------------------------------
    pembacaan sensor cahaya sesuai interval yang ditentukan
    kemudian mengirim datanya ke message broker
    --------------------------------------------------------*/
  if (TimerLDR.isReady()) {
    // kirim data LDR ke message broker
    snprintf (msg, MSG_BUFFER_SIZE, "%d", SensorLDR());
    client.publish(outTopicLDR, msg);

    // update tampilan ke OLED setelah terjadi perubahan nilai
    updateOLED();

    TimerLDR.reset();
  }

  /*-----------------------------------------
    pembacaan sensor jarak sesuai interval,
    kemudian mengirim data ke message broker
    -----------------------------------------*/
  if (TimerSR04.isReady()) {
    // Memanfaatkan memory buffer untuk mempercepat proses fetch data
    // dan  mengurangi waktu tunda saat data dikirim dari microcontroller
    // ke message broker MQTT mosquitto
    snprintf (msg, MSG_BUFFER_SIZE, "%d", SensorJarakUltraSonic());

    // Kirim data yang berada di dalam memory buffer ke message broker
    // sesuai dengan topic yag telah ditentukan dengan peritah client.publish
    client.publish(outTopicSR04, msg);

    // update tampilan ke OLED setelah terjadi perubahan nilai
    updateOLED();

    // timer di reset kembali ke counter 0
    TimerSR04.reset();
  }

  /*---------------------------------------------
    Membaca sensor suhu dan kelembaban DHT11
    sesuai interval yang ditetapkan.
    Kemudian mengirim datanya ke message broker
    sesuai dengan topic yang ditentukan
    ---------------------------------------------*/
  if (TimerDHT.isReady()) {

    // memanggil prosedur SensorDHT()
    // membaca suhu & kelembaban
    SensorDHT();

    // update tampilan ke OLED setelah terjadi perubahan nilai
    updateOLED();

    // Format data dibah menjadi sebuah bentuk array.
    // Hal ini karena dalam satu siklus waktu sensor DHT11
    // menghasilkan 2 nilai sekaligus, yaitu suhu dan kelembaban
    dhtData["suhu"] = tempValid;
    dhtData["kelembaban"] = humValid;

    // Untuk menghemat sumberdaya maka dalam sekali transmisi data ke message broker
    // nilai suhu dan kelembaban dikirim sekaligus, sehingga digunakan serialisasi data.
    // Format data semula berupa array menjadi format JSON dengan menggunakan fungsi serializeJson
    char buffer[256];
    size_t n = serializeJson(dhtData, buffer);

    // Kirim data yang berada di dalam memory buffer ke message broker
    // sesuai dengan topic yag telah ditentukan dengan peritah client.publish
    client.publish(outTopicDHT, buffer, n);

    // Timer di-reset kembali ke counter 0
    TimerDHT.reset();
  }
}

/*--------------------------------------------
  Fungsi mengendalikan kecepatan putaran FAN
  dengan cara PWM (pulse with modulation)
  --------------------------------------------*/
void KontrolKecepatanFan() {
  /*------------------------------------------------------------------------------------------------------------------
    referensi https://www.electronicwings.com/nodemcu/nodemcu-pwm-with-arduino-ide
    analogWriteFreq(500); secara default adalah 500
    analogWriteRange(100); secara default max bernilai 1023

    Memetakan antara jarak objek yang dideteksi oleh ultrasonic dengan RPM Fan
    Semakin dekat antara objek dengan sensor ultrasonic makan RPM Fan akan semakin cepat
    Di sini dipetakan jarak antara 1-30cm menjadi 1023-0 pwm analogread
    Sebagai pembuktian, silahkan dekat dan jauhkan benda dengan ultrasonic, kemudian perhatikan RPM Fan yang terjadi
    -------------------------------------------------------------------------------------------------------------------*/

  int speedfan = map(SensorJarakUltraSonic(), 30, 1, 0, 1023);
  analogWrite(pinFan, speedfan);
  Serial.println("Speed FAN: " + String(speedfan));
}

void SpeedFANSub(int speedFAN) {
  int speedfan = map(speedFAN, 1, 100, 0, 1023);
  analogWrite(pinFan, speedfan);
}

/*-------------------------------------
  Fungsi menghitung intensitas cahaya
  dengan sensor LDR secara analog
  -------------------------------------*/
int SensorLDR() {
  int nilaiAnalogLDR = analogRead(pinLDR);
  /*--------------------------------------------------------------------------------
    Referensi perhitung Lux
    https://arduinodiy.wordpress.com/2013/11/03/measuring-light-with-an-arduino/
    https://emant.com/316002
    VOut = nilaiAnalogLDR * (3.3 / 1023) = nilaiAnalogLDR * ‭‭0.0032258064516129‬
    Perhitungan ini tidak dikalibrasi
    ----------------------------------------------------------------------------------*/

  double Vout = nilaiAnalogLDR * 0.0032258064516129;
  int lux = 330 / (10 * ((3.3 - Vout) / Vout));
  Serial.println("Lux Intensity= " + String(int(lux)));
  return lux;
}

/*------------------------------------------
  Fungsi menghitung jarak benda penghalang
  Dengan Sensor Ultrasonic HR-SR04
  ------------------------------------------*/
int SensorJarakUltraSonic() {

  // Membersihkan pin pinTrigger selama 2 microdetik
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);

  // Set pinTrigger menjadi HIGH selama 10 microdetik
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  // Menghitng jarak berdasarkan  waktu perjalanan
  // gelombang suara dalam mikrodetik
  long Durasi = pulseIn(pinEcho, HIGH);
  int JarakCM = Durasi * 0.034 / 2;    // Jarak dalam satuan CM
  int JarakInch = Durasi * 0.0133 / 2; // Jarak dalam satuan INCH

  Serial.println("Jarak Cm=" + String(JarakCM) + " Inch=" + String(JarakInch));
  return JarakCM;
}

/*------------------------------------
  Fungsi membaca suhu dan kelembaban
  dengan sensor DHT11
  ------------------------------------*/
void SensorDHT() {
  byte suhu = 0;
  byte hum = 0;

  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&suhu, &hum, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);
    delay(100);
    return;
  }

  // Memastikan suhu dan kelembaban valid
  // bila bernilai 0 maka diambil dari nilai sebelumnya
  if (suhu != 0 || hum != 0) {
    tempValid = suhu;
    humValid = hum;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)tempValid); Serial.print(" *C, ");
  Serial.print((int)humValid); Serial.println(" H");
}

/*-------------------------
  Fungsi suara Buzz Piezo
  --------------------------*/
void beepBuzz(unsigned char delayms) {
  srChannel.set(pinBuzz, HIGH);
  delay(delayms);
  srChannel.set(pinBuzz, LOW);
  delay(delayms);
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
        srChannel.set(i, HIGH);
        delay(tunda);
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

    //LEH hidup dari samping ke tengah
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

/*------------------------------------------------------
  Fungsi memetakan kode tombol/keypad remote IR.
  Berdasarkan kode yang dicatat tsb akan menjadi dasar
  engecekkan ke langkah berikutnya
  ------------------------------------------------------*/
void BacaKodeRemoteIR() {
  if (PenerimaIR.decode(&hasil)) {
    // Kualitas remote yang buruk menyebabkan debouncing
    // Decode kode tombol dengan lebar 8 saja yang akan diproses.
    // Setiap remote memiliki lebar kode valid masing-masing
    // Pastikan untuk dilakukan pemetaan kode terlebih dahulu
    String ngatasiDebounce = String((int)hasil.value, (unsigned char)DEC);
    if (ngatasiDebounce.length() == 8) {
      KodeTombolRemote = hasil.value;
      Serial.println("Kode remote: " + String(KodeTombolRemote));

      /// kirim kode keypad ke message broker
      snprintf (msg, MSG_BUFFER_SIZE, "Anda menekan keypad dengan kode: %d", KodeTombolRemote);
      client.publish(outTopicIR, msg);
    } else {
      // proses pemetaan kode tombol ditampilkan pada serial monitor
      unsigned int kodeGagal = hasil.value;
      Serial.println("Length Decode: " + String(ngatasiDebounce.length()));
      Serial.println("Kode remote tidak diproses: " + String(kodeGagal));
    }
    PenerimaIR.resume();
  }
  delay(100);
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

/*-----------------------------------------
  Mengendalikan LED menggunakan Remote IR
  ------------------------------------------*/
void HidupkanLEDDenganIR() {
  MematikanSemuaLED();

  if (KodeTombolRemote == 1303529910) {
    // hidupkan LED 1
    // dengan tombol 1
    srChannel.set(0, HIGH);
  } else if (KodeTombolRemote == 1303562550) {
    // hidupkan LED 1, 2
    // dengan tombol 2
    srChannel.set(0, HIGH);
    srChannel.set(1, HIGH);
  } else if (KodeTombolRemote == 1303524300) {
    // hidupkan LED 1, 2, 3
    // dengan tombol 3
    srChannel.set(0, HIGH);
    srChannel.set(1, HIGH);
    srChannel.set(2, HIGH);
  } else if (KodeTombolRemote == 1303540110) {
    // hidupkan LED 1, 2, 3, 4
    // dengan tombol 4
    srChannel.set(0, HIGH);
    srChannel.set(1, HIGH);
    srChannel.set(2, HIGH);
    srChannel.set(3, HIGH);
  } else if (KodeTombolRemote == 1303572750) {
    // hidupkan LED 1, 2, 3, 4, 5
    // dengan tombol 5
    srChannel.set(0, HIGH);
    srChannel.set(1, HIGH);
    srChannel.set(2, HIGH);
    srChannel.set(3, HIGH);
    srChannel.set(4, HIGH);
  } else if (KodeTombolRemote == 1303516140) {
    // hidupkan LED 1, 2, 3, 4, 5, 6
    // dengan tombol 6
    srChannel.set(0, HIGH);
    srChannel.set(1, HIGH);
    srChannel.set(2, HIGH);
    srChannel.set(3, HIGH);
    srChannel.set(4, HIGH);
    srChannel.set(5, HIGH);
  } else if (KodeTombolRemote == 1303531950) {
    // hidupkan LED 1, 2, 3, 4, 5, 6, 7
    // dengan tombol 7
    srChannel.set(0, HIGH);
    srChannel.set(1, HIGH);
    srChannel.set(2, HIGH);
    srChannel.set(3, HIGH);
    srChannel.set(4, HIGH);
    srChannel.set(5, HIGH);
    srChannel.set(6, HIGH);
  } else if (KodeTombolRemote == 1303564590) {
    // hidupkan LED 1, 2, 3, 4, 5, 6, 7, 8
    // dengan tombol 8
    srChannel.set(0, HIGH);
    srChannel.set(1, HIGH);
    srChannel.set(2, HIGH);
    srChannel.set(3, HIGH);
    srChannel.set(4, HIGH);
    srChannel.set(5, HIGH);
    srChannel.set(6, HIGH);
    srChannel.set(7, HIGH);
  } else if (KodeTombolRemote == 1303520220) {
    // hidupkan LED 1, 2, 3, 4, 5, 6, 7, 8, 9
    // dengan tombol 9
    srChannel.set(0, HIGH);
    srChannel.set(1, HIGH);
    srChannel.set(2, HIGH);
    srChannel.set(3, HIGH);
    srChannel.set(4, HIGH);
    srChannel.set(5, HIGH);
    srChannel.set(6, HIGH);
    srChannel.set(7, HIGH);
    srChannel.set(8, HIGH);
  }
}

/*----------------------------------------
  Fungsi koneksi jaringan ke Access Point
  ----------------------------------------*/
void KoneksiWIFI() {
  Serial.print("Connecting to ");
  Serial.println(wifiName);

  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();

  // Memposisikan NodeMCU sebagai station
  // NodeMCU dihubungkan ke Access Point
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiName, wifiPass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // NodeMCU telah terhubung ke Access Point
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Tampilkan informasi IP
  display.setCursor(0, 12); display.println("WiFi connected");
  display.display(); delay(1000);
  display.setCursor(0, 24); display.println(WiFi.localIP());
  display.display(); delay(1000);
  display.setCursor(0, 36); display.println("IoT Smart Device");
  display.display(); delay(1000);
  display.setCursor(0, 48); display.println("Development Board");
  display.display(); delay(3000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", brokerUser, brokerPass)) {

      Serial.println("connected");

      // memastikan bahwa IoT Development Board
      // telah meng-subscribe semua aktuator
      client.subscribe(inTopicFAN);
      client.subscribe(inTopicRelay);
      client.subscribe(inTopicLED);
      client.subscribe(inTopicPiezo);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}

/*-------------------------------------------------------------
   Fungsi callback adalah 'listen' jika ada data
   yang diterima oleh server(NodeMCU). Kemudian menyimpan data
   ke variable berdasarkan nama TOPIC yang bersesaian
  -------------------------------------------------------------*/
void callback(char* topic, byte* payload, unsigned int length) {
  // variable StringPayload untuk menyimpan konten paket data yang diterima
  String StringPayload = "";

  // Menjadikan setiap character yang diterima menjadi string utuh
  // melalui proses penggabungan character
  for (int i = 0; i < length; i++) {
    StringPayload += (char)payload[i];
  }

  Serial.println("TOPIC: " + String(topic));
  Serial.println("PAYLOAD: " + String(StringPayload));

  // Mem-filter data berdasarkan nama topic nya masing-masing
  if (strcmp(topic, inTopicFAN) == 0) {
    // Topic: "/fanpwm"
    SpeedFANSub(StringPayload.toInt());
  } else if (strcmp(topic, inTopicRelay) == 0) {
    // Topic: "/relay"
    if (StringPayload == "ON") {
      // Mengaktifkan Relay jika StringPayload = "ON"
      srChannel.set(pinRelay, HIGH);
    } else {
      // Menonaktifkan Relay jika StringPayload = "OFF"
      srChannel.set(pinRelay, LOW);
    }
  } else if (strcmp(topic, inTopicPiezo) == 0) {
    // Topic: "/piezo"
    if (StringPayload == "ON") {
      // Mengaktifkan Buzz jika StringPayload = "ON"
      srChannel.set(pinBuzz, HIGH);
    } else {
      // Menonaktifkan Buzz jika StringPayload = "OFF"
      srChannel.set(pinBuzz, LOW);
    }
  } else if (strcmp(topic, inTopicLED) == 0) {
    // Topic: "/ledanim"
    for (int i = 0; i <= 8; i++) {
      // Menset status channel shift register mulai dari 0-8 menjadi LOW
      srChannel.set(i, LOW);
    }

    for (int i = 1; i <= StringPayload.toInt(); i++) {
      // Menset status channel shift register mulai dari 0
      // sampai nilai maks yang diterima dari payload menjadi HIGH
      srChannel.set(i - 1, HIGH);
    }
  }
}

void updateOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);    display.print("Light");
  display.setCursor(75, 0);   display.print(String(SensorLDR()));
  display.setCursor(100, 0);  display.print("Lux");

  display.setCursor(0, 14);   display.print("Temperature");
  display.setCursor(75, 14);  display.print(String(tempValid));
  display.drawCircle(100, 13, 2, SSD1306_WHITE);
  display.setCursor(105, 14); display.print("C");

  display.setCursor(0, 28);   display.print("Humidity");
  display.setCursor(75, 28);  display.print(String(humValid));
  display.setCursor(100, 28); display.print("H");

  display.setCursor(0, 42);   display.print("Distance");
  display.setCursor(75, 42);  display.print(String(SensorJarakUltraSonic()));
  display.setCursor(100, 42); display.print("CM");

  display.display();
}
```
## Pengembangan Sisi Aplikasi Desktop

Di sini kita memerlukan IDE Visual Studio dengan bahasa pemgraman C# sebagai pilihannya. Dalam hal ini saya menggunakan Visual Studio 2017, jika Anda belum memilikinya dapat mendownloadnya versi communitiy atau gratis di link berikut https://my.visualstudio.com/Downloads?q=visual%20studio%202017&wt.mc_id=o~msft~vscom~older-downloads.

Setelah sukses menginstalasi, langkah selanjutnya bisa mengikuti tahapannya berikut ini:

Buka menu **File > New Project**

![](../.gitbook/assets/CS1.png)

Tentukan jenis bahasa pemrogramannya menjadi C#, tentukan nama projek dan lokasi dimana file akan ditempatkan seperti tampak ilustrasi di bawah ini, kemudian klik tombol OK.

![](../.gitbook/assets/CS2.png)

Setelah itu akan muncul satu window form bernama form1. Dari window form1 tersebut kita akan menambahkan beberapa control/widget yang diperlukan. 

Pertama adalah kita menambahkan sebuah TabControl dengan tiga TabPage di dalamnya. Untuk menambahkan control atau widget dengan cara men-drag-drop widget dari toolbox ke window form.

![](../.gitbook/assets/CS3.png)

![](../.gitbook/assets/CS4.png)

Ubah **Property Text** pada masing-masing tabPage, dengan memilih salah satu tabPage. Klik pada body tabPage, kemudian ubah Property Text-nya. Hal ini akan mengubah title masing-masing tabPage. Lakukan cara yang sama untuk semua tabPage.

- Text tabPage1 = “Actuator”
- Text tabPage2 = “Sensor LDR & Ultrasonic”
- Text tabPage3 = “Sensor DHT11 (Suhu & Kelembaban)”

![](../.gitbook/assets/CS5.png)

Ganti nama Form yang semula “Form1” menjadi “frmIoTDashboard”

![](../.gitbook/assets/CS6.png)

Bila ada permintaan konfirmasi, pilih **Yes**.

![](../.gitbook/assets/CS7.png)

### Kebutuhan Library

Sebelum melangkah lebih jauh, kita perlu menambahkan beberapa library ke dalam projek yang kita bangun. Library tersebut antara lain:

- Library LiveCharts untuk menangani visualisasi grafis. 
- Library M2MQTT untuk menangani komunikasi MQTT
- Library Newton.JSON untuk menangani data format JSON

Sama seperti pada lingkungan pengembangan pemrograman modern lainnya, Visual Studio juga menyediakan koneksi repository seperti git atau npm. Di sini menggunakan NuGet.org.

Buka menu **Project > Manage Nuget Package**.

![](../.gitbook/assets/CS8.png)

Pilih kata kunci **newtonsoft** pada field pencarian, pilih library **Newtonsoft.Json**, terakhir klik pada tombol Install. Lakukan hal yang sama untuk dua library lainnya sesuai gambar ilustrasi di bawah ini

![](../.gitbook/assets/CS9.png)

![](../.gitbook/assets/CS10.png)

![](../.gitbook/assets/CS11.png)

Untuk mengetahui apakah semua library terinstall dengan baik dan benar, silahkan pilih tab **Installed**.

![](../.gitbook/assets/CS12.png)

### Tab Page “Actuator

Sekarang kita kembali ke tabPage Actuator. Di sini kita akan menambahkan beberapa control, antara lain

![](../.gitbook/assets/TB1.jpg)

Adapun rancangan yang dibuat adalah sebagai berikut

![](../.gitbook/assets/CS13.png)

- CheckBox Relay bertujuan untuk mengaktifkan dan menonaktifkan Relay pada IoT Smart Development Board
- CheckBox Buzzer bertujuan untuk mengaktifkan dan menonaktifkan Buzzer/Speaker pada IoT Smart Development Board
- TrackBar Led Controller bertujuan untuk mengendalikan seberapa banya LED yang aktif pada IoT Smart Development Board
- TrackBar Speed FAN, bertujuan untuk mengendalikan kecepatan putar FAN pada IoT Smart Development Board.

> Note. Anda tidak perlu kuatir jika mengalami kesalahan, karena diakhir ulasan akan disertai dengan link source code lengkap yang bisa dicoba.

### Tab Page "Sensor LDR & Ultrasonic"

Pilih terlebih dahulu tabPage2 atau tabPage “Sensor LDR & Ultrasonic”. Di dalamnya terdapat dua groupBox dimana setiap groupBox berisi dua chart cartesian yang akan memvisualisasikan data intensitas cahaya dalam satuan LUX yang diterima dari sensor LDR dan data jarak penghalang dalam satuan cm yang diterima dari sensor Ultrasonic HC-SR04.

![](../.gitbook/assets/TB2.jpg)

![](../.gitbook/assets/CS14.png)

![](../.gitbook/assets/CS15.png)

> **Note**. Jika control LiveChart tidak tampak pada Window Toolbox maka simpan terlebih dahulu projek Anda, kemudian tutup dan buka kembali visual studio projek Anda.

![](../.gitbook/assets/CS16.png)

![](../.gitbook/assets/CS17.png)

![](../.gitbook/assets/CS18.png)

### Tab Page “Sensor DHT11 (Suhu & Kelembaban)”

Perancangan berikutnya adalah tabPage“Sensor DHT11 (Suhu & Kelembaban)”. Di sini kita akan menambahkan dua groupBox, dimana setiap groupBox berisi chart **SolidGauge** dari liveCharts. Kedua SolidGauge akan memvisualisasikan nilai suhu dan kelembaban yang diterima dari sensor DHT11.

![](../.gitbook/assets/TB3.jpg)

![](../.gitbook/assets/CS19.png)

![](../.gitbook/assets/CS20.png)

![](../.gitbook/assets/CS21.png)

### Control “Timer”

Untuk memvisualisasikan data-data sensor secara *real-time* pada grafis maka diperlukan control timer. Control timer tersebut akan bekerja sesuai interval yang ditentukan (secara ideal disesuaikan dengan interval pengiriman data sensor di sisi IoT Development Board) untuk membaca data yang diterima oleh *event subscriber* MQTT.

Di sini dibutuhkan tiga timer, antara lain:

- **timerLDR**, control timer sensor LDR dengan interval eksekusi 300 milidetik.
- **timerSR04**, control timer sensor pengukur jarak penghalang ultrasonic HC-SR04 dengan interval eksekusi 0,5 detik (500 milidetik).
- **timerDHT**, control timer sensor DHT untuk mengukur suhu dan kelembaban dengan interval eksekusi 1,5 detik (1500 milidetik).

Untuk menambahkan control timer, cukup *drag-drop* control timer ke form windows. Kemudian beri nama dengan **timerLDR**, **timerSR04**, dan **timerDHT**. Sedangkan pengaturan interval dan kapan aktifasi timer akan dilakukan secara kode program.

![](../.gitbook/assets/CS22.png)

Kode Program C#.NET
Untuk memulai memprogram C# Winform. Pilih control CheckBox **cbRelay** dua kali, atau kilik sekali kemudian perhatikan pada window event khusunya event CheckedChange. Dari situ akan diarahkan ke mode coding.

![](../.gitbook/assets/CS23.png)

![](../.gitbook/assets/CS24.png)

Dengan cara yang hampir serupa akan berlaku pada semua event control yang memang dibutuhkan. Anda tinggal memperhatikan nama setiap event yang terdapat dalam contoh sudah dapat menebak event apa yang diperlukan.

Adapun kode program lengkapnya adalah sebagai berikut:

```csharp
/******************************************************************************
 *  IoT Smart Device Development Board - IoT & C#.NET Winform                 *
 *  Dodit Suprianto | DSP-TECH | https://dsp-tech.gitbook.io                  *
 *  https://doditsuprianto.blogspot.com/ | https://github.com/doditsuprianto  *
 *  Email: doditsuprianto@gmail.com                                           *
 ******************************************************************************/
using System;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Media;
using LiveCharts;
using LiveCharts.Defaults;
using LiveCharts.Wpf;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using Newtonsoft.Json;
using System.Windows;

namespace DemoIoTCSharp
{
    public partial class frmIoTDashboard : Form
    {
        // class data json yang akan di deserialize
        public class DHT
        {
            public UInt32 suhu { get; set; }
            public UInt32 kelembaban { get; set; }
        }

        // Status relay dan buzzer, default OFF
        private String RelayState = "OFF";
        private String BuzzerState = "OFF";

        // Alamat IP dan Port Broker MQTT
        // Silahkan disesuaikan dengan alamat IP Broker MQTT Anda
        private const String IPBroker = "192.168.0.102";
        private const UInt16 PORT = 1883;

        // User & Password Broker MQTT 
        private const String userBroker = "AdminMQTT";
        private const String pwdBroker = "pwd123";

        // Topik Sensor
        private const String outTopicDHT = "/dht";
        private const String outTopicLDR = "/ldr";
        private const String outTopicSR04 = "/sr04";

        // Topik Aktuator
        private const String inTopicFAN = "/fanpwm";
        private const String inTopicRelay = "/relay";
        private const String inTopicLED = "/ledanim";
        private const String inTopicPiezo = "/piezo";

        static UInt32 nilaiLDR;
        static UInt32 nilaiSR04;
        static UInt32 nilaiSuhu;
        static UInt32 nilaiKelembaban;

        // Constructor koneksi client dengan Broker MQTT
        MqttClient client = new MqttClient(IPBroker, PORT, false, null, null, MqttSslProtocols.None);

        //public SeriesCollection SeriesCollection { get; set; }
        public ChartValues<ObservableValue> ValuesLDR { get; set; }
        public ChartValues<ObservableValue> ValuesSR04 { get; set; }

        public frmIoTDashboard()
        {
            InitializeComponent();

            // Text title Form
            this.Text = "IoT Dashboard System";

            // Text title tab page
            tabControl1.TabPages[0].Text = "Actuator";
            tabControl1.TabPages[1].Text = "Sensor LDR & Ultrasonic";
            tabControl1.TabPages[2].Text = "Sensor DHT11 (Suhu & Kelembaban)";

            // Text title checkbox
            cbRelay.Text = "Relay ON/OFF";
            cbBuzzer.Text = "Buzzer ON/OFF";

            // Mengubah warna background trackbar menjadi putih
            System.Drawing.SolidBrush putih = new System.Drawing.SolidBrush(System.Drawing.Color.White);
            SliderLED.BackColor = putih.Color;
            SliderFAN.BackColor = putih.Color;

            // Inisialisasi label text FAN dan LED
            lblValueFAN.Text = "0";
            lblValueLED.Text = "0";

            // Menjalin koneksi dengan Broker MQTT
            client.Connect(Guid.NewGuid().ToString(), userBroker, pwdBroker);

            // Membuat event dan memanggil method client_MqttMsgPublishReceived secara otomatis
            // ketika ada pesan MQTT yang masuk
            client.MqttMsgPublishReceived += client_MqttMsgPublishReceived;

            // Mendeklarasikan subscriber MQTT
            client.Subscribe(new string[] { outTopicLDR }, new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });
            client.Subscribe(new string[] { outTopicSR04 }, new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });
            client.Subscribe(new string[] { outTopicDHT }, new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });

            // Inisialisasi slider/trackbar LED
            SliderLED.Minimum = 0;
            SliderLED.Maximum = 9;
            SliderLED.Value = 0;

            // Inisialisasi slider/trackbar FAN
            SliderFAN.Minimum = 0;
            SliderFAN.Maximum = 100;
            SliderFAN.Value = 0;
            SliderFAN.TickFrequency = 10;

            // Constructor nilai chart
            ValuesLDR = new ChartValues<ObservableValue> { };
            ValuesSR04 = new ChartValues<ObservableValue> { };

            //chartIntensitasCahaya.LegendLocation = LegendLocation.Right;

            // Menentukan interval dan mengaktifkan timer LDR
            timerLDR.Interval = 300;
            timerLDR.Enabled = true;

            // Menentukan interval dan mengaktifkan timer Ultrasonic
            timerSR04.Interval = 500;
            timerSR04.Enabled = true;

            // Menentukan interval dan mengaktifkan timer DHT
            timerDHT.Interval = 1500;
            timerDHT.Enabled = true;
        }

        static void client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
        {
            // Memeriksa topic dan menangkap data untuk diolah lebih lanjut
            if (e.Topic == outTopicDHT)
            {
                // Men-deserialisasi data json menjadi variable suhu dan kelembaban
                DHT dht = JsonConvert.DeserializeObject<DHT>(Encoding.UTF8.GetString(e.Message));
                nilaiSuhu = dht.suhu;
                nilaiKelembaban = dht.kelembaban;
            }
            else if (e.Topic == outTopicLDR)
            {
                // Menampung data LDR
                nilaiLDR = Convert.ToUInt32(Encoding.UTF8.GetString(e.Message));
            }
            else if (e.Topic == outTopicSR04)
            {
                //Menampung data jarak ultrasonic
                nilaiSR04 = Convert.ToUInt32(Encoding.UTF8.GetString(e.Message));
            }
        }

        private void cbRelay_CheckedChanged(object sender, EventArgs e)
        {
            // Mengecek status checkbox Relay
            if (cbRelay.Checked)
            {
                // Jika checkbox Relay dicentang maka status relay ON
                RelayState = "ON";
            }
            else
            {
                // Jika checkbox Relay tidak dicentang maka status relay OFF
                RelayState = "OFF";
            }

            // Memastikan pesan menjadi string sebelum di publish
            string strValue = Convert.ToString(RelayState);

            // publish pesan dengan topik inTopicRelay, QoS 2
            client.Publish(inTopicRelay, Encoding.UTF8.GetBytes(strValue), MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE, false);
        }

        private void cbBuzzer_CheckedChanged(object sender, EventArgs e)
        {
            // Mengecek status checkbox Buzer
            if (cbBuzzer.Checked)
            {
                // Jika checkbox Buzzer dicentang maka status buzzer ON
                BuzzerState = "ON";
            }
            else
            {
                // Jika checkbox Buzzer dicentang maka status buzzer OFF
                BuzzerState = "OFF";
            }

            // Memastikan pesan menjadi string sebelum di publish
            string strValue = Convert.ToString(BuzzerState);

            // publish pesan dengan topik inTopicPiezo, QoS 2
            client.Publish(inTopicPiezo, Encoding.UTF8.GetBytes(strValue), MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE, false);
        }

        private void frmIoTDashboard_Load(object sender, EventArgs e)
        {
            //*******************************
            // Timeseries Intensitas Cahaya
            // Sensor LDR
            //*******************************
            chartIntensitasCahaya.Series.Add(new LineSeries
            {
                Values = ValuesLDR,
                StrokeThickness = 2,
                PointGeometrySize = 10,
                DataLabels = true,
                //Stroke = Brushes.Yellow,
            });

            chartIntensitasCahaya.AxisX.Add(new LiveCharts.Wpf.Axis
            {
                Title = "Waktu",
            });


            chartIntensitasCahaya.AxisY.Add(new LiveCharts.Wpf.Axis
            {
                Title = "Intensitas Cahaya",
                LabelFormatter = x => x + " lux"
            });


            //******************************
            // Timeseries Jarak Penghalang
            // Sensor HC-SR04
            //******************************
            chartJarakPenghalang.Series.Add(new LineSeries
            {
                Values = ValuesSR04,
                StrokeThickness = 2,
                PointGeometrySize = 10,
                DataLabels = true,
                Stroke = Brushes.Red,
                Fill = Brushes.Transparent
            });

            chartJarakPenghalang.AxisX.Add(new LiveCharts.Wpf.Axis
            {
                Title = "Waktu",
            });


            chartJarakPenghalang.AxisY.Add(new LiveCharts.Wpf.Axis
            {
                Title = "Jarak Penghalang",
                LabelFormatter = x => x + " cm"
            });
        }

        private void frmIoTDashboard_FormClosed(object sender, FormClosedEventArgs e)
        {
            // Memutuskan koneksi dengan Broker MQTT ketika Form Closed
            client.Disconnect();

            // Memnonaktifkan timer ketika Form Closed
            timerDHT.Enabled = false;
            timerLDR.Enabled = false;
            timerSR04.Enabled = false;
        }

        private void timerLDR_Tick(object sender, EventArgs e)
        {
            // Maksimum 30 data ditampilkan dalam satu chart
            if (ValuesLDR.Count() > 30)
            {
                // Jika lebih dari 30 data maka data index ke-0 dihapus
                // berarti shift data ke kiri atau bergeser ke kiri
                ValuesLDR.RemoveAt(0);
            }
            else
            {
                // Jika kurang dari 30 data maka akan ditambah di sebelah kanan
                ValuesLDR.Add(new ObservableValue(nilaiLDR));
            }
        }

        private void timerSR04_Tick(object sender, EventArgs e)
        {
            // Maksimum 20 data ditampilkan dalam satu chart
            if (ValuesSR04.Count() > 20)
            {
                // Jika lebih dari 20 data maka data index ke-0 dihapus
                // berarti shift data ke kiri atau bergeser ke kiri
                ValuesSR04.RemoveAt(0);
            }
            else
            {
                // Jika kurang dari 20 data maka akan ditambah di sebelah kanan
                ValuesSR04.Add(new ObservableValue(nilaiSR04));
            }
        }

        private void timerDHT_Tick(object sender, EventArgs e)
        {
            // Gauge suhu
            solidGaugeSuhu.Uses360Mode = true;
            solidGaugeSuhu.From = 0;
            solidGaugeSuhu.To = 100;
            solidGaugeSuhu.Value = nilaiSuhu;

            // Gauge kelembaban
            solidGaugeKelembaban.From = 0;
            solidGaugeKelembaban.To = 100;
            solidGaugeKelembaban.Value = nilaiKelembaban;
            solidGaugeKelembaban.Base.LabelsVisibility = Visibility.Hidden;
            solidGaugeKelembaban.Base.GaugeActiveFill = new LinearGradientBrush
            {
                GradientStops = new GradientStopCollection
                {
                    new GradientStop(Colors.Yellow, 0),
                    new GradientStop(Colors.Orange, .5),
                    new GradientStop(Colors.Red, 1)
                }
            };
        }

        private void sliderLED_Scroll(object sender, EventArgs e)
        {
            // Mengkonversi value slider menjadi string
            String strValue = SliderLED.Value.ToString();

            //Menampilkan value slider pada label lblValueLED
            lblValueLED.Text = strValue;

            // Mengirim pesan ke Broker MQTT
            client.Publish(inTopicLED, Encoding.UTF8.GetBytes(strValue), MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE, false);
        }

        private void sliderFAN_Scroll(object sender, EventArgs e)
        {
            int value = (sender as TrackBar).Value;
            double indexDbl = (value * 1.0) / SliderFAN.TickFrequency;
            int index = Convert.ToInt32(Math.Round(indexDbl));
            SliderFAN.Value = SliderFAN.TickFrequency * index;

            // Mengkonversi value slider menjadi string
            String strValue = SliderFAN.Value.ToString();

            //Menampilkan value slider pada label lblValueFAN
            lblValueFAN.Text = strValue;

            // Mengirim pesan ke Broker MQTT
            client.Publish(inTopicFAN, Encoding.UTF8.GetBytes(strValue), MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE, false);
        }
    }
}
```
Download Source Code IoT dan C# Desktop Winform: https://github.com/doditsuprianto/IoT-Development-Board-DSP-TECH/raw/master/DemoIoTCSharp.zip

## Demo Video Projek


![](../.gitbook/assets/CS25.png)

![](../.gitbook/assets/CS26.png)

![](../.gitbook/assets/CS27.png)

![](../.gitbook/assets/CS28.png)
