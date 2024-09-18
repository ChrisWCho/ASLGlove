#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_ADDR   0x3C
#define SSD1306_128_64
Adafruit_SSD1306 display(-1);

//Accelerometer
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

const int thumb1=11;
const int thumb2=10;
const int index1=9;
const int index2=8;
const int mid1=7;
const int mid2=6;
const int ring1=5;
const int ring2=4;
const int pink1=3;
const int pink2=2;
const int next=12;
const int clean=13;
int count=0;
int lettercount=0;
int t1,t2,i1,i2,m1,m2,r1,r2,p1,p2,n,c;
char letter;

void setup() {
  Serial.begin(9600);
  Serial.println("Moo");
  
  //OLED
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(6,0);
  display.display();

  //Accelerometer
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  pinMode(thumb1, INPUT_PULLUP);
  pinMode(thumb2, INPUT_PULLUP);
  pinMode(index1, INPUT_PULLUP);
  pinMode(index2, INPUT_PULLUP);
  pinMode(mid1, INPUT_PULLUP);
  pinMode(mid2, INPUT_PULLUP);
  pinMode(ring1, INPUT_PULLUP);
  pinMode(ring2, INPUT_PULLUP);
  pinMode(pink1, INPUT_PULLUP);
  pinMode(pink2, INPUT_PULLUP);
  pinMode(next, INPUT_PULLUP);
  pinMode(clean, INPUT);
}

void loop() {
  //Accelerometer
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  t1=digitalRead(thumb1);
  t2=digitalRead(thumb2);
  i1=digitalRead(index1);
  i2=digitalRead(index2);
  m1=digitalRead(mid1);
  m2=digitalRead(mid2);
  r1=digitalRead(ring1);
  r2=digitalRead(ring2);
  p1=digitalRead(pink1);
  p2=digitalRead(pink2);
  n=digitalRead(next);
  c=digitalRead(clean);

  if ((t1==LOW&&t2==LOW&&i1==LOW&&i2==LOW&&m1==LOW&&m2==LOW&&r1==LOW&&r2==LOW&&p1==LOW&&p2==LOW)&&(gyro_x>25000)){
      count=0;
      display.clearDisplay();
      display.display();
  }

  if (t1==LOW&&t2==LOW&&i1==HIGH&&i2==HIGH&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
    letter='A';
  }

  if (t1==HIGH&&t2==HIGH&&i1==LOW&&i2==LOW&&m1==LOW&&m2==LOW&&r1==LOW&&r2==LOW&&p1==LOW&&p2==LOW){
    letter='B';
  }

  if (t1==LOW&&t2==HIGH&&i1==HIGH&&i2==HIGH&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
      letter='C';
  }

  if (t1==HIGH&&t2==HIGH&&i1==LOW&&i2==LOW&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
      letter='D';
  }

  if (t1==HIGH&&t2==HIGH&&i1==LOW&&i2==HIGH&&m1==LOW&&m2==HIGH&&r1==LOW&&r2==HIGH&&p1==LOW&&p2==HIGH){
      letter='E';
  }

  if (t1==HIGH&&t2==HIGH&&i1==HIGH&&i2==HIGH&&m1==LOW&&m2==LOW&&r1==LOW&&r2==LOW&&p1==LOW&&p2==LOW){
      letter='F';
  }


  if ((t1==HIGH&&t2==HIGH&&i1==LOW&&i2==LOW&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH)&&(accelerometer_y<=-15000)){
      letter='G'; //conflicts with "D" Gyrometer needed
  }

  if (t1==HIGH&&t2==HIGH&&i1==LOW&&i2==LOW&&m1==LOW&&m2==LOW&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
    if (c==HIGH){
        lettercount++;
        delay(250);
    }
    if (lettercount==0){
      letter='U'; //conflicts with "H"
    }
    if (lettercount==1){
      letter='V';
    }
    if(lettercount==2){
      lettercount=0;
    }
  }
  
  if ((t1==HIGH&&t2==HIGH&&i1==LOW&&i2==LOW&&m1==LOW&&m2==LOW&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH)&&(accelerometer_y<=-15000)){
      letter='H';
  }

  if (t1==HIGH&&t2==HIGH&&i1==HIGH&&i2==HIGH&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==LOW&&p2==LOW){
      letter='I';
  }

  if ((t1==HIGH&&t2==HIGH&&i1==HIGH&&i2==HIGH&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==LOW&&p2==LOW)&&(accelerometer_y<=-15000)){
      letter='J';
//      delay(2000);//conflicts with "I" accelerometer needed
  }

  if (t1==HIGH&&t2==LOW&&i1==LOW&&i2==LOW&&m1==LOW&&m2==LOW&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
      letter='K';
  }

  if (t1==LOW&&t2==LOW&&i1==LOW&&i2==LOW&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
      letter='L';
  }

  if (t1==HIGH&&t2==LOW&&i1==HIGH&&i2==HIGH&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
    if (c==HIGH){
        lettercount++;
        delay(250);
    }
    if (lettercount==0){
      letter='M';
    }
    if (lettercount==1){
      letter='N';
    }
    if (lettercount==2){
      letter='T';
    }
    if(lettercount==3){
      lettercount=0;
    }
  }

  if (t1==HIGH&&t2==HIGH&&i1==HIGH&&i2==HIGH&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
    if (c==HIGH){
        lettercount++;
        delay(250);
    }
    if (lettercount==0){
      letter='O';
    }
    if (lettercount==1){
      letter='S';
    }
    if(lettercount==2){
      lettercount=0;
    }
  }

  if (t1==LOW&&t2==LOW&&i1==LOW&&i2==LOW&&m1==HIGH&&m2==LOW&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
      letter='P';
  }

  if (t1==LOW&&t2==LOW&&i1==HIGH&&i2==LOW&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
      letter='Q';
  }

  if (t1==HIGH&&t2==HIGH&&i1==LOW&&i2==LOW&&m1==LOW&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
      letter='R';
  }

  if (t1==HIGH&&t2==HIGH&&i1==LOW&&i2==LOW&&m1==LOW&&m2==LOW&&r1==LOW&&r2==LOW&&p1==HIGH&&p2==HIGH){
      letter='W';
  }

  if (t1==HIGH&&t2==HIGH&&i1==LOW&&i2==HIGH&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH){
      letter='X';
  }

  if (t1==LOW&&t2==LOW&&i1==HIGH&&i2==HIGH&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==LOW&&p2==LOW){
      letter='Y';
  }

  if ((t1==HIGH&&t2==HIGH&&i1==LOW&&i2==LOW&&m1==HIGH&&m2==HIGH&&r1==HIGH&&r2==HIGH&&p1==HIGH&&p2==HIGH)&&(accelerometer_z>=12000)){
      letter='Z'; //conflicts with "D" accelerometer needed
  }

  Serial.println(letter);

  display.setTextSize(3);
  
  display.setTextColor(WHITE, BLACK); //Allows the display to clear only one part without clearing the whole display
  display.setCursor(55,12);
  display.print(" ");
  
//  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(55,12);
  display.print(letter);
  display.display();

  if (n==LOW){
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(6*count,0);
    display.print(letter);
    count++;
    display.display();
  }

//  if (c==HIGH){
//    count=0;
//  display.clearDisplay();
//  display.display();    
//  }

  letter=NULL;
  Serial.println(c);
  
//  Serial.print(t1);
//  Serial.print(t2);
//  Serial.print(i1);
//  Serial.print(i2);
//  Serial.print(m1);
//  Serial.print(m2);
//  Serial.print(r1);
//  Serial.print(r2);
//  Serial.print(p1);
//  Serial.println(p2);

}
