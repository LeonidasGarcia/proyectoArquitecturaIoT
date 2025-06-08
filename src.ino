#include <BH1750.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>                
#include <DallasTemperature.h>

OneWire ourWire(2);
BH1750 sensor;
LiquidCrystal_I2C lcd(0x27,16,2); // 0x27: Dirección en memoria que utiliza la pantalla LCD
DallasTemperature sensors(&ourWire);

int generalDelay = 2000;

void setup() {
  delay(1000);
  Wire.begin();
  sensors.begin();
  sensor.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

const char* classifyMoisture(int value) {
  if (value > 800) return "Muy seco";
  else if (value > 600) return "Seco";
  else if (value > 300) return "Óptimo";
  else return "Muy mojado";
}

const char* classifyLux(unsigned int lux) {
  if (lux <= 5) return "Oscuridad total";
  else if (lux <= 50) return "Muy poca luz";
  else if (lux <= 200) return "Luz baja";
  else if (lux <= 1000) return "Luz media";
  else if (lux <= 10000) return "Luz alta";
  else if (lux <= 50000) return "Luz muy alta";
  else return "Exceso extremo";
}

String classifyTemperature(float temp) {
  if (temp < 10) return "Frio extremo!";
  else if (temp < 18) return "Clima frio";
  else if (temp <= 25) return "Temp ideal";
  else if (temp <= 32) return "Algo caliente";
  else return "Mucho calor!";
}

void loop() { 

  unsigned int lux = sensor.readLightLevel();
  int humidity = analogRead(A0);

  int humidityPercent = map(humidity, 1023, 0, 0, 100);
  
  
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nivel de luz");
  lcd.setCursor (0,1);
  lcd.print(classifyLux(lux));
  
  delay(generalDelay);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nivel de humedad");
  lcd.setCursor (0,1);
  lcd.print(humidityPercent);
  lcd.print("%");
  lcd.print(" - ");
  lcd.print(classifyMoisture(humidity));

  delay(generalDelay);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(classifyTemperature(temp));
  lcd.setCursor (0,1);
  lcd.print(temp);
  lcd.print(" C");
  
  

  delay(generalDelay);

}
