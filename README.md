# Balatro - Chain of Responsibility & Observer Pattern

Proyek ini adalah implementasi sistem permainan kartu ala Balatro menggunakan C++ dengan dua design pattern utama:
1. **Chain of Responsibility**: untuk evaluasi kombinasi poker hand (bergerak dari kombinasi tertinggi hingga terendah).
2. **Observer Pattern**: untuk sistem Joker modifier yang dinamis dan fleksibel (terhubung melalui `JokerObserver`, `Joker`, dan `JokerManager`).

Program menggunakan deck standar 52 kartu, memilih 5 kartu terbaik secara otomatis dari 8 kartu yang ditarik, mengevaluasi kombinasi poker, menghitung score `Chips x Mult`, memproses efek berbagai Joker aktif, lalu memvalidasi target Blind dan reward.

## Alur Permainan

Setiap ronde menjalankan urutan berikut:

```text
Generate 8 kartu
    -> Pilih 5 kartu terbaik dari 56 kombinasi (3 kartu sisa tersimpan di tangan)
    -> Evaluasi kombinasi dengan Chain of Responsibility
    -> Hitung Base Score (Base Chips + Card Chips) x Base Mult
    -> Notifikasi ke JokerManager (Observer Pattern) untuk modifikasi score
    -> Cek Blind
    -> Berikan reward atau Game Over
```

### 1. Generate Hand

`HandGenerator` membuat deck standar berisi 52 kartu dari empat suit (`Hearts`, `Diamonds`, `Clubs`, `Spades`) dan rank 2 sampai Ace. Deck diacak, lalu 8 kartu diambil tanpa duplikasi. Kartu yang sudah diambil dikeluarkan dari deck dan deck di-reset jika kartu tersisa kurang dari 8.

### 2. Choose/Play Hand

`HandSelector::playHand()` membuat seluruh kombinasi 5 kartu dari 8 kartu tersedia:

```text
C(8, 5) = 56 kombinasi
```

Setiap kombinasi dikirim ke checker. Kombinasi dengan `HandRank` tertinggi dipilih. Kartu yang tidak dimainkan (3 kartu) tetap berada di tangan pemain (`heldCards`).

### 3. Evaluasi Chain (Chain of Responsibility)

Urutan Chain harus tetap dari kombinasi tertinggi ke terendah:

```text
Flush Five
Flush House
Five of a Kind
Royal Flush
Straight Flush
Four of a Kind
Full House
Flush
Straight
Three of a Kind
Two Pair
Pair
High Card
```

Untuk satu kombinasi, chain berhenti ketika checker menemukan hasil yang cocok. Selector tetap memeriksa kombinasi lain karena hasil yang lebih tinggi mungkin ada pada kombinasi berikutnya.

### 4. Scoring

`ScoringRule` menggunakan rumus:

```text
Total Base Score = (Base Chips + nilai kartu dimainkan) x Base Mult
```

J, Q, K, dan Ace dihitung sebagai 10 Chips. Nilai dasar `Chips` dan `Mult` berbeda untuk setiap kombinasi poker.

### 5. Sistem Joker (Observer Pattern)

Sistem Joker diimplementasikan menggunakan arsitektur Observer Pattern yang terhubung melalui `ScoreContext`:

- `JokerObserver`: Interface abstrak dengan method `onScoreCalculated(ScoreContext& context)`.
- `Joker`: Kelas dasar abstrak turunan dari `JokerObserver` dengan properti nama dan deskripsi dinamis.
- `JokerManager`: Subject / Manager yang mengelola koleksi Joker aktif dan menotifikasi seluruh Joker saat score dihitung.
- `ScoreContext`: Objek konteks yang menyimpan data perhitungan skor (`chips`, `mult`, `handRank`, `playedCards`, `heldCards`).

#### Jenis Joker yang Diimplementasikan:
1. **Joker** (Default Joker):
   - Efek: Memberikan bonus flat `+4 Mult`.
2. **Mad Joker**:
   - Efek: Memberikan bonus `+10 Mult` jika kombinasi kartu yang dimainkan mengandung **Two Pair** (termasuk Full House & Flush House).
3. **Misprint**:
   - Efek: Memberikan bonus acak `+0 s/d +23 Mult` pada setiap evaluasi tangan.
4. **Raised Fist**:
   - Efek: Menambahkan 2x nilai rank dari kartu bernilai **terendah yang tersisa di tangan** (`held cards`) ke Mult.
5. **Flat Chip Joker**:
   - Efek: Memberikan bonus flat `+20 Chips`.
6. **Pair Joker**:
   - Efek: Memberikan bonus `+4 Mult` jika kombinasi kartu mengandung **Pair**.

### 6. Blind dan Reward

`BlindRule` menentukan kemenangan berdasarkan total score akhir setelah dimodifikasi oleh Joker. Jika menang, `RewardRule` menambahkan money. Jika gagal melewati target Blind, ronde dihentikan dan game berakhir (Game Over).

## Struktur File

### Model Data
- `Card.h`: `Suit`, `Rank`, `Card` (dengan operator perbandingan dan fungsi format).
- `Hand.h`: `HandRank`, `Hand` (dengan method `getHeldCards()`), dan `EvaluationResult`.
- `ScoreContext.h`: Struktur konteks data scoring untuk interaksi Joker.

### Pembuatan dan Pemilihan Kartu
- `HandGenerator.h/.cpp`: Membuat, mengacak deck, dan menghasilkan 8 kartu.
- `HandSelector.h/.cpp`: Memeriksa 56 kombinasi dan memilih 5 kartu terbaik.

### Evaluasi Kartu (Chain of Responsibility)
- `HandChecker.h/.cpp`: Rantai checker kombinasi poker dari Flush Five hingga High Card.

### Aturan Permainan & Sistem Joker (Observer Pattern)
- `GameRules.h/.cpp`: Scoring dasar, penentuan target Blind, dan kalkulasi Reward.
- `JokerObserver.h`: Interface Observer untuk Joker.
- `Joker.h`: Base class abstrak untuk Joker.
- `JokerManager.h/.cpp`: Subjek pengelola dan pemicu seluruh efek Joker aktif.
- `DefaultJoker.h/.cpp`: Implementasi Joker (+4 Mult).
- `MadJoker.h/.cpp`: Implementasi Mad Joker (+10 Mult jika mengandung Two Pair).
- `MisprintJoker.h/.cpp`: Implementasi Misprint (+0-23 Mult).
- `RaisedFistJoker.h/.cpp`: Implementasi Raised Fist (2x rank kartu terendah di tangan).
- `FlatChipJoker.h/.cpp`: Implementasi Flat Chip Joker (+20 Chips).
- `PairJoker.h/.cpp`: Implementasi Pair Joker (+4 Mult jika Pair).
- `JokerCard.h/.cpp`: Kompatibilitas mundur (Legacy adapter).

### Game Loop
- `GameManager.h/.cpp`: Mengatur seluruh alur ronde dan interaksi antar-sistem.
- `main.cpp`: Inisialisasi rantai checker dan eksekusi sesi permainan.

## Kompilasi dan Menjalankan Program

Dari folder `Balatro-desain-pattern`:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic *.cpp -o main.exe
./main.exe
```
