int LPWM = 11;
int RPWM = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(LPWM, OUTPUT);
  pinMode(RPWM, OUTPUT);
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
}
int c = 0;
void loop() {
  // put your main code here, to run repeatedly:
  c = 0;
  analogWrite(RPWM, 0);
  for(; c <= 255; c ++){
    analogWrite(LPWM, c);
    delay(10);
  }
  for(; c >= 0; c --){
    analogWrite(LPWM, c);
    delay(10);
  }
  delay(1000);

  c = 0;
  analogWrite(LPWM, 0);
  for(; c <= 255; c ++){
    analogWrite(RPWM, c);
    delay(10);
  }
  for(; c >= 0; c --){
    analogWrite(RPWM, c);
    delay(10);
  }
  delay(1000);


}
