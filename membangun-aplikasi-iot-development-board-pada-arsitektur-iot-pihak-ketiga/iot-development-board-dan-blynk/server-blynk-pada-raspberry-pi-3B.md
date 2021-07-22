# Server Blynk Pada Raspberry Pi 3 (atau di atasnya)

Server IoT Blynkk merupakan aplikasi yang cukup "light weight", artinya ringan untuk dijalankan, seklipun menggunakan komputer SoC (single on chip) seperti Raspberry Pi 3B+. Tahapan instalasi dan konfigurasi server blynk serupa dengan contoh sebelumnya. Mungkin yang perlu diperhatikan adalah bagaimana menyiapkan dan menginstall sistem operasi linux pada Raspberry Pi 3b+.

## Kebutuhan Hardware & Software IoT Server Blynk
Server IoT Blynk tergolong aplikasi ringan, sehingga blynk dapat diinsntal pada Raspberry Pi 3 yang sumberdayanya rendah.

Adapun kebutuhan hardware dan software dalam projek ini antara lain: 
- Komputer Raspberry Pi 3 Model B atau B+ (dikenal juga istilah SoC – system on chip) 
- MicroSD minimal 8/16 GB, sebagai tempat penyimpanan sistem operasi linux dan aplikasi IoT Server Blynk. Sebaiknya gunakan MicroSD class 10 karena berpengaruh pada kecepatan proses.
- Adapter MicroSD ke USB atau MicroSD ke SD-Card, tergantung kebutuhan.
- Adaptor tegangan 5 Volt, arus minimal 2 Amper sebagai power supply Raspberry PI 3

![](../images/maidbpaipk20.JPG)

- File image Raspbian 2020-02-13-raspbian-buster-full.zip yang akan diinstal pada Raspberry Pi 3 sebagai sistem operasi linux raspbian. Versi sistem operasi tidak harus sama. Anda dapat men-download-nya di https://www.raspberrypi.org/downloads/raspbian/, khususnya https://downloads.raspberrypi.org/raspbian_full_latest

Anda harus mengekstrak terlebih dahulu file .ZIP tersebut menjadi file .IMG.

![](../images/maidbpaipk21.JPG)

- SDFormatter, yaitu aplikasi untuk mem-format MicroSD sebelum dilakukan burning sistem operasi. File di-download di https://www.sdcard.org/downloads/formatter/eula_windows/.

![](../images/maidbpaipk22.JPG)

- Balena Etcher, yaitu aplikasi untuk mem-burning image Linux Raspbian ke dalam MicroSD. Etcher dapat di-download di https://www.balena.io/etcher/.

![](../images/maidbpaipk23.JPG)

## Software SDCard Formatter
Ekstrak file **SDCardFormatterv5_WinEN.zip** yang telah di-download. Jalankan file SD Card Formatter 5.0.1 Setup.exe. Kemudian ikuti tahapan instalasinya sampai selesai.

![](../images/maidbpaipk24.JPG)

![](../images/maidbpaipk25.JPG)

![](../images/maidbpaipk26.JPG)

![](../images/maidbpaipk27.JPG)

![](../images/maidbpaipk28.JPG)

![](../images/maidbpaipk29.JPG)

## Software Balena Etcher
Jalankan file **balenaEtcher-Setup-1.5.79.exe** dari windows explorer. Nama file yang di-download mengikuti update versinya sehingga tidak harus sama dengan yang tertera dalam tulisan buku.

![](../images/maidbpaipk30.JPG)

![](../images/maidbpaipk31.JPG)

![](../images/maidbpaipk32.JPG)

## Format Memori microSD

Masukkan MicroSD + Adapter ke USB komputer atau SD Card Reader komputer, kemudian jalankan aplikasi SD Card Formatter. Sebelum memformat, pastikan lokasi drive MicroSD sudah benar agar tidak terjadi salah format. Pilih Quick format pada Formatting options.

![](../images/maidbpaipk33.JPG)

![](../images/maidbpaipk34.JPG)

![](../images/maidbpaipk35.JPG)

![](../images/maidbpaipk36.JPG)

## Burning Image Linux Raspbian Ke MicroSD
- Masukkan MicroSD + Adapter ke USB komputer atau SD Card Reader komputer.
- Jalankan aplikasi balenaEtcher. Di sini MicroSD akan terdeteksi secara otomatis oleh Balena Etcher tanpa perlu memilih tombol Select Drive.
- Pilih tombol Select Image, kemudian pilih file image 2020-02-13-raspbian-buster-full.img.
- Pilih tombol Flash untuk mem-burning image Linux Raspbian ke dalam MicroSD.

![](../images/maidbpaipk37.JPG)

![](../images/maidbpaipk38.JPG)

![](../images/maidbpaipk39.JPG)

![](../images/maidbpaipk40.JPG)

![](../images/maidbpaipk41.JPG)

Jika proses burning Raspbian selesai, namun Anda diminta untuk mem-format drive microSD maka abaikan saja, jangan di-format!

![](../images/maidbpaipk42.JPG)

## Instalasi Linux Raspbian Pada Raspberry Pi 3

Berikut ini tahapan instalasi Linux Raspbian ke Raspberry Pi 3:
- Lepas MicroSD dari adapternya setelah diburning dengan Linux Raspbian.
- Pasang memori MicroSD ke slot MicroSD Raspberry Pi 3. 
- Pasang keyboard USB dan mouse USB ke Raspberry Pi 3.
- Hubungkan jack VGA HDMI Raspberry Pi 3 ke monitor (gunakan adapter VGA jika diperlukan). Monitor hanya digunakan saat proses instalasi, setelah itu kita dapat mengkonfigurasi Raspbian dengan aplikasi remote Putty melalui jaringan komputer.
- Hubungkan Adaptor ke Raspberry Pi 3 untuk menghidupkannya.

Ketika power supply dihidupkan maka Raspberry Pi 3 akan melakukan booting dan instalasi awal. Selanjutnya kuti langkah-langkahnya berikut ini:

![](../images/maidbpaipk43.JPG)

![](../images/maidbpaipk44.JPG)

![](../images/maidbpaipk45.JPG)

![](../images/maidbpaipk46.JPG)

![](../images/maidbpaipk47.JPG)

![](../images/maidbpaipk48.JPG)

![](../images/maidbpaipk49.JPG)

![](../images/maidbpaipk50.JPG)

![](../images/maidbpaipk51.JPG)

Untuk memudahkan proses instalasi Blynk, gunakan aplikasi remote SSH Putty. Tujuannya untuk mengendalikan Raspberry Pi 3 secara jarak jauh. Oleh karena itu aktifkan terlebih dahulu service SSH server pada Raspberry Pi 3 dengan cara buka aplikasi console/terminal dengan menggunakan perintah

```cpp
sudo raspi-config
```
![](../images/maidbpaipk52.JPG)

Dari sini akan muncul windows daftar layanan, pilih **Interfacing Options**, kemudian pilih tombol **Select**.

![](../images/maidbpaipk53.JPG)

![](../images/maidbpaipk54.JPG)

![](../images/maidbpaipk55.JPG)

Karena aplikasi remote membutuhkan IP tujuan untuk dikoneksikan, yaitu alamat IP Raspberry Pi 3, maka silahkan buka console Raspberry Pi 3, kemudian gunakan perintah.

```cpp
ifconfig
```

![](../images/maidbpaipk56.JPG)

Diasumsikan Raspberry Pi 3 telah terhubung dengan access point sehingga Raspberry Pi 3 akan mendapatkan alamat IP dinamis dari router. Sebagai contoh alamat IP 192.168.1.6. Bisa jadi IP Anda akan berubah tergantung dari pemberian alamat IP oleh router Anda.

Untuk membuktikan apakah Raspberry Pi 3 dapat di-remote dari laptop, pertama download terlebih dahulu aplikasi putty di :
- https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html
- https://the.earth.li/~sgtatham/putty/latest/w64/putty-64bit-0.73-installer.msi (64bit) 
- https://the.earth.li/~sgtatham/putty/latest/w32/putty-0.73-installer.msi (32bit).

Selanjutnya instal putty dan buka aplikasinya.

![](../images/maidbpaipk57.JPG)

![](../images/maidbpaipk58.JPG)

Login default Raspberry Pi 3 adalah "pi", sedangan password-nya sama dengan password ketika Anda menginstal Raspberry Pi 3 pertamakali.

Dari sini sudah dapat me-remote Raspberry Pi 3 dari laptop.

![](../images/maidbpaipk59.JPG)

## Instalasi Server IoT Blynk

Langkah berikutnya adalah instalasi Server IoT Blynk. Anda dapat mengkonfigurasinya secara langsung melalui console/shell Raspberry Pi 3 atau melalui aplikasi putty secara remote.

Blynk membutuhkan java dalam pengoperasiannya, sehingga pastikan Raspberry Pi 3 telah diinstall dengan java. Untuk mengetahuinya gunakan perintah java -version. Bila menggunakan aplikasi putty tampak seperti ini:

![](../images/maidbpaipk60.JPG)

Bila menggunakan console Raspberry Pi 3 akan tampak seperti ini:

![](../images/maidbpaipk61.JPG)

Bila muncul pesan sperti di bawah ini, berarti Raspberry Pi 3 telah terinstal java.

```cpp
openjdk version "11.0.6" 2020-01-14
OpenJDK Runtime Environment (build 11.0.6+10-post-Raspbian-1deb10u1)
OpenJDK Server VM (build 11.0.6+10-post-Raspbian-1deb10u1, mixed mode)
```

Namun bila tampak pesan seperti tampak di bawah ini, berarti java belum terinstal. Silahkan instal java terlebih dahulu dengan perintah

```cpp
sudo apt install default-jre
```

atau

```cpp
sudo apt-get install default-jdk
```

![](../images/maidbpaipk62.JPG)

Selanjutnya adalah membuat folder dimana aplikasi Blynk akan diinstall. Gunakan perintah mkdir blynk yang berarti membuat folder bernama "blynk". Kemudian buat folder baru lagi bernama "**server_data**" di dalam folder blynk sebagai tempat penyimpanan data Blynk. Berikut perintah lengkapnya:

```cpp
pi@raspberrypi:~ $ mkdir blynk
pi@raspberrypi:~ $ cd blynk
pi@raspberrypi:~/blynk $ mkdir server_data
```

![](../images/maidbpaipk63.JPG)

![](../images/maidbpaipk64.JPG)

![](../images/maidbpaipk65.JPG)

Masih berada di dalam folder "blynk", kita akan meng-install aplikasi IoT Server Blynk dengan cara meng-cloning file Blynk dari repository github ke Raspberry Pi 3. Untuk mengetahui release Blynk versi terbaru, silahkan kunjungi halaman ini https://github.com/blynkkk/blynk-server/releases.

![](../images/maidbpaipk66.JPG)

Perintah untuk meng-clone aplikasi Server IoT blynk dari github adalah sebagai berikut:

```cpp
wget https://github.com/blynkkk/blynk-server/releases/download/v0.41.12/server-0.41.12-java8.jar
```

![](../images/maidbpaipk67.JPG)

![](../images/maidbpaipk68.JPG)

![](../images/maidbpaipk69.JPG)

![](../images/maidbpaipk70.JPG)

Selanjutnya, untuk mengaktifkan Server IoT Blynk gunakan perintah:

```cpp
java -jar server-0.41.12-java8.jar -dataFolder server_data &
```

![](../images/maidbpaipk71.JPG)

Jika muncul pesan seperti di atas maka Server IoT Blynk telah aktif dan siap digunakan.

![](../images/maidbpaipk72.JPG)

Anda bisa menggunakan browser internet untuk mengadministrasi user, mengkonfigurasi, dan lain-lain melalui halaman Dashboard Blynk, baik secara lokal di Raspberry Pi 3 itu sendiri atau melalui komputer lain dalam satu jarignan. 

Berikut ini cara untuk membuka halaman Dashboard Blynk secara remote. Dimana saya menggunakan browser internet Opera. 
- Alamat URL secara remote: https://192.168.1.6:9443/admin 
- Alamat URL secara lokal: https://127.0.0.1:9443/admin
- User admin Blynk default: admin@blynk.cc 
- Password admin Blynk default: admin.

> Note. User dan password admin dapat diubah melalui Dashboard Blynk. Tetapi untuk saat ini kita biarkan menggunakan user dan pasword default.

![](../images/maidbpaipk73.JPG)

![](../images/maidbpaipk74.JPG)

Tampilan di bawah ini merupakan user yang telah terdaftar dalam Server IoT Blynk. User yang dimaksud adalah user yang memiliki terasosiasi dengan smart devic. Satu user bisa memiliki beberapa smart device. Namun untuk saat ini belum ada user yang terdaftar kecuali Admin. Hal ini akan kita bahas dibagian selanjutnya.

![](../images/maidbpaipk75.JPG)