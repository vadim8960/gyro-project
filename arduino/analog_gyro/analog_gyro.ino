#define GYRO_SENSITIVITY 0.0033; //0.0033

#define ANALOG_SENSITIVITY 0.0047 //0.0047

int sensor = A0; // analog gyro port
int change = 0; // ATD conversion change
float position = 0.0; // current cardinal position
unsigned long timetook = 0; //sample time taken
unsigned long lasttook = 0; //last sample time

void setup(){
  Serial.begin(9600);
}

void loop(){
  int gyro_x = analogRead(sensor);
//  Serial.println(gyro_x);
  if(abs(gyro_x-337)>3)
    change = gyro_x-337; 

  lasttook = timetook;
  timetook = millis();

  float time = (float(timetook)-float(lasttook))/1000.0;                             

  float degchange = change * time *  ANALOG_SENSITIVITY / GYRO_SENSITIVITY ;

  position = position+degchange;

  position = makecardinal(position);

  Serial.println(position);

  change=0;

  delay(10);
}

float makecardinal(float position){
  if(position > 360.00){
      position = position-360.00;
    }else if(position < 0){
      position = 360+position;
    }
    return position;
}
