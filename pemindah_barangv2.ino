#include "AFMotor.h" //library dari driver motor
#include <Servo.h> //library dari motor servo

const int MOTOR_1 = 1;
const int MOTOR_2 = 2;
const int MOTOR_3 = 3;
const int MOTOR_4 = 4;

/*sinyal mengatur pengontrol kecepatan*/
AF_DCMotor motor1(MOTOR_1, MOTOR12_64KHZ);  
AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ);
AF_DCMotor motor3(MOTOR_3, MOTOR12_64KHZ);
AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ);

/*Deklarasi nama servo*/
Servo servo1;
Servo servo2;

/*masukan/pengaturan speed*/
int state;
int Speed = 130;

void setup() {
  /*pengatur kecepatan 0-255*/
  motor1.setSpeed(Speed); 
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);
  Serial.begin(9600); // mengatur kecepatan ke 9600bit/second
  delay(500);

  servo1.attach(10);
  servo2.attach(9);
  
  servo1.write(95);
  servo2.write(160);
}

void loop() {
  if(Serial.available() > 0){ //jika data dikirim, baca dan simpan dalam state
    state = Serial.read();
    if(state > 10){Speed = state;}
  }

  motor1.setSpeed(Speed); //mengatur kecepatan 0-255
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                Kontrol Tombol + Suara
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
if (state == 1){forward(); }       // jika state bernilai 1, maka akan maju kedepan
else if (state == 2){backward(); } // jika state bernilai 2, maka akan kebelakang
else if (state == 3){turnLeft(); } // jika state bernilai 3, maka akan belok kiri
else if (state == 4){turnRight();} // jika state bernilai 4, maka akan belok kanan
else if (state == 5){Stop(); }     // jika state bernilai 5, maka akan berhenti
else if (state == 6){grab(); }     // jika state bernilai 6, maka gripper[servo1] akan menyapit
else if (state == 7){drop(); }     // jika state bernilai 7, maka gripper[servo1] akan melepas 
else if (state == 8){up(); }       // jika state bernilai 8, maka gripper[servo2] akan bergerak ke atas
else if (state == 9){down(); }     // jika state bernilai 9, maka gripper[servo2] akan bergerak ke bawah
else if (state == 10){Sup(); }     // jika state bernilai 10, maka gripper[servo2] bisa bergerak ke full ke atas
else if (state == 11){Sdown(); }   // jika state bernilai 11, maka gripper[servo2] akan bergerak ke bawah atau nilai awal
//~~~~~~~~~~~~~~~~~~~~~~~~~~~ End Kontrol Tombol + Suara ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                              Kontrol Suara Belok
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
else if (state == 12){turnLeft(); delay(1000); state = 5; } // jika state bernilai 12, maka belok kiri dengan 0,8 detik lalu berhenti
else if (state == 13){turnRight(); delay(1000); state = 5; }// jika state bernilai 13, maka belok kanan dengan 0,8 detik lalu berhenti
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End Kontrol Suara Belok ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
delay(80);
}

//Maju ke depan
void forward(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);  
}

//Bergerak ke Belakang
void backward(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);  
}

//Belok Kiri
void turnLeft(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

//Belok Kanan
void turnRight(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD); 
}


//Berhenti
void Stop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void grab(){
 servo1.write(175);
}

void drop(){
 servo1.write(95);
}

void up(){
 servo2.write(50);
}

void down(){
 servo2.write(160);
}

void Sup(){
 servo2.write(100);
}

void Sdown(){
 servo2.write(160);
}
