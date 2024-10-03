// Mendefinisikan pin untuk LED
const int redPin = 2;
const int yellowPin = 3;
const int greenPin = 4;

// Mendefinisikan pin untuk seven segment display
const int segA1 = 5;
const int segB1 = 6;
const int segC1 = 7;
const int segD1 = 8;
const int segE1 = 9;
const int segF1 = 10;
const int segG1 = 11;

const int segA2 = 12;
const int segB2 = A0;
const int segC2 = A1;
const int segD2 = A2;
const int segE2 = A3;
const int segF2 = A4;
const int segG2 = A5;

// Pin untuk tombol
const int buttonPin = 13;

// Variabel untuk status tombol
int buttonState = 0;

void setup() {
  // Mengatur pin LED sebagai output
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // Mengatur pin seven segment sebagai output
  pinMode(segA1, OUTPUT);
  pinMode(segB1, OUTPUT);
  pinMode(segC1, OUTPUT);
  pinMode(segD1, OUTPUT);
  pinMode(segE1, OUTPUT);
  pinMode(segF1, OUTPUT);
  pinMode(segG1, OUTPUT);

  pinMode(segA2, OUTPUT);
  pinMode(segB2, OUTPUT);
  pinMode(segC2, OUTPUT);
  pinMode(segD2, OUTPUT);
  pinMode(segE2, OUTPUT);
  pinMode(segF2, OUTPUT);
  pinMode(segG2, OUTPUT);
  
  // Mengatur pin tombol sebagai input
  pinMode(buttonPin, INPUT);

  // Menyalakan LED hijau terlebih dahulu
  digitalWrite(greenPin, HIGH);
}

void loop() {
  // Membaca status tombol
  buttonState = digitalRead(buttonPin);

  // Jika tombol ditekan, LED hijau akan berkedip, lalu pindah ke LED kuning, dan LED merah dengan hitung mundur
  if (buttonState == HIGH) {
    // LED hijau berkedip selama 2 detik
    blinkLED(greenPin, 2000);

    // LED kuning berkedip selama 3 detik
    blinkLED(yellowPin, 3000);

    // LED merah menyala selama 20 detik dengan tampilan angka hitung mundur
    digitalWrite(redPin, HIGH);
    for (int i = 20; i >= 0; i--) {
      displayNumber(i); // Tampilkan angka di seven segment
      delay(1000); // Tunggu 1 detik
    }
    digitalWrite(redPin, LOW);

    // Kembali ke kondisi awal, menyalakan LED hijau
    digitalWrite(greenPin, HIGH);
  }
}

void displayNumber(int num) {
  // Mendapatkan digit puluhan dan satuan
  int tens = num / 10;
  int units = num % 10;

  // Menampilkan digit puluhan
  displaySingleDigit(tens, segA1, segB1, segC1, segD1, segE1, segF1, segG1);
  
  // Menampilkan digit satuan
  displaySingleDigit(units, segA2, segB2, segC2, segD2, segE2, segF2, segG2);
}

void displaySingleDigit(int digit, int a, int b, int c, int d, int e, int f, int g) {
  // Menonaktifkan semua segmen
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);

  // Menghidupkan segmen berdasarkan angka
  switch(digit) {
    case 0: digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(e, HIGH); digitalWrite(f, HIGH); break;
    case 1: digitalWrite(b, HIGH); digitalWrite(c, HIGH); break;
    case 2: digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(d, HIGH); digitalWrite(e, HIGH); digitalWrite(g, HIGH); break;
    case 3: digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(g, HIGH); break;
    case 4: digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(f, HIGH); digitalWrite(g, HIGH); break;
    case 5: digitalWrite(a, HIGH); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(f, HIGH); digitalWrite(g, HIGH); break;
    case 6: digitalWrite(a, HIGH); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(e, HIGH); digitalWrite(f, HIGH); digitalWrite(g, HIGH); break;
    case 7: digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, HIGH); break;
    case 8: digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(e, HIGH); digitalWrite(f, HIGH); digitalWrite(g, HIGH); break;
    case 9: digitalWrite(a, HIGH); digitalWrite(b, HIGH); digitalWrite(c, HIGH); digitalWrite(d, HIGH); digitalWrite(f, HIGH); digitalWrite(g, HIGH); break;
    default: break; // Tidak ada tampilan untuk nilai di luar 0-9
  }
}

// Fungsi untuk berkedip LED
void blinkLED(int ledPin, int duration) {
  unsigned long startTime = millis();
  while (millis() - startTime < duration) {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
  }
}
