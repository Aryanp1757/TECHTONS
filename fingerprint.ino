#include<Fingerprint.h>  
#include<SoftwareSerial.h>  
#include<Streaming.h>  
#include<Servo.h>  
  
#define __Debug 1  
  
const int pinServo = 6;  
const int angleServo = 60;  
  
#if __Debug  
#define DBG(X) Serial.println(X)  
#else  
#define DBG(X)  
#endif  
  
SoftwareSerial mySerial(A5, A4);  
Fingerprint finger = Fingerprint( & mySerial);  
Servo myservo;  
  
void open_close_door()   
{  
    myservo.attach(pinServo);  
    for (int i = 20; i < angleServo; i++)   
    {  
        myservo.write(i);  
        delay(5);  
    }  
    delay(2000);  
    for (int i = (angleServo - 1); i >= 20; i--)  
    {  
        myservo.write(i);  
        delay(5);  
    }  
    myservo.detach();  
}  
  
void setup()   
{  
    Serial.begin(38400);  
    finger.begin(19200);  
    delay(500);  
    DBG("setup ok!");  
}  
  
void loop()   
{  
    if (getFingerprintIDez() >= 0)   
    {  
        open_close_door();  
        DBG("get right finger, open door now!!");  
        delay(2000);  
    }  
    delay(50);  
}  
  
int getFingerprintIDez()   
{  
    if !finger.verifyPassword())   
    {  
        DBG("Did not find fingerprint sensor :(");  
        return -1;  
    }  
    uint8_t p = finger.getImage();  
    if (p != FINGERPRINT_OK)   
    {  
        return -1;  
    }  
    p = finger.image2Tz();  
    if (p != FINGERPRINT_OK)  
    {  
        return -1;  
    }  
    p = finger.fingerFastSearch();  
    if (p != FINGERPRINT_OK)   
    {  
        return -1;  
    }  
    #if __Debug  
        Serial.print("Found ID #");  
        Serial.print(finger.fingerID);  
        Serial.print(" with confidence of ");  
        DBG(finger.confidence);  
    #endif  
      
    return finger.fingerID;  
} 