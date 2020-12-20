#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Adafruit_SSD1306 display(-1);

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire);

float napiecie = 0;//Wartość przeliczona na napięcie w V
float temp;
void setup() {
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  sensors.begin(); //Inicjalizacja czujnikow

// Intro wyswietlacza
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.println("Termometr");
  display.display();
  delay(100);
  display.setCursor(5,20);
  display.println("Serowarski");
  display.display();
  delay(100);
  display.setTextSize(1);
  display.setCursor(48,45);
  display.println("v2.0");
  display.display();
  delay(500);
  display.clearDisplay();
}

void loop() { 
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);

//------------------------------------------------------------------------------

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Aktualna Temperatura:");

  display.setTextSize(4);
  display.setCursor(10,18);
  display.print(temp,1);

  display.setTextSize(1);
  display.setCursor(105,16);
  display.print("o");
  display.setCursor(113,19);
  display.print("C");

  float odczytanaWartosc = analogRead(A0); //Odczytujemy wartość napięcia
  napiecie = (odczytanaWartosc * (5.0/1024.0)) * 1.28; //Przeliczenie wartości na napięcie

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,57);
  display.print("Stan baterii:");
  display.print(napiecie);
  display.setCursor(104,57);
  display.print("V");
  display.display();

  if (napiecie < 3.60) {
    alarm();
  }
  delay (100);
  display.clearDisplay();
}

void alarm() {
  display.setCursor(110,57);
  display.print("!!!");
  display.display();
}
