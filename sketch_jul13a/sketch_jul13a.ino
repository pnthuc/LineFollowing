#include <MPU6050_tockn.h>
#include <SoftwareSerial.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

long timeEncoder = 0;
long timeY = 0;
int dem = 0;

SoftwareSerial mySerial(3, 2); // RX, TX

void dem_xung(){
  dem ++;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  while (!Serial) {
    ; 
  }
  attachInterrupt(0, dem_xung, RISING);
}
int MAX_SPEED = 50;
int MIN_SPEED = -50;
void loop() { 
  mpu6050.update();
  //Len doc xuong doc
  if(millis() - timeY > 100){
    timeY = millis();
//    int x = mpu6050.getAngleX();
    int y = mpu6050.getAngleY();
//    int z = mpu6050.getAngleZ();

    // y âm là nó xuống dốc
    // y dương là nó lên dốc

    while(y >= 44){
      // Dừng ESC
    }
    while(y <= -44){
      // Dừng ESC
    }
  }  
  // Encoder
  if(millis() - timeEncoder > 1000){
    timeEncoder = millis();
    int rpm = (dem / 6) * 60;
    int d = 0.25; // đường kính mai đo r điền vô (đơn vị mét)
    float vantoc = float(dem/6) * float(acos(-1) * d); // m/s
    Serial.println(vantoc); // sủa vận tốc cho điện thoại nghe
    if(vantoc >= 3){
      MAX_SPEED = max(MAX_SPEED, 50);
      if(MAX_SPEED < 100)
        MAX_SPEED += 10;
    }else MAX_SPEED = 0;
    // viết vận tốc vào ESC
    dem = 0;
  }
}
