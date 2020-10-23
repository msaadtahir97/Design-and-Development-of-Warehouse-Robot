#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
SoftwareSerial softSerial(62,63);
int mid;        //sensor values 
int midleft;
int midright;
int left;
int right;
int IR_backright;
int IR_backleft;
long durationS1;
int distanceS1;
int IR_mid_pin = 48  ;       //sensors pin definition
int IR_mid_left_pin = 36;
int IR_mid_right_pin = 32;
int IR_left_pin = 28;
int IR_right_pin = 42;
int IR_backleft_pin = 26;
int IR_backright_pin = 22;
int L1 = 4;            //for motor
int L2 = 5;
int R1 = 7;
int R2 = 6;
int y=1;
int l;
int q=1;


String G="99117651";
String F="8320817351";
String H="831569551";
String I="8321224151";
String J="19511823751";
String K="12189751";
String L="2111421751";
String M="8324215851";
String N="99261251";
String O="11272051";
String P="19521920251";
String Q="8322219851";
String T="993216851";
String A="992011351";
String R="8323324551";
String S="991184051";
String hh="9911611251";
String ii="993019451";
String aa="992011351";
String bb="832086651";
String zz="2111421751";
String item;
int x[9];
int b=1;
int c=1;
char receive;
#define SS_PIN 49
#define RST_PIN 11
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 
// Init array that will store new NUID 
byte nuidPICC[4];
const int trigPinS1 = 2;
const int echoPinS1 = 3;
int Lift1 = 9;            //for motor
int Lift2 = 10;
void Proceed(void);
void Forward(void);
void Backward(void);
void Left(void);
void Right(void);
void Read(void);
void Up(void);
void Down(void);
void sonar(void);
void stopplate(void);
void rightninety(void);
void leftninety(void);void uturn(void);
void outofline(void);
void Adjust(void);
void ustop(void);
void restpoint(void);
void btcheck(void);

void setup() {
      Serial.begin(9600);
      pinMode(IR_mid_pin, INPUT);
      pinMode(IR_mid_left_pin, INPUT);
      pinMode(IR_mid_pin, INPUT);
      pinMode(IR_left_pin, INPUT);
      pinMode(IR_right_pin, INPUT);
      pinMode(IR_backleft_pin, INPUT);
      pinMode(IR_backright_pin, INPUT);
      pinMode(L1, OUTPUT);
      pinMode(L2, OUTPUT);
      pinMode(R1, OUTPUT);
      pinMode(R2, OUTPUT);
      pinMode(Lift1, OUTPUT);
      pinMode(Lift2, OUTPUT);
      pinMode(trigPinS1, OUTPUT); // Sets the trigPin as an Output
      pinMode(echoPinS1, INPUT); // Sets the echoPin as an Input
       softSerial.begin(9600);
       SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
      
      }
void(* resetFunc)(void)=0;
void loop() {
  btcheck();
}


void sonar()
{
  delay(300);
  // Clears the trigPin
  digitalWrite(trigPinS1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinS1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinS1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationS1 = pulseIn(echoPinS1, HIGH);
  // Calculating the distance
  distanceS1 = durationS1 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("DistanceS1: ");
  Serial.println(distanceS1);
}
void Read()
{
  mid = digitalRead(IR_mid_pin);
  Serial.print("mid ");
  Serial.println(mid);
  midleft = digitalRead(IR_mid_left_pin);
    Serial.print("midleft ");
  Serial.println(midleft);
  midright = digitalRead(IR_mid_right_pin);
    Serial.print("midright ");
  Serial.println(midright);
  left = digitalRead(IR_left_pin);
    Serial.print("left ");
  Serial.println(left);
  right = digitalRead(IR_right_pin);
    Serial.print("right ");
  Serial.println(right);
  IR_backleft = digitalRead(IR_backleft_pin);
  IR_backright = digitalRead(IR_backright_pin);   
  Serial.println("Read");  
  light();
}
void Forward()
{
    analogWrite(L1, 160);
    analogWrite(L2, 0);
    analogWrite(R1, 160);
    analogWrite(R2, 0);
    Serial.println("Forward");
    Read();
    delay(100);
}

void Backward()
{
    analogWrite(L1, 0);
    analogWrite(L2, 150);
    analogWrite(R1, 0);
    analogWrite(R2, 150);
    Serial.println("Backward");
    delay(100);
}

void Left()
{
    analogWrite(L1, 0);
    analogWrite(L2, 150);
    analogWrite(R1, 150);
    analogWrite(R2, 0);
    Serial.println("Left");
    Read();
    delay(100);
}

void Right()
{
    analogWrite(L1, 150);
    analogWrite(L2, 0);
    analogWrite(R1, 0);
    analogWrite(R2, 150);
    Serial.println("Right");
    Read();
    delay(100);
}


void Stop()
{
  while(1)
  {
  analogWrite(L1, 0);
  analogWrite(L2, 0);
  analogWrite(R1, 0);
  analogWrite(R2, 0);
  Serial.print("stop");
  Serial.println(" ");
  }
}

void rightninety()
{
  while(mid==0 || midright==0 || midleft==0)
    {
    analogWrite(L1, 180);
    analogWrite(L2, 0);
    analogWrite(R1, 0);
    analogWrite(R2, 180);
    Serial.println("Rightninetywithwhile");
    Read();
    }
    Read();
    Proceed(); 
}
void outofline()
{
  
    Serial.println("outoflinewithwhile");
    analogWrite(L1, 180);
    analogWrite(L2, 0);
    analogWrite(R1, 0);
    analogWrite(R2, 180); 
    delay(3000);
  }
  void restpoint()
{
    Read();
    Serial.println("outoflinewithwhile");
    analogWrite(L1, 0);
    analogWrite(L2, 180);
    analogWrite(R1, 180);
    analogWrite(R2, 0);
    delay(3000);
  }
  void uturn()
  {
    Serial.println("uturn");
    item="";
    outofline();
    rightninety();
    }
 void utstop()
  {
    Serial.println("ustop");
    item="";
    restpoint();
    while(midleft==1 || mid==1 || mid==1)
    {
     analogWrite(L1, 0);
    analogWrite(L2, 150);
    analogWrite(R1, 150);
    analogWrite(R2, 0);
    Serial.println("Left");
    Read();
      }
      Stop();
    }
void leftninety()
{
  Read();
  while(mid==0 || midright==0 || midleft==0)
    {
    analogWrite(L1, 0);
    analogWrite(L2, 180);
    analogWrite(R1, 180);
    analogWrite(R2, 0);
    Serial.println("Lefttninetywithwhile");
    Read();
    }
    Read();
    Proceed(); 
}
void Up()
{
    
    item="";
    Serial.println("motor stopped");
    Serial.println(" ");
    sonar();

    while(distanceS1 < 21)
    {
      Serial.println("lifting plates");
     analogWrite(L1, 0);
    analogWrite(L2, 0);
    analogWrite(R1, 0);
    analogWrite(R2, 0);
    analogWrite(Lift1, 0);
    analogWrite(Lift2, 180);
    sonar();
    }
    analogWrite(Lift1, 0);
    analogWrite(Lift2, 0);
    delay(200);
    Read();
    Proceed();
}
void Down()
{
    
    item="";
    Serial.println("motor stopped");
    Serial.println(" ");
    sonar();

    while(distanceS1 > 17)
    {
      Serial.println("lifting plates");
     analogWrite(L1, 0);
    analogWrite(L2, 0);
    analogWrite(R1, 0);
    analogWrite(R2, 0);
    analogWrite(Lift1, 180);
    analogWrite(Lift2, 0);
    sonar();
    }
    analogWrite(Lift1, 0);
    analogWrite(Lift2, 0);
    delay(200);
    Read();
    
}


void stopplate()
{
  analogWrite(Lift1, 0);
    analogWrite(Lift2, 0);
    Read();
    Proceed();
  }
void Proceed()

{
  Serial.println("Proceed");
  Read();
  if(mid==1 && midleft==1 && midright==1 && right==0 && left==0)
{
    Forward();
    Serial.println("forward");
    Serial.println(" ");
    }
  
   if(mid==1 && midleft==1 && midright==0 && right==0 && left==0)
   {
    Serial.println("left");     
    Serial.println(" ");
    Left();
   
   }
   if(mid==0 && midright==1 && midleft==0 && left==0 && right==0 )
   {
    Serial.println("Right");     
    Serial.println(" ");
    Right();
    } 
 if(mid==0 && midleft==1 && midright==0 && right==0 && left==0)
        {  
          
          Serial.println("left");
          Serial.println(" ");
          Left(); 
          
          }
         
if(mid==1 && midleft==0 && midright==1 && right==0 && left==0)
       {Serial.println("right");
        Serial.println(" ");     
        Right();
       
       }
if((mid==1 || midright==1) && right==1)
            {
              Serial.println(" ");
              analogWrite(L1, 160);
              analogWrite(L2, 0);
              analogWrite(R1, 160);
              analogWrite(R2, 0);
              delay(1800);
              Serial.println("rightninety");
              rightninety();
             }
 if((mid==1 || midleft==1) && left==1)
            {
              analogWrite(L1, 160);
              analogWrite(L2, 0);
              analogWrite(R1, 160);
              analogWrite(R2, 0);
              Serial.println(" ");
              delay(1800);
              Serial.println("leftninety");
              leftninety();
             }
if(mid==0 && midleft==0 && midright==0 && right==0 && left==0)
   {
    Stop();
    }
}
void light()
{
  radio();
  if(l==1)
  { 
     
                if(item==H || item==I || item==bb)
                {
                  item="";
                  Up();
                  }

                  if(q==1)
                  {
                if(item==S || item==R || item==ii )
                {
                  
                 q=2;
                  item="";
                  uturn();
                  Down();
                }
                  }
                item="";
  }

   if(l==2)
  {

                if(item==K || item==G || item==F)
                {
                  item="";
                  Down();
                

                }
                  if (item==S || item==R || item==ii)
                  {
                    item="";
                    Up();
                    uturn();
                    }
                item="";
  }
  }

void radio() {

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;


 for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
  printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
   rfid.PICC_HaltA();

  
  rfid.PCD_StopCrypto1();
  
}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : "");
    
    item+=String(buffer[i]);
  }

  Serial.println(" ");
  Serial.println(item);
  

}

void Adjust()
{
  Serial.println("Adjust");
  while(IR_backleft==0 || IR_backright==0)
  {
    if(IR_backright==0 && IR_backleft==1)
    {
    analogWrite(L1, 150);
    analogWrite(L2, 0);
    analogWrite(R1, 0);
    analogWrite(R2, 150);

    Serial.println("backRIGHT");
    Read();
    delay(100);
    }
    if(IR_backleft==0 && IR_backright==1)
    {
    analogWrite(L1, 0);
    analogWrite(L2, 150);
    analogWrite(R1, 150);
    analogWrite(R2, 0);
    Serial.println("backLEFT");
    Read();
    delay(100);
    }

    if(IR_backleft==0 && IR_backright==0)
    {
    analogWrite(L1, 150);
    analogWrite(L2, 0);
    analogWrite(R1, 0);
    analogWrite(R2, 150);
    Serial.println("backRightboth");
    Read();
    delay(100);
    }

    
  }
}

void btcheck()
{
  if(softSerial.available() > 0)
  { // Checks whether data is comming from the serial port
  receive = softSerial.read(); // Reads the data from the serial port
  Serial.println(receive);
 }
 if (receive == 'A') {
  Serial.println(receive);
  l=1;
  Proceed();


 }
 else if (receive == 'B' ) {
  l=2;
  Proceed();


 } 
} 
