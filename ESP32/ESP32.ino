#include <WiFi.h>
#include <WebServer.h>

int nbrPersonne = 0;  // INITIALISATION A 0
int comptPrecedent = 0;  // VALEUR PRECEDENTE DU LASER AU COMPTEUR
int decomptPrecedant = 0; // VALEUR PRECEDENTE DU LASER AU DECOMPTEUR

const char* ssid = "*******";
const char* password = "*******";

WebServer server(80);  
           
int compteur(){
    int valeur = !(digitalRead(12)); // VALEUR RECEPTEUR LASER
    digitalWrite(13, HIGH); // EMETTEUR LASER
    if(valeur == 0 && comptPrecedent == 1){
        nbrPersonne++;
        comptPrecedent = 0;
        digitalWrite(27, HIGH);
        delay(200);
        digitalWrite(27, LOW);
        Serial.println("Nombre de personne : " + (String)nbrPersonne);
    }
    else if(valeur == 1){ 
        comptPrecedent = 1;
        delay(300);
        digitalWrite(27, LOW);
    }
    return nbrPersonne;
}
int decompteur(){
    int valeur = !(digitalRead(25)); // VALEUR RECEPTEUR LASER
    digitalWrite(26, HIGH); // EMETTEUR LASER
    if(valeur == 0 && decomptPrecedant == 1){
        nbrPersonne--;
        if(nbrPersonne <= 0){
          nbrPersonne = 0;
        }
        decomptPrecedant = 0;
        digitalWrite(27, HIGH);
        delay(200);
        digitalWrite(27, LOW);
        Serial.println("Nombre de personne : " + (String)nbrPersonne);
    }
    else if(valeur == 1){ 
        decomptPrecedant = 1;
        delay(300);
        digitalWrite(27, LOW);
    }
    return nbrPersonne;
}
void razBouton(){
    digitalWrite(33, HIGH);
    boolean raz = digitalRead(32);
    if(raz == HIGH){
        nbrPersonne = 0;
        digitalWrite(27, HIGH);
        delay(200);
        digitalWrite(27, LOW);
        Serial.println("Mise a zero : " + (String)nbrPersonne);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(13, OUTPUT); // EMETTEUR LASER 
    pinMode(12, INPUT);  // RECEPTEUR LASER
    pinMode(26, OUTPUT); // EMETTEUR LASER 
    pinMode(25, INPUT);  // RECEPTEUR LASER
    pinMode(27, OUTPUT); // LED 
    pinMode(33, OUTPUT); // Bouton retour a zero
    pinMode(32, INPUT);  // Bouton retour a zero
    delay(100);
    
    Serial.println("Connecting to ");
    Serial.println(ssid);
    
    //connect to your local wi-fi network
    WiFi.begin(ssid, password);
    
    //check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    }
    Serial.println("");
    Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
    
    server.on("/", handle_OnConnect);
    server.onNotFound(handle_NotFound);
    
    server.begin();
    Serial.println("HTTP server started");
}
void loop() {
    server.handleClient();
    compteur();
    decompteur();
    razBouton();
}

void handle_OnConnect() {
     server.send(200, "text/html", SendHTML(nbrPersonne)); 
}

void handle_NotFound(){
     server.send(404, "text/plain", "Not found");
}

String SendHTML(int val){
    String ptr = "<!DOCTYPE html> <html>\n";
    ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr +="<title>Nombre de personne</title>\n";
    ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
    ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
    ptr +="</style>\n";
    ptr +="<script>function timedRefresh(timeoutPeriod) {\n";  
    ptr +="setTimeout('location.reload(true);',timeoutPeriod);}\n"; 
    ptr +="window.onload = timedRefresh(2000);</script>\n";
    ptr +="</head>\n";
    ptr +="<body>\n";
    ptr +="<div id=\"webpage\">\n";
    ptr +="<h1>Nombre de personne en direct</h1>\n";
    ptr +="<p>Nombre : ";
    ptr +=val;
    ptr +="</p>";
    ptr +="</div>\n";
    ptr +="</body>\n";
    ptr +="</html>\n";
    return ptr;
}