#include <PS2X_lib.h> 

#define PS2_DAT 13// data
#define PS2_CMD 11 //command
#define PS2_SEL 10 // attention
#define PS2_CLK 12 //clock
PS2X ps2x; // tạo PS2 điều khiển lớp
int error = 0;
byte type = 0;
byte vibrate = 0;

//Chẵn là dương thì thuận chiều, lẽ là dương thì ngược chiều

const byte MotorInput[4] = {2, 4, 6, 8};
const byte MotorOutput[4] = {3, 5, 7, 9};
//Pittong - Dùng High,Low
#define LeftHand 22
#define RightHand 24
#define MiddleHand 26
bool isCloseL = false; //Ktra tay trái đóng hay mở
bool isCloseR = false;  
bool isCloseM = false;
bool isCloseBoth = false; //Ktra cả 2 tay đang đóng hay mở
bool isPress1 = false, isPress2 = false;
//Ổ bi,dùng digital
#define obi_1 28
#define obi_2 30
//0:tay trai,1:tay phai,2:tay giua,3:dong mo ca 2 tay,4:d/c keo di len, 5:d/c keo di xuong
boolean buttons[6] = {false};
//---------------------------------------------------------------------------------------------------------------------------------
void setup()
{
  pinMode(LeftHand,OUTPUT);
  pinMode(RightHand,OUTPUT);
  pinMode(MiddleHand,OUTPUT);
  pinMode(obi_1,OUTPUT);
  pinMode(obi_2,OUTPUT);
  delay(500);
  Serial.begin(9600);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
  if (error == 0) {
    Serial.print("Đã tìm thấy bộ điều khiển ");
  }
  else if (error == 1)
    Serial.println("Không kết nối đc, thử lại...");

  else if (error == 2)
    Serial.println("Bộ điều khiển tìm thấy nhưng không chấp nhận lệnh");

  else if (error == 3)
    Serial.println("Bộ điều khiển từ chối để vào chế độ Pressures ,hoặc ko hỗ trợ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Tay điều khiển không phù hợp ");
      break;
    case 1:
      Serial.println("Đã tìm thấy DualShock ");
      break;
  }
  
  a();
}
void a()
{
  delay(500);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
  if (error == 0) {
    Serial.print("Đã tìm thấy bộ điều khiển ");
  }
  else if (error == 1)
    Serial.println("Không kết nối đc, thử lại...");

  else if (error == 2)
    Serial.println("Bộ điều khiển tìm thấy nhưng không chấp nhận lệnh");

  else if (error == 3)
    Serial.println("Bộ điều khiển từ chối để vào chế độ Pressures ,hoặc ko hỗ trợ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Tay điều khiển không phù hợp ");
      break;
    case 1:
      Serial.println("Đã tìm thấy DualShock ");
      break;
  }

}

int Channels[3] = {0};
long long int sys_start = 0;
int MAX_SPEED = 255;
int MIN_SPEED = -MAX_SPEED;
//=======================================================================================================================================
void loop() {
 buttonState();
 ProcessMotor();
}

void buttonState() {


  ps2x.read_gamepad(false, vibrate);

  Channels[0] = map(ps2x.Analog(PSS_LY), 256, 0, -255, 255);
  Channels[2] = map(ps2x.Analog(PSS_LX), 0, 256, -255, 255);
  Channels[1] = map(ps2x.Analog(PSS_RX), 0, 256, -255, 255);

  for (int i = 0; i < 3; i++) {
    if (abs(Channels[i]) <= 100) {
      Channels[i] = 0;
    }
  }

  int sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += abs(Channels[i]);
  }
  sum /= 3;
  if (sum < 20) {
    sys_start = millis();
  }

  Channels[1] /= 2;
  Channels[2] /= 1.5;
  if (millis() - sys_start < 400) {  
   Channels[2] = (float)(Channels[2] * ((millis() - sys_start + 310)) / 710);
   Channels[0] = (float)(Channels[0] * ((millis() - sys_start + 100)) / 500);
   Channels[1] = (float)(Channels[1] * ((millis() - sys_start + 310)) / 710);
  }

  
    Serial.print(Channels[0]);
    Serial.print("    ");
    Serial.print(Channels[1]);
    Serial.print("    ");
    Serial.print(Channels[2]);
    Serial.println();
}
void ProcessMotor() {

  int Motors[4] = {0};
  Motors[0] = Channels[0];
  Motors[1] = Channels[0];
  Motors[2] = Channels[0];
  Motors[3] = Channels[0];

  Motors[0] += Channels[1];
  Motors[1] -= Channels[1];
  Motors[2] -= Channels[1];
  Motors[3] += Channels[1];

  Motors[0] += Channels[2];
  Motors[1] -= Channels[2];
  Motors[2] += Channels[2];
  Motors[3] -= Channels[2];

  SetSpeed(Motors);
}
int SetSpeed(int* motors) {
  Constrains(motors);
  for (int i = 0; i < 4; i++) {
    if (motors[i] >= 0) {
      analogWrite(MotorInput[i], motors[i]);
      analogWrite(MotorOutput[i], 0);
    } else {
      analogWrite(MotorInput[i], 255 + motors[i]);
      analogWrite(MotorOutput[i], 255);
    }

  }
}
void Constrains(int *motors) {
  int TEMP_MAX_SPEED = 0;
  if (millis() - sys_start < 400) {
    TEMP_MAX_SPEED = (float)(MAX_SPEED * ((millis() - sys_start + 800)) / 1200);
  } else {
    TEMP_MAX_SPEED = MAX_SPEED;
  }

  int TEMP_MIN_SPEED = -TEMP_MAX_SPEED;

  int temp = TEMP_MIN_SPEED;
  for (int i = 0; i < 4; i++) {
    if (motors[i] > temp) {
      temp = motors[i];
    }
  }

  if (temp > TEMP_MAX_SPEED) {
    float ratio = (float)TEMP_MAX_SPEED / temp;
    for (int i = 0; i < 4; i++) {
      motors[i] *= ratio;
    }
  }

  temp = TEMP_MAX_SPEED;
  for (int i = 0; i < 4; i++) {
    if (motors[i] < temp) {
      temp = motors[i];
    }
  }

  if (temp < TEMP_MIN_SPEED) {
    float ratio = (float)TEMP_MIN_SPEED / temp;
    for (int i = 0; i < 4; i++) {
      motors[i] *= ratio;
    }
  }
}
