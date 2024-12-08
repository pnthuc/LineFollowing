 #include <PS2X_lib.h> // 1.6v thư viện
//------------------------------Khai báo---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
bool isCloseR = false; //Tay phải đóng hay mở
bool isCloseM = false; //Tay giữa đóng hay mở
bool isCloseBoth = false; //Ktra cả 2 tay đang đóng hay mở
//bool isPress1 = false, isPress2 = false;
//Ổ bi,dùng digital
#define obi_1 28 //Kéo lên
#define obi_2 30 //Kéo xuống
//0:tay trai,1:tay phai,2:tay giua,3:dong mo ca 2 tay,4:d/c keo di len, 5:d/c keo di xuong
boolean buttons[6] = {false};
//--------------------------------Setup---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
int MAX_SPEED = 255; // SPEED
//==============================loop=====================================================================================================================================================================================================================================================
void loop() {
 ProcessMotor();
 delay(50);
 taygap();
 delay(10);
}
//=====================================================Di chuyển===================================================================================================================================================================================================================================
void Stop(){
  for(int c = 0; c < 4; c ++){
    analogWrite(MotorInput[c], 0);
    analogWrite(MotorOutput[c], 0);
  }
}
void Forward(){
  for(int c = 0; c < 4; c ++){
    analogWrite(MotorInput[c], MAX_SPEED);
    analogWrite(MotorOutput[c], 0);    
  }
}
void Backward(){
  for(int c = 0; c < 4; c ++){
    analogWrite(MotorInput[c], 0);
    analogWrite(MotorOutput[c], MAX_SPEED);    
  }
}
void Left(){
  for(int c = 0; c < 4; c ++){
    analogWrite(MotorInput[c], MAX_SPEED * (c % 2));
    analogWrite(MotorOutput[c], MAX_SPEED * !(c % 2));
  }
}
void Right(){
  for(int c = 0; c < 4; c ++){
    analogWrite(MotorInput[c], MAX_SPEED * !(c % 2));
    analogWrite(MotorOutput[c], MAX_SPEED * (c % 2));
  }  
}
void ProcessMotor(){
  if(ps2x.ButtonPressed(PSB_PAD_UP)){
    Forward();
  }else if(ps2x.ButtonPressed(PSB_PAD_DOWN)){
    Backward();
  }else if(ps2x.ButtonPressed(PSB_PAD_LEFT)){
    Left();
  }else if(ps2x.ButtonPressed(PSB_PAD_RIGHT)){
    Right();
  }else Stop();
}
//=========================================Chức năng====================================================================================================================================================================================================================================================
bool isMove_obi = false;
void taygap() {
  //ps2x.read_gamepad(false, vibrate);
  //----------------Ổ bi-------------------------------------------------------------------------
  bool temp = ps2x.Button(PSB_GREEN);
  if (temp != buttons[4]) {
    buttons[4] = temp;
    if (temp) {
      digitalWrite(obi_1,1);
      //Serial.println("Keo Len");
    } else {
      digitalWrite(obi_1,0);
     // Serial.println("STOP keo");
    }
  }
  temp = ps2x.Button(PSB_BLUE);
  if (temp != buttons[5]) {
    buttons[5] = temp;
    if (temp) {
      digitalWrite(obi_2, 1);
   //   Serial.println("Keo Xuong");
    } else {
     // Serial.println("Stop keo");
      digitalWrite(obi_2,0);
    }
  }
  // DONE
  //------------------Tay Gắp-------------------------------------------------------------------------
  temp = ps2x.Button(PSB_L1);
  if (temp != buttons[0]) { //Tay Trái
    buttons[0] = temp;
    if (temp) {
      if (!isCloseL) {
        Serial.println("Dong tay trai");
        //digitalWrite(13, HIGH);
        digitalWrite(LeftHand, 1);
        isCloseL = true;
      } else {
        Serial.print("Mo tay trai");
       // digitalWrite(13, LOW);
        digitalWrite(LeftHand, 0);
        isCloseL = false;
      }
    }
  }
  //-----------------------------------------------
  temp = ps2x.Button(PSB_R1);
  if (temp != buttons[1]) { //Tay Phải
    buttons[1] = temp;
    if (temp) {
      if (!isCloseR) {
       // Serial.println("Dong tay phai");
        digitalWrite(RightHand, 1);
        isCloseR = true;
      } else {
      //  Serial.println("Mo tay phai");
        digitalWrite(RightHand, 0);
        isCloseR = false;
      }
    }
  }
  //-----------------------------------------------
  temp = ps2x.Button(PSB_R2);
  if (temp != buttons[2]) { //Tay Giữa
    buttons[2] = temp;
    if (temp) {
      if (!isCloseM) {
     //   Serial.println("Dong tay giua");
        digitalWrite(MiddleHand, 1);
        isCloseM = true;
      } else {
      //  Serial.println("Mo tay giua");
        digitalWrite(MiddleHand, 0);
        isCloseM = false;
      }
    }
  }
  //-----------------------------------------------
  temp = ps2x.Button(PSB_L2);
  if (temp != buttons[3]) { //Đóng mở 2 tay cùng lúc
    buttons[3] = temp;
    if (temp) {
      if(isCloseL && isCloseR){
        digitalWrite(LeftHand, 0);
        digitalWrite(RightHand, 0);
        isCloseL = false;
        isCloseR = false;
      }
      else if(!isCloseL && !isCloseR) {
        //Serial.println("Mo ca hai tay");
        digitalWrite(LeftHand, 1);
        digitalWrite(RightHand, 1);
        isCloseL = true;
        isCloseR = true;
      }
      else if (isCloseL || isCloseR) {
       // Serial.println("Dong ca hai tay");
        digitalWrite(LeftHand,0);
        digitalWrite(RightHand, 0);
        isCloseL = false;
        isCloseR = false;
      } 
    }
  }
  // DONE
  //------------------Tay Quay-------------------------------------------------------------------------  

/*
 * kfha klghdfkl hglkfhg 
 *  gdflshgl khsdflkg hlkdf
 *   dfsgh jklfsdheglk hdfsg 
 *   ghldksf hgldfh s;g 
 *    ldkfshg jlkdfhs gkjldfshk jlghdsf
 *    hg hljkfdhg jkldfshg jkldfshg kljdfhg kldfhg 
 */
  
}
