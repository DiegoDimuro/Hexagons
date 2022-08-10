#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "DeathStar";
const char* password = "Tesla1983";

const String host = "http://api.openweathermap.org/data/2.5/weather?q=Colegiales&units=metric&APPID=";
const String privateKey = "c515daa1fe824ab071c97764a511bfbf";
const int delayTime = 10000; // sugerencia 1 minuto -> 60000


void setup() {
  Serial.begin(115200);
  delay(20);

  // Nos intentamos conectar a la red wifi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado a la red WiFi!!!");
  Serial.println("");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { 
    HTTPClient http;
    http.begin(host + privateKey); //armamos la URL
    int httpCode = http.GET();  //Realizamos la petición
    if (httpCode > 0) { //código de retorno
        String data = http.getString();
        //Serial.println(httpCode); // esperamos que sea 200
        //Serial.println(data);

            // String input;
            StaticJsonDocument<1024> doc;
            DeserializationError error = deserializeJson(doc, data);
            if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
            }
            float coord_lon = doc["coord"]["lon"]; // -58.4492
            float coord_lat = doc["coord"]["lat"]; // -34.5737
            JsonObject weather_0 = doc["weather"][0];
            int weather_0_id = weather_0["id"]; // 800
            const char* weather_0_main = weather_0["main"]; // "Clear"
            const char* weather_0_description = weather_0["description"]; // "clear sky"
            const char* weather_0_icon = weather_0["icon"]; // "01n"
            const char* base = doc["base"]; // "stations"
            JsonObject main = doc["main"];
            float main_temp = main["temp"]; // 12.09
            float main_feels_like = main["feels_like"]; // 10.76
            int main_temp_min = main["temp_min"]; // 10
            int main_temp_max = main["temp_max"]; // 13
            int main_pressure = main["pressure"]; // 1024
            int main_humidity = main["humidity"]; // 54
            int visibility = doc["visibility"]; // 10000
            float wind_speed = doc["wind"]["speed"]; // 2.06
            int wind_deg = doc["wind"]["deg"]; // 190
            int clouds_all = doc["clouds"]["all"]; // 0
            long dt = doc["dt"]; // 1620695928
            JsonObject sys = doc["sys"];
            int sys_type = sys["type"]; // 1
            int sys_id = sys["id"]; // 8224
            const char* sys_country = sys["country"]; // "AR"
            long sys_sunrise = sys["sunrise"]; // 1620643006
            long sys_sunset = sys["sunset"]; // 1620680620
            int timezone = doc["timezone"]; // -10800
            long id = doc["id"]; // 3435356
            const char* name = doc["name"]; // "Colegiales"
            int cod = doc["cod"]; // 200
            Serial.print("Temperatura: ");
            Serial.println(main_temp);
            Serial.print("Ubicacion: ");
            Serial.println(name);
      }
    else {
      Serial.println("Error en la petición HTTP");
    }
    http.end(); //cerramos conexión y liberamos recursos
  }
  delay(delayTime);
}