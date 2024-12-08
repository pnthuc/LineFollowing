//definition of pid module
#define MAX_YAW_PID +90
#define MIN_YAW_PID -90
int16_t yawError, yawPreError;
double yawP, yawI, yawD;
double yawKp = 0.3;  // dông co lắc ---> giảm
double yawKd = 0.05;
double yawKi = 0;
double yawPID;
int isTranslate = 0;
int16_t setPointZ = 0;
int speed1, speed2, speed3, speed4;
int pid;
double PIDyaw(int _yawValue, int _yawSetpoint) {
  yawError = _yawSetpoint - _yawValue;
  yawP = yawError;
  yawD = yawError - yawPreError;
  yawI = yawError + yawI;
  yawPID = yawKp * yawP + yawKd * yawD + yawKi * yawI;
  if (yawPID > MAX_YAW_PID) {
    yawPID = MAX_YAW_PID;
  }
  if (yawPID < MIN_YAW_PID) {
    yawPID = MIN_YAW_PID;
  }
  yawPreError = yawError;
  return yawPID;
}

//definition of compass module
int16_t compassData = 0;

//definition of gamepad module
#define NONE 0
#define R 1
#define L 2
#define UP 3
#define UP_R 4
#define UP_L 5
#define DOWN 6
#define DOWN_R 7
#define DOWN_L 8
#define LEFT 9
#define LEFT_R 10
#define LEFT_L 11
#define RIGHT 12
#define RIGHT_R 13
#define RIGHT_L 14
#define UP_RIGHT 15
#define UP_RIGHT_R 16
#define UP_RIGHT_L 17
#define UP_LEFT 18
#define UP_LEFT_R 19
#define UP_LEFT_L 20
#define DOWN_RIGHT 21
#define DOWN_RIGHT_R 22
#define DOWN_RIGHT_L 23
#define DOWN_LEFT 24
#define DOWN_LEFT_R 25
#define DOWN_LEFT_L 26

char serialCommand;

//definition of motor module
#define R_PWM1 44
#define L_PWM1 2
#define R_PWM2 10
#define L_PWM2 9
#define R_PWM3 8
#define L_PWM3 7
#define R_PWM4 6
#define L_PWM4 5
#define R_PWM5 3
#define L_PWM5 4
#define R_PWM6 1
#define L_PWM6 12

// thêm cơ cấu chấp hành
int xylanh_gap_1 = 27;
int xylanh_keo_1 = 29;
int xylanh_gap_2 = 31;
int xylanh_keo_2 = 33;
int xylanh_gap_3 = 35;
int xylanh_keo_3 = 37;
int xucbong = 39;


// khai bao cambien
int sensor_1 = A0;
int sensor_2 = A1;

// khai bao gia tri cambien
int gtcambien_1 = 0;
int gtcambien_2 = 0;

// dieu chinh toc do
int runSpeed = 55;
int curveSpeed = 25;
int runSpeed1 = 70;
int curveSpeed1 = 25;
int runSpeed2 = 30;
int curveSpeed2 = 10;
int speedbanbong = 120;
int speedbanbong1 = 120;
int speedbanbong2 = 150;

int isBallShootingMode = 0;
// them chuc nang bam giu/dem
int flag1;
int flag2;
int flag3;
int flag4;
int flag5;
int flag6;
int flag7;
int flag8;
int flag9;
int flag10;


void motor1(int speed) {
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed > 0) {
    analogWrite(R_PWM1, abs(speed));
    digitalWrite(L_PWM1, 0);
  } else {
    digitalWrite(R_PWM1, 0);
    analogWrite(L_PWM1, abs(speed));
  }
  speed1 = speed;
}

void motor2(int speed) {
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed < 0) {
    analogWrite(R_PWM2, abs(speed));
    digitalWrite(L_PWM2, 0);
  } else {
    digitalWrite(R_PWM2, 0);
    analogWrite(L_PWM2, abs(speed));
  }
  speed2 = speed;
}

void motor3(int speed) {
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed < 0) {
    analogWrite(R_PWM3, abs(speed));
    digitalWrite(L_PWM3, 0);
  } else {
    digitalWrite(R_PWM3, 0);
    analogWrite(L_PWM3, abs(speed));
  }
  speed3 = speed;
}

void motor4(int speed) {
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed > 0) {
    analogWrite(R_PWM4, abs(speed));
    digitalWrite(L_PWM4, 0);
  } else {
    digitalWrite(R_PWM4, 0);
    analogWrite(L_PWM4, abs(speed));
  }
  speed4 = speed;
}


//initialize all module
void setup() {
  Serial.begin(9600);
  Serial2.begin(115200);  // IMU  baudrate (unchangable)
  Serial3.begin(19200);

  // cơ cấu chấp hành

  pinMode(xylanh_gap_1, OUTPUT);
  pinMode(xylanh_gap_2, OUTPUT);
  pinMode(xylanh_gap_3, OUTPUT);
  pinMode(xylanh_keo_1, OUTPUT);
  pinMode(xylanh_keo_2, OUTPUT);
  pinMode(xylanh_keo_3, OUTPUT);
  pinMode(xucbong, OUTPUT);
  pinMode(R_PWM5, OUTPUT);
  pinMode(L_PWM5, OUTPUT);
  pinMode(R_PWM6, OUTPUT);
  pinMode(L_PWM6, OUTPUT);


  pinMode(sensor_1, INPUT);
  pinMode(sensor_2, INPUT);
  delay(2000);
  Serial2.write('o');
  // TESTTTTTTTTTTTTTT CHIỀU quay mootop----

  //   while(1)
  // {
  //     motor1(0);
  //     motor2(0);
  //     motor3(0);
  //     motor4(0);
  //     delay(1000);

  //     motor1(50);
  //     motor2(0);
  //     motor3(0);
  //     motor4(0);
  //     delay(1000);
  //     motor1(-50);
  //     motor2(0);
  //     motor3(0);
  //     motor4(0);
  //     delay(1000);

  //     motor1(0);
  //     motor2(50);
  //     motor3(0);
  //     motor4(0);
  //     delay(1000);

  //     motor1(0);
  //     motor2(-50);
  //     motor3(0);
  //     motor4(0);
  //     delay(1000);

  //     motor1(0);
  //     motor2(0);
  //     motor3(50);
  //     motor4(0);
  //     delay(1000);
  //     motor1(0);
  //     motor2(0);
  //     motor3(-50);
  //     motor4(0);
  //     delay(1000);

  //     motor1(0);
  //     motor2(0);
  //     motor3(0);
  //     motor4(50);
  //     delay(1000);
  //     motor1(0);
  //     motor2(0);
  //     motor3(0);
  //     motor4(-50);
  //     delay(1000);
  // }                     // hc05 baudrate (edit due to hc05 baudrate setting)
}
//phan chuong trinh con co cau
void motorbanbongthuan() {
  analogWrite(L_PWM5, speedbanbong);
  analogWrite(R_PWM5, 0);
  analogWrite(L_PWM6, speedbanbong);
  analogWrite(R_PWM6, 0);
}
void motorbanbongdung() {
  analogWrite(L_PWM5, 0);
  analogWrite(R_PWM5, 0);
  analogWrite(L_PWM6, 0);
  analogWrite(R_PWM6, 0);
}
//chuong trinh gap so 1
void xylanh_gap_1_on() {
  digitalWrite(xylanh_gap_1, HIGH);
}
void xylanh_gap_1_off() {
  digitalWrite(xylanh_gap_1, LOW);
}
void xylanh_keo_1_on() {
  digitalWrite(xylanh_keo_1, HIGH);
}
void xylanh_keo_1_off() {
  digitalWrite(xylanh_keo_1, LOW);
}
// chuong trinh gap so 2
void xylanh_keo_2_off() {
  digitalWrite(xylanh_keo_2, LOW);
}
void xylanh_keo_2_on() {
  digitalWrite(xylanh_keo_2, HIGH);
}
void xylanh_gap_2_on() {
  digitalWrite(xylanh_gap_2, HIGH);
}
void xylanh_gap_2_off() {
  digitalWrite(xylanh_gap_2, LOW);
}
// chuong trinh tay gap so 3
void xylanh_keo_3_off() {
  digitalWrite(xylanh_keo_3, LOW);
}
void xylanh_keo_3_on() {
  digitalWrite(xylanh_keo_3, HIGH);
}
void xylanh_gap_3_on() {
  digitalWrite(xylanh_gap_3, HIGH);
}
void xylanh_gap_3_off() {
  digitalWrite(xylanh_gap_3, LOW);
}
// chuong trinh xuc bong
void xucbong_on() {
  digitalWrite(xucbong, HIGH);
}
void xucbong_off() {
  digitalWrite(xucbong, LOW);
}
//main process
int debug;
void loop() {
  Serial.print(debug);
  Serial.print(" ");
  //read gamepad data
  if (Serial3.available()) {
    serialCommand = (char)Serial3.read();
  }
  // Serial.print(serialCommand);
  // Serial.print(" ");
  // Serial.println(millis());

  // La bàn số comment chỗ này
  Serial2.write('z');  // request data from IMU
  while (!Serial2.available())
    ;                                       // waiting data coming from IMU
  uint8_t highByte = Serial2.read();        // encode using big endian
  uint8_t lowByte = Serial2.read();         // encode using big endian
  compassData = (highByte << 8) | lowByte;  // decode compassData
  Serial.print(compassData);
  Serial.print(" ");
  Serial.println(millis());
  // dieu chinh toc do robot
  if (serialCommand == 'g') {
    runSpeed = runSpeed1;
    curveSpeed = curveSpeed1;
    speedbanbong = speedbanbong1;
  } else if (serialCommand == 'h') {
    runSpeed = runSpeed2;
    curveSpeed = curveSpeed2;
    speedbanbong = speedbanbong2;
  }
  //code chuyen che do

  if (serialCommand == 'v') {
    isBallShootingMode = 0;
  } else if (serialCommand == 'n') {
    isBallShootingMode = 1;
  }

  else if (serialCommand == 'z') {
    serialCommand = 0;
    char temp;
    while (Serial3.available()) {
      temp = Serial3.read();
      delay(1);
    }
    int16_t setPoint = compassData - 1800;
    while (abs(compassData - setPoint) > 100) {
      Serial2.write('z');  // request data from IMU
      while (!Serial2.available())
        ;                                       // waiting data coming from IMU
      uint8_t highByte = Serial2.read();        // encode using big endian
      uint8_t lowByte = Serial2.read();         // encode using big endian
      compassData = (highByte << 8) | lowByte;  // decode compassData
      Serial.print(compassData); Serial.print(" "); Serial.print(setPoint);
      Serial.print(" ");
      Serial.println(millis());
      pid = PIDyaw(compassData, setPoint);
      // motor1(0 + pid);
      // motor2(0 + pid);
      // motor3(0 + pid);
      // motor4(0 + pid);
      motor1(-30);
      motor2(-30);
      motor3(-30);
      motor4(-30);
      delay(2);
    }
    motor1(0);
    motor2(0);
    motor3(0);
    motor4(0);
    while (Serial3.available()) {
      temp = Serial3.read();
      delay(1);
    }
  } else if (serialCommand == 'c') {
    serialCommand = 0;
    char temp;
    while (Serial3.available()) {
      temp = Serial3.read();
      delay(1);
    }
    debug--;
    Serial.print("c");

    int16_t setPoint = compassData + 1800;
    while (abs(compassData - setPoint) > 100) {
      Serial2.write('z');  // request data from IMU
      while (!Serial2.available())
        ;                                       // waiting data coming from IMU
      uint8_t highByte = Serial2.read();        // encode using big endian
      uint8_t lowByte = Serial2.read();         // encode using big endian
      compassData = (highByte << 8) | lowByte;  // decode compassData
      Serial.print(compassData); Serial.print(" "); Serial.print(setPoint);
      Serial.print(" ");
      Serial.println(millis());
      pid = PIDyaw(compassData, setPoint);
      // motor1(0 + pid);
      // motor2(0 + pid);
      // motor3(0 + pid);
      // motor4(0 + pid);
      motor1(30);
      motor2(30);
      motor3(30);
      motor4(30);
      delay(2);
    }
    motor1(0);
    motor2(0);
    motor3(0);
    motor4(0);
    while (Serial3.available()) {
      temp = Serial3.read();
      delay(1);
    }
  }
  gtcambien_1 = digitalRead(sensor_1);
  gtcambien_2 = digitalRead(sensor_2);
  if (serialCommand == 'a' && isBallShootingMode == 0) {
    while (serialCommand == 'a') {
      while (!Serial3.available())
        ;
      serialCommand = (char)Serial3.read();
      delay(2);
    }
    if (flag1 == 0) {
      xylanh_gap_1_off();
      flag1 = 1;
    } else {
      xylanh_gap_1_on();
      flag1 = 0;
    }
  } else if (serialCommand == 'w' && isBallShootingMode == 0) {
    while (serialCommand == 'w') {
      while (!Serial3.available())
        ;
      serialCommand = (char)Serial3.read();
      delay(2);
    }
    if (flag2 == 0) {
      xylanh_keo_1_off();
      flag2 = 1;
    } else {
      xylanh_keo_1_on();
      flag2 = 0;
    }
  } else if (serialCommand == 'd' && isBallShootingMode == 0) {
    while (serialCommand == 'd') {
      while (!Serial3.available())
        ;
      serialCommand = (char)Serial3.read();
      delay(2);
    }
    if (flag3 == 0) {
      xylanh_gap_2_off();
      flag3 = 1;
    } else {
      xylanh_gap_2_on();
      flag3 = 0;
    }
  } else if (serialCommand == 'x' && isBallShootingMode == 0) {
    while (serialCommand == 'x') {
      while (!Serial3.available())
        ;
      serialCommand = (char)Serial3.read();
      delay(2);
    }
    if (flag4 == 0) {
      xylanh_keo_2_off();
      flag4 = 1;
    } else {
      xylanh_keo_2_on();
      flag4 = 0;
    }
  }

  if (serialCommand == 'a' && isBallShootingMode == 1) {
    while (serialCommand == 'a') {
      while (!Serial3.available())
        ;
      serialCommand = (char)Serial3.read();
      delay(2);
    }
    if (flag5 == 0) {
      xylanh_gap_3_off();
      flag5 = 1;
    } else {
      xylanh_gap_3_on();
      flag5 = 0;
    }
  } else if (serialCommand == 'w' && isBallShootingMode == 1) {
    while (serialCommand == 'w') {
      while (!Serial3.available())
        ;
      serialCommand = (char)Serial3.read();
      delay(2);
    }
    if (flag6 == 0) {
      xylanh_keo_3_off();
      flag6 = 1;
    } else {
      xylanh_keo_3_on();
      flag6 = 0;
    }
  } else if (serialCommand == 'd' && isBallShootingMode == 1) {
    while (serialCommand == 'd') {
      while (!Serial3.available())
        ;
      serialCommand = (char)Serial3.read();
      delay(2);
    }
    if (flag7 == 0) {
      xucbong_off();
      flag7 = 1;
    } else {
      xucbong_on();
      flag7 = 0;
    }
  } else if (serialCommand == 'x' && isBallShootingMode == 1) {
    while (serialCommand == 'x') {
      while (!Serial3.available())
        ;
      serialCommand = (char)Serial3.read();
      delay(2);
    }
    if (flag8 == 0) {
      motorbanbongthuan();
      flag8 = 1;
    } else {
      motorbanbongdung();
      flag8 = 0;
    }
  }




  //move base
  if (serialCommand == NONE) {
    isTranslate = 0;
    motor1(0);
    motor2(0);
    motor3(0);
    motor4(0);
  } else if (serialCommand == R) {
    isTranslate = 0;
    motor1(-runSpeed);
    motor2(-runSpeed);
    motor3(-runSpeed);
    motor4(-runSpeed);
  } else if (serialCommand == L) {
    isTranslate = 0;
    motor1(runSpeed);
    motor2(runSpeed);
    motor3(runSpeed);
    motor4(runSpeed);
  }

  else if (serialCommand == UP) {
    if (isTranslate == 0) {
      isTranslate = 1;
      setPointZ = compassData;
    }
    pid = PIDyaw(compassData, setPointZ);
    motor1(+runSpeed + pid);
    motor2(-runSpeed + pid);
    motor3(-runSpeed + pid);
    motor4(+runSpeed + pid);
  } else if (serialCommand == UP_R) {
    isTranslate = 0;
    motor1(+runSpeed - curveSpeed);
    motor2(-runSpeed - curveSpeed);
    motor3(-runSpeed - curveSpeed);
    motor4(+runSpeed - curveSpeed);
  } else if (serialCommand == UP_L) {
    isTranslate = 0;
    motor1(+runSpeed + curveSpeed);
    motor2(-runSpeed + curveSpeed);
    motor3(-runSpeed + curveSpeed);
    motor4(+runSpeed + curveSpeed);
  }

  else if (serialCommand == DOWN) {
    if (isTranslate == 0) {
      isTranslate = 1;
      setPointZ = compassData;
    }
    pid = PIDyaw(compassData, setPointZ);
    motor1(-runSpeed + pid);
    motor2(+runSpeed + pid);
    motor3(+runSpeed + pid);
    motor4(-runSpeed + pid);
  } else if (serialCommand == DOWN_R) {
    isTranslate = 0;
    motor1(-runSpeed - curveSpeed);
    motor2(+runSpeed - curveSpeed);
    motor3(+runSpeed - curveSpeed);
    motor4(-runSpeed - curveSpeed);
  } else if (serialCommand == DOWN_L) {
    isTranslate = 0;
    motor1(-runSpeed + curveSpeed);
    motor2(+runSpeed + curveSpeed);
    motor3(+runSpeed + curveSpeed);
    motor4(-runSpeed + curveSpeed);
  }

  else if (serialCommand == RIGHT) {
    if (isTranslate == 0) {
      isTranslate = 1;
      setPointZ = compassData;
    }
    pid = PIDyaw(compassData, setPointZ);
    motor1(-runSpeed + pid);
    motor2(-runSpeed + pid);
    motor3(+runSpeed + pid);
    motor4(+runSpeed + pid);
  } else if (serialCommand == RIGHT_R) {
    isTranslate = 0;
    motor1(-runSpeed - curveSpeed);
    motor2(-runSpeed - curveSpeed);
    motor3(+runSpeed - curveSpeed);
    motor4(+runSpeed - curveSpeed);
  } else if (serialCommand == RIGHT_L) {
    isTranslate = 0;
    motor1(-runSpeed + curveSpeed);
    motor2(-runSpeed + curveSpeed);
    motor3(+runSpeed + curveSpeed);
    motor4(+runSpeed + curveSpeed);
  }

  else if (serialCommand == LEFT) {
    if (isTranslate == 0) {
      isTranslate = 1;
      setPointZ = compassData;
    }
    pid = PIDyaw(compassData, setPointZ);

    motor1(+runSpeed + pid);
    motor2(+runSpeed + pid);
    motor3(-runSpeed + pid);
    motor4(-runSpeed + pid);
  } else if (serialCommand == LEFT_R) {
    isTranslate = 0;
    motor1(+runSpeed - curveSpeed);
    motor2(+runSpeed - curveSpeed);
    motor3(-runSpeed - curveSpeed);
    motor4(-runSpeed - curveSpeed);
  } else if (serialCommand == LEFT_L) {
    isTranslate = 0;
    motor1(+runSpeed + curveSpeed);
    motor2(+runSpeed + curveSpeed);
    motor3(-runSpeed + curveSpeed);
    motor4(-runSpeed + curveSpeed);
  }

  else if (serialCommand == UP_RIGHT) {
    if (isTranslate == 0) {
      isTranslate = 1;
      setPointZ = compassData;
    }
    pid = PIDyaw(compassData, setPointZ);

    motor1(+0 + pid);
    motor2(-runSpeed + pid);
    motor3(+0 + pid);
    motor4(+runSpeed + pid);
  } else if (serialCommand == UP_RIGHT_R) {
    isTranslate = 0;
    motor1(+0 - curveSpeed);
    motor2(-runSpeed - curveSpeed);
    motor3(+0 - curveSpeed);
    motor4(+runSpeed - curveSpeed);
  } else if (serialCommand == UP_RIGHT_L) {
    isTranslate = 0;
    motor1(+0 + curveSpeed);
    motor2(-runSpeed + curveSpeed);
    motor3(+0 + curveSpeed);
    motor4(+runSpeed + curveSpeed);
  }

  else if (serialCommand == UP_LEFT) {
    if (isTranslate == 0) {
      isTranslate = 1;
      setPointZ = compassData;
    }
    pid = PIDyaw(compassData, setPointZ);

    motor1(+runSpeed + pid);
    motor2(+0 + pid);
    motor3(-runSpeed + pid);
    motor4(+0 + pid);
  } else if (serialCommand == UP_LEFT_R) {
    isTranslate = 0;
    motor1(+runSpeed - curveSpeed);
    motor2(+0 - curveSpeed);
    motor3(-runSpeed - curveSpeed);
    motor4(+0 - curveSpeed);
  } else if (serialCommand == UP_LEFT_L) {
    isTranslate = 0;
    motor1(+runSpeed + curveSpeed);
    motor2(+0 + curveSpeed);
    motor3(-runSpeed + curveSpeed);
    motor4(+0 + curveSpeed);
  }

  else if (serialCommand == DOWN_RIGHT) {
    if (isTranslate == 0) {
      isTranslate = 1;
      setPointZ = compassData;
    }
    pid = PIDyaw(compassData, setPointZ);
    motor1(-runSpeed + pid);
    motor2(+0 + pid);
    motor3(+runSpeed + pid);
    motor4(+0 + pid);
  } else if (serialCommand == DOWN_RIGHT_R) {
    isTranslate = 0;
    motor1(-runSpeed - curveSpeed);
    motor2(+0 - curveSpeed);
    motor3(+runSpeed - curveSpeed);
    motor4(+0 - curveSpeed);
  } else if (serialCommand == DOWN_RIGHT_L) {
    isTranslate = 0;
    motor1(-runSpeed + curveSpeed);
    motor2(+0 + curveSpeed);
    motor3(+runSpeed + curveSpeed);
    motor4(+0 + curveSpeed);
  }

  else if (serialCommand == DOWN_LEFT) {
    if (isTranslate == 0) {
      isTranslate = 1;
      setPointZ = compassData;
    }
    pid = PIDyaw(compassData, setPointZ);
    motor1(+0 + pid);
    motor2(+runSpeed + pid);
    motor3(+0 + pid);
    motor4(-runSpeed + pid);
  } else if (serialCommand == DOWN_LEFT_R) {
    isTranslate = 0;
    motor1(+0 - curveSpeed);
    motor2(+runSpeed - curveSpeed);
    motor3(+0 - curveSpeed);
    motor4(-runSpeed - curveSpeed);
  } else if (serialCommand == DOWN_LEFT_L) {
    isTranslate = 0;
    motor1(+0 + curveSpeed);
    motor2(+runSpeed + curveSpeed);
    motor3(+0 + curveSpeed);
    motor4(-runSpeed + curveSpeed);
  }
  // delay(100);
}
