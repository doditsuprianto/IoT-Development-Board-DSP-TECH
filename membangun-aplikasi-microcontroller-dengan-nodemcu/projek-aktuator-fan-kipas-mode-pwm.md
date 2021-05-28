# Projek Aktuator FAN \(Kipas\) Mode PWM

### Dasar Teori

#### Pengenalan

Pulse Width Modulation \(PWM\) adalah teknik di mana lebar pulsa divariasikan sambil menjaga frekuensi gelombang konstan.

![](../.gitbook/assets/1.gif)

#### Generasi PWM

Periode pulsa terdiri dari siklus ON \(VCC\) dan siklus OFF \(GND\). Fraksi yang sinyalnya AKTIF selama suatu periode dikenal sebagai siklus kerja.

![](../.gitbook/assets/2.gif)

Misalnya. Pulsa dengan periode 10ms akan tetap ON \(tinggi\) selama 2ms. Oleh karena itu, duty cycle akan tetap

**D = 2ms / 10ms = 20%**

Melalui teknik PWM, kita dapat mengontrol daya yang dikirim ke beban dengan menggunakan sinyal ON-OFF. Sinyal PWM dapat digunakan untuk mengontrol kecepatan motor DC dan untuk mengubah intensitas LED. Selain itu, ini juga dapat digunakan untuk menghasilkan sinyal sinus. Pulse Width Modulated signal dengan duty cycle berbeda ditunjukkan di bawah ini.

![PWM Duty cycle](../.gitbook/assets/3%20%289%29.png)

ESP8266 berbasis NodeMCU memiliki fungsionalitas antarmuka PWM melalui pemrograman perangkat lunak. Ini dicapai dengan metode interupsi pengatur waktu. Rentang frekuensi PWM untuk ESP8266 dapat disesuaikan hingga 1KHz.

#### Pin PWM pada NodeMCU Kit

![Pin NodeMCU PWM](../.gitbook/assets/4%20%284%29.png)

#### Fungsi Arduino untuk NodeMCU PWM

* **analogWrite \(pin, dutycycle\)**: Mengaktifkan software PWM pada pin yang ditentukan. siklus tugas dalam kisaran dari 0 hingga PWMRANGE, yaitu 1023 secara default.
* **analogWrite \(pin, 0\)**: Menonaktifkan PWM pada pin yang ditentukan.
* **analogWriteRange \(new\_range\)**: Fungsi ini digunakan untuk mengubah rentang PWM \(duty cycle\).
* **analogWriteFreq \(new\_frequency\)**: Frekuensi PWM adalah 1kHz secara default. Panggil fungsi ini untuk mengubahnya dengan frekuensi baru. Frekuensi PWM berada dalam kisaran 1 - 1000Khz.

#### Contoh

Mari kita tulis sketsa Arduino untuk menyetel PWM pada pin ke-6 NodeMCU dan memvariasikan siklus tugasnya dengan potensiometer yang terhubung ke pin ADC NodeMCU. Di sini kami menghubungkan LED pada pin PWM untuk memvisualisasikan efek \(Kecerahan LED\) dari variasi PWM.

![Kontrol Kecerahan LED menggunakan NodeMCU PWM](../.gitbook/assets/5%20%285%29.png)

#### Sketsa Arduino untuk PWM

```cpp
uint8_t LEDpin = D6;

// Secara default frekuensi PWM adalah 1000Hz dan 
// kita menggunakan yang sama.
// untuk aplikasi ini maka tidak perlu mengatur.

void setup(){
  Serial.begin(115200);
  // setel siklus kerja 50% awal
  analogWrite(LEDpin, 512);  
}

void loop(){
  // membaca nilai potensiometer dan atur duty cycle PWM
  uint16_t dutycycle =  analogRead(A0); 
  
  // batasi duty cycle maksimal 1023 jika potensio melewati nilai tersebut
  if(dutycycle > 1023) dutycycle = 1023;
  
  Serial.print("Duty Cycle: ");  
  Serial.println(dutycycle);
  analogWrite(LEDpin, dutycycle);
  delay(100);
}
```

### Tujuan

### Rancangan

### Kode Program

### Video Projek

### Tugas

