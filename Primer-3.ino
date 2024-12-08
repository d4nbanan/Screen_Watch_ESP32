#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <ArduinoJson.h>

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

const char *ssid     = "";
const char *password = "";

WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "ua.pool.ntp.org", 7200, 60000); // ТАЙМЗОНА(в сек.)  соединение 1 раз/минута
NTPClient timeClient(ntpUDP, "ua.pool.ntp.org", 10800, 86400000);

String weekDays[7]={"BC", "\757H", "BT", "CP", "4T", "\757T", "C\753"};

unsigned long lastTime = 0, timerDelay = 60000;
String response;
int temp_c, wind, condition, maxTemp, minTemp;

String datesJSON = "{'2022':{'first':{'day':30,'month':10,'offset':7200},'second':{'day':26,'month':3,'offset':10800}},'2023':{'first':{'day':29,'month':10,'offset':7200},'second':{'day':31,'month':3,'offset':10800}},'2024':{'first':{'day':27,'month':10,'offset':7200},'second':{'day':30,'month':3,'offset':10800}},'2025':{'first':{'day':26,'month':10,'offset':7200},'second':{'day':29,'month':3,'offset':10800}},'2026':{'first':{'day':25,'month':10,'offset':7200},'second':{'day':28,'month':3,'offset':10800}},'2027':{'first':{'day':31,'month':10,'offset':7200},'second':{'day':26,'month':3,'offset':10800}},'2028':{'first':{'day':29,'month':10,'offset':7200},'second':{'day':25,'month':3,'offset':10800}},'2029':{'first':{'day':28,'month':10,'offset':7200},'second':{'day':31,'month':3,'offset':10800}},'2030':{'first':{'day':27,'month':10,'offset':7200},'second':{'day':30,'month':3,'offset':10800}},'2031':{'first':{'day':26,'month':10,'offset':7200},'second':{'day':28,'month':3,'offset':10800}},'2032':{'first':{'day':31,'month':10,'offset':7200},'second':{'day':27,'month':3,'offset':10800}},'2033':{'first':{'day':30,'month':10,'offset':7200},'second':{'day':26,'month':3,'offset':10800}},'2034':{'first':{'day':29,'month':10,'offset':7200},'second':{'day':25,'month':3,'offset':10800}},'2035':{'first':{'day':28,'month':10,'offset':7200},'second':{'day':30,'month':3,'offset':10800}},'2036':{'first':{'day':26,'month':10,'offset':7200},'second':{'day':29,'month':3,'offset':10800}}}";

void setup() {
    temp_c = 0;
    wind = 0;
    condition = 0;
    maxTemp = 0;
    minTemp = 0;
    
    Serial.begin(9600);

    DynamicJsonDocument dates(1024);
    deserializeJson(dates, datesJSON);

//    день_переведения_на_летнее_время = dates[текущий_год]["first"]["day"];
//    день_переведения_на_зимнее_время = dates[текущий_год]["second"]["day"];
//
//    месяц_переведения_на_летнее_время = dates[текущий_год]["first"]["month"];
//    месяц_переведения_на_зимнее_время = dates[текущий_год]["second"]["month"];
//
//    на_какой_часовой_пояс_переходить = dates[текущий_год]["first"]["offset"];
    
    
//    WiFiManager wifiManager;
//    wifiManager.autoConnect("AutoConnectDatex");

    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    timeClient.begin();
}

void sendReques(){
    WiFiClient client;
    HTTPClient http;

    response = "";

    while(response == ""){
        http.begin(client, "http://sleepy-dawn-36650.herokuapp.com/");
        http.addHeader("Content-Type", "application/json");
        int httpResponseCode = http.GET();
        Serial.println(httpResponseCode);

        response = http.getString();
        StaticJsonDocument<1024> doc;
        deserializeJson(doc, response, DeserializationOption::NestingLimit(20));
    
        temp_c = (int)doc["temp"];
        wind = (int)doc["wind"];
        condition = (int)doc["condition"];
        maxTemp = (int)doc["maxtemp"];
        minTemp = (int)doc["mintemp"];
        
        http.end();
        lastTime = millis();
    }
}

int monthDay, currentMonth, currentYear;

int firstReq = 0;

void loop() {
    if(firstReq == 0){
        sendReques();
        firstReq = 1;
    }
  
    if ((millis() - lastTime) > timerDelay) {
        sendReques();
    }

//    Serial.print(response);
    
    timeClient.update();
  
    unsigned long epochTime = timeClient.getEpochTime(); //время UNIX
    int currentHour = timeClient.getHours();
    int currentMinute = timeClient.getMinutes();
    int currentSecond = timeClient.getSeconds();
    String weekDay = weekDays[timeClient.getDay()]; //день недели
    
    struct tm *ptm = gmtime ((time_t *)&epochTime); 
    monthDay = ptm->tm_mday;
    currentMonth = ptm->tm_mon+1;
    currentYear = ptm->tm_year+1900;

//    String monthDayStr = String(monthDay);
//    String currentMonthStr = String(currentMonth);
//    String currentYearStr = String(currentYear);

    String currentDate = String(monthDay) + "." + String(currentMonth) + "." + String(currentYear);

  

    String formattedTime = timeClient.getFormattedTime();
    
  //  Serial.print("  ");
  //  Serial.println(currentDate);
  //  Serial.print(weekDay);
  //  Serial.print(" ");
  //  Serial.print(formattedTime);
  //  
  //  Serial.println("");

    Serial.print("\f");
    Serial.print(formattedTime);
    Serial.print(weekDay);
    Serial.print(currentDate);

    Serial.println("");
  
    String temp_cStr = String(abs(temp_c));
    if(abs(temp_c) < 10){
        temp_cStr = String(0) + temp_cStr;
    }
    if(temp_c >= 0){
        temp_cStr = "+" + temp_cStr;
    } else {
        temp_cStr = "-" + temp_cStr;
    }
    Serial.print(temp_cStr);
    Serial.print("\770");
//    Serial.print(" ");
  
    if(condition == 1000){
        Serial.print("()"); // солнечно
    } else if(condition == 1003 || condition == 1006){
        Serial.print("\157\760"); // переменная облачность
    } else if(condition == 1030 || condition == 1135 || condition == 1147){
        Serial.print("\760T"); // туман
    } else if(condition == 1009 || condition == 1072 || condition == 1168 || condition == 1150 || condition == 1171){
        Serial.print("\760\760"); // пасмурно
    } else if(condition == 1063 || condition == 1153 || condition == 1180 || condition == 1183 || condition == 1186 || condition == 1189){
        Serial.print("\760\660"); // слабый дождь
    } else if(condition == 1192 || condition == 1195 || condition == 1201 || condition == 1240){
        Serial.print("\760\662"); // сильный дождь
    } else if(condition == 1087){
        Serial.print("\760\373"); // гроза
    } else if(condition == 1066 || condition == 1210 || condition == 1213 || condition == 1255){
        Serial.print("\760\452"); // слабый снег
    } else if(condition == 1216 || condition == 1219 || condition == 1222 || condition == 1225 || condition == 1258){
        Serial.print("\452\452"); // сильный снег
    } else if(condition == 1279 || condition == 1282){
        Serial.print("\452\373"); // снег с грозой
    } else if(condition == 1273){
        Serial.print("\660\373"); // слабый дождь с грозой
    } else if(condition == 1276){
        Serial.print("\662\373"); // сильный дождь с грозой
    } else if(condition == 1069 || condition == 1204){
        Serial.print("\660\452"); // легкий дождь со снегом
    } else if(condition == 1114){
        Serial.print("\452\176"); // низовая метель
    } else if(condition == 1117){
        Serial.print("\452\767"); // снежная буря
    } else if(condition == 1207 || condition == 1249 || condition == 1252){
        Serial.print("\662\452"); // сильный дождь со снегом
    } else if(condition == 1198 || condition == 1237 || condition == 1261){
        Serial.print("\137\660"); // слабый ледяной дождь
    } else if(condition == 1264){
        Serial.print("\137\662"); // сильный ледяной дождь
    } else if(condition == 1243 || condition == 1246){
        Serial.print("\137\662"); // ливень
    } else{
        Serial.print("--");
    }
  
    Serial.print(" ");
    String maxTempStr = String(abs(maxTemp));
    if(abs(maxTemp) < 10){
        maxTempStr = String(0) + maxTempStr;
    }
    if(maxTemp >= 0){
        maxTempStr = "+" + maxTempStr;
    } else {
        maxTempStr = "-" + maxTempStr;
    }
    Serial.print(maxTempStr);
    Serial.print("\770>");
    
    String minTempStr = String(abs(minTemp));
    if(abs(minTemp) < 10){
        minTempStr = String(0) + minTempStr;
    }
    if(minTemp >= 0){
        minTempStr = "+" + minTempStr;
    } else {
        minTempStr = "-" + minTempStr;
    }
    Serial.print(minTempStr);
    Serial.print("\770");
    
    Serial.print(" ");
  
    if(wind < 99){
        Serial.print("\176" + String(wind));
    } else {
        Serial.print(wind);
    }
//    Serial.println("");
  delay(1000);
      
}
