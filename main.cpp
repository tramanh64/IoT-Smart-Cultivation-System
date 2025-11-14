// ==== BLYNK CONFIG ====
#define BLYNK_TEMPLATE_NAME "test"
#define BLYNK_AUTH_TOKEN "gC0qmFecupliijwqDzebjTQNfQL1-sha"
#define BLYNK_TEMPLATE_ID "TMPL6fV6uEyIh"
#define BLYNK_PRINT Serial // Enable Blynk debug print

// ==== LIBRARIES ====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ==== WiFi CONFIG ====
char ssid[] = "Iphone S23 ultra";
char pass[] = "123456777";

// ==== HARDWARE DEFINITIONS ====
#define DHTPIN 16
#define DHTTYPE DHT11
#define SOIL_SENSOR_PIN 32
#define RELAY_PIN 26

// ==== OBJECT INITIALIZATION ====
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

// ==== MOISTURE THRESHOLDS ====
const int DO_AM_BAT_BOM = 30; // Turn pump ON when moisture < 30%
const int DO_AM_TAT_BOM = 60; // Turn pump OFF when moisture > 60%

// ==== STATUS VARIABLES ====
bool cheDoTuDong = true; // true: Auto Mode, false: Manual Mode

// ==== PUMP CONTROL & APP SYNC FUNCTION ====
void dieuKhienBom(bool turnon) {
  if (turnon) {
    digitalWrite(RELAY_PIN, LOW); // Turn pump ON
    // Update pump button on app
    Blynk.virtualWrite(V3, 1);
    Blynk.virtualWrite(V5, 255); // Turn LED widget ON
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Turn pump OFF
    // Update pump button on app
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V5, 0); // Turn LED widget OFF
  }
}

// ==== BLYNK: Sync state on connect ====
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V3, V4); // Sync V3, V4 from server
  Blynk.virtualWrite(V3, digitalRead(RELAY_PIN) == LOW ? 1 : 0); // Sync pump status
  Blynk.virtualWrite(V4, cheDoTuDong ? 1 : 0); // Sync mode status
}

// ==== BLYNK: Mode Selection (V4) ====
BLYNK_WRITE(V4) {
  int value = param.asInt();
  cheDoTuDong = (value == 1);
  Serial.println(cheDoTuDong ? "Mode: AUTO" : "Mode: MANUAL");
}

// ==== BLYNK: Manual Pump Control (V3) ====
BLYNK_WRITE(V3) {
  if (!cheDoTuDong) { // Only works in manual mode
    int pumpState = param.asInt();
    dieuKhienBom(pumpState);
  }
}

// ==== SENSOR READING AND PROCESSING FUNCTION ====
void docVaXuLyCamBien() {
  float nhietdo = dht.readTemperature();
  float doamkk = dht.readHumidity();
  int soilRaw = analogRead(SOIL_SENSOR_PIN);
  float doamdat = map(soilRaw, 0, 4095, 100, 0); // Map analog value to 100-0%

  // Check for DHT11 sensor read error
  if (isnan(nhietdo) || isnan(doamkk)) {
    nhietdo = 0.0;
    doamkk = 0.0;
    Serial.println("Failed to read from DHT11 sensor!");
  }

  // Send data to Blynk
  Blynk.virtualWrite(V0, nhietdo); // Temperature
  Blynk.virtualWrite(V1, doamkk);  // Air Humidity
  Blynk.virtualWrite(V2, doamdat); // Soil Moisture

  // Display on LCD line 1
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(nhietdo, 1);
  lcd.print((char)223); // Degree symbol °
  lcd.print("C H:");
  lcd.print(doamkk, 0);
  lcd.print("%");

  // Display on LCD line 2
  lcd.setCursor(0, 1);
  lcd.print("Dat:"); // Soil
  lcd.print(doamdat, 0);
  lcd.print("% ");
  lcd.print(cheDoTuDong ? "AUTO " : "MANU ");
  lcd.print(digitalRead(RELAY_PIN) == LOW ? "ON " : "OFF");

  // Handle automatic irrigation logic (only in auto mode)
  if (cheDoTuDong) {
    if (doamdat < DO_AM_BAT_BOM) {
      dieuKhienBom(true); // Turn pump ON
    } else if (doamdat > DO_AM_TAT_BOM) {
      dieuKhienBom(false); // Turn pump OFF
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Default pump state is OFF

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  // Connect to WiFi with timeout
  unsigned long startAttemptTime = millis();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connect Fail");
    while (true); // Stop if cannot connect
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi OK!");
  delay(1000);

  // Connect to Blynk with timeout
  startAttemptTime = millis();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  while (!Blynk.connected() && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (!Blynk.connected()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Blynk Connect Fail");
    while (true); // Stop if cannot connect
  }
  
  lcd.clear();
  // Set up timer to call docVaXuLyCamBien every 2 seconds
  timer.setInterval(2000L, docVaXuLyCamBien);
}

void loop() {
  Blynk.run(); // Maintain Blynk connection
  timer.run(); // Run timed tasks
}