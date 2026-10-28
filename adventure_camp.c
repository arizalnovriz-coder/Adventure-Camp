/*
 * ============================================================
 *  PROJECT   : Adventure Camp - Sistem Penyewaan Peralatan
 *  MATA KULIAH: Algoritma dan Pemrograman Lanjutan
 *  Nama      : Novriz Arizal
 *  NIM       : C2583207051
 *  Kelas     : PTI3B
 *  Bahasa    : C
 * ============================================================
 *  Fitur:
 *   1. Lihat daftar peralatan
 *   2. Sewa peralatan (+ diskon berdasarkan lama sewa)
 *      - Tantangan tambahan: beberapa jenis peralatan dalam
 *        satu transaksi
 *   3. Riwayat transaksi (maks. 10 transaksi)
 *   4. Keluar
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---------- Konstanta ---------- */
#define JUMLAH_ALAT      5     /* jumlah jenis peralatan          */
#define MAKS_TRANSAKSI   10    /* kapasitas riwayat transaksi     */
#define PANJANG_NAMA     50    /* panjang maksimal nama penyewa   */
#define PANJANG_ALAT     60    /* panjang teks ringkasan alat     */
#define MAKS_UNIT        1000  /* batas atas jumlah unit          */
#define MAKS_HARI        365   /* batas atas lama sewa            */
#define GARIS_DOUBLE     "========================================"
#define GARIS_SINGLE     "----------------------------------------"

/* ---------- Data peralatan (array) ---------- */
const char *namaAlat[JUMLAH_ALAT] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};
const int hargaAlat[JUMLAH_ALAT] = {50000, 15000, 20000, 10000, 12000};

/* ---------- Riwayat transaksi (array per kategori) ---------- */
char riwayatNama[MAKS_TRANSAKSI][PANJANG_NAMA];
char riwayatAlat[MAKS_TRANSAKSI][PANJANG_ALAT];
int  riwayatUnit[MAKS_TRANSAKSI];
int  riwayatHari[MAKS_TRANSAKSI];
int  riwayatTotal[MAKS_TRANSAKSI];
int  jumlahTransaksi = 0;

/* ---------- Prototipe fungsi ---------- */
void tampilkanMenu(void);
void tampilkanDaftarPeralatan(void);
void tungguEnter(void);
int  bacaAngka(const char *prompt, int min, int max);
void bacaTeks(const char *prompt, char *hasil, int ukuran);
int  bacaYT(const char *prompt);
int  hitungPersenDiskon(int hari);
void tampilkanStruk(const char *nama, const int idx[], const int qty[],
                    int n, int hari, int subtotal, int persen,
                    int diskon, int total);
void simpanTransaksi(const char *nama, const int idx[], const int qty[],
                     int n, int hari, int total);
void tampilkanRiwayat(void);
int  sewaPeralatan(void);

/* ============================================================
 *  FUNGSI UTAMA
 * ============================================================ */
int main(void)
{
    int pilihan;
    int lanjut = 1;

    while (lanjut) {
        tampilkanMenu();
        pilihan = bacaAngka("Pilih menu [1-4]: ", 1, 4);

        switch (pilihan) {
        case 1:
            tampilkanDaftarPeralatan();
            tungguEnter();
            break;
        case 2:
            lanjut = sewaPeralatan();
            break;
        case 3:
            tampilkanRiwayat();
            tungguEnter();
            break;
        case 4:
            lanjut = 0;
            break;
        }
    }

    printf("\n%s\n", GARIS_DOUBLE);
    printf("  Terima kasih telah menggunakan\n");
    printf("  layanan Adventure Camp. Sampai jumpa!\n");
    printf("%s\n", GARIS_DOUBLE);
    return 0;
}

/* ============================================================
 *  TAMPILAN
 * ============================================================ */

/* Menampilkan menu utama */
void tampilkanMenu(void)
{
    printf("\n%s\n", GARIS_DOUBLE);
    printf("            ADVENTURE CAMP\n");
    printf("      SISTEM PENYEWAAN PERALATAN\n");
    printf("%s\n", GARIS_DOUBLE);
    printf("1. Lihat Daftar Peralatan\n");
    printf("2. Sewa Peralatan\n");
    printf("3. Lihat Riwayat Transaksi\n");
    printf("4. Keluar\n");
    printf("%s\n", GARIS_DOUBLE);
}

/* Menampilkan seluruh peralatan beserta harga sewa per hari */
void tampilkanDaftarPeralatan(void)
{
    int i;

    printf("\n%s\n", GARIS_DOUBLE);
    printf("          DAFTAR PERALATAN\n");
    printf("%s\n", GARIS_DOUBLE);
    printf("%-4s %-25s %s\n", "No.", "Peralatan", "Harga/Hari");
    printf("%s\n", GARIS_SINGLE);
    for (i = 0; i < JUMLAH_ALAT; i++) {
        printf("%-4d %-25s Rp%d\n", i + 1, namaAlat[i], hargaAlat[i]);
    }
    printf("%s\n", GARIS_DOUBLE);
}

/* Menunggu pengguna menekan Enter (kembali ke menu utama) */
void tungguEnter(void)
{
    char buf[100];
    printf("Tekan Enter untuk kembali ke menu utama...");
    fgets(buf, sizeof(buf), stdin);
}

/* ============================================================
 *  INPUT & VALIDASI
 * ============================================================ */

/* Membaca bilangan bulat dalam rentang [min, max].
 * Diulang terus sampai masukan valid (bukan huruf, bukan di luar rentang). */
int bacaAngka(const char *prompt, int min, int max)
{
    char buf[100];
    char *akhir;
    long nilai;

    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            /* EOF: hentikan program dengan rapi */
            printf("\nInput berakhir. Program ditutup.\n");
            exit(0);
        }

        nilai = strtol(buf, &akhir, 10);

        /* lewati spasi/newline di belakang angka */
        while (*akhir == ' ' || *akhir == '\t' || *akhir == '\n' || *akhir == '\r')
            akhir++;

        if (akhir == buf || *akhir != '\0') {
            printf("  [!] Masukan harus berupa angka. Coba lagi.\n");
        } else if (nilai < min || nilai > max) {
            printf("  [!] Masukan harus antara %d sampai %d. Coba lagi.\n", min, max);
        } else {
            return (int)nilai;
        }
    }
}

/* Membaca teks (nama) yang tidak boleh kosong */
void bacaTeks(const char *prompt, char *hasil, int ukuran)
{
    char buf[200];
    int i, panjang, kosong;

    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("\nInput berakhir. Program ditutup.\n");
            exit(0);
        }

        /* hapus newline di akhir */
        buf[strcspn(buf, "\r\n")] = '\0';

        /* cek apakah hanya berisi spasi */
        panjang = (int)strlen(buf);
        kosong = 1;
        for (i = 0; i < panjang; i++) {
            if (!isspace((unsigned char)buf[i])) {
                kosong = 0;
                break;
            }
        }

        if (kosong) {
            printf("  [!] Nama tidak boleh kosong. Coba lagi.\n");
        } else {
            strncpy(hasil, buf, ukuran - 1);
            hasil[ukuran - 1] = '\0';
            return;
        }
    }
}

/* Membaca pilihan Y/T. Mengembalikan 1 jika Y, 0 jika T */
int bacaYT(const char *prompt)
{
    char buf[100];
    char c;

    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("\nInput berakhir. Program ditutup.\n");
            exit(0);
        }
        c = (char)toupper((unsigned char)buf[0]);
        if ((c == 'Y' || c == 'T') && (buf[1] == '\n' || buf[1] == '\r' || buf[1] == '\0')) {
            return (c == 'Y');
        }
        printf("  [!] Masukan harus Y atau T. Coba lagi.\n");
    }
}

/* ============================================================
 *  LOGIKA BISNIS
 * ============================================================ */

/* Menentukan persentase diskon berdasarkan lama sewa */
int hitungPersenDiskon(int hari)
{
    if (hari >= 5)
        return 15;
    else if (hari >= 3)
        return 10;
    else
        return 0;
}

/* Menyimpan transaksi ke array riwayat */
void simpanTransaksi(const char *nama, const int idx[], const int qty[],
                     int n, int hari, int total)
{
    int i, totalUnit = 0;
    int k = jumlahTransaksi;

    for (i = 0; i < n; i++)
        totalUnit += qty[i];

    strncpy(riwayatNama[k], nama, PANJANG_NAMA - 1);
    riwayatNama[k][PANJANG_NAMA - 1] = '\0';

    /* Jika lebih dari satu jenis alat: "Nama pertama +N lain" */
    if (n == 1) {
        snprintf(riwayatAlat[k], PANJANG_ALAT, "%s", namaAlat[idx[0]]);
    } else {
        snprintf(riwayatAlat[k], PANJANG_ALAT, "%s +%d lain",
                 namaAlat[idx[0]], n - 1);
    }

    riwayatUnit[k]  = totalUnit;
    riwayatHari[k]  = hari;
    riwayatTotal[k] = total;
    jumlahTransaksi++;
}

/* Menampilkan struk penyewaan */
void tampilkanStruk(const char *nama, const int idx[], const int qty[],
                    int n, int hari, int subtotal, int persen,
                    int diskon, int total)
{
    int i;
    char labelDiskon[20];

    printf("\n%s\n", GARIS_DOUBLE);
    printf("            ADVENTURE CAMP\n");
    printf("            STRUK PENYEWAAN\n");
    printf("%s\n", GARIS_DOUBLE);
    printf("Nama Penyewa   : %s\n", nama);
    printf("Lama Sewa      : %d hari\n", hari);

    for (i = 0; i < n; i++) {
        printf("%s\n", GARIS_SINGLE);
        printf("Peralatan      : %s\n", namaAlat[idx[i]]);
        printf("Harga per Hari : Rp%d\n", hargaAlat[idx[i]]);
        printf("Jumlah Unit    : %d\n", qty[i]);
        printf("Biaya          : Rp%d\n", hargaAlat[idx[i]] * qty[i] * hari);
    }

    printf("%s\n", GARIS_SINGLE);
    printf("Subtotal       : Rp%d\n", subtotal);
    sprintf(labelDiskon, "Diskon (%d%%)", persen);
    printf("%-15s: Rp%d\n", labelDiskon, diskon);
    printf("%s\n", GARIS_SINGLE);
    printf("TOTAL BAYAR    : Rp%d\n", total);
    printf("%s\n", GARIS_DOUBLE);
    printf("Terima kasih telah menggunakan\n");
    printf("layanan Adventure Camp!\n\n");
}

/* Proses penyewaan lengkap.
 * Mengembalikan 1 jika pengguna ingin kembali ke menu utama,
 * 0 jika ingin mengakhiri program. */
int sewaPeralatan(void)
{
    char nama[PANJANG_NAMA];
    int idx[JUMLAH_ALAT];   /* indeks peralatan yang dipilih */
    int qty[JUMLAH_ALAT];   /* jumlah unit tiap peralatan    */
    int n = 0;              /* jumlah jenis alat di keranjang */
    int hari, subtotal = 0, persen, diskon, total;
    int i, j, pilih, unit, ketemu, tambahLagi;

    /* Cek kapasitas riwayat */
    if (jumlahTransaksi >= MAKS_TRANSAKSI) {
        printf("\n%s\n", GARIS_DOUBLE);
        printf("  [!] Kapasitas riwayat penuh (%d transaksi).\n", MAKS_TRANSAKSI);
        printf("      Transaksi baru tidak dapat diterima.\n");
        printf("%s\n", GARIS_DOUBLE);
        tungguEnter();
        return 1;
    }

    printf("\n%s\n", GARIS_DOUBLE);
    printf("           SEWA PERALATAN\n");
    printf("%s\n", GARIS_DOUBLE);

    /* 1. Nama penyewa */
    bacaTeks("Nama penyewa: ", nama, PANJANG_NAMA);

    /* 2-3. Pilih peralatan & jumlah unit (bisa lebih dari satu jenis) */
    do {
        tampilkanDaftarPeralatan();
        pilih = bacaAngka("Pilih peralatan [1-5]: ", 1, JUMLAH_ALAT) - 1;
        unit  = bacaAngka("Jumlah unit (min. 1): ", 1, MAKS_UNIT);

        /* Jika alat yang sama dipilih lagi, jumlahnya digabung */
        ketemu = 0;
        for (j = 0; j < n; j++) {
            if (idx[j] == pilih) {
                qty[j] += unit;
                ketemu = 1;
                break;
            }
        }
        if (!ketemu) {
            idx[n] = pilih;
            qty[n] = unit;
            n++;
        }

        printf("  -> Ditambahkan: %d x %s\n", unit, namaAlat[pilih]);

        if (n < JUMLAH_ALAT)
            tambahLagi = bacaYT("Sewa peralatan jenis lain dalam transaksi ini? (Y/T): ");
        else
            tambahLagi = 0; /* semua jenis alat sudah dipilih */
    } while (tambahLagi);

    /* 4. Lama penyewaan */
    hari = bacaAngka("Lama penyewaan (hari, min. 1): ", 1, MAKS_HARI);

    /* Hitung biaya */
    for (i = 0; i < n; i++)
        subtotal += hargaAlat[idx[i]] * qty[i] * hari;

    persen = hitungPersenDiskon(hari);
    diskon = subtotal * persen / 100;
    total  = subtotal - diskon;

    /* Simpan dan tampilkan struk */
    simpanTransaksi(nama, idx, qty, n, hari, total);
    tampilkanStruk(nama, idx, qty, n, hari, subtotal, persen, diskon, total);

    if (jumlahTransaksi >= MAKS_TRANSAKSI) {
        printf("[!] Perhatian: kapasitas riwayat sudah penuh.\n\n");
    }

    return bacaYT("Kembali ke menu utama? (Y/T): ");
}

/* Menampilkan riwayat transaksi, jumlah transaksi, dan total pendapatan */
void tampilkanRiwayat(void)
{
    int i;
    int pendapatan = 0;

    printf("\n%s\n", GARIS_DOUBLE);
    printf("           RIWAYAT TRANSAKSI\n");
    printf("%s\n", GARIS_DOUBLE);

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        printf("%s\n", GARIS_DOUBLE);
        return;
    }

    printf("%-3s %-12s %-26s %-6s %-5s %s\n",
           "No", "Nama", "Peralatan", "Unit", "Hari", "Total");
    printf("%s\n", GARIS_SINGLE);

    for (i = 0; i < jumlahTransaksi; i++) {
        printf("%-3d %-12.12s %-26.26s %-6d %-5d Rp%d\n",
               i + 1, riwayatNama[i], riwayatAlat[i],
               riwayatUnit[i], riwayatHari[i], riwayatTotal[i]);
        pendapatan += riwayatTotal[i];
    }

    printf("%s\n", GARIS_SINGLE);
    printf("Jumlah Transaksi : %d\n", jumlahTransaksi);
    printf("Total Pendapatan : Rp%d\n", pendapatan);
    printf("%s\n", GARIS_DOUBLE);
}
