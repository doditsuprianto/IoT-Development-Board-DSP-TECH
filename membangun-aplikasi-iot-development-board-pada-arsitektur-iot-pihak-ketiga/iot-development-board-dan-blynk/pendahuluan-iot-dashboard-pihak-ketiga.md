# Pendahuluan IoT Dashboard Pihak Ketiga

Terdapat banyak macam aplikasi IoT Dashboard dan IoT Server yang dapat dimanfaatkan, misalnya **thingsboard.io**, **thinger.io**, **thingspeak.io**, **blynk**, dan lain-lain. Namun pada bagian ini kita akan membahas bagaimana mengkomunikasikan antara IoT Development dengan IoT Server Blynk.

Konsep *publiser*, *subscriber* dan *broker message* mungkin tidak tampak pada blynk karena segala kerumitan kode program telah dibungkus menjadi *service API (application programming interface)* yang siap digunakan di sisi IoT Development Board.

Terdapat dua sisi blynk yang harus diinstal, yaitu sisi server yang berfungsi sebagai back end dan sisi client yang diinstall pada perangkat mobile (dapat diunduh dari playstore).

Blynk memberi kemudahan dalam mengatur widget untuk memonitor dan mengontrol device (dalam hal ini IoT Development Board). Sebagai referensi silahkan kunjungi dokumentasi blynk di https://docs.blynk.cc

Layanan IoT Server Blynk versi cloud disediakan secara gratis. Adapun keuntungan menggunakan layanan Blynk Cloud, antara lain:
- Kita akan mudah mengaksesnya dimanapun dan kapanpun karena IoT Server Blynk Cloud bersifat publik.
- Kita tidak perlu membangun infrastruktur Blynk yang dibangun karena mereka sudah membuatnya dengan keamanan tinggi tentunya.
- Berbiaya rendah karena layanannya bersifat gratis (pembatasan dibatasi jumlah fiturnya).

Kerugian menggunakan layanan Blynk Cloud, antara lain:
- Memiliki keterbatasan jumlah widget yang bisa dipasang.
- Memiliki keterbatasan jumlah device yang bisa dikomunisikan.
- Kurang memiliki kebebasan dalam mengkonfigurasi server blynk karena posisi kita sebagai client. Ini berarti hanya tersedia satu akun user, yaitu kita saja.
- Untuk memanfaatkan banyak device dan widget harus membeli “Energy”, yaitu semacam deposit voucher yang akan dipotong sesuai pemakaian layanan. Jika Anda membutuhkan lebih banyak widget maka Anda harus membelinya.

Untungnya Blynk berbaik hati karena menyediakan aplikasinya secara gratis, sehingga blynk dapat di-install pada infrastruktur yang kita miliki.

Blynk mendukung banyak smart device, misalnya NodeMCU (ESP8266), Arduino, Raspberry Pi, ARM Mbed dan lain-lain. Silahkan kunjungi link https://github.com/blynkkk/blynkkk.github.io/blob/master/SupportedHardware.md untuk mengetahui lebih detil device yang didukung oleh blynk. Disarankan pula untuk membaca halaman dokumennya di https://docs.blynk.cc yang berisi tata cara instalasi dan konfigurasi server IoT blynk.

Perlu diketahui bahwa server blynk dapat di install pada komputer dan raspberry pi 3B+ (atau seri di atasnya) dengan sistem operasi Linux tentunya.
