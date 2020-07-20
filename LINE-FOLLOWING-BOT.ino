#include <QTRSensors.h>                       // IMPORTING THE QTR SENSORS LIBRARY TO WORK WITH POLOLU SENSOR


#define NUM_SENSORS   8                       // number of sensors used
#define TIMEOUT       2500                    // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   QTR_NO_EMITTER_PIN      // emitter is controlled by digital pin 2
#define l1 A1
#define l2 A3
#define r1 A0
#define r2 A2
#define r_pwm 11
#define l_pwm 9
#define w 300
#define b 500
QTRSensorsRC qtrrc((unsigned char[]) {2, 3, 4, 5, 6, 7, 8, 12},    // sensors 0 through 7 are connected to digital pins 2 through 8 and 12, respectively
NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int a[NUM_SENSORS], position;
// INITIALISING OUR VALUES
float desired_value = 3500, last_error = 0, integral = 0,kp,ki,kd,leftmotor_speed=100,rightmotor_speed=100,error=0,derivative=0,output=0;

// STARTING OUR SETUP
void setup()
{ 
  delay(500);
  pinMode(l1,OUTPUT);   //right motor
  pinMode(l2,OUTPUT);   //right motor
  pinMode(r1,OUTPUT);   //left motor
  pinMode(r2,OUTPUT);   //left motor
  pinMode(l_pwm,OUTPUT);//left pwm pin
  pinMode(r_pwm,OUTPUT);//right pwm pin

  digitalWrite(13, HIGH);     // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();        // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);      // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
  unsigned int position = qtrrc.readLine(a);

}



void move_straight1()            // CALIBERATED STRAIGHT LINE MOTION
{
    digitalWrite(l1,LOW);
    digitalWrite(l2,HIGH);
    digitalWrite(r1,LOW);
    digitalWrite(r2,HIGH);
  
    //analogWrite(l_pwm,150);
    //analogWrite(r_pwm,150);
  
    analogWrite(l_pwm,leftmotor_speed+output);
    analogWrite(r_pwm,rightmotor_speed-output);
}

 void move_straight2 ()          // NORMAL STRAIGHT LINE MOTION
 {
    digitalWrite(l1,LOW);
    digitalWrite(l2,HIGH);
    digitalWrite(r1,LOW);
    digitalWrite(r2,HIGH);
  
    analogWrite(l_pwm,180);
    analogWrite(r_pwm,180);
  
    //analogWrite(l_pwm,leftmotor_speed+output);
    //analogWrite(r_pwm,rightmotor_speed-output);
 }
 void move_right()
 {
    digitalWrite(l1, LOW);
    digitalWrite(l2, HIGH);
    digitalWrite(r1, HIGH);
    digitalWrite(r2, LOW);
    
    analogWrite(r_pwm,100);
    analogWrite(l_pwm,100);
 }
 void move_left(){
    digitalWrite(l1, HIGH);
    digitalWrite(l2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r2, HIGH);
    analogWrite(r_pwm,100);
    analogWrite(l_pwm,100);  
 }
 void stop1(){
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
    analogWrite(r_pwm,140);
    analogWrite(l_pwm,140);
}
 void reverse(){
    digitalWrite(l1, HIGH);
    digitalWrite(l2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r2, HIGH);
    analogWrite(r_pwm,80);
    analogWrite(l_pwm,80);
 }
 void loop()
{

  position = qtrrc.readLine(a);

  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(a[i]);
    Serial.print('\t');
  }
  
  //Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position);

  if((((a[7]>b)||((a[6]>b)&&(a[5]>b)))&&((a[3]>b)&&(a[4]>b))&&(a[0]<w)))                   //for left turn cases
  {
  stop1();
  delay(500);
  move_straight2();
  delay(400);
  move_left();
  //delay(250);
   
    position = qtrrc.readLine(a);
    
    while(!(((a[0]<w)&&(a[1]<w))&&(((a[2]>b)||(a[3]>b))&&((a[5])>b||(a[4]>b)))&&((a[7]<w)||(a[6]<w))))                            
    {
      move_left();
      position = qtrrc.readLine(a);
     }
  } 
  if(((a[0]>b)||(a[1]>b))&&((a[3]>b)&&(a[4]>b))&&(a[7]<w))                                 //for right turn cases
  {
    stop1();
    delay(400);
    move_straight2();
    delay(200);
    if(((a[7]<w)&&(a[6]<w))&&((a[3]<w)&&(a[4]<w))&&((a[0]<w)&&(a[1]<w)))                   //for only right
    {
    move_right();
    //delay(150);
    
       position = qtrrc.readLine(a);

       while(!(((a[7]<w)||(a[6]<w))&&((a[3]>b)&&(a[4]>b))&&((a[0]<w)||(a[1]<w))))
       {
        move_right();
        position = qtrrc.readLine(a);
       }
    }
    else if((a[7]<w)&&((a[3]>b)&&(a[4]>b))&&(a[0]<w))                                     //for both straight and right
    {
      move_straight1();
      position = qtrrc.readLine(a);
    }
  }
  if((a[7]<w)&&(a[3]<w)&&(a[4]<w)&&(a[0]<w))                                              //for reverse
  {
    stop1();
    delay(300);
    move_left();
    //delay(600);
    
        position = qtrrc.readLine(a);

        while(!(((a[0]<w)&&(a[1]<w))&&(((a[2]>b)||(a[3]>b))&&((a[5])>b||(a[4]>b)))&&((a[7]<w)&&(a[6]<w))))
        {
          move_left();
          
          position = qtrrc.readLine(a);
        }
  }
  if((a[7]>b)&&(a[5]>b)&&(a[3]>b)&&(a[0]>b))                                             //for different cases
  {
    stop1();
    delay(500);
    move_straight2();
    delay(100); 
    if((a[7]<w)&&(a[3]<w)&&(a[4]<w)&&(a[0]<w))                                           // for T junction
    {
      stop1();
      delay(400);
      move_left();
      delay(300);
  
      position = qtrrc.readLine(a);
    while(!(((a[7]<w)||(a[6]<w))&&((a[3]>b)&&(a[4]>b))&&((a[0]<w)||(a[1]<w))))                                
    {
      move_left();
      position = qtrrc.readLine(a);
     } 
    }
    else if(((a[7]<w)||(a[6]<w))&&((a[3]>b)&&(a[4]>b))&&((a[0]<w)||(a[1]<w)))           // for + junction
    {
      stop1();
      delay(400);
      move_left();
      delay(300);
   
      position = qtrrc.readLine(a);
    
    while(!(((a[7]<w)||(a[6]<w))&&((a[3]>b)&&(a[4]>b))&&((a[0]<w)||(a[1]<w))))                                
    {
      move_left();
      position = qtrrc.readLine(a);
     } 
    }
     else                                                                               // for end point
    {
      stop1();
      delay(200);
    }
  }
   
 
  kp = 0.040;                   
  kd = 0.034; 
  ki = 0.000001;
  position = qtrrc.readLine(a);
  
  error = desired_value - position;
  derivative = error - last_error;
  integral = error + integral;

  output = kp * error + ki * integral + kd * derivative;

  last_error=error;       

 move_straight1();
}
  





             
 
