//motor pins - cable coloring
int enA = 11; //black
int in1 = 10; //red
int in2 = 9;  //yellow
int in3 = 8;  //brown
int in4 = 7;  //purple
int enB = 6;  //white
#define RIGHT 0
#define LEFT 1
//sensor pins
int leftTrig = 13;
int leftEcho = 12;
int frontTrig = 4;
int frontEcho = 5;

//desirable distance from walls
float front_limit = 20; //cm
float left_limit = 15;

//movement status flags ,0:false 1:true
float path_ahead = 1;

//left error, derivative etc
float left_error = 0;
float left_last_error = 0;
float left_derivative = 0;

//front error,derivative etc
float front_error = 0;
float front_last_error = 0;
float front_derivative = 0;

//wall following parameters
float Kp_wall = 20;
float Kd_wall = 5;

//right run parameters
float Kp_front = 30;
float Kd_front = 15;

//motor PWM values
float left_wheel;
float right_wheel;

float leftSensor(){
  float Distance = 0;
  float Duration = 0;
  digitalWrite(leftTrig,LOW);
  delayMicroseconds(2);
  digitalWrite(leftTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(leftTrig,LOW);
  Duration = pulseIn(leftEcho,HIGH);
  Distance = Duration/29/2;     //distance to cm
  delay(25);
  return Distance; 
}

float frontSensor(){
  float Distance = 0;
  float Duration = 0;
  digitalWrite(frontTrig,LOW);
  delayMicroseconds(2);
  digitalWrite(frontTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(frontTrig,LOW);
  Duration = pulseIn(frontEcho,HIGH);
  Distance = Duration/29/2;     //distance to cm
  delay(25);
  return Distance; 
}

void setup() {
  // put your setup code here, to run once:
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enB,OUTPUT);

  pinMode(leftTrig,OUTPUT);
  pinMode(leftEcho,INPUT);
  pinMode(frontTrig,OUTPUT);
  pinMode(frontEcho,INPUT);

  delay(2000);
  
  //start motors
  analogWrite(enB,150);
  analogWrite(enA,150);

  digitalWrite(in3, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  front_check:
  front_error = frontSensor() - front_limit;
  front_derivative = front_error - front_last_error;
  front_last_error = front_error;

  if(frontSensor()<front_limit){ //wall ahead
    path_ahead = 0; //no more path, we need to take a turn
    init_wall_following(); //init wall following parameters for future use
    goto left_check;
  }
  else path_ahead = 1;  //path ahead to traverse
  left_check:
  left_error = leftSensor() - left_limit;
  left_derivative = left_error - left_last_error;
  left_last_error = left_error;

  if(left_error<10){ //near left wall
    if(path_ahead == 1) 
      wall_follower_PD(); //PD control for wall following
    else{
      //right_turn_PD();
    stopMoving();
    delay(100);
    //moveReverse();
    //delay(300);
    turn(RIGHT, 300);
    stopMoving();
    delay(100);
    }
  }
  else{ //error>10, left turn is available
    path_ahead = 1;    //expect clear path ahead
    left_turn_PD();   //PD control for left turn
  }
}

void init_wall_following(){
  left_error = 0;
  left_last_error = 0;
  left_derivative = 0;
}

void init_front(){
  front_error = 0;
  front_derivative = 0;
  front_last_error = 0;
}

void wall_follower_PD(){
  float correction = Kp_wall*left_error + Kd_wall*left_derivative;

  //avoid PWM overflow
  if(correction>127) correction = 127;
  if(correction<-127) correction = -127;

  left_wheel = 128 - correction;
  right_wheel = 128 + correction;

  analogWrite(enB,right_wheel);
  analogWrite(enA,left_wheel);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void left_turn_PD(){
  float correction = 2.5*left_error + 2.5*left_derivative; //small Kp, Kd ,correction must be slow in order to turn properly

  //avoid PWM overflow
  if(correction>127) correction = 127;
  if(correction<-127) correction = -127;

  left_wheel = 128 - correction;
  right_wheel = 128 + correction;

  analogWrite(enB,right_wheel);
  analogWrite(enA,left_wheel);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

}

void right_turn_PD(){
  float correction = Kp_front*front_error+Kd_front*front_derivative;

  //avoid RWM overflow
  if(correction>127) correction = 127;
  if(correction<-127) correction = -127;

  left_wheel = 128 - correction;
  right_wheel = 128 + correction;

  analogWrite(enB,right_wheel);
  analogWrite(enA,left_wheel);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
void moveReverse(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stopMoving(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void turn(int _direction, int ms)   
{
  if(_direction == LEFT){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(ms);
  }
  else{
    analogWrite(enA, 128);
    analogWrite(enB, 128);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(ms);
  }
}
