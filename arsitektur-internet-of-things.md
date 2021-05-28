# Arsitektur Internet of Things

### **Building Block Internet of Things**

Seperti yang diulas pada bab 1, Internet of Things \(IoT\) adalah jaringan perangkat yang dapat merasakan, mengakumulasi, dan mentransfer data melalui internet tanpa campur tangan manusia.

Apa yang membuat perangkat seperti hidup? Mereka bisa merasakan dan berkomunikasi satu sama lain. Bayangkan jika benda mati bisa merasakan dan berinteraksi satu sama lain tanpa campur tangan manusia tentu hal itu menakjubkan. Ini adalah konsep yang mendasari Internet of Things.

Sekarang Anda mungkin telah memahami bahwa IoT bukan hanya perangkat konsumen yang terhubung ke Internet. Faktanya, IoT adalah teknologi yang membangun sistem yang mampu merasakan dan merespons rangsangan secara mandiri dari dunia nyata tanpa campur tangan manusia. Oleh karena itu, kami perlu mengembangkan aliran proses untuk kerangka kerja yang pasti dimana solusi IoT dibangun.

#### Arsitektur IoT umumnya terdiri dari 4 tahap berikut:

![IoT Architecture Building Block \(Sumber: https://www.edureka.co/blog/what-is-iot/\)](.gitbook/assets/0%20%283%29.png)

* **Tahap 1 \(Sensor / Aktuator\):**

Suatu hal dalam konteks “Internet of Things”, harus dilengkapi dengan sensor dan aktuator sehingga memberikan kemampuan untuk memancarkan, menerima dan memproses sinyal.

* **Tahap 2 \(Sistem Akuisisi Data / Data Acquition Systems\):**

Data dari sensor dimulai dalam bentuk analog yang perlu dikumpulkan dan diubah menjadi aliran digital untuk diproses lebih lanjut. Sistem akuisisi data melakukan fungsi agregasi dan konversi data ini.

* **Tahap 3 \(Analisis Tepi / Edge Analytics\):**

Setelah data IoT diubah menjadi digital dan dikumpulkan, mungkin diperlukan pemrosesan lebih lanjut sebelum memasuki pusat data, di sinilah Edge Analytics masuk.

* **Tahap 4 \(Cloud Analytics\):**

Data yang membutuhkan pemrosesan lebih mendalam diteruskan ke pusat data fisik atau sistem berbasis cloud.

### **MQTT Messaging Protocol**

Tabel di bawah ini merupakan beberapa spesifikasi protokol pesan yang umum diterapkan pada platrform Internet of Things

<table>
  <thead>
    <tr>
      <th style="text-align:left"></th>
      <th style="text-align:left"><b>DDS</b>
      </th>
      <th style="text-align:left"><b>AMQP</b>
      </th>
      <th style="text-align:left"><b>CoAP</b>
      </th>
      <th style="text-align:left"><b>MQTT</b>
      </th>
      <th style="text-align:left"><b>REST /HTTP</b>
      </th>
      <th style="text-align:left"><b>XMP</b>
      </th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align:left"><b>Transport</b>
      </td>
      <td style="text-align:left">
        <p>UDP/IP</p>
        <p>(unicast + multicast)</p>
        <p>TCP/IP</p>
      </td>
      <td style="text-align:left">
        <p>TCP/</p>
        <p>IP</p>
      </td>
      <td style="text-align:left">
        <p>UDP/</p>
        <p>IP</p>
      </td>
      <td style="text-align:left">
        <p>TCP/</p>
        <p>IP</p>
      </td>
      <td style="text-align:left">TCP/IP</td>
      <td style="text-align:left">
        <p>TCP/</p>
        <p>IP</p>
      </td>
    </tr>
    <tr>
      <td style="text-align:left"><b>Interaction Model</b>
      </td>
      <td style="text-align:left">
        <p>Publish-and-Subscribe,</p>
        <p>Request-Replay</p>
      </td>
      <td style="text-align:left">Point-to-Point Message Exchange</td>
      <td style="text-align:left">Request-Replay (REST)</td>
      <td style="text-align:left">Publish-and-Subscribe</td>
      <td style="text-align:left">Request-Replay</td>
      <td style="text-align:left">Point-to-Point Message Exchange</td>
    </tr>
    <tr>
      <td style="text-align:left"><b>Scope</b>
      </td>
      <td style="text-align:left">
        <p>Device-to-Device</p>
        <p>Device-to-Cloud</p>
        <p>Cloud-to-Cloud</p>
      </td>
      <td style="text-align:left">
        <p>Device-to-Device</p>
        <p>Device-to-Cloud</p>
        <p>Cloud-to-Cloud</p>
      </td>
      <td style="text-align:left">Device-to-Device</td>
      <td style="text-align:left">
        <p>Device-to-Cloud</p>
        <p>Cloud-to-Cloud</p>
      </td>
      <td style="text-align:left">
        <p>Device-to-Cloud</p>
        <p>Cloud-to-Cloud</p>
      </td>
      <td style="text-align:left">
        <p>Device-to-Cloud</p>
        <p>Cloud-to-Cloud</p>
      </td>
    </tr>
    <tr>
      <td style="text-align:left"><b>Automatic Discovery</b>
      </td>
      <td style="text-align:left">&#x221A;</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">&#x221A;</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
    </tr>
    <tr>
      <td style="text-align:left"><b>Content Awareness</b>
      </td>
      <td style="text-align:left">
        <p>Content-based</p>
        <p>Routing Queries</p>
      </td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
    </tr>
    <tr>
      <td style="text-align:left"><b>QoS</b>
      </td>
      <td style="text-align:left">Extensive (20+)</td>
      <td style="text-align:left">Limited</td>
      <td style="text-align:left">Limited</td>
      <td style="text-align:left">Limited</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
    </tr>
    <tr>
      <td style="text-align:left"><b>Interoperability Level</b>
      </td>
      <td style="text-align:left">Semantic</td>
      <td style="text-align:left">Structural</td>
      <td style="text-align:left">Semantic</td>
      <td style="text-align:left">Foundational</td>
      <td style="text-align:left">Semantic</td>
      <td style="text-align:left">Structural</td>
    </tr>
    <tr>
      <td style="text-align:left"><b>Security</b>
      </td>
      <td style="text-align:left">TLS, DTLS, DOS Security</td>
      <td style="text-align:left">TLS + SASL</td>
      <td style="text-align:left">DTLS</td>
      <td style="text-align:left">TLS</td>
      <td style="text-align:left">HTTPS</td>
      <td style="text-align:left">TLS + SASL</td>
    </tr>
    <tr>
      <td style="text-align:left"><b>Data Prioritization</b>
      </td>
      <td style="text-align:left">Transport Priorities</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
      <td style="text-align:left">-</td>
    </tr>
    <tr>
      <td style="text-align:left"><b>Fault Tolerance</b>
      </td>
      <td style="text-align:left">Decentralized</td>
      <td style="text-align:left">Implementation-Specific</td>
      <td style="text-align:left">Decentralized</td>
      <td style="text-align:left">Broker is SpoF</td>
      <td style="text-align:left">Server is SpoF</td>
      <td style="text-align:left">Server is SpoF</td>
    </tr>
  </tbody>
</table>

Tabel Protocol Transport IoT \(Sumber https://iot.eclipse.org/\)

Seperti tampak pada tabel di atas, terdapat beberapa jenis protokol transport yang dapat diterapkan pada arsitektur IoT. Namun pada kesempatan ini kita hanya membahas protokol pesan MQTT \(_Message Queuing Telemetry Transport_\) karena MQTT merupakan protokol pesan terdepan dan paling banyak digunakan pada ekosistem IoT saat ini.

MQTT awalnya dibuat oleh Dr. Andy Stanford-Clark dan Arlen Nipper pada tahun 1999. Tujuan asli dari metode komunikasi ini adalah agar memungkinkan perangkat pemantauan yang digunakan dalam industri minyak dan gas untuk mengirim datanya ke server jarak jauh. Dalam banyak kasus, perangkat pemantauan seperti itu digunakan pada lokasi terpencil dimana segala jenis jalur darat, koneksi kabel, atau koneksi transmisi radio akan sulit, atau tidak mungkin untuk dibuat. Pada saat itu, satu-satunya pilihan untuk kasus semacam itu adalah komunikasi satelit yang sangat mahal karena dihitung berdasarkan seberapa banyak data yang digunakan. Dengan ribuan sensor di lapangan, industri membutuhkan bentuk komunikasi yang dapat memberikan data cukup handal untuk digunakan dengan menggunakan bandwidth minimal.

MQTT distandarisasi sebagai open source di bawah Organization for the Advancement of Structured Information Standards \(OASIS\) pada tahun 2013. OASIS masih mengelola standar MQTT.

MQTT berjalan di atas TCP / IP menggunakan topologi PUSH / SUBSCRIBE. Dalam arsitektur MQTT, terdapat dua jenis sistem: klien dan broker. Broker adalah server yang berkomunikasi dengan klien. Broker menerima komunikasi dari klien dan mengirimkan komunikasi tersebut ke klien lain. Klien tidak berkomunikasi secara langsung satu sama lain, melainkan terhubung ke broker. Setiap klien bisa jadi publisher/penerbit, subscriber/pelanggan, atau keduanya.

MQTT adalah protokol berbasis event-driven/peristiwa. Tidak ada transmisi data berkala atau berkelanjutan. Ini meminimalkan transmisi. Klien hanya mempublikasikan jika ada informasi yang akan dikirim, dan broker hanya mengirimkan informasi ke pelanggan \(subscriber\) ketika data baru tiba.

![](.gitbook/assets/1.png)

![Arsitektur Publish/Subscribe MQTT \(Sumber: https://mqtt.org\)](.gitbook/assets/2%20%289%29.png)

Cara lain MQTT meminimalkan transmisinya adalah dengan mengkonstruksi pesan kecil \(_small message_\) yang ditentukan dengan ketat. Setiap pesan memiliki header tetap hanya 2 byte. Header opsional dapat digunakan tetapi akan meningkatkan ukuran pesan. Muatan pesan dibatasi hanya 256 MB.

Dengan tiga tingkat _Quality of Service_ \(QoS\) yang berbeda memungkinkan perancang jaringan untuk memilih antara meminimalkan transmisi data dan memaksimalkan keandalan.

* QoS 0 - Menawarkan jumlah minimum transmisi data. Dengan level ini, setiap pesan dikirim ke pelanggan satu kali tanpa konfirmasi. Tidak ada cara untuk mengetahui apakah pelanggan menerima pesan tersebut. Metode ini terkadang disebut sebagai “_fire and forget_” atau “_at most once delivery_”. Karena tingkat ini mengasumsikan bahwa pengiriman selesai, pesan tidak disimpan untuk pengiriman ke klien terputus yang kemudian tersambung kembali.
* QoS 1 - Broker mencoba untuk menyampaikan pesan dan kemudian menunggu tanggapan konfirmasi dari subscriber. Jika konfirmasi tidak diterima dalam jangka waktu tertentu, pesan dikirim kembali. Dengan menggunakan metode ini, subscriber dapat menerima pesan lebih dari sekali jika broker tidak menerima pengakuan subscriber tepat waktu. Ini terkadang disebut sebagai “_at least once delivery_”.
* QoS 2 - Klien dan broker menggunakan jabat tangan empat langkah untuk memastikan bahwa pesan diterima, dan hanya diterima sekali. Ini terkadang disebut sebagai “_exactly once delivery_”.

QoS 0 mungkin merupakan pilihan terbaik untuk situasi dimana komunikasi dapat diandalkan tetapi terbatas. QoS 2 akan menjadi pilihan terbaik untuk situasi dimana komunikasi tidak dapat diandalkan, tetapi koneksi tidak terbatas pada sumberdaya. QoS 1 menyediakan solusi terbaik dari kedua pilihan di atas, tetapi mengharuskan aplikasi yang menerima data mengetahui cara menangani duplikasi.

Untuk QoS 1 dan QoS 2, pesan untuk klien yang dalam kondisi offline namun masih memiliki sesi persisten maka akan disimpan atau diantrikan. Jika klien kembali online, pesan ini dikirim ulang sesuai dengan level QoS yang diperlukan.

Pesan dalam MQTT dupublikasikan sebagai topik. Topik adalah struktur dalam hierarki yang menggunakan karakter garis miring \(/\) sebagai pembatas. Struktur ini menyerupai pohon direktori pada sistem file komputer. Struktur seperti “_sensor/OilandGas/Pressure/_” memungkinkan subscriber untuk menentukan bahwa itu hanya boleh dikirim data dari klien yang mempublikasikan ke topik “_Pressure_”, atau untuk pandangan yang lebih luas, bisa jadi semua data dari klien yang mempublikasikan ke _sensor_/ topik _OilandGas_. Topik tidak dibuat secara eksplisit di MQTT. Jika broker menerima data yang dipublikasikan ke topik yang saat ini tidak ada, topik tersebut dibuat begitu saja, dan klien dapat berlangganan ke topik baru.

Untuk menjaga footprint kecil, pesan yang diterima tidak disimpan pada broker kecuali mereka ditandai dengan bendera \(flag/penanda\) yang dipertahankan. Ini disebut pesan yang dipertahankan. Pengguna yang ingin menyimpan pesan yang diterima perlu menyimpannya di tempat lain di luar protokol MQTT. Ada satu pengecualian.

Sebagai protokol yang digerakkan oleh event/peristiwa, sangat mungkin, bahwa _subscriber_ menerima sangat sedikit pesan untuk topik tertentu, bahkan dalam jangka waktu yang lama. Dalam struktur topik yang disebutkan sebelumnya, mungkin pesan ke topik _Pressure_ hanya dikirim ketika sensor mendeteksi bahwa tekanan telah melebihi jumlah tertentu. Dengan asumsi bahwa apa pun yang dipantau oleh sensor itu tidak sering gagal, mungkin perlu berbulan-bulan, atau bahkan bertahun-tahun sebelum klien menerbitkan pesan ke topik itu.

Untuk memastikan bahwa _subscriber_ baru menerima pesan dari suatu topik, broker dapat menyimpan pesan terakhir yang dikirim ke setiap topik. Ini disebut pesan yang dipertahankan. Setiap kali klien baru berlangganan ke suatu topik atau ketika klien yang ada kembali online, pesan yang dipertahankan dikirim ke pelanggan, dengan demikian memastikan bahwa langganan tersebut aktif, dan memiliki informasi terbaru.

> **Catatan:** Bagaimana penggunaan protokol message MQTT pada platform IoT menurut penulis sebaiknya dibahas pada buku Iot tingkat lanjut karena untuk mempraktekannya perlu membangun infrastruktur IoT secara “create from scratch”. Kali ini kita hanya membahas IoT secara “best practie” untuk memberi pandangan secara umum IoT bagi pemula.

