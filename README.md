# Adventure Camp - Sistem Penyewaan Peralatan Camping

| | |
|---|---|
| **Nama Lengkap** | Novriz Arizal |
| **NIM** | C2583207051 |
| **Kelas** | PTI3B |
| **Program Studi** | Pendidikan Teknologi Informasi |
| **Universitas** | Universitas Muhammadiyah Tasikmalaya |
| **Mata Kuliah** | Algoritma dan Pemrograman Lanjutan |
| **Nama Proyek** | Adventure Camp - Sistem Penyewaan Peralatan |

## Deskripsi Singkat

Adventure Camp adalah aplikasi berbasis console (bahasa C) untuk membantu pencatatan
penyewaan perlengkapan camping. Program menerima pesanan, menghitung biaya otomatis,
memberi diskon berdasarkan lama sewa, mencetak struk, dan menyimpan riwayat transaksi
selama program berjalan.

### Fitur
- Menu utama interaktif (berulang sampai pengguna memilih keluar)
- Daftar peralatan dan harga sewa per hari
- Penyewaan dengan validasi input (unit >= 1, lama sewa >= 1 hari, nomor alat valid, nama tidak kosong)
- Diskon: 1-2 hari = 0%, 3-4 hari = 10%, >= 5 hari = 15%
- Struk transaksi
- Riwayat transaksi (kapasitas 10), jumlah transaksi, dan total pendapatan
- Pemberitahuan jika kapasitas riwayat penuh
- **Tantangan tambahan:** beberapa jenis peralatan dalam satu transaksi

### Daftar Peralatan
| No | Peralatan | Harga/Hari |
|---|---|---|
| 1 | Tenda Kapasitas 4 Orang | Rp50.000 |
| 2 | Sleeping Bag | Rp15.000 |
| 3 | Kompor Portable | Rp20.000 |
| 4 | Matras Camping | Rp10.000 |
| 5 | Lampu Camping | Rp12.000 |

## Cara Kompilasi dan Menjalankan

```bash
gcc adventure_camp.c -o adventure_camp
./adventure_camp        # Linux / macOS
adventure_camp.exe      # Windows
```

## Screenshot Hasil Eksekusi

> Ganti placeholder di bawah dengan screenshot asli dari terminal Anda
> (simpan gambar di folder `screenshots/`).

### Menu Utama
![Menu Utama](screenshots/menu-utama.png)

### Daftar Peralatan
![Daftar Peralatan](screenshots/daftar-peralatan.png)

### Struk Penyewaan
![Struk](screenshots/struk.png)

### Riwayat Transaksi
![Riwayat](screenshots/riwayat.png)
