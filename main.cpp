#include <Arduino.h>
#include <Servo.h>

// Definisikan pin untuk sensor ultrasonic
const int trigPin = 9;  // Pin untuk trig
const int echoPin = 10; // Pin untuk echo

// Definisikan objek servo
Servo myServo;

// Pin untuk servo
const int servoPin = 6;

// Variabel untuk menyimpan durasi dan jarak
long duration;
int distance;

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);
  
  // Set pin untuk trig sebagai output dan echo sebagai input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attaching servo ke pin yang telah ditentukan
  myServo.attach(servoPin);

  // Set servo ke posisi awal
  myServo.write(0); // Posisi awal (0 derajat)
}

void loop() {
  // Bersihkan trigPin dengan memberi low selama 2 mikrodetik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Beri high ke trigPin selama 10 mikrodetik
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca echoPin, kembalikan durasi dalam mikrodetik
  duration = pulseIn(echoPin, HIGH);

  // Hitung jarak dalam cm
  distance = duration * 0.034 / 2;

  // Cetak jarak ke serial monitor untuk debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Jika jarak kurang dari 50 cm, gerakkan servo
  if (distance < 50) {
    myServo.write(90); // Servo bergerak ke 90 derajat
  } else {
    // Jika jarak lebih dari 50 cm, kembalikan servo ke posisi awal
    myServo.write(0); // Servo kembali ke 0 derajat
  }

  // Delay untuk stabilitas pembacaan sensor
  delay(100);
}
