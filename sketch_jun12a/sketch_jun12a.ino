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

int relay1 = 1;
int relay2 = 2;
int button = 3;

boolean buttons[6] = {false};

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  pinMode(button, INPUT);
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
  lup();
}
void lup()
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
void loop() {
  // put your main code here, to run repeatedly:
  bool temp = ps2x.Button(PSB_GREEN);
  if (temp != buttons[4]) {
    buttons[4] = temp;
    if (temp) {
      digitalWrite(relay1,1);
    } else {
      digitalWrite(relay1,0);
    }
  }
  temp = ps2x.Button(PSB_BLUE);
  if (temp != buttons[5]) {
    buttons[5] = temp;
    if (temp) {
      digitalWrite(relay2, 1);
    } else {
      digitalWrite(relay2,0);
    }
  }
}
