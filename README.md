<<<<<<< HEAD
# 🎮 Game Pacman - Proyek Akhir

Selamat datang di repositori game **Pacman** kami! Proyek ini dikembangkan sebagai tugas akhir mata kuliah Projek 2. Game ini dibuat menggunakan bahasa C dan berjalan di Windows dengan bantuan beberapa library.

---

## 👥 Anggota Kelompok

- Adjie Ali Nurfidzal - 241511034
- M. Jibfril Fathi F.A. - 241511049
- Raihana Aisha Az-Zahra - 241511056
- Revaldi Ardhi Prasetyo - 241511057
- Seruni Libertina Islami - 241511064

---

## 🧠 Tentang Game Pacman

Pacman adalah game klasik di mana pemain mengendalikan karakter Pacman yang harus mengumpulkan semua titik-titik (dot) sambil menghindari para hantu. Jika Pacman menyentuh hantu, nyawa akan berkurang. Terdapat juga power-up yang memberikan efek khusus selama permainan.

---

## 💻 Teknologi yang Digunakan

- Bahasa Pemrograman: **C**
- Compiler: **MinGW**
- Header dan Library:
  - `<graphics.h>` (BGI graphics via WinBGIm)
  - `<windows.h>`
  - `<mmsystem.h>` (untuk sound)
  - `<math.h>`, `<stdlib.h>`, `<time.h>`, `<stdio.h>`
- Linker flags saat kompilasi:

```bash
-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm
```

---

## 🚀 Fitur Utama

- ✅ User friendly interface
- ✅ Leaderboard
- ✅ Power-up untuk efek tambahan seperti kebal, skor dobel, dan freeze
- ✅ Animasi Pacman
- ✅ Game Over dan Restart otomatis
- ✅ Pause dan panduan permainan (guide)
- ✅ Efek suara dan musik latar (BGM)
- ✅ Sistem skor berjalan dinamis
- ✅ Pergerakan dinamis Ghost menggunakan linked list
- ✅ Sistem nyawa menggunakan struktur linked list

---

## 🛠️ Instalasi

### 1️⃣ Prasyarat

- OS: **Windows**
- Compiler: **MinGW**
- Sudah menginstal **WinBGIm** dan file header terkait (`graphics.h`)

### 2️⃣ Clone Repositori

```bash
git clone https://github.com/raihanaiooo/pacman.git
cd pacman
```

### 3️⃣ Kompilasi Program

```bash
g++ body/collision-raihana.c body/ghost-adjie.c body/leaderboard-raihana.c body/pacman-raihana.c body/pacman-seruni.c body/pause.c body/powerup.c body/scoring.c body/ui-revaldi.c D:\pacman\main.c -o D:\pacman/output.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm
```

- Atau menggunakan win + shift + B

### 4️⃣ Jalankan Game

```bash
./pacman.exe
```

---

## 🕹️ Cara Bermain

### 🎯 Tujuan Permainan

- Kumpulkan semua dot dan power-up untuk menang.
- Hindari hantu agar tidak kehilangan nyawa.
- Gunakan power-up untuk bertahan atau menambah skor.
- Game over jika nyawa habis.
- Menang jika semua dot habis.

### 🎮 Kontrol Permainan

| Tombol      | Fungsi                    |
| ----------- | ------------------------- |
| ⬅️ ⬆️ ➡️ ⬇️ | Menggerakkan Pacman       |
| `P`         | Pause game                |
| `R`         | Restart permainan         |
| `Q`         | Keluar dari game          |
| `G`         | Tampilkan panduan (guide) |

---

Terima kasih telah memainkan game kami! 🎉
=======
# pacman
>>>>>>> fathi
