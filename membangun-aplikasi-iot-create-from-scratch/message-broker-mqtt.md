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

#### MQTT Explorer

Saya asumsikan bahwa file diperleh dari [http://mqtt-explorer.com](http://mqtt-explorer.com) maka tahap instalasinya adalah sebagai berikut

![Download MQTT Explorer](../.gitbook/assets/8%20%283%29.png)

![Klik 2x pada file MQTT Explorer](../.gitbook/assets/9%20%283%29.png)

![Proses Instalasi MQTT Explorer](../.gitbook/assets/10%20%284%29.png)

![Sampai di sini instalasi MQTT Explorer sukses](../.gitbook/assets/11%20%281%29.png)



