// Pin definisi untuk seven segment (digit pertama dan kedua)
const int segPins1[] = {2, 3, 4, 5, 6, 7, 8}; // Pin untuk seven segment 1 (satuan)
const int segPins2[] = {9, 10, 11, 12, 13, A0, A1}; // Pin untuk seven segment 2 (puluhan)

// Digit untuk menampilkan angka pada seven segment (abcdefg)
const byte numbers[] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

// Variabel counter dan timer
int count = 21; // Mulai dari 20
unsigned long previousMillis = 0;
const long interval = 1000; // Interval 1 detik

void setup() {
  // Setup pin mode untuk seven segment
  for (int i = 0; i < 7; i++) {
    pinMode(segPins1[i], OUTPUT);
    pinMode(segPins2[i], OUTPUT);
  }
}

void loop() {
  unsigned long currentMillis = millis(); // Mendapatkan waktu saat ini

  // Jika sudah melewati interval 1 detik
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Decrement count
    if (count > 0) {
      count--;
    } else {
      count = 20; // Kembali ke 20 setelah mencapai 0
    }

    // Update seven segment display
    displayNumber(count);
  }
}

// Fungsi untuk menampilkan angka pada kedua seven segment
void displayNumber(int number) {
  int tens = number / 10;   // Ambil digit puluhan
  int ones = number % 10;   // Ambil digit satuan

  // Tampilkan angka satuan pada seven segment 1
  byte num1 = numbers[ones];
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins1[i], bitRead(num1, i)); // Mengatur pin segmen sesuai angka satuan
  }

  // Tampilkan angka puluhan pada seven segment 2
  byte num2 = numbers[tens];
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins2[i], bitRead(num2, i)); // Mengatur pin segmen sesuai angka puluhan
  }
}
