#define MAX_NAME_LENGTH 50
#define MAX_ENTRIES 5

// Struktur data untuk menyimpan informasi leaderboard,
// berisi nama pemain dan skor yang dicapai
typedef struct 
{
    char name[MAX_NAME_LENGTH];
    int score;
} Leaderboard;

// Fungsi untuk memuat data leaderboard dari penyimpanan ke array entries,
// dan mengupdate nilai count dengan jumlah entri yang dimuat
void loadLeaderboard(Leaderboard entries[], int *count);

// Fungsi untuk menyimpan data leaderboard dari array entries ke penyimpanan,
// dengan jumlah entri sebanyak count
void saveLeaderboard(Leaderboard entries[], int count);

// Fungsi untuk memperbarui leaderboard dengan nama pemain baru dan skornya,
// menambahkan atau mengurutkan entri sesuai skor
void updateLeaderboard(const char *playerName, int score);

// Fungsi untuk menampilkan isi leaderboard ke layar atau output
void displayLeaderboard();