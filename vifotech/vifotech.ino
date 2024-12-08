Le Quang Phuc
#include <SimpleKalmanFilter.h>
#include <SoftwareSerial.h>
#include <MPU6050_tockn.h>
#include <Servo.h>
#include <Wire.h>

Servo ESC;
SoftwareSerial HC05(8, 10);
MPU6050 mpu6050(Wire);

SimpleKalmanFilter filter(2, 2, 0.01);

float d = 0.25, speed = 0; // đường kính (m)
unsigned long timeEncoder = 0;
int cnt = 0;
float MAX_BATTERY_PERCENTAGE = 12.2, MIN_BATTERY_PERCENTAGE = 10.8;

int smap(int n) {
  return (int) map(n, 0, 1023, 1000, 2000);
}

float kalman(float x) {
  x = filter.updateEstimate(x);
  x = filter.updateEstimate(x);
  return x;
}

void dem_xung() {cnt++;}

void setup() {
  Serial.begin(9600);
  HC05.begin(9600);

  pinMode(A3, INPUT);
  ESC.attach(3); // Mạch cũ chân 3
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true); // Động cơ chạy ngu thì để false test đống băm xung 2 dòng dưới
  
  // Tạo xung khởi tạo động cơ
  ESC.write(smap(500)); // Mò xung cho động cơ chạy (xưa chạy 12V t để 500)
  delay(2500); // Đáng lý ko cần delay vì hàm mpu nó dừng sẵn 3s để set gtri toạ độ ban đầu, nhma t nghi hàm mpu phế nên vẫn delay

  attachInterrupt(digitalPinToInterrupt(9), dem_xung, RISING); // Nếu ko đc câu dây từ domino qua chân 2 và CHECK THÔNG MẠCH
}

void loop() {
  // Lên dốc xuống dốc
  mpu6050.update();
  float y = kalman(mpu6050.getAngleY());
  if(y <= -44) {
    ESC.writeMicroseconds(smap(0)); // Dừng động cơ
  } else {
    ESC.writeMicroseconds(smap(1023)); // Mò xung cho động cơ chạy
  }

  // Tính phần trăm pin
  float volt_sensor = float(analogRead(A3) * 4 / 1023.0);
  float volt_in = float(volt_sensor * 3000.0 / 1000.0);
  int battery_report = (volt_in - MIN_BATTERY_PERCENTAGE) * 100.0 / (MAX_BATTERY_PERCENTAGE - MIN_BATTERY_PERCENTAGE);
  battery_report = (battery_report >= 0 ? battery_report : 0);

  // Đọc tốc độ
  if (millis() - timeEncoder > 100) { // đọc số vòng mỗi 100ms (m/0.1s)
    timeEncoder = millis();
    
    speed = kalman(float(cnt / 6.0) * float(acos(-1) * d) / 0.1 * 3.6); // km/h

    cnt = 0;
  }

  String res = 'B' + String(int(speed)) + ',' + String(int(battery_report)) + 'E';
  while(res.length() < 10) res += '#';

  // String to char array
  char resBuf[10];
  res.toCharArray(resBuf, 10);

  HC05.println(resBuf);

  delay(200);
}
