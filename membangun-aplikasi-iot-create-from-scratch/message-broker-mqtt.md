---
description: Instalasi & konfigurasi Message Broker secara lokal (laptop/PC)
---

# Message Broker MQTT

### Pengantar

Seperti dijelaskan pada bagian sebelumnya, bahwa di dalam konsep _client-server_, message broker merupakan entitas tersendiri yang berjalan pada protokol TCP/IP, ia bertindak sebagai _server message_ yang melayani _client message_ dengan konsep _publish/subscribe_ dan _topic_. 

![Arsitektur Message Broker Secara Umum](../.gitbook/assets/mqtt_broker.png)

![Arsitektur Message Broker Pada Cloud AWS](../.gitbook/assets/schema-how-to-bridge-mosquitto-to-aws-iot-core.png)

Di beberapa jenis produk message broker disertai dengan mekanisme routing queue \(antrian\) dengan berbagai jenis model broadcast message seperti yang terdapat pada [RabbitMQ](https://www.rabbitmq.com).

![Arsitektur Message Broker Pada MQTT](../.gitbook/assets/exchanges-topic-fanout-direct.png)

Terdapat beberapa protokol message broker yang bisa digunakan, misalnya AMQP, CoAP, EMQ, MQTT dan lain-lain. Namun pada kesempatan ini kita akan menggunakan message broker MQTT, dimana secara defacto message broker MQTT banyak diimplementasikan pada saat ini.

### Instalasi Message Broker MQTT Mosquitto

Pada bagian ini kita akan menginstalasi dan mengkonfigurasi message broker MQTT dengan konfigurasi minimal. Salah satu message broker MQTT yang populer adalah Mosquitto. Anda dapat men-downloadnya di [https://mosquitto.org/download/](https://mosquitto.org/download/) atau [download di sini](https://drive.google.com/file/d/10fGD8_2RmLTw9uk5Ij5C385gFCZlJKaO/view?usp=sharing).

![Download File Mosquitto](../.gitbook/assets/1a.png)

Pilih file mosquitto yang sesuai dengan mesin Anda untuk di-download

![Klik dua kali pada file mosquitto-2.0.10-install-windows-x64](../.gitbook/assets/1%20%288%29.png)

Lakukan instalasi message broker MQTT Mosquitto sesuai tahapan berikut

![Pilih tombol Next](../.gitbook/assets/2%20%285%29.png)

![Pilih tombol Next](../.gitbook/assets/3%20%2810%29.png)

![Sesuaikan penempatan path bila perlu, kemudian klik tombol Next](../.gitbook/assets/4%20%287%29.png)

![Pilih tombol Finish](../.gitbook/assets/5%20%286%29.png)

Lakukan pengujian apakah Mosquitto telah terinstall dan berfungsi benar, dengan cara  masuk ke window command sebagai Administrator

![Masuk Command sebagai Administrator](../.gitbook/assets/6%20%285%29.png)

Kemudian jalankan service message broker MQTT Mosquitto dengan perintah berikut **net start mosquitto**. Jika diperoleh pesan "_**The Mosquitto service was started successfully**_", berarti instalasi mosquitto sukses dan siap digunakan.

![](../.gitbook/assets/7%20%285%29.png)

### Instalasi Aplikasi MQTT Client Tools

Aplikasi MQTT Client Tools berguna untuk menguji apakah transmisi data \(baik publisher /subscriber dan topic\) antara device dan message broker bekerja dengan benar. Hal ini akan mempersempit tingkat kesalahan bila arsitektur yang dibangun melibatkan perangkat embedded system. 

Ada 2 aplikasi MQTT Client Tools yang direkomendasikan, yaitu:

* **MQTTBox**, silahkan download [MQTTBox di sini](https://drive.google.com/file/d/1JysiDtmRBNcoarwzurwLZcEnK6EBL42D/view?usp=sharing)
* **MQTT Explorer**, silahkan download MQTT Explorer di [http://mqtt-explorer.com](http://mqtt-explorer.com) atau [download di sini](https://drive.google.com/file/d/1i3yJb8TOqqeSdqwzH8wo_vV8nm7oLolF/view?usp=sharing).

#### Instalasi & Konfigurasi MQTT Explorer

Saya asumsikan bahwa file diperleh dari [http://mqtt-explorer.com](http://mqtt-explorer.com) maka tahap instalasinya adalah sebagai berikut

![Download MQTT Explorer](../.gitbook/assets/8%20%283%29.png)

![Klik 2x pada file MQTT Explorer](../.gitbook/assets/9%20%283%29.png)

![Proses Instalasi MQTT Explorer](../.gitbook/assets/10%20%284%29.png)

Buat koneksi baru antara MQTT Explorer dan Message Broker Mosquitto dengan kofigurasi berikut:

* Name : MQTT Local Host
* Protocol: mqtt://
* Host: localhost
* Port: 1883 \(default\)
* Username: &lt;kosong&gt;
* Password: &lt;kosong&gt;

Kemudian klik tombol CONNECT untuk memastikan koneksi dengan mosquito terjalin. Jika tidak ada masalah lanjutkan dengan klik tombol SAVE.

![Konfigurasi MQTT Explorer dengan Mosquitto Lokal Server](../.gitbook/assets/11%20%284%29.png)

![MQTT Explorer  Terhubung Dengan Mosquitto](../.gitbook/assets/12%20%283%29.png)

#### Instalasi & Konfigurasi MQTTBox

Instalasi dan konfigurasi MQTTBox serupa dengan cara sebelumnya

![Klik 2x pada file MQTTBox-win](../.gitbook/assets/13a.png)

![Proses Instalasi](../.gitbook/assets/13%20%283%29.png)

![Membuat Koneksi ke Mosquitto, Klik tombol &quot;Create MQTT Client&quot;](../.gitbook/assets/14aa.png)

Isikan konfigurasi MQTTBox, kemudian klik tombol **Save**.

* MQTT Client Name: MQTT Broker Workshop
* Protocol: mqtt/tcp
* Host: localhost:1883
* Username: &lt;kosong&gt; default
* Password: &lt;kosong&gt; default

![](../.gitbook/assets/14%20%281%29.png)

Jika tidak terjadi masalah koneksi dengan mosquitto berarti semua berjalan normal. 

### Konfigurasi User & Password Akses Message Broker Mosquitto

Pada bagian ini kita akan mengkonfigurasi message broker mosquitto dengan tambahan keamanan user dan password. Serta konfigurasi agar message broker mosquitto dapat diakses remote oleh perangkat jarak jauh pada jaringan lokal.

Buka aplikasi editor Notepad++ sebagai Administrator untuk membuat user dan password untuk di hashing.

![Membuka aplikasi Notepad++ sebagai Administrator](../.gitbook/assets/14b.png)

Buat teks berisi user:password misalnya **AdminMQTT:pwd123**, kemudian simpan file tanpa disertai tipe file dengan nama **password**. Dalam kasus komputer saya, letakkan file di **C:\Program Files\mosquitto**

![Buat file password yang berisi user:password](../.gitbook/assets/15%20%281%29.png)

![Simpan file password](../.gitbook/assets/16%20%281%29.png)

Lakukan hashing terhadap file password tersebut dengan perintah pada command **mosquitto\_passwd -U password**. Parameter "password" yang terakhir adalah nama file yang dibuat sebelumnya.

![Hashing password dari file password](../.gitbook/assets/17%20%281%29.png)

Untuk membuktikann apak password telah di-hashing, silahkan buka kembali file **password** yang berada di C:\Program Files\mosquitto dengan editor Notepad++.

![Membuka file password](../.gitbook/assets/18%20%281%29.png)

![Hasil Hashing password Mosquitto](../.gitbook/assets/19%20%281%29.png)

Pengujian akses service message broker mosquitto dengan user dan password dengan cara mengubah konfigurasi koneksi pada MQTTBox. Isikan parameter berikut:

* Host: localhost:1883 atau 192.168.0.101:1883
* Username: AdminMQTT
* Password: pwd123

![Akses mosquitto dengan user, password dan localhost](../.gitbook/assets/20%20%281%29.png)

Anda juga mengakses service message broker mosquitto menggunakan host alamat IP, dalam hal ini adalah 192.168.0.101

![Akses mosquitto dengan user, password dan ip:192.168.0.101:1883](../.gitbook/assets/20a%20%281%29.png)

Jika koneksi antara MQTT Client \(MQTTBox\) dan MQTT Broker \(mosquitto\), saatnya sekarang membuat entitas publisher yang dibernama **dht**. kolom payload adalahdata yang dikirk ke message broker mosquitto.

![Menambahkan Publisher](../.gitbook/assets/20b.png)

Subscriber adalah sisi yang meminta me-_request_ data ke publisher, tentunya melalui jembatan message broker yang bertindak sebagai manajer lalu lintas data antara subscriber dan publisher. 

Nama topic antara subscriber dan publisher harus sesuai agar komunikasi keduanya bisa terjalin. Sebagai contoh nama topic subsciber adalah **dht** \(sama dengan topic pada publisher\).

![Menambahkan Subscriber](../.gitbook/assets/20c.png)

Ketika tombol publish dipilih, maka data pada kolom payload akan dikirim ke subscriber dengan topic dht.

![Hasil komunikasi antara publisher dan subscriber](../.gitbook/assets/20d.png)

### Konfigurasi Akses Service Message Broker Mosquitto Secara Remote

Banyak kasus ditemui bahwa komunikasi antara Client MQTT dan Broker MQTT berada pada mesin berbeda. Misalnya sisi client menggunakan perangkat Embedded System, sedangkan Message Broker berada di laptop. 

Di sini kita perlu mengkonfigurasi MQTT Message Broker Mosquitto terlebih dahulu agar dapat diakses oleh client-client secara remote dalam satu network.

#### Konfigurasi File mosquitto.conf

Pertama dilakukan adalah mengkonfigurasi file **mosquitto.conf** yang berada di folder **C:\Program Files\mosquitto** dengan aplikasi editor Notepad++.

![Buka file konfigurasi mosquitto.conf](../.gitbook/assets/22%20%281%29.png)

Cek alamat IP komputer lokal Anda dimana aIP Listener Message Broker Mosquitto berada. Gunakan perintah **ipconfig** pada window command yang akan bertindak. Dalam kasus laptop saya adalah 192.168.0.101.

![Melihat alamat IP Mosquitto](../.gitbook/assets/22a.png)

Selanjutnya lakukan perubahan terhadap 4 parameter pada **mosquitto.conf**:

* listener 1883 192.168.0.101 
* listener 1883 localhost 
* protocol mqtt 
* allow\_anonymous false 
* password\_file C:\Program Files\mosquitto\password

![Salah satu contoh perubahan paramater konfigurasi mosquitto](../.gitbook/assets/23.png)

Menghentikan dan me-restart ulang service message broker dengan command sebagai berikut:

* net stop mosquitto 
* net start mosquitto

![Stop dan start service message broker mosquitto](../.gitbook/assets/24.png)

#### Firewall Rule Aplikasi mosquitto.exe

Tujuan konfigurasi firewall dengan rule aplikasi agar layanan message broker mosquitto tidak diblokir oleh firewall windows defender.

![Buka service firewall dengan menuliskan firewall.cpl](../.gitbook/assets/26.png)

![Pilih menu Allow an app or feature through Windows Defender Firewall](../.gitbook/assets/27.png)

![Pilih button Allow another app](../.gitbook/assets/28.png)

![Pilih tombol Browse untuk memilih aplikasi mosquitto](../.gitbook/assets/29.png)

![Pilih file mosquitto pada C:\Program Files\mosquitto](../.gitbook/assets/30%20%281%29.png)

![Setelah masuk daftar pilih tombol OK](../.gitbook/assets/31.png)

#### Firewall Rule Port

Konfigurasi firewall dengan rule port bertujuan agar firewall windows defender memberi izin message broker mosquitto dengan port 1883 dapat diakses dari luar.

Terdapat dua jenis rule port yang harus dikofigurasi, yaitu:

* Port - Inbound Rule
* Port - Outbound Rule

**Konfigurasi Port Inbound Rule**

![Buka layana firewall](../.gitbook/assets/32.png)

![Pilih Inbound Rules dan New Rules](../.gitbook/assets/33.png)

![Pilih Port kemudian klik tombol Next](../.gitbook/assets/34%20%281%29.png)

![Pilih Specific local Port dan isikan 1883](../.gitbook/assets/35.png)

![Pilih Allow the connection](../.gitbook/assets/36%20%281%29.png)

![Beri tanda centang pada semua pilihan](../.gitbook/assets/37%20%281%29.png)

![Beri nama rule dan sertakan deksripsi rule](../.gitbook/assets/38.png)

**Konfigurasi Port Outbound Rule**

Dengan cara serupa dengan inbound rule, ikuti langkah-langkah berikut untuk membentuk port outbound rule

![Konfigurasi port outbound rule](../.gitbook/assets/39%20%281%29.png)

![Pilih Port](../.gitbook/assets/40.png)

![Menentukan port 1883](../.gitbook/assets/41.png)

![Mengizinkan semua koneksi untuk port 1883](../.gitbook/assets/42.png)

![Mengaplikasikan izin port 1883 untuk domain, private, dan public](../.gitbook/assets/43.png)

![Memberi nama rule dan deskripsi rule](../.gitbook/assets/44.png)

### Mengakses Message Broker Secara Remote

Setelah semua konfigurasi dijalankan, saatnya kita menguji coba message broker secara remote. Sebagai bahan percobaan akan kita gunakan aplikasi Android MQTT Client bernama **MyMQTT**. Silahkan download aplikasi tersebut  melalui Google Play Store.

![](../.gitbook/assets/1-whatsapp-image-2021-06-08-at-7.34.31-pm.jpeg)

Sesuaikan konfigurasi koneksi pada MyMQTT, dimana alamat IP Message Broker adalah **192.168.0.101**. Hal ini tentu harus disesuaikan dengan alamat IP Anda masing-masing. 

Sesuaikan dengan nama user dan password message broker dengan setting sebelumnya, dimana user adalah **AdminMQTT** dan password adalah **pwd123**.

![Pilih menu Settings](../.gitbook/assets/4a-whatsapp-image-2021-06-08-at-7.34.31-pm.jpg)

![Konfigurasi Koneksi](../.gitbook/assets/3-whatsapp-image-2021-06-08-at-7.34.31-pm.jpeg)

Setelah memilih tombol Save akan muncul notifikasi bahwa koneksi sukses, artinya koneksi antara MyMQTT Android dan Message Broker Mosquitto sukses terjalin.

Selanjutnya pilih menu publish, yang akan mengirim data \(payload\) dari MyMQTT Android ke message broker mosquitto.

![](../.gitbook/assets/4-whatsapp-image-2021-06-08-at-7.34.31-pm.jpeg)

Sebagai contoh, kita akan mengirim data string "**kirim dari andoid**", kemudian pilih tombol Publish.

![](../.gitbook/assets/5-whatsapp-image-2021-06-08-at-7.34.30-pm.jpeg)

Sekarang cek kembali MQTT client pada MQTTBox. Pada bagian box Subscriber dengan topic **dht** akan diterima data string berupa tulisan "kirim dari Android".

![](../.gitbook/assets/45.png)

Sampai di sini kita telah memahami bagaimana cara mengkomunikasikan antara MQTT Client dan MQTT Broker, bagaimana teknik instalasi dan konfigurasi message broker, baik bekerja secara lokal maupun remote, bagaimana cara kerja subscriber dan publisher, dan topic.

> Untuk mengkases message broker secara remote, pastikan bahwa perangkat antara message broker dan perangkat message client berada dalam satu network.

