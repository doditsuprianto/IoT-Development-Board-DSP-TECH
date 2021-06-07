# Memanfaatkan widget interface Node-Red

Layaknya sebuah IoT platform yang mempermudah pengguna dalam memvisualisaikan atau menyajikan data kepada pengguna, Node-RED juga menyediakan sebuah dashboard agar kita dapat dengan mudah untuk menyajikan data secara live atau real time.

Untuk menggunakan atau membuat tampilan dashhboard menggunakan Node-RED juga sangat mudah, yaitu tinggal melakukan drag and drop pada worksheet untuk setiap komponen.

![https://flows.nodered.org/node/node-red-dashboard](../../.gitbook/assets/dashboard.png)

### Install Dashboard Node-RED

Untuk menggunakan dashboard Node-RED, kita harus install terlebih dahulu modulnya terlebih dahulu. Dapat dilakukan menggunakan 2 cara untuk installasinya, sebagai berikut

* Menggunakan perintah `npm`.

Langkah-langkah yang dapat dilakukan adalah sebagai berikut

1. Masuk ke direktori installasi Node-RED, ketika menggunakan EC2 terdapat di `/home/ubuntu/.node-red`. Jalankan perintah

   `cd /home/ubuntu/.node-red` di EC2 Anda.

2. Selanjutnya jalankan perintah `npm i node-red-dashboard`.

* Menggunakan menu `Manage pallete` pada Node-RED, mengakses Node-RED via browser.

Langkah yang dapat dilakukan adalah sebagai berikut

* Silakan akses Node-RED via browser, misalkan [`http://ec2-52-91-160-126.compute-1.amazonaws.com:1880/`](http://ec2-34-239-124-118.compute-1.amazonaws.com:1880/).
* Klik button yang terdapat di pojok kanan atas dan cari menu `Manage pallete`. Perhatikan gambar di bawah ini

![Manage pallete](../../.gitbook/assets/01.png)

* Sehingga akan muncul jendela `User Settings`, pilih tab `install` dan ketik `dashboard` sehingga akan muncul modul-modul yang bisa kita install dan klik `tombol install`. Untuk lebih jelasnya perhatikan gambar di bawah ini

![Halaman Pallete](../../.gitbook/assets/02.png)

* Akan muncul pop notifikasi proses install seperti gambar di bawah ini, silakan pilih atau klik `tombol install`.

![node-red-dashboard](../../.gitbook/assets/03.png)

* Silakan cek dengan melihat pada Node-RED via browser, seharusnya sudah bertambah komponen-komponen dashboard pada pallete yang terdapat di sebelah kanan. ![](images/04.png)

![](../../.gitbook/assets/05.png)

