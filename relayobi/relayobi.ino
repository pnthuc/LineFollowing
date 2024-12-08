////////////////////////////////////////////////////////////////////////////////////////
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
  //------------------Tay Gắp--------------------------------------
  
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
}
////////////////////////////////////////////////////////////////////////
