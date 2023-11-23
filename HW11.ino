#include "Clicky.h"


int button0 = 0;
int button1 = 1;
bool GreenState = false;
bool RedState = false;
int cCount = 0;
int threshold  = 4000;

int button0_State = 0;
int button1_State = 0;

Clicky Button_0;
Clicky Button_1;
float potentiometer;


void setup() {
  Button_0.setup(2);
  Button_1.setup(3);

  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  int a0v = analogRead(A0);
  Serial.begin(9600);

}

void loop() {
  bool is_button0_clicked = Button_0.wasClicked();
  bool is_button1_clicked = Button_1.wasClicked();
  int a0 = analogRead(A0);

  if (is_button0_clicked && button0_State == 0 && button1_State == 0) {
    button0_State = 1;
    cCount++;
  }else if (is_button1_clicked && button0_State == 1 && button1_State == 0){
    button1_State = 1;
    cCount++;
  }else if (is_button1_clicked && button1_State == 1 && button0_State == 1){
    GreenState = true;
    cCount++;
  }else if(is_button0_clicked || is_button1_clicked) {
    cCount++;
  }
  
  if (GreenState == false && cCount == 3){
    RedState = true;
  }
  
  if (GreenState && a0 > 4000){
    digitalWrite(5, HIGH);
    delay(500);
    digitalWrite(5, LOW);
    delay(500);
  }else if(RedState){
    digitalWrite(6, HIGH);
    delay(500);
    digitalWrite(6, LOW);
    delay(500);
  }

  Serial.println("Button_0_State" + String(button0_State)+ "Button_1_State?" + String(button1_State) + "cCount" + String(cCount) + String(a0));


  delay(10);

}
