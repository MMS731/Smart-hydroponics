#include <Wire.h>
#define SENSOR_ADDR 0x38
#define MEASURE_01 0xAC
#define MEASURE_02 0x33
#define MEASURE_03 0x00
#define DATA_SIZE 7
#define MEASURE_DELAY 80



byte data[DATA_SIZE];

void setup() {
  Wire.begin();
  Serial.begin(9600);
  delay(1000);
}

void loop() 
{
  Wire.beginTransmission(SENSOR_ADDR);
  Wire.write(MEASURE_01);
  Wire.write(MEASURE_02);
  Wire.write(MEASURE_03);
  Wire.endTransmission();
  delay(MEASURE_DELAY);


  Wire.requestFrom(SENSOR_ADDR, DATA_SIZE);
  int index = 0;
  while (Wire.available()) 
  {
    data[index++] = Wire.read();
  }

  Serial.print("Received bytes : ");
  for (int i = 0; i < 6; i++) {
    Serial.print(data[i]);
    Serial.print(" ");
  }
  Serial.println("  ");
  uint32_t humidity   = data[1];                          
  humidity <<= 8;
  humidity  |= data[2];
  humidity <<= 4;
  humidity  |= data[3] >> 4;

  float hum = ((float)humidity / 1048576) * 100;
  Serial.print("Humidity ");
  Serial.println(hum);
  //Serial.println(" ");


  uint32_t temperature   = data[3] & 0x0F;                
  temperature <<= 8;
  temperature  |= data[4];
  temperature <<= 8;
  temperature  |= data[5];

  float temp = ((float)temperature / 1048576) * 200 - 50;
  Serial.print("Temperature ");
  Serial.println(temp);
  Serial.println(" ");

  delay(5000); // Delay before next loop iteration

}