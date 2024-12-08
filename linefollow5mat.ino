#include <PS2X_lib.h> 
#include <Servo.h>    

// Khai báo đối tượng myservo dùng để điều khiển servo

Servo myservo;          //servo den len xuong
Servo myservo1;         //servo tay gap
Servo myservo2;         //servo ban bong
int servoPin = 21;
int servoPin1 = 20;
int servoPin2 = 19;
//Khai báo
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define PS2_DAT 13// data
#define PS2_CMD 11 //command
#define PS2_SEL 10 // attention
#define PS2_CLK 12 //clock
PS2X ps2x; // tạo PS2 điều khiển lớp

int error = 0;
byte type = 0;
byte vibrate = 0;

//definition of pid module
int banbong = 6 ;
int DC1_A = 5;
int DC1_B = 4;
int DC2_A = 2;
int DC2_B = 3;

int led[5] = {14, 15, 16, 17, 18};

bool state = true;

bool buttons[10] = {false};

// Setup
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup(){
  //khai bao servo

  myservo.attach(servoPin);
  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
  
  //khai bao chan xung  
  
  for(int c = 0; c < 5; c ++)
    pinMode(led[c], INPUT);
  pinMode(banbong,OUTPUT);
  pinMode(DC1_A, OUTPUT);
  pinMode(DC2_A, OUTPUT);
  pinMode(DC1_B, OUTPUT);
  pinMode(DC2_B, OUTPUT);
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
  for(int c = 0; c < 3; c ++)
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

int MAX_SPEED = 250; // SPEED

// loop
//==================================================================

void loop() {
  ps2x.read_gamepad(false, vibrate);
  if(ps2x.ButtonPressed(PSB_R2)){
    state = !state;
  }

  if(state){
    ProcessMotor();
    taygap();
  }else{
   doline();
  }
}


// Di chuyển
//=========================================================================================

void ProcessMotor(){
  if(ps2x.Button(PSB_PAD_UP)){
    analogWrite(DC1_A, MAX_SPEED);
    analogWrite(DC2_A, MAX_SPEED);
  }else if(ps2x.Button(PSB_PAD_DOWN)){
    analogWrite(DC1_B, MAX_SPEED);
    analogWrite(DC2_B, MAX_SPEED);
  }else if(ps2x.Button(PSB_R1)){
    analogWrite(DC1_B, 250 );
    analogWrite(DC2_A, 255);
  }else if(ps2x.Button(PSB_L1)){
    analogWrite(DC1_A, 255);
    analogWrite(DC2_B, 255);
  }else{
    analogWrite(DC1_A, 0);
    analogWrite(DC1_B, 0);
    analogWrite(DC2_A, 0);
    analogWrite(DC2_B, 0);
  }
  
}

// Dò line
// =================================================================================================================
void E(int e){
  if(e == 1){
    analogWrite(DC1_A, 0);
    analogWrite(DC2_A, 0);
    analogWrite(DC1_B, 0);
    analogWrite(DC2_B, 0);    
  }else if(e == 2){
      analogWrite(DC1_B, 0);
      analogWrite(DC2_B, 0);
      analogWrite(DC1_A, 200 );
      analogWrite(DC2_A, 200 );  
  }else if(e == 3){
      analogWrite(DC1_B, 200);
      analogWrite(DC2_B, 0);
      analogWrite(DC1_A, 0);
      analogWrite(DC2_A, 200);
  }else if(e == 4){
      analogWrite(DC1_B, 0);
      analogWrite(DC2_B, 200);
      analogWrite(DC1_A, 200);
      analogWrite(DC2_A, 0);  
  }else if(e == 5){
      analogWrite(DC1_B, 250);
      analogWrite(DC2_B, 0);
      analogWrite(DC1_A, 0);
      analogWrite(DC2_A, 250);  
  }else if(e == 6){
      analogWrite(DC1_B, 0);
      analogWrite(DC2_B, 250);
      analogWrite(DC1_A, 250);
      analogWrite(DC2_A, 0);
  }
}
int e = 0;
void doline(){
  int sens[5];
  for(int c = 0; c < 5; c ++)
    sens[c] = digitalRead(led[c]);
  led[4] = 1;
  if(!sens[0] and !sens[1] and !sens[2] and !sens[3] and !sens[4]){
      e = 1;
      analogWrite(DC1_A, 0);
      analogWrite(DC2_A, 0);
      analogWrite(DC1_B, 0);
      analogWrite(DC2_B, 0);
  }else if(!sens[2]){
      e = 2;
      analogWrite(DC1_B, 0);
      analogWrite(DC2_B, 0);
      analogWrite(DC1_A, 200 );
      analogWrite(DC2_A, 200 );  
  }else if(!sens[1]){
      e = 3;
      analogWrite(DC1_B, 200);
      analogWrite(DC2_B, 0);
      analogWrite(DC1_A, 0);
      analogWrite(DC2_A, 200);
  }else if(!sens[3]){
      e = 4;
      analogWrite(DC1_B, 0);
      analogWrite(DC2_B, 200);
      analogWrite(DC1_A, 200);
      analogWrite(DC2_A, 0);  
  }
  else if(!sens[0]){
      e = 5;
      analogWrite(DC1_B, 250);
      analogWrite(DC2_B, 0);
      analogWrite(DC1_A, 0);
      analogWrite(DC2_A, 250);  
  }
  else if(!sens[4]){
      e = 6;
      analogWrite(DC1_B, 0);
      analogWrite(DC2_B, 250);
      analogWrite(DC1_A, 250);
      analogWrite(DC2_A, 0);
  }
  else{
    E(e);
  }
}
// Chức năng
//===============================================================
bool dabanchua = false;
bool dalenchua = false;
bool dagapchua = false;
bool danapbongchua = false;
void taygap() {
  //servo den len xuong
  //....................................................................
  if(ps2x.ButtonPressed(PSB_BLUE))           //tay len bo bong
    if (!dalenchua)
      myservo.write(160), dalenchua = true;
    else
      myservo.write(0), dalenchua = false;
  bool temp = (ps2x.Analog(PSS_RY) == 0);    //tay len gap co
  if(temp != buttons[0]){
    buttons[0] = temp;
    if(temp)
      myservo.write(100);
  }
  temp = (ps2x.Analog(PSS_RY) == 255);       //tay xuong
  if(temp != buttons[1]){
    buttons[1] = temp;
    if(temp)
      myservo.write(0);
  }
  //tay gap bong
  //...................................................................
  if(ps2x.ButtonPressed(PSB_PINK))
    if (!dagapchua)
      myservo1.write(25),dagapchua = true;
    else
      myservo1.write(0), dagapchua = false;
  //may ban bong
  //...................................................................
  if(ps2x.ButtonPressed(PSB_RED))
    if (!danapbongchua)                                  //servo day bong
      myservo2.write(180),danapbongchua = true;
    else
      myservo2.write(0),danapbongchua =false;
  
  if(ps2x.ButtonPressed(PSB_L2))                         //banh xe ban bong
    if(!dabanchua)
      analogWrite(6,120) ,dabanchua = true;
    else
      analogWrite(6,0), dabanchua = false;
  if(ps2x.ButtonPressed(PSB_GREEN))                         //banh xe ban bong
    if(!dabanchua)
      digitalWrite(6,1) ,dabanchua = true;
    else
      digitalWrite(6,0), dabanchua = false;
}