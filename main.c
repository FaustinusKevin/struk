/*  Faustinus Kevin Pradipta
    Teknik Elektro 22   %
    22.F1.0001
 */
#include <stdio.h>
#include <string.h>


typedef struct {
    char nama[50];
    int stok;
    int harga;
} Barang;
void input_error(void) {
    printf("Input Salah, Silakan coba lagi.\n");
}
void print_struk(Barang barang[],int pesanan[][2],int jml_pesanan,int total) {
    printf("============================\n");
    printf("|        Kevin's Store     |\n");
    printf("============================\n\n");
    printf("Pesanan:\n");
    printf("Kategori Smartphone:\n");
    for (int i = 0; i < jml_pesanan; i++) {
        int index_barang = pesanan[i][0];
        int jumlah = pesanan[i][1];
        if (index_barang >= 0 && index_barang <= 6) {
            printf("%d, %dx %s - Rp %d\n",i+1, jumlah, barang[index_barang].nama, barang[index_barang].harga * jumlah);
        }
    }
    printf("\nKategori Aksesoris:\n");
    for (int i = 0; i < jml_pesanan; i++) {
        int index_barang = pesanan[i][0];
        int jumlah = pesanan[i][1];
        if (index_barang >= 7 && index_barang <= 12) {
            printf("%d, %dx %s - Rp %d\n",i+1, jumlah, barang[index_barang].nama, barang[index_barang].harga * jumlah);
        }
    }
    printf("\nSubtotal: Rp %d\n", total);
    printf("Pajak (10%%): Rp %d\n", total / 10);
    printf("Total: Rp %d\n\n", total * 11 / 10);
    printf("=======================\n");
    printf("Pilihan:\n");
    printf("- Ketik 'H' diikuti dengan nomor pesanan untuk menghapus salah satu pesanan\n");
    printf("- Ketik 'R' untuk membatalkan semua pesanan\n");
    printf("- Ketik 'T' untuk menambah pesanan\n");
    printf("- Ketik 'S' untuk Selesai\n\n");
}
int main(void) {
    Barang barang[] = {
        {"Redmi Note 12", 3, 2999000},
        {"Redmi Note 12 Pro", 2, 4599000},
        {"Poco M4 Pro", 1, 2799000},
        {"Poco X5 5G", 2, 3449000},
        {"Redmi 10C", 0, 1899000},
        {"Xiaomi 12", 0, 7999000},
        {"Xiaomi 12 Pro", 1, 12999000},
        {"Charger 33W", 5, 159000},
        {"Redmi Buds Essential", 4, 199000},
        {"PB Xiaomi 10.000mAh", 0, 249000},
        {"Redmi Smartband", 3, 399000},
        {"RedmiBuds 3", 2, 449000},
        {"Redmi Buds 3 Pro", 3, 699000},
    };
    int jml_barang = sizeof(barang) / sizeof(barang[0]);
    int pesanan[100][2];
    int jml_pesanan = 0;
    int total = 0;
    printf("========================\n");
    printf("|   Selamat Datang Di  |\n");
    printf("|     Kevin's Store    |\n");
    printf("========================\n\n");
    printf("Barang Di Toko Kami, Mohon pilih yang tersedia \n\n");
    
    while (1) {
        printf("Smartphone yang tersedia:\n");
        for (int i =0; i <= 6; i++) {
            printf("%d. %s (Stok: %d) - Rp %d\n", i+1,  barang[i].nama, barang[i].stok, barang[i].harga);
        }
       
        printf("\nAksesoris yang tersedia:\n");
        for (int i =7; i < jml_barang; i++) {
            printf("%d. %s (Stok: %d) - Rp %d\n", i+1, barang[i].nama, barang[i].stok, barang[i].harga);
        }
        int nomor_barang, jumlah;
        printf("Masukkan nomor barang yang ingin dibeli (0 untuk selesai): ");
        if (scanf("%d", &nomor_barang) != 1) {
            input_error();
            continue;
        }
        if (nomor_barang == 0) {
            goto struk;
        }
        printf("Masukkan jumlah barang yang ingin dibeli:");
        if (scanf("%d", &jumlah) != 1) {
            input_error();
            continue;
        }
        int index_barang =  nomor_barang - 1;
        if (index_barang < 0 || index_barang >= jml_barang) {
            input_error();
            continue;
        }
        if (barang[index_barang].stok < jumlah) {
            printf("Stok tidak tersedia.\n");
            continue;
        }
        barang[index_barang].stok -= jumlah;
        
        pesanan[jml_pesanan][0] = index_barang;
        pesanan[jml_pesanan][1] = jumlah;
        jml_pesanan++;
        total += barang[index_barang].harga * jumlah;
        
        
    struk:
        print_struk(barang, pesanan, jml_pesanan, total);
        
        char pilihan[10];
        printf("Masukkan pilihan: ");
        scanf("%s", pilihan);
        
        if (strcmp(pilihan, "R") == 0) {
            for (int i = 0; i < jml_pesanan; i++) {
                int index_barang = pesanan[i][0];
                int jumlah = pesanan[i][1];
                barang[index_barang].stok += jumlah;
            }
            jml_pesanan = 0;
            total = 0;
            printf("Pesanan berhasil direset.\n");
            goto struk;
        }
        else if (strcmp(pilihan, "H") == 0) {
            int nomor_pesanan;
            printf("Masukkan nomor pesanan yang ingin dihapus: ");
            if (scanf("%d", &nomor_pesanan) != 1) {
                input_error();
                goto struk;
            }
            if (nomor_pesanan < 1 || nomor_pesanan > jml_pesanan) {
                input_error();
                goto struk;
            }
            int index_hapus = nomor_pesanan - 1;
            int index_barang_hapus = pesanan[index_hapus][0];
            int jumlah_hapus = pesanan[index_hapus][1];
            barang[index_barang_hapus].stok += jumlah_hapus;
            for (int i = index_hapus; i < jml_pesanan-1; i++) {
                pesanan[i][0] = pesanan[i+1][0];
                pesanan[i][1] = pesanan[i+1][1];
            }
            jml_pesanan--;
            total -= barang[index_barang_hapus].harga * jumlah_hapus;
            //ini adalah bagian untuk menghapus pesanan dari daftar pesanan yang ada lalu menyesuaikan stok barang yang terkait dengan pesanan. Setelah penghapusan pesanan, akan memperbarui nilai total biaya dari seluruh pesanan.
            printf("Pesanan berhasil dihapus.\n");
            goto struk;
        }
        else if (strcmp(pilihan, "T") == 0){
            printf("\nApa yang ingin anda tambahkan\n");
            continue;
        }
        else if (strcmp(pilihan, "S") == 0){
            printf("\nTerima Kasih Telah Berbelanja\n");
            break;
        }
        else {
            input_error();
            goto struk;
        }
    }
    return 0;
}

