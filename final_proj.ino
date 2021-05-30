#include <M5Stack.h>
#include "secrets.h"

// Parameters

#define NOTE_C 277
#define NOTE_D 311
#define NOTE_E 330

// Ultrasonic's Pins
#define echoPin 21
#define trigPin 22

// Joystick's Pin
#define SW 5
#define A3 36
#define A4 35

// Potentiometer's Pin
#define A0 2

// Connect to the internet
const char* ssid = MY_SSID;
const char* pass = MY_PASS;

const char* resource = MY_WEBHOOK;
const char* server = "maker.ifttt.com";

int counter = 0; // counter for mute button
int volume = 3; // initial volume
long duration, cm; // for sonar
int frequency = 0; // changed freq
int potential, tonee = 0; // potential and changed tone
int old_po=0; // old potential

// Hardware Setup


void setup() 
{
  M5.begin();
  M5.Power.begin();
  M5.Speaker.setVolume(3);
  M5.Speaker.update();
  M5.Lcd.setTextSize(8);
  //Serial.begin(9600);

}

void loop() 
{
  if (M5.BtnA.wasPressed()) 
  {
    counter++;
  }

  if (volume < 1) 
  {
    volume = 1;
  }
  else if (volume > 10) 
  {
    volume = 10;
  }
  adjustVolume();
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(0, 50, 2);
  M5.Lcd.printf("Vol %d\n", volume);

  adjustFrequency();
  M5.Lcd.setCursor(0, 100, 2);
  M5.Lcd.printf("Freq %d\n", frequency);

  adjustTone();
  M5.Lcd.setCursor(0, 150, 2);
  M5.Lcd.printf("Tone %d\n", tonee);

  mute_status(counter);

  if (check_distance(sonar()) == 0) 
  {
    M5.Speaker.tone(NOTE_C+tonee, 500 + frequency);
  }

  else if (check_distance(sonar()) == 1) 
  {
    M5.Speaker.tone(NOTE_D+tonee, 500 + frequency);
  }

  else if (check_distance(sonar()) == 2) 
  {
    M5.Speaker.tone(NOTE_E+tonee, 500 + frequency);
  }
  else if (check_distance(sonar()) == -1) {}

  M5.Lcd.setCursor(0, 50, 2);
  if (M5.BtnB.wasPressed()) 
  {
    volume--;
    M5.Speaker.setVolume(volume);
    M5.Speaker.update();
  }
  if (M5.BtnC.wasPressed()) 
  {
    volume++;
    M5.Speaker.setVolume(volume);
    M5.Speaker.update();
  }

  M5.update();

}

int check_distance(long distance) 
{
  int sound;
  if (distance <= 5) 
  {
    sound = 0;
  }
  else if (distance > 5 && distance <= 15) 
  {
    sound = 1;
  }
  else if (distance > 15 && distance <= 50) 
  {
    sound = 2;
  }
  else {
    sound = -1;
  }

  return sound;
}

void mute_status(int click) 
{
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);

  if (click % 2 == 0) 
  {
    unmute();
  }
  else {
    mute();
  }
}

void unmute() 
{
  //Serial.println("unmute");
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.fillCircle(300, 10, 10, GREEN);
}

void mute() 
{
  //Serial.println("mute");
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.fillCircle(300, 10, 10, RED);
  for (;;) 
  {
    M5.Speaker.mute();
    if (M5.BtnA.wasPressed()) {
      break;
    }
  }
}

long sonar() 
{
  M5.Lcd.setCursor(0, 0, 2);
  pinMode(trigPin, OUTPUT);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  M5.Lcd.print(cm);
  return cm;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void adjustVolume() 
{
  if (M5.BtnB.wasPressed()) 
  {
    volume--;
    M5.Speaker.setVolume(volume);
    M5.Speaker.update();
  }
  if (M5.BtnC.wasPressed()) {
    volume++;
    M5.Speaker.setVolume(volume);
    M5.Speaker.update();
  }

  if (volume <= 1) 
  {
    volume = 1;
  }
  else if (volume >= 10) 
  {
    volume = 10;
  }  
}

void adjustFrequency() 
{
  int Y_value = analogRead(A4);
  int X_value = analogRead(A3);
  switch (X_value) {
    case 0:
      frequency++;
      break;
    case 4095:
      frequency--;
      break;
    default:
      break;
  }

  if (frequency <= -500) {
    frequency = 500;
  }
}

void adjustTone() 
{
  potential = analogRead(A0);

  if (old_po = 0) {
    old_po = potential;
  }

  if (old_po - potential <=  100) {
    tonee++;
  }
  else if (old_po - potential >= -100) {
    tonee--;
  }
}

