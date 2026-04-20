#include <SoftwareSerial.h>

SoftwareSerial gsm(10, 11);

int trig1 = 2, echo1 = 3;
int trig2 = 4, echo2 = 5;
int trig3 = 6, echo3 = 7;
int trig4 = 8, echo4 = 9;

int threshold = 10;

String number = "+91XXXXXXXXXX";

void setup() {
  gsm.begin(9600);

  pinMode(trig1, OUTPUT); pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT); pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT); pinMode(echo3, INPUT);
  pinMode(trig4, OUTPUT); pinMode(echo4, INPUT);
}

int check(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long t = pulseIn(echo, HIGH);
  int d = t * 0.034 / 2;

  if(d < threshold) return 1; // occupied
  else return 0; // free
}

void loop() {

  int s1 = check(trig1, echo1);
  int s2 = check(trig2, echo2);
  int s3 = check(trig3, echo3);
  int s4 = check(trig4, echo4);

  String msg = "";

  if(s1==0) msg += "Slot1 Free\n";
  if(s2==0) msg += "Slot2 Free\n";
  if(s3==0) msg += "Slot3 Free\n";
  if(s4==0) msg += "Slot4 Free\n";

  if(msg == "") msg = "Parking Full";

  gsm.println("AT+CMGF=1");
  delay(1000);

  gsm.print("AT+CMGS=\"");
  gsm.print(number);
  gsm.println("\"");

  delay(1000);
  gsm.print(msg);
  gsm.write(26);

  delay(20000); // 20 sec gap
}