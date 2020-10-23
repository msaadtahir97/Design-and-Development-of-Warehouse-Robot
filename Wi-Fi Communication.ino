#include <SoftwareSerial.h>
int x=0;
int humd =50;
String output5State = "off"; 
String response = "";
String temp;
SoftwareSerial esp8266(12,13); //  RX  is pin 2,  TX Arduino line is pin 3.
#define DEBUG true                            



void setup()
{
  Serial.begin(9600);

  
  
  esp8266.begin(115200);

  
  sendData("AT+UART_DEF=9600,8,1,0,0\r\n",2000,DEBUG);
  esp8266.end();

  

  esp8266.begin(9600);

  sendData("AT+RST\r\n",2000,DEBUG); // rst
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); //   AP + Station mode, dual mode!
  sendData("AT+CWJAP=\"AndroidAPAACA\",\"saad2005\"\r\n",3000,DEBUG); //connect to "Memoon" router
  delay(5000);  //Time given to establish a stable connection
  //sendData("AT+CWSAP=\"Memoon\",\"12345678\",5,0\r\n",3000,DEBUG);  //give name to the local server of ESP8266
  //sendData("AT+CWLAP\r\n",1000,DEBUG);
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  //sendData("AT+CWJAP\r\n",1000,DEBUG); // get ssid
  sendData("AT+CIPSTATUS\r\n",1000,DEBUG);
  //sendData("AT+CIPSTA\r\n",1000,DEBUG);
  //sendData("AT+CWDHCP=2,0\r\n",1000,DEBUG);
  pinMode(8, OUTPUT);
}
 
void loop()
{
  humd=analogRead(A0);
  temp=String(humd)+"%";
  
  if(esp8266.available()) // check if the esp is sending a message 
  {
    if(esp8266.find("+IPD,"))
    {
     delay(300);
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
                                           // '0' - 48 = 0
                                           // '1' - 48 = 1
     
  //String webpage = "<head><meta http-equiv=""refresh"" content=""600""></head>";
PROGMEM String webpage = "<head><meta http-equiv=""refresh"" content=""600""></head>";
 webpage+="<body style='background-color:MediumSeaGreen;'>";
 webpage+="<style>     .button {background-color: #0099cc;border: 2px solid #3B6A6A ;color: #892C27 ;padding: 15px 32px; font-weight: bold; text-align: center;text-decoration: none;display: inline-block;font-size: 16px;margin: 4px 2px;cursor: pointer;}   </style>";
 webpage+="<style>     .button1 {background-color: Red;border: 2px solid brown ;color: black ;padding: 14px 44px; font-weight: bold; text-align: center;text-decoration: none;display: inline-block;font-size: 35px;margin: 4px 2px;cursor: pointer;}   </style>";

 webpage+= "<style> div { background-color: #ACADB4; width: 100px; color: brown; border: 2px solid #609782; padding: 15px 32px; margin: 4px 2px; } </style>";
 webpage+= "<style> .div1 { background-color: #CFD3E6; width: 400px; border: 2px solid #609782; padding: 0px 32px; margin: 4px 2px; } </style>";
 
 webpage+="<br>";
  webpage+="</br>";
   webpage+="<br>";
  webpage+="</br>";
  webpage+="<center><div class='div1'><h1><font color='red'>Warehouse User Interface</font></h1></div></center>";

    webpage+="<br>";
    webpage+="</br>";


  
 


 
 
 

  
  
  //If we get a response that switch is off, we change the button display to "ON"

        
         webpage+="<form method=\"get\">";
     
         /*webpage+="<center><p><form><input type= 'text' id='foo' placeholder='onetotwo'></p></center>";*/
        
        webpage+="<center><select id='foo' style='padding: 15px 32px; border: 2px solid #325B5B; font-weight: bold; background-color: #58B9B4; color: #892C27'><option value='Select'>Select Task</option><option value='Stationone'>Station1 to Station2</option><option value='Stationtwo'>Station2 to Station1</option><option value='hello'>Station1 to Station3</option><option value='audi'>Station3 to Station2</option></select></center>";


         
          webpage+="<center><h2><input type=button class=button value='Schedule Task' onmousedown=location.href=document.getElementById('foo').value></h2></center>"; 
          webpage+="<br>";
          webpage+="</br>";
        

          webpage+="<center><div><b>Battery Status</b></div></center>";
          webpage+="<center><h4><font color='red'; size='6'>";
          webpage+=temp;
          webpage+="</font></h4></center>";

          webpage+="<br>";
          webpage+="</br>";

          
          
          webpage+="<center><h5><input type=button class=button1 value='Emergency Stop' onmousedown=location.href='RobotStop'></h5></center>"; 
   
          
          
    
  
 /*webpage+="<p><a href=\"/5/on\"><button class=\"button1\">ON</button></a></p>";
  
  //Else if we get a response that switch is on, we change the button display to "OFF"
  
 /* webpage+="<p><a href=\"/5/off\"><button class=\"button2\">OFF</button></a></p>";
  */
  webpage+="</body></html>";

    
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);

     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);

     
    }

    
    
  }
}
 
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }
//Now read the modified header index that contains data sent by the user through the webpage
//Here we are sending "/5/on" or "/5/off" to indicate the state of button named "5"
//"output5state" is a variable string that contains the current state of button "5"
//If we get a response that switch is off, we change the state to "off" and vice versa


 if (response.indexOf("Stationone") >= 0) {
  delay(10000);
  digitalWrite(8,LOW);
  delay(10000);
  digitalWrite(8,HIGH);
              }
 if (response.indexOf("RobotStop") >= 0) {
  
             delay(1000);
             
              digitalWrite(8,LOW);
              } 
              


                        
    
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    return response;
}


int parse(String command){
    char charBuf[20];
    command.toCharArray(charBuf, 20);
    
    //Begin black magic supplied by @mdma at:
    // https://community.spark.io/t/gpio-control-via-gui/6310/7
    const int value_count = 8;  // the maximum number of values
    int values[value_count];    // store the values here
    
    char string[20];
    strcpy(string, charBuf);  // the string to split
    int idx = 0;
    for (char* pt=strtok(string, "~"); pt && idx<value_count; pt=strtok(NULL, "~")) {
       values[idx++] = atoi(pt);
    }
    //End black magic.
    
   
    
    return 0;
}

void Proceed()
{
  while(x!=1){
     delay(10000);
    digitalWrite(8,LOW);
    delay(10000);
    x=1;
  }
              digitalWrite(8,HIGH); 
}
