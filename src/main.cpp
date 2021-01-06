#include <main.h>


char auth[] = "mMr8AR-_F-kEKt-NhL2plyCaYaAB-uJQ";
char ssid[] = "Dootam Roy";           //WIFI Name
char pass[] = "rocketman123";           //WIFI Password

//int minRange = 312;
//int maxRange = 712;


int speedX = 0 ;
int speedY = 0;

float voltage = 0.00;
float vol_ratio_factor = 1.3;  //Resistors Ration Factor


void moveControl(int x, int y)
{

    if (x >= 500 && x <= 514 && y >= 500 && y <= 514) // mid point.
    {
      digitalWrite(L_1, LOW);
      digitalWrite(L_2 , LOW);
      digitalWrite( R_1, LOW);
      digitalWrite(R_2, LOW);

      Serial.println("Stop");
    }
    else
    {
      speedY = map(y, 0, 1024, -1024, 1024);
      //Serial.println(speedY);
      speedX = map(x, 0, 1024, 1024, -1024);
      //Serial.println(speedX);


      //MOTOR CONTROL.
      if (speedY >= 0){
        
        int turn_speedL = speedY - speedX;
        int turn_speedR = speedY + speedX;

      
        if (turn_speedL < 0)
        {
          if (speedY < 100)
          {
            turn_speedL = 0;
          }
          else
          {
            turn_speedL = -turn_speedL;
          }
        
        }
        else if(turn_speedR < 0)
        {
          if (speedY < 100)
          {
            turn_speedR = 0;
          }
          else
          {
            turn_speedR = -turn_speedR;
          }
          //turn_speedR = -turn_speedR;
        }
        

        //turn_speedL = map(turn_speedL, 0, 1024, minSpeed, maxSpeed);
        //turn_speedR = map(turn_speedR, 0, 1024, minSpeed, maxSpeed);

        //Serial.print(turn_speedL);
        //Serial.print("       ");
        //Serial.println(turn_speedR);



        //forward.
        analogWrite(L_2,turn_speedL);
        digitalWrite(L_1, LOW);
        analogWrite(R_2,turn_speedR);
        digitalWrite(R_1, LOW);

      }
      else{
        //backward.
        speedY = -speedY;

        int turn_speedL = speedY - speedX;
        int turn_speedR = speedY + speedX;

      
        if (turn_speedL < 0)
        {
          if (speedY < 100)
          {
            turn_speedL = 0;
          }
          else
          {
            turn_speedL = -turn_speedL;
          }
        
        }
        else if(turn_speedR < 0)
        {
          if (speedY < 100)
          {
            turn_speedR = 0;
          }
          else
          {
            turn_speedR = -turn_speedR;
          }
          //turn_speedR = -turn_speedR;
        }
        

        //turn_speedL = map(turn_speedL, 0, 1024, minSpeed, maxSpeed);
        //turn_speedR = map(turn_speedR, 0, 1024, minSpeed, maxSpeed);

        //Serial.print(turn_speedL);
        //Serial.print("       ");
        //Serial.println(turn_speedR);


        analogWrite(L_1, turn_speedR);
        digitalWrite(L_2, LOW);
        analogWrite(R_1,turn_speedL);
        digitalWrite(R_2, LOW);

      }
      
    
    }
    
  
}



void setup() {

  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

    pinMode(L_1, OUTPUT);
    pinMode(L_2 , OUTPUT);
    pinMode(R_1, OUTPUT);
    pinMode(R_2, OUTPUT);
    //pinMode(A0, INPUT);

    digitalWrite(R_2, LOW);
    digitalWrite(R_1 , LOW);
    digitalWrite( L_2, LOW);
    digitalWrite(L_1, LOW);
}

void loop() {

  Blynk.run();

  //Serial.print("voltage   :  ");
  //Serial.println(voltage);

}

BLYNK_WRITE(V1)
{
    int x = param[0].asInt();
    int y = param[1].asInt();

    // Do something with x and y
    Serial.print("X = ");
    Serial.print(x);
    Serial.print("; Y = ");
    Serial.println(y);


  moveControl(x,y);
  
}

BLYNK_READ(V0){   // battery gauge.

  float Vvalue=0.0, Rvalue=0.0;

  /////////////////////////////////////Battery Voltage//////////////////////////////////  
  for(unsigned int i=0;i<10;i++){
    
  Vvalue=Vvalue+analogRead(BAT);         //Read analog Voltage
  delay(5);                              //ADC stable

  }
  Vvalue=(float)Vvalue/10.0;            //Find average of 10 values
  Rvalue=(float)(Vvalue/1024.0)*3.3;      //Convert Voltage in 5v factor

  voltage=Rvalue*vol_ratio_factor;          //Find original voltage by multiplying with factor

    /////////////////////////////////////Battery Voltage//////////////////////////////////

  //send to app.
  Blynk.virtualWrite(V0, voltage);
}
