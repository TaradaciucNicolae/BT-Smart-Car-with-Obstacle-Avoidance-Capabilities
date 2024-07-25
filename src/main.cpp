#include <PS5BT.h>
// #include <PS5Parser.h>
// #include <usbhub.h>

/*
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
*/

#include <SPI.h>

#include <DC_GearMotors/GearMotors.h>
#include <ServoMotor/ServoMotor.h>
// #include <Buzzer/Buzzer.h>
#include <Ultrasonic_sensor/UltrasonicSensor.h>
#include <Lumini/Lumini.h>

USB Usb;
BTD Btd(&Usb);
// PS5BT PS5(&Btd, PAIR);
PS5BT PS5(&Btd);

bool printAngle = false, printTouch = false;
uint16_t lastMessageCounter = -1;
uint8_t player_led_mask = 0;
bool microphone_led = false;
uint32_t ps_timer;
bool PS5conectat = false;
int OneLoopCounter = 1;
int ValoarePragMotor;
int ValoareServo;
int CounterAutonom = 1;
int ValoareDistanta;
int ValoareDistantaRepoz;
bool FaruriOn = false;
int i;

void OprireAuto()
{
  Usb.Task();
  if (PS5.getButtonPress(CIRCLE))
  {
    CounterAutonom = 0;
    Usb.Task();
  }
}

void EvitareColiziune()
{
          while (distance()<=10){
          forward(0);
          OprireAuto();
        }
}

void delay_plus_evitare(int milisecunde)
{ 
  for(i=0;i<milisecunde;i++)
  {
    delay(1);
    EvitareColiziune();
    OprireAuto();
  }
  
}

void EvitareObsDreaptaObstacol()
{
  if(distance()<30)
  {
    forward(0);

  }
}

void setup()
{
  Serial.begin(115200);

  if (Usb.Init() == -1)
  {
    Serial.print(F("\r\nOSC did not start"));
    while (1)
      ; // Halt
  }

  init_Ultrasonic_Sensor();
  // sei();
  // init_horn_buzz();
  pwm_init();
  sei();
}

void loop()
{ // Serial.begin(115200);

  Usb.Task();

  // delay(50);
  // Serial.print(F("\r\n Valoare distanta: "));
  // Serial.print(distance());
  //  distance();
  // CitestePozitieMouse();
  //  detecteaza(mouse);

  if (!PS5.connected() && PS5conectat == false && OneLoopCounter == 1)
  {
    Serial.print(F("\r\n\nSe cauta controllerul de PS5 !"));
    OneLoopCounter = 0;
  }

  if (PS5.connected() && PS5conectat == false)
  {
    PS5conectat = true;
    Serial.print(F("\r\n\nControllerul de PS5 a fost conectat !"));
    FaruriPornite();
    delay(20);
    FaruriOprite();
  }

  if (!PS5.connected())
  {
    forward(0);
  }

  if (PS5.connected() && lastMessageCounter != PS5.getMessageCounter())
  {
    lastMessageCounter = PS5.getMessageCounter();
    /*
        if (PS5.getAnalogHat(LeftHatX) > 137 || PS5.getAnalogHat(LeftHatX) < 117 || PS5.getAnalogHat(LeftHatY) > 137 || PS5.getAnalogHat(LeftHatY) < 117 || PS5.getAnalogHat(RightHatX) > 137 || PS5.getAnalogHat(RightHatX) < 117 || PS5.getAnalogHat(RightHatY) > 137 || PS5.getAnalogHat(RightHatY) < 117)
        {
          Serial.print(F("\r\nLeftHatX: "));
          Serial.print(PS5.getAnalogHat(LeftHatX));
          Serial.print(F("\tLeftHatY: "));
          Serial.print(PS5.getAnalogHat(LeftHatY));
          Serial.print(F("\tRightHatX: "));
          Serial.print(PS5.getAnalogHat(RightHatX));
          Serial.print(F("\tRightHatY: "));
          Serial.print(PS5.getAnalogHat(RightHatY));


        }
        */

    // distance();

    Usb.Task();
    ValoareServo = PS5.getAnalogHat(LeftHatX);

    if ((ValoareServo >= 0) || (ValoareServo <= 255))
    {
      servo_set(map(ValoareServo, 255, 0, 35, 145), 180); // 35 si 145
    }
    else
    {
      servo_set(90, 180);
    }

    ValoarePragMotor = 35;
    if (PS5.getAnalogButton(L2) || PS5.getAnalogButton(R2))
    { // These are the only analog buttons on the PS5 controller
      //   /*
      //  Serial.print(F("\r\nL2: "));
      //   Serial.print(PS5.getAnalogButton(L2));
      //  Serial.print(F("\tR2: "));
      //  Serial.print(PS5.getAnalogButton(R2));
      //*/
      if (PS5.getAnalogButton(L2) > ValoarePragMotor && PS5.getAnalogButton(R2) < ValoarePragMotor)
      {
        reverse(PS5.getAnalogButton(L2));
      }

      if (PS5.getAnalogButton(L2) < ValoarePragMotor && PS5.getAnalogButton(R2) > ValoarePragMotor)
      {
        forward(PS5.getAnalogButton(R2));
      }

      if (PS5.getAnalogButton(L2) < ValoarePragMotor && PS5.getAnalogButton(R2) < ValoarePragMotor)
      {
        forward(0);
      }
    }
    else
    {
      forward(0);
    }

    /*

        if(PS5.getButtonPress(CIRCLE) == 1)
        {
          horn_buzz();
        }
        else{
        no_horn_buzz();
        }
        */

    /* Serial.print("   sdsdsdsd:    ");
    Serial.println(PS5.ps5Data.gyroX);
    Serial.print("   ");
      Serial.print(PS5.ps5Data.gyroY);
    Serial.print("   ");
      Serial.println(PS5.ps5Data.gyroZ);
          Serial.print("   ");
      Serial.print(PS5.ps5Data.accX);
    Serial.print("   ");
      Serial.println(PS5.ps5Data.accY);
          Serial.print("   ");
  //    Serial.println(PS5.ps5Data.);
    Serial.println("   ");

*/

    // Hold the PS button for 1 second to disconnect the controller
    // This prevents the controller from disconnecting when it is reconnected,
    // as the PS button is sent when it reconnects
    if (PS5.getButtonClick(PS))
    {
      Serial.print(F("\r\n\nControllerul de PS5 a fost deconectat !"));
      FaruriPornite();
      delay(20);
      FaruriOprite();
      PS5conectat = false;
      OneLoopCounter = 1;
      PS5.disconnect();
    }

    if (PS5.getButtonClick(UP))
    {
      if (FaruriOn == true)
      {
        FaruriOprite();
        FaruriOn = false;
        // delay(50);
      }
      else
      {

        FaruriPornite();
        FaruriOn = true;
        // delay(50);
      }
    }

    if (PS5.getButtonClick(TRIANGLE) && CounterAutonom == 1) // are un delay la apasarea " CIRCLE"
    {
      // init_Ultrasonic_Sensor(); // merge doar cu initiere aici

      while (CounterAutonom == 1)
      {
        Usb.Task();
        OprireAuto();
        // Serial.print(F("\r\n Valoare distanta: "));
        // Serial.print(distance());
        forward(250);
        servo_set(93, 180);
        ValoareDistanta = distance();
        if (ValoareDistanta <= 50 && ValoareDistanta > 10) // Evitare obstacol indepartat
        {
          OprireAuto();
          // if (rand() % 2 == 1)
          // { //evitare prin stanga
          //   servo_set(120, 180);
          //   delay(50);
          //   servo_set(90,180);
          //   delay(50);
          //   servo_set(60,180);
          //   delay(100);
          //   servo_set(90,180);
          //   delay(50);
          //   servo_set(120,180);
          //   delay(50);
          //    OprireAuto();

          //   // return;
          // }
          //   else
          //   { // evitare prin dreapta
          servo_set(70, 180);
          delay(47); 
         // EvitareColiziune();
          // if(distance()<35) // daca a facut dreapta si e alt obstacol, inapoi si testeaza spre stanga, 
          // {
          //   reverse(250);
          //   delay_plus_evitare(40);
          //   servo_set(40,180);
          //   delay_plus_evitare(40);
          //   servo_set(90,180);
          //   //if mergi inainte si e alt obstacol inseamna ca e un perete deci intoarcete complet altfel fa dreapta ca sa revii pe traseu

          // }
          //else
        //  {
        //    EvitareColiziune();
         // servo_set(90, 180);
         // delay_plus_evitare(20);
                 //   EvitareColiziune();
          servo_set(130, 180);
          delay(45); // era delay

         // EvitareColiziune();

          servo_set(90, 180);
          delay_plus_evitare(20);  // era delay
          //EvitareColiziune();

          servo_set(60, 180);
          delay_plus_evitare(10);// era delay
          //EvitareColiziune();


          servo_set(90,180);
          delay_plus_evitare(30);
          
          OprireAuto();
          // return;
          //  }
        //  }
       // delay_plus_evitare(1000);
          EvitareColiziune();

        }

       EvitareColiziune();

        // if (distance() < 30)
        // {
        //   if (rand() % 2 == 1)
        //   {
        //     OprireAuto();
        //     forward(0);
        //     delay(50);
        //     servo_set(145, 180);
        //     reverse(250);
        //     delay(50);
        //     reverse(0);
        //     ValoareDistantaRepoz = distance();
        //     if (ValoareDistantaRepoz < 30)
        //     {
        //       OprireAuto();
        //       servo_set(35, 180);
        //       reverse(250);
        //       delay(100);
        //       reverse(0);
        //       ValoareDistantaRepoz = distance();
        //     }
        //   }
        //   else
        //   {
        //     OprireAuto();
        //     forward(0);
        //     delay(50);
        //     servo_set(35, 180);
        //     reverse(250);
        //     delay(50);
        //     reverse(0);

        //     if (ValoareDistantaRepoz < 30)
        //     {
        //       OprireAuto();
        //       servo_set(145, 180);
        //       reverse(250);
        //       delay(100);
        //       reverse(0);
        //       ValoareDistantaRepoz = distance();
        //     }
        //   }
        // }

        OprireAuto();
      }
      CounterAutonom = 1;
      forward(0);
      servo_set(90, 180);
    }
  }
}
