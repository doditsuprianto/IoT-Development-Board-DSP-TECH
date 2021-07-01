---
description: Kendali microcontroller degnan cara primitive melalui SOCKET
---

# Kendali Jarak Jauh Menggunakan Protokol SOCKET TCP/IP

Pada bagian ini akan dipelajari bagaiamana mengkomunikasikan antara "IoT Development Board" dan berbagai Aplikasi dengan platform berbeda.

Komunikasi antara keduanya dijalin menggunakan Socket TCP yang masih keluarga dari protokol tranport http. Komunikasi ini tergolong tradisional karena belum menerapkan konsep manajemen pesan seperti broker message pada protokol MQTT. Namun socket TCP sampai saat ini masih sering digunakan untuk berbagai jenis keperluan, dimana sumberdaya tidak menjadi masalah karena kita ketahui bahwa protokol aplikasi http memiliki overhead sumberdaya yang cukup besar.

Diasumsikan bahwa Anda telah memahami konsep dasar jaringan komputer, termasuk routing jika diperlukan. Semuanya mengacu pada protokol network model TCP/IP.

Anda diharapkan telah menguasai bahasa pemrograman C#, Java dan Android, karena kita tidak mungkin membahas setiap bahasa pemrograman dalam tutorial ini.

## Pemrograman Socket TCPPemrograman Socket TCP
Pemrograman socket adalah cara menghubungkan dua node pada jaringan untuk berkomunikasi satu sama lain. Satu socket (node) mendengarkan pada port tertentu di sebuah IP, sementara socket lainnya menjangkau yang lain untuk membentuk koneksi. Server membentuk socket listener (pendengar) sementara klien menjangkau server.

Cara kerja socket dapat dijelaskan sebagai berikut: Panggilan sistem **socket()** membuat socket baru. Di sisi server, **bind()** digunakan untuk mengasosiasikan socket dengan salah satu alamat IP server dan nomor port yang akan didengarkan. Ketika ini selesai, socket diaktifkan dengan panggilan sistem **Listen()**.

![Arsitektur Coket TCP](https://www.it.uu.se/education/course/homepage/dsp/vt19/images/module-2/tcp-socket.png "Arsitektur Coket TCP")

Panggilan sistem **accept()** memblokir hingga klien terhubung (menggunakan **connect()** pada akhirnya). Setelah ini, data dapat dikirim dan diterima menggunakan dalam contoh ini **send()** dan **recv()** **(write()** dan **read()** juga akan berfungsi).

Perhatikan bahwa setelah koneksi dibuat, tidak ada perbedaan khusus antara *peers* dengan sebelum koneksi ketika satu menunggu koneksi dari yang lain. Kedua ujung dapat mengirim dan menerima data dalam urutan apa pun; prosedur yang tepat tentang bagaimana hal ini dilakukan biasanya ditentukan oleh protokol level aplikasi apa yang digunakan. Sebagai contoh, jika server adalah server web dan klien adalah browser web, biasanya klien mengirimkan permintaan (*request*) dan server meresponsnya (*response*) sesuai dengan protokol HTTP.

Ketika salah satu node ingin mengakhiri koneksi, ia menggunakan **close**, yang akan memulai jabat tangan tiga arah (kosep *three way handshaking*) untuk penghentian koneksi.

Langkah-langkah untuk membuat socket TCP di sisi klien:
- Buat socket menggunakan fungsi socket();
- Hubungkan socket ke alamat server menggunakan fungsi connect();
- Mengirim dan menerima data melalui fungsi read() dan write().
- Tutup koneksi dengan menggunakan fungsi close().

Langkah-langkah dalam membangun socket TCP di sisi server:
- Buat socket dengan fungsi socket();
- Ikat socket ke alamat menggunakan fungsi bind();
- Dengarkan koneksi dengan fungsi listening();
- Terima koneksi dengan panggilan sistem fungsi accept(). Panggilan ini biasanya memblokir hingga klien terhubung dengan server.
- Mengirim dan menerima data melalui kirim() dan terima().
- Tutup koneksi dengan menggunakan fungsi close().

Agar tidak timbul pemblokiran telalu lama oleh server ketika klien berusaha menjalin koneksi dengannya, namun karena terkendala suatu hal maka sistem (disediakan oleh API Socket) memberi batas waktu tertentu untuk putus dengan sendirinya (fungsi timeout).  Sehingga ketika klien lain berusaha untuk menjalin hubungan dengan server dapat melakukannya.

Optimasi lain yang dapat dilakukan oleh socket adalah dengan menggunakan **thread**, yaitu kemampuan untuk membagi kerja secara paralel antara server-socket dengan banyak client-socket. Otomatis hal ini akan mengurangi antrian request dari klien ke server karena job/task dapat ditangani secara bersamaan. Istilah ini disebut degnan **asynchrouns socket**, sedangkan request klien yang dilaksanakan satu per satu oleh server dan tidak akan berpindah ke request klien lainnya selama request pertama belum selesai disebut dengan synchrounus socket.

Berikut beberapa referensi tentang model client-server Socket TCP/IP yang layak menjadi sumber bacaan:
- https://users.cs.duke.edu/~chase/cps196/slides/sockets.pdf
- https://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf
- https://www.cs.dartmouth.edu/~campbell/cs60/socketprogramming.html

