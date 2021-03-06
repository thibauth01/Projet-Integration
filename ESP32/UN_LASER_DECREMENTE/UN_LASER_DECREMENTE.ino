#include <WiFi.h>
#include <HTTPClient.h>

/*
  1 LASERS SUR UNE CARTE POUR COMPTER 
  LES SORTIES DANS UNE SEULE PORTE
*/

// Network credentials
const char* ssid = "V30";
const char* password = "11111111";

String scene = "1";

const char* serverName = "http://peopleflux.gauthierbohyn.com/post-esp-data.php";
String apiKeyValue = "12mAT5Ab3j7F9";
boolean vrai = 0;  // VALEUR PRECEDENTE DU LASER AU COMPTEUR

void setup() {
  Serial.begin(115200);
  pinMode(18, INPUT);  // RECEPTEUR LASER ENTRÉE
  pinMode(21, OUTPUT); // LED bleu
  pinMode(23, OUTPUT); // LED jaune
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
    ledBlink(2,23);
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  ledBlink(2,21);
  Serial.println(WiFi.localIP());
}
void ledBlink(int x, int y){ // Clignotement LED
  int i;
  for(i=0;i<x;i++){       
    digitalWrite(y, HIGH); // Allume led
    delay(200);            // Attend 0.2s
    digitalWrite(y, LOW);  // Eteint led
    delay(100);            // Attend 0.1s
  }
}
int decremente(){
  int valeur = (digitalRead(18)); // VALEUR RECEPTEUR LASER
  if(valeur == 0 && vrai == 1){
    vrai = 0;
    ledBlink(1,21);
    return 1;
  }
  else if(valeur == 1){
    vrai = 1;
    return 0;
  }
}
void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    
    HTTPClient http;
    // Domain name with URL path
    http.begin(serverName);
    
    // Content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&id_stage=" + scene
                          + "&nbr_sortie=" + "1";
    
    // Send HTTP POST request
    if(decremente() == 1){
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);
      delay(500);
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      if(httpResponseCode!=200){
        ledBlink(3,23);
      }
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
    ledBlink(2,23);
  } 
}
