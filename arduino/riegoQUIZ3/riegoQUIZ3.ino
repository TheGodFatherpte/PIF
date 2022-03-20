  
   /*
   * Diseñador: Anderson Lopez Martinez
   * proyecto PIF
   * Sistema de riego automatico
   * Codigo: 1001236801
   * Archivo: D:\Users\Anderson\Documents\Semestre 2021-2\electronica digital\Arduino\arduino_Ejemplos
   * fecha inicio:18/12/2021
   * fecha fin:18/02/2022

   * Descripcion control crecimientoy  humedad en plataforma Arduino IDE
   */
#include <DHT.h>//sensores temperatura y humedad DHT11
#include <Wire.h>//allows you to communicate with I2C / TWI devices.
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

//definimos enradas del sensor ultrasonido 
int Trigger = A0;
int Echo = 10;

//definimos a que pin se conecta el sensor
//#define button1 A0  //boton 1
#define HT2 A1 //sensor 2
#define button2 A2 //boton 2

#define HT1 9  //sensor 1
#define HT3 8 //sensor 3

//Tpo de sensor 
#define DHTTYPE DHT11

//inicializamos el sensor DHT11
//indicamos pin a trabajar y tipo de sensor 
DHT dht2 (HT2, DHTTYPE);

DHT dht3 (HT3, DHTTYPE);
DHT dht1 (HT1, DHTTYPE);


//declaramos variables
//sensor1***
int ref =20, ref1 = 20;

//sensor2***
int ref2=20,ref3=20;

//sensor3***
int ref4=20,ref5=10;

String linea1 = "H1:";
String linea2 = "T1:";
String linea3 = "H2:";
String linea4 = "T2:";
String linea5 = "H3:";
String linea6 = "T3:";


void setup() {

  //comunicacion SERIAL sensor ultrasonico
  Serial.begin(9600);
  pinMode(Trigger,OUTPUT);
  pinMode(Echo,OUTPUT);
  digitalWrite(Trigger, LOW);//Iniciamos el pin 0

  
  lcd.setCursor(0,0);
  lcd.print("Control de temperatura y humedad");
 
pinMode(button2,INPUT_PULLUP);
  // iniciamos counicacion con el LCD
  lcd.begin (20,4);

  //iniciamos sensores DHT
  dht1.begin();//sensor1
  dht2.begin();//sensor2
   dht3.begin();//sensor3


  //declaramos funciones de los pines 
  pinMode(A5,OUTPUT);//TEMPERATURA1
  pinMode(13,OUTPUT);//HUMEDAD1
  pinMode(A4,OUTPUT);//TEMPERATURA2
  pinMode(A3,OUTPUT);//HUMEDAD2
  pinMode(12,OUTPUT);//TEMPERATURA3
  pinMode(11,OUTPUT);//HUMEDAD3

  //Mensaje binevenida
  lcd.setCursor(0,0);
  lcd.print("Control de crecimiento y humedad");
  delay(3000);
  lcd.clear();
  lcd.print("mantenga presionado un boton para Pausar...");
  delay(1000);
  lcd.clear();
}

void loop() {


  // esperamos 2
  delay(1000);
 
  ///SENSOR 1 ///
  float h = dht2.readHumidity();//leer humedad relativa 
  float t = dht2.readTemperature();//leer temperatura en Grados centigrados
  float f = dht2.readTemperature(true);//leer temperatura en grados Fareheit

//omprobamos si hay un error de lectura

  if (isnan(h) || isnan(t) || isnan(f))
  {
    lcd.println("Error obteniendo los datos del sensor DHT11");
    return;
  } 
  
//SENSOR2//
  float h2 = dht2.readHumidity();//leer humedad relativa 
  float t2 = dht2.readTemperature();//leer temperatura en Grados centigrados
  float f2 = dht2.readTemperature(true);//leer temperatura en grados Fareheit


 //SENSOR3//
  float h3 = dht3.readHumidity();//leer humedad relativa 
  float t3 = dht3.readTemperature();//leer temperatura en Grados centigrados
  float f3 = dht3.readTemperature(true);//leer temperatura en grados Fareheit

//comprobamos alguin error de lectura 
  if (isnan(h) || isnan(t) || isnan(t))
  {
    lcd.println("Error obteniendo los datos del sensor DHT11");
    return;
  } 

//imprimimos la informacion calculada en el display lcd 
lcd.setCursor(0,0);
lcd.print(linea1);
lcd.print(h);
lcd.print("%");
lcd.setCursor(10,0);
lcd.print(linea2);
lcd.print(t);
lcd.print("*C");

lcd.setCursor(0,1);
lcd.print(linea3);
 lcd.print(h2);
lcd.print("%");
lcd.setCursor(10,1);
lcd.print(linea4);
lcd.print(t2);
lcd.print("*C");

lcd.setCursor(0,2);
lcd.print(linea5);
lcd.print(h3);
lcd.print("%");
lcd.setCursor(10,2);
lcd.print(linea6);
lcd.print(t3);
lcd.print("*C");

delay(2000); 


//Arranque apagado del equipo
//SENSOR 1 //
 if(t>ref)
 {
  digitalWrite(A5,HIGH);
  lcd.setCursor(0,3);
  lcd.print("FAN1 ON");
  delay(1000);
  lcd.clear();
 }
 else
 {
  digitalWrite(A5,LOW);
  lcd.setCursor(0,3);
  lcd.print("FAN1 OFF");
  delay(1000);
  lcd.clear();
 }
 if(h<ref1)
 {
  digitalWrite(13,HIGH);
  lcd.setCursor(0,3);
  lcd.print("PUMP1 ON");
  delay(1000);
  lcd.clear();
 } else
 {
      digitalWrite(13,LOW);
      lcd.setCursor(0,3);
      lcd.print("PUMP1 OFF");
      delay(1000);
      lcd.clear();
 }
   ///SENSOR 2 /////////
if(t2>ref2)
    {
      digitalWrite(A4,HIGH);
      lcd.setCursor(0,3);
      lcd.print("FAN2 ON");
      delay(1000);
      lcd.clear();     
    }
    else
    {
      digitalWrite(A4,LOW);
      lcd.setCursor(0,3);
      lcd.print("FAN2 OFF");
      delay(1000);
      lcd.clear();   
    }
    if(h2<ref3)
    {
      digitalWrite(A3,HIGH);
      lcd.setCursor(0,3);
      lcd.print("PUMP2 ON");
      delay(1000);
      lcd.clear();  
    }
    else
    {
      digitalWrite(A3,LOW);
      lcd.setCursor(0,3);
      lcd.print("PUMP2 OFF");
      delay(1000);
      lcd.clear();  
    }

    if (t3>ref4)
 {
     digitalWrite(12,HIGH);
      lcd.setCursor(0,3);
      lcd.print("FAN3 ON");
      delay(1000);
      lcd.clear();  
 }
      else{
            digitalWrite(12,LOW);
            lcd.setCursor(0,3);
            lcd.print("FAN3 OFF");
            delay(1000);
            lcd.clear();  
      }
 if (h3<ref5)
 {
      digitalWrite(11,HIGH);
      lcd.setCursor(0,3);
      lcd.print("PUMP3 ON");
      delay(1000);
      lcd.clear();  
 }
    else{
        digitalWrite(11,LOW);
        lcd.setCursor(0,3);
        lcd.print("PUMP3 OFF");
        delay(1000);
        lcd.clear();  
    }
    delay(500);
   

 

 if(digitalRead(button2))
 {
  lcd.clear(); 
 ///********INICIO codigo ultrasonido********
long tiempo;//tiempo en que demora el eco
long d;//distancia centimetros
long d1;
digitalWrite(Trigger,HIGH);
delayMicroseconds(10);  //ENVIAMOS PULSO 10us
digitalWrite(Trigger,LOW);

tiempo = pulseIn(Echo,HIGH);//ancho del pulso
d =(tiempo/59);              //escalamos tiempo a distancia en cm 
d1 = d/3;
lcd.print("Control crecimiento de la planta");
lcd.setCursor(0,2);
lcd.print("-->");
lcd.print(d1);//enviando derialmente el valor de la distancia 
lcd.print("cm");
lcd.println();
delay(2000);//pausa 100ms

  ///********FIN codigo ultrasonido********
 }


 //Fin else
  }
   
