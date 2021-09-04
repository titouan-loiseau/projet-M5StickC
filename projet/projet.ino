#include <M5StickC.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "ESP32_MailClient.h"
#include "credentials.h"

//---------//
//VARIABLES//
//---------//


//Accélérations
float accX = 0;
float accY = 0;
float accZ = 0;

float acc_seuil = 4; //Seuil de détection de la chute

//WIFI
WiFiMulti WiFiMulti;

char* wifi_ssid = WIFISSID; //Fichier credentials.h
char* wifi_password = WIFIPASS; //Fichier credentials.h

//EMAIL

#define GMAIL_SMTP_SEVER "smtp.gmail.com" //Serveur SMTP GMail
#define GMAIL_SMTP_PORT 465 //Port SMTP

SMTPData EmailData;



//---------//
//FONCTIONS//
//---------//


//Envoie un E-Mail à l'addresse "recipient" en provenence de l'addresse "sender"
String sendEmail(char *subject, char *sender, char *body, char *recipient, boolean htmlFormat) {
  EmailData.setLogin(GMAIL_SMTP_SEVER, GMAIL_SMTP_PORT, GMAIL_SMTP_USERNAME, GMAIL_SMTP_PASSWORD);
  EmailData.setSender(sender, GMAIL_SMTP_USERNAME);
  EmailData.setSubject(subject);
  EmailData.setMessage(body, htmlFormat);
  EmailData.addRecipient(recipient);
  if (!MailClient.sendMail(EmailData)) 
    return MailClient.smtpErrorReason();
  
  return "";
}


//-----//
//SETUP//
//-----//


void setup(void) {

  //Démarrage du M5
  M5.begin();

  //Communications avec l'ordinateur (debug)
  Serial.begin(115200);

  //Démarrage de l'accéléromètre du M5
  M5.MPU6886.Init();

  //Connexion au réseau WiFi
  WiFiMulti.addAP(wifi_ssid,wifi_password);
  M5.Lcd.print("Conexion au reseau WiFi ");
  while(WiFiMulti.run() != WL_CONNECTED) {
        M5.Lcd.print(".");
        delay(500);
  }
  M5.Lcd.println("");
  M5.Lcd.println("WiFi connecte");
  M5.Lcd.println("Addresse IP: ");
  M5.Lcd.println(WiFi.localIP());
  delay(500);
}


//----//
//LOOP//
//----//


void loop() {
  //Lit l'accélération 
  M5.MPU6886.getAccelData(&accX,&accY,&accZ);

  //Debug valeurs
  /*
  Serial.print("X: ");
  Serial.print(accX);
  Serial.print(", Y: ");
  Serial.print(accY);
  Serial.print(", Z: ");
  Serial.println(accZ);
  */

  float norme_acc = sqrt(accX*accX + accY*accY + accZ*accZ); //Calcul de la norme du vecteur d'accélération 

  if(norme_acc > acc_seuil) {
    //CHUTE
    M5.Lcd.fillScreen(RED);
  }

  
  
  //Détection appui bouton
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    //Envoie un E-Mail à soi-même sur l'adresse définie dans credentials.h
    sendEmail("Appui Bouton", GMAIL_SMTP_USERNAME, "Le bouton du M5StickC a été appuyé", GMAIL_SMTP_USERNAME, false);
  }
  
  delay(100);
}
