//Create By I Wayan Sujane DBC 115 027 
//UNIVERSITAS PALANGKA RAYA
//Fakultas Teknik Jurusan Teknik Informatika

#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

int ldr1=A1, ldr2=A2; // Sensor LDR
int nilaiLDR1, nilaiLDR2;

int count_r_Total = 0, count_r_Bagus = 0, count_r_Jelek = 0;
int count_k_Total = 0, count_k_Bagus = 0, count_k_Jelek = 0;

const int proximity = 7; //Sensor Deteksi Benda

//Inisialisasi Tombol
const int b1=8, b2=9, b3=10;
int ok   = 0,
    next = 0,
    back = 0;

const int IN3 = 5, IN4 = 4, ENB = 3;
int motor = 57; //Kecepatan Dinamo

unsigned long interval=1000;
unsigned long previousMillis=0;
bool ledState = false;

Servo palang1, palang2;
int palang1_buka  = 90, //Mengatur Derajat
    palang1_tutup = 40,
    palang2_buka  = 10,
    palang2_tutup = 105;
int pos = 0;
int counter = 0;
int counterr;

//in LED = 13;
//int hitung = 0;
//int kondisi1 = 0;
//int status1;


void setup()
{
  Serial.begin(9600);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENB, OUTPUT);
  
  pinMode(proximity, INPUT);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" I WAYAN SUJANE");
  lcd.setCursor(0,1);
  lcd.print("===DBC 115027===");
  delay(3000);
  lcd.clear();

  pinMode(13, OUTPUT);
  digitalWrite(13, ledState);

  palang1.attach(11);
  palang2.attach(12);
  palang1.write(palang1_buka);
  palang2.write(palang2_tutup);
}

void splash()
{  
  lcd.setCursor(0,0);
  lcd.print("L ");delay(200); lcd.print("O ");delay(200);
  lcd.print("A ");delay(200); lcd.print("D ");delay(200);
  lcd.print("I ");delay(200); lcd.print("N ");delay(200);
  lcd.print("G ");delay(200); lcd.clear();
  lcd.print("L O A D I N G");delay(500);
  lcd.setCursor(0,1);
  lcd.print("~");delay(100); lcd.print("~");delay(100);
  lcd.print("~");delay(100); lcd.print("~");delay(100);
  lcd.print("~");delay(100); lcd.print("~");delay(100);
  lcd.print("~");delay(100); lcd.print("~");delay(100);
  lcd.print("~");delay(100); lcd.print("~");delay(100);
  lcd.print("~");delay(100); lcd.print("~");delay(100);
  lcd.print("~");delay(100); lcd.print("~");delay(100);
  lcd.print("~");delay(100); lcd.print("~");delay(100);  
  lcd.clear();
}
 
void loading2()  
{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("~");delay(50); lcd.print("~");delay(50);
  lcd.print("~");delay(50); lcd.print("~");delay(50);
  lcd.print("=");delay(50); lcd.print("");delay(50);
  lcd.print("~");delay(50); lcd.print("~");delay(50);
  lcd.print("~");delay(50); lcd.print("~");delay(50);
  lcd.print("=");delay(50); lcd.print("=");delay(50);
  lcd.print("~");delay(50); lcd.print("~");delay(50);
  lcd.print("~");delay(50); lcd.print("~");delay(100);
  lcd.clear();  
}

void serial_monitor()
{
  int sensorBenda = digitalRead(proximity);
  nilaiLDR1 = analogRead(ldr1);
  nilaiLDR2 = analogRead(ldr2);
  Serial.print("A=");Serial.print(nilaiLDR1);
  Serial.print(" B=");Serial.print(nilaiLDR2);
  Serial.print(" Counter= ");Serial.print(counter);
  if (sensorBenda == LOW)
  {
    Serial.print(" C=");Serial.println("LOW"); 
  }
  else
  {
    Serial.print(" C=");Serial.println("HIGH");
  }
}

/* 
=============================================================================== 
Opsional pada tampilan Tes Sensor 
===============================================================================*/
void awal1()
{
  while(1)
  {
    analogWrite(ENB, 0); 
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CEK SENSOR>>");
    lcd.setCursor(0,1);
    lcd.print("1. CONVEYOR ON");
    delay(500);    
    
    ok = digitalRead(b1);
    next = digitalRead(b2);
    back = digitalRead(b3);
    if (ok == HIGH)
    {
      delay(100);
      loading2();
      convon();
    }
    if (next == HIGH) 
    {
      delay(100);
      awal2();
    }
    if (back == HIGH)
    {
      delay(100);
      loading2();
      menu_utama();
    }    
  }  
}

void awal2()
{
  while(1)
  {
    analogWrite(ENB, 0); 
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CEK SENSOR>>");
    lcd.setCursor(0,1);
    lcd.print("2. CONVEYOR OFF");
    delay(500);    
    
    ok = digitalRead(b1);
    next = digitalRead(b2);
    back = digitalRead(b3);
    if (ok == HIGH)
    {
      delay(100);
      loading2();      
      convoff();
    }
    if (next == HIGH) 
    {
      delay(100);
      awal1();
    }
    if (back == HIGH)
    {
      delay(100);
      loading2();
      menu_utama();
    }    
  }  
}

void convon()
{
  while(1)
  { 
    //Serial.println("cek_sensor");
    //Dinamo Conveyor
//    serial_monitor();
    analogWrite(ENB, motor); //58
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    int sensorBenda = digitalRead(proximity);
    nilaiLDR1 = analogRead(ldr1);
    nilaiLDR2 = analogRead(ldr2);

    if (sensorBenda == LOW)
    {
//      digitalWrite(13, HIGH);
      counter++;
      Serial.print("A=");Serial.print(nilaiLDR1);
      Serial.print(" B=");Serial.print(nilaiLDR2);
      Serial.print(" Counter= ");Serial.println(counter);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" Nilai Sensor = ");
      lcd.setCursor(1,1);
      lcd.print("A");lcd.print(nilaiLDR1);
      lcd.setCursor(7,1);
      lcd.print("B");lcd.print(nilaiLDR2);
      lcd.setCursor(13,1);
      lcd.print("C");lcd.print(sensorBenda);
//      delay(100);
      lcd.clear(); 
    }
    else
    {
//      digitalWrite(13, LOW);
      counter = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" Nilai Sensor = ");
      lcd.setCursor(1,1);
      lcd.print("A");lcd.print(nilaiLDR1);
      lcd.setCursor(7,1);
      lcd.print("B");lcd.print(nilaiLDR2);
      lcd.setCursor(13,1);
      lcd.print("C");lcd.print(sensorBenda);   
      delay(100);       
      lcd.clear(); 
    }

      next = digitalRead(b2);
      back = digitalRead(b3);
      if (next == HIGH)
      {
        palang1.write(palang1_tutup);
        palang2.write(palang2_buka);
      }
      else if (next == LOW)
      {
        palang1.write(palang1_buka); // tutup palang belok
        palang2.write(palang2_tutup); // tutup palang kanan
      }
      if (back == HIGH)
      {
        delay(100);
        awal1();
      }    
    }
}

void convoff()
{
   while(1)
    { 
      //Serial.println("cek_sensor");
      //Dinamo Conveyor
      serial_monitor();
      analogWrite(ENB, 0); //58
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      int sensorBenda = digitalRead(proximity);
      nilaiLDR1 = analogRead(ldr1);
      nilaiLDR2 = analogRead(ldr2);
      if (sensorBenda == LOW)
      {
//        digitalWrite(13, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Nilai Sensor = ");
        lcd.setCursor(1,1);
        lcd.print("A");lcd.print(nilaiLDR1);
        lcd.setCursor(7,1);
        lcd.print("B");lcd.print(nilaiLDR2);
        lcd.setCursor(13,1);
        lcd.print("C");lcd.print(sensorBenda);
        delay(300);
        lcd.clear(); 
      }
      else
      {
//        digitalWrite(13, LOW);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Nilai Sensor = ");
        lcd.setCursor(1,1);
        lcd.print("A");lcd.print(nilaiLDR1);
        lcd.setCursor(7,1);
        lcd.print("B");lcd.print(nilaiLDR2);
        lcd.setCursor(13,1);
        lcd.print("C");lcd.print(sensorBenda);
        delay(300);
        lcd.clear(); 
      }

      next = digitalRead(b2);
      back = digitalRead(b3);
      if (next == HIGH)
      {
        palang1.write(palang1_tutup);
        palang2.write(palang2_buka);
      }
      else if (next == LOW)
      {
        palang1.write(palang1_buka); // tutup palang belok
        palang2.write(palang2_tutup); // tutup palang kanan
      }
      if (back == HIGH)
      {
        delay(100);
        awal1();
      }    
    }  
}
/* 
=============================================================================== 
Opsional pada tampilan Tes Sensor 
===============================================================================*/

/* 
=============================================================================== 
Penentuan Baik dan Buruk Telur Ayam Berdasarkan Resistansi Cahaya 
===============================================================================*/
void sensor_ayam_ras()
{
      counter++;
      Serial.print("A= "); Serial.print(nilaiLDR1);
      Serial.print(" B= "); Serial.print(nilaiLDR2);      
      Serial.print(" Counter= "); Serial.println(counter);
      nilaiLDR1 = analogRead(ldr1);
      nilaiLDR2 = analogRead(ldr2);
//      delay(50);
      if ((counter == 5) && (nilaiLDR1 <= 913))
      {
//        delay(100);
        count_r_Bagus++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("IN = ");
        lcd.print(count_r_Total);
        lcd.setCursor(8,0);
        lcd.print("Cek>(OK)");
        lcd.setCursor(0,1);
        lcd.print("TERDETEKSI   RAS");        
        palang1.write(palang1_tutup);//40
        palang2.write(palang2_buka);//10
        Serial.println("======"); 
        delay(1500);
      }
      if ((counter == 5) && (nilaiLDR1 >=914))
      {
        count_r_Jelek++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("IN = ");
        lcd.print(count_r_Total);
        lcd.setCursor(8,0);
        lcd.print("Cek>(OK)");
        lcd.setCursor(0,1);
        lcd.print("TERDETEKSI   RAS");               
        palang1.write(palang1_buka);//90
        palang2.write(palang2_tutup);//104
        Serial.println("======");         
        delay(1000);
      }
}

void sensor_ayam_kampung()
{
      counterr++;
      Serial.print("A= "); Serial.print(nilaiLDR1);
      Serial.print(" B= "); Serial.print(nilaiLDR2);      
      Serial.print(" Counter= "); Serial.println(counterr);
      nilaiLDR1 = analogRead(ldr1);
      nilaiLDR2 = analogRead(ldr2); 
//      if ((counterr == 6) && (nilaiLDR2 <=949))
      if ((nilaiLDR2 <=949) && (counterr == 7))
      {
        count_k_Bagus++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("IN = ");
        lcd.print(count_k_Total);
        lcd.setCursor(8,0);
        lcd.print("Cek>(OK)");
        lcd.setCursor(0,1);
        lcd.print("TERDETEKSI KMPNG");
        palang1.write(palang1_tutup);//40
        palang2.write(palang2_buka);//10
        Serial.print("A= "); Serial.println(nilaiLDR2);  
        Serial.println("======");       
        delay(1300);
      }
//      if ((counterr == 6) && (nilaiLDR2 >=950))
      if ((nilaiLDR2 >=950) && (counterr == 7))
      {
        count_k_Jelek++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("IN = ");
        lcd.print(count_k_Total);
        lcd.setCursor(8,0);
        lcd.print("Cek>(OK)");
        lcd.setCursor(0,1);
        lcd.print("TERDETEKSI KMPNG");        
        palang1.write(palang1_buka);//90
        palang2.write(palang2_tutup);//104
        Serial.print("A= "); Serial.println(nilaiLDR2);     
        Serial.println("======");        
        delay(1000);
      }
}
/* 
=============================================================================== 
Penentuan Baik dan Buruk Telur Ayam Berdasarkan Resistansi Cahaya 
===============================================================================*/

/* 
=============================================================================== 
Menampilkan Menu Utama Ketika Baru Dinyalakan
===============================================================================*/
void menu_utama()
{
  menu_utama1:
  while(1)
  {
    analogWrite(ENB, 0); 
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);    
    palang1.write(90);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OPSIONAL TELUR>>");
    lcd.setCursor(0,1);
    lcd.print("1. AYAM RAS");
    delay(500);

    ok = digitalRead(b1);
    next = digitalRead(b2);
    back = digitalRead(b3);
    if (ok == HIGH)
    {
      delay(100);
      loading2();
      ayam_ras();
    }
    if (next == HIGH) 
    {
      delay(100);
      goto menu_utama2;
    }
    if (back == HIGH)
    {
      delay(100);
      goto menu_utama1;
    }
  }

  menu_utama2:
  while(1)
  {
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OPSIONAL TELUR>>");
    lcd.setCursor(0,1);
    lcd.print("2. AYAM KAMPUNG");
    delay(500);

    ok = digitalRead(b1);
    next = digitalRead(b2);
    back = digitalRead(b3);
    if (ok == HIGH)
    {
      delay(100);
      loading2();
      ayam_kampung();
    }
    if (next == HIGH) 
    {
      delay(100);
      goto menu_utama3;
    }
    if (back == HIGH)
    {
      delay(100);
      goto menu_utama1;
    } 
  } 

  menu_utama3:
  while(1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OPSIONAL TELUR>>");
    lcd.setCursor(0,1);
    lcd.print("3. CEK SENSOR");
    delay(500);

    ok = digitalRead(b1);
    next = digitalRead(b2);
    back = digitalRead(b3);
    if (ok == HIGH)
    {
      delay(100);
      awal1();
    }
    if (next == HIGH) 
    {
      delay(100);
      goto menu_utama1;
    }
    if (back == HIGH)
    {
      delay(100);
      goto menu_utama1;
    } 
  }
}
/* 
=============================================================================== 
Menampilkan Menu Utama Ketika Baru Dinyalakan
===============================================================================*/

/* 
=============================================================================== 
Tampilan Ketika Telur Ayam Dipilih
===============================================================================*/
void interface_ayam_ras()
{   
    //Serial.println("interface_ayam_ras");
    //Dinamo Conveyor
    analogWrite(ENB, motor); 
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
//    serial_monitor();
    int sensorBenda = digitalRead(proximity);
    if (sensorBenda == LOW)
    {
//      digitalWrite(13, HIGH);
      sensor_ayam_ras();
      count_r_Total = count_r_Bagus + count_r_Jelek;
    }
    else
    {
//      digitalWrite(13, LOW);
      counter = 0;
      palang1.write(palang1_buka);
      palang2.write(palang2_tutup);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("IN = ");
      lcd.print(count_r_Total);
      lcd.setCursor(8,0);
      lcd.print("Cek>(OK)");
      lcd.setCursor(0,1);
      lcd.print("KOSONG       RAS");
      delay(100);
      lcd.clear();
    }
}  

void interface_ayam_kampung()
{    
    //Dinamo Conveyor
//    serial_monitor();
    analogWrite(ENB, motor); 
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
    int sensorBenda = digitalRead(proximity);
    if (sensorBenda == LOW)
    {
      sensor_ayam_kampung();
      count_k_Total = count_k_Bagus + count_k_Jelek;
    }
    else
    {
      counterr = 0;
      palang1.write(palang1_buka);//90
      palang2.write(palang2_tutup);//104
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("IN = ");
      lcd.print(count_k_Total);
      lcd.setCursor(8,0);
      lcd.print("Cek>(OK)");
      lcd.setCursor(0,1);
      lcd.print("KOSONG     KMPNG");
      delay(100);
      lcd.clear(); 
    }
}

void ayam_ras()
{
  //menu1:   //A Y A M   R A S
  while(1)
  {
    interface_ayam_ras();
    
    ok = digitalRead(b1);
    next = digitalRead(b2);
    back = digitalRead(b3);
    
    if (ok == HIGH)
    {
      delay(100);
      loading2();
      total_ayam_ras();
    }
    if (next == LOW) {}
    if (back == HIGH) 
    {
      delay(100);
      count_r_Total = 0;
      count_r_Bagus = 0;
      count_r_Jelek = 0;
      loading2();
      menu_utama();
    }
  }
}

void ayam_kampung()
{
  //menu2:  // A Y A M   K A M P U N G
  while(1)
  {
    interface_ayam_kampung();
    
    ok = digitalRead(b1);
    next = digitalRead(b2);
    back = digitalRead(b3);
    if (ok == HIGH)
    {
      delay(100);
      loading2();
      total_ayam_kampung();
    }
    if (next == LOW) {}
    if (back == HIGH) 
    {
      delay(100);
      count_k_Total = 0;
      count_k_Bagus = 0;
      count_k_Jelek = 0;
      loading2();
      menu_utama();
    }
  }
}
/* 
=============================================================================== 
Tampilan Ketika Telur Ayam Ras Dipilih
===============================================================================*/

/* 
=============================================================================== 
Tampilan Total Telur Yang Telah Diperiksa 
===============================================================================*/
void total_ayam_ras()
{
   //tampil total telur ayam ras
   //Serial.println("total_ayam_ras");
   analogWrite(ENB, 0); 
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW);       
   while(1)
   {           
     lcd.setCursor(0,0);
     lcd.print("Ayam Ras=");
     lcd.print(count_r_Total);
     lcd.setCursor(0,1);
     lcd.print("BGS=");
     lcd.print(count_r_Bagus);
     lcd.setCursor(6,1);
     lcd.print(" JLK=");
     lcd.print(count_r_Jelek);
     delay(500);
     lcd.clear();
      
     ok = digitalRead(b1);
     next = digitalRead(b2);
     back = digitalRead(b3);
     if (ok == LOW) {}
     if (next == HIGH) 
     {
       delay(100);
       ayam_ras();
     }
     if (back == HIGH) 
     {
       delay(100);
       count_r_Total = 0;
       count_r_Bagus = 0;
       count_r_Jelek = 0;
       loading2();
       menu_utama();
     }
   }
}

void total_ayam_kampung()
{  
   //Serial.println("total_ayam_kampung");
   analogWrite(ENB, 0); 
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW);   
   while(1)
   {           
      lcd.setCursor(0,0);
      lcd.print("Ayam Kampung=");
      lcd.print(count_k_Total);
      lcd.setCursor(0,1);
      lcd.print("BGS=");
      lcd.print(count_k_Bagus);
      lcd.setCursor(6,1);
      lcd.print(" JLK=");
      lcd.print(count_k_Jelek);
      delay(500);
      lcd.clear();
      
      ok = digitalRead(b1);
      next = digitalRead(b2);
      back = digitalRead(b3);
      if (ok == LOW) {}
      if (next == HIGH) 
      {
        delay(100);
        ayam_kampung();
      }
      if (back == HIGH) 
      {
        delay(100);
        count_k_Total = 0;
        count_k_Bagus = 0;
        count_k_Jelek = 0;
        loading2();
        menu_utama();
      }
   }
}
/* 
=============================================================================== 
Tampilan Total Telur Yang Telah Diperiksa 
===============================================================================*/


void loop()
{
  splash();
  
  //Millis untuk menyalakan lampu secara terus menerus
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval)
  ledState = !ledState;
  digitalWrite(13, ledState);
  previousMillis = millis();
  
  palang1.write(palang1_buka);
  palang2.write(palang2_tutup);  
  menu_utama();
}
