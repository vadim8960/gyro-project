#define GYRO_SENSITIVITY 0.0033;

#define ANALOG_SENSITIVITY 0.0047
// Arduino USB'Ye baglandıgında 4.575 V ile
//çalışıyor. (Aref=4575) Analog çözünürlük
//10bit dolayısıyla hassaslık=4575/1024

int sensor = A0; // analog gyro port
int change = 0; // ATD conversion change
float position = 0.0; // current cardinal position
unsigned long timetook = 0; //sample time taken
unsigned long lasttook = 0; //last sample time

void setup(){
  Serial.begin(9600);
}

void loop(){

  //Döngüde o an oluşan analog değeri gyro_x değişkenine atıyoruz.
  int gyro_x = analogRead(sensor);

//Gyro Hareket etmez ikenki değeri ile
// hareket sonrası değişim ditital olarak
// 3 birimin üstünde değilse bunu yok sayıyoruz.
//Değişim dijital olarak 3 birimin üstünde ise
//change değişkenine değişimi atıyoruz.
//Bendeki gyro şu anda hareket etmez iken
//dijital olarak 352 değerini gösteriyor.

  if(abs(gyro_x-358)>3)
    change = gyro_x-358; 

  //Son döngüde harcanan zamanı hesaplamak
  //için lasttok ve timetook degerlerini güncelliyoruz.
  lasttook = timetook;
  timetook = millis();

    float time = (float(timetook)-float(lasttook))/1000.0;                             
    //Son döngüde geçen zamanı hesaplıyoruz (saniye cinsinden)

    float degchange = change * time *  ANALOG_SENSITIVITY / GYRO_SENSITIVITY ;
    //Derece olarak değişim miktarını hesaplıyoruz. 

    position = position+degchange;
  //position değerinin değerini derece cinsinden
  //buldugumuz değer kadar arttırıyoruz.

    position = makecardinal(position);
  //360 dereceden büyük 0 dereceden küçük olma
  // durumları için dönüşümleri yapıyoruz.

  Serial.println(position);  //Derece bilgisini seri porta yazdırıyoruz.

  change=0;

  delay(10);
}

//Derece Dönüşüm fonksiyonu
float makecardinal(float position){
  if(position > 360.00){
      position = position-360.00;
    }else if(position < 0){
      position = 360+position;
    }
    return position;
}
