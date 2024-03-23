#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Audio.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define I2S_DOUT      33 // connect to DAC pin DIN
#define I2S_BCLK      32 // connect to DAC pin BCK
#define I2S_LRC       25 // connect to DAC pin LCK
Audio audio;

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 5
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


// https://pjrp.github.io/MDParolaFontEditor
MD_MAX72XX::fontType_t newFont[] PROGMEM = 
{
	3, 0, 0, 0, 	// 0
	2, 0, 0, 	// 1
	3, 0, 0, 0, 	// 2
	3, 0, 0, 0, 	// 3
	3, 0, 0, 0, 	// 4
	3, 0, 0, 0, 	// 5
	3, 0, 0, 0, 	// 6
	3, 0, 0, 0, 	// 7
	3, 0, 0, 0, 	// 8
	3, 0, 0, 0, 	// 9
	0, 	// 10
	0, 	// 11
	0, 	// 12
	0, 	// 13
	0, 	// 14
	0, 	// 15
	0, 	// 16
	0, 	// 17
	0, 	// 18
	0, 	// 19
	0, 	// 20
	0, 	// 21
	0, 	// 22
	0, 	// 23
	0, 	// 24
	0, 	// 25
	0, 	// 26
	0, 	// 27
	0, 	// 28
	0, 	// 29
	0, 	// 30
	0, 	// 31
	0, 	// 32
	0, 	// 33
	0, 	// 34
	0, 	// 35
	0, 	// 36
	0, 	// 37
	0, 	// 38
	0, 	// 39
	0, 	// 40
	0, 	// 41
	0, 	// 42
	0, 	// 43
	0, 	// 44
	0, 	// 45
	0, 	// 46
	0, 	// 47
	3, 60, 66, 60, 	// 48
	3, 68, 126, 64, 	// 49
	3, 100, 82, 76, 	// 50
	3, 34, 74, 52, 	// 51
	3, 30, 16, 126, 	// 52
	3, 46, 74, 50, 	// 53
	3, 60, 74, 50, 	// 54
	3, 2, 114, 14, 	// 55
	3, 52, 74, 52, 	// 56
	3, 76, 82, 60, 	// 57
	1, 20, 	// 58
	0, 	// 59
	0, 	// 60
	0, 	// 61
	0, 	// 62
	0, 	// 63
	0, 	// 64
	0, 	// 65
	0, 	// 66
	0, 	// 67
	0, 	// 68
	0, 	// 69
	0, 	// 70
	0, 	// 71
	0, 	// 72
	0, 	// 73
	0, 	// 74
	0, 	// 75
	0, 	// 76
	0, 	// 77
	0, 	// 78
	0, 	// 79
	0, 	// 80
	0, 	// 81
	0, 	// 82
	0, 	// 83
	0, 	// 84
	0, 	// 85
	0, 	// 86
	0, 	// 87
	0, 	// 88
	0, 	// 89
	0, 	// 90
	0, 	// 91
	0, 	// 92
	0, 	// 93
	0, 	// 94
	0, 	// 95
	0, 	// 96
	0, 	// 97
	0, 	// 98
	0, 	// 99
	0, 	// 100
	0, 	// 101
	0, 	// 102
	0, 	// 103
	0, 	// 104
	0, 	// 105
	0, 	// 106
	0, 	// 107
	0, 	// 108
	0, 	// 109
	0, 	// 110
	0, 	// 111
	0, 	// 112
	0, 	// 113
	0, 	// 114
	0, 	// 115
	0, 	// 116
	0, 	// 117
	0, 	// 118
	0, 	// 119
	0, 	// 120
	0, 	// 121
	0, 	// 122
	0, 	// 123
	0, 	// 124
	0, 	// 125
	0, 	// 126
	0, 	// 127
	0, 	// 128
	0, 	// 129
	0, 	// 130
	0, 	// 131
	0, 	// 132
	0, 	// 133
	0, 	// 134
	0, 	// 135
	0, 	// 136
	0, 	// 137
	0, 	// 138
	0, 	// 139
	0, 	// 140
	0, 	// 141
	0, 	// 142
	0, 	// 143
	0, 	// 144
	0, 	// 145
	0, 	// 146
	0, 	// 147
	0, 	// 148
	0, 	// 149
	0, 	// 150
	0, 	// 151
	0, 	// 152
	0, 	// 153
	0, 	// 154
	0, 	// 155
	0, 	// 156
	0, 	// 157
	0, 	// 158
	0, 	// 159
	0, 	// 160
	0, 	// 161
	0, 	// 162
	0, 	// 163
	0, 	// 164
	0, 	// 165
	0, 	// 166
	0, 	// 167
	0, 	// 168
	0, 	// 169
	0, 	// 170
	0, 	// 171
	0, 	// 172
	0, 	// 173
	0, 	// 174
	0, 	// 175
	0, 	// 176
	0, 	// 177
	0, 	// 178
	0, 	// 179
	0, 	// 180
	0, 	// 181
	0, 	// 182
	0, 	// 183
	0, 	// 184
	0, 	// 185
	0, 	// 186
	0, 	// 187
	0, 	// 188
	0, 	// 189
	0, 	// 190
	0, 	// 191
	0, 	// 192
	0, 	// 193
	0, 	// 194
	0, 	// 195
	0, 	// 196
	0, 	// 197
	0, 	// 198
	0, 	// 199
	0, 	// 200
	0, 	// 201
	0, 	// 202
	0, 	// 203
	0, 	// 204
	0, 	// 205
	0, 	// 206
	0, 	// 207
	0, 	// 208
	0, 	// 209
	0, 	// 210
	0, 	// 211
	0, 	// 212
	0, 	// 213
	0, 	// 214
	0, 	// 215
	0, 	// 216
	0, 	// 217
	0, 	// 218
	0, 	// 219
	0, 	// 220
	0, 	// 221
	0, 	// 222
	0, 	// 223
	0, 	// 224
	0, 	// 225
	0, 	// 226
	0, 	// 227
	0, 	// 228
	0, 	// 229
	0, 	// 230
	0, 	// 231
	0, 	// 232
	0, 	// 233
	0, 	// 234
	0, 	// 235
	0, 	// 236
	0, 	// 237
	0, 	// 238
	0, 	// 239
	0, 	// 240
	0, 	// 241
	0, 	// 242
	0, 	// 243
	0, 	// 244
	0, 	// 245
	0, 	// 246
	0, 	// 247
	0, 	// 248
	0, 	// 249
	0, 	// 250
	0, 	// 251
	0, 	// 252
	0, 	// 253
	0, 	// 254
	0, 	// 255
};


// Dane sieci WiFi
const char *ssid =     "Winter_is_Coming_Guest";
const char *password = "966_Kocia!Szajka";

WiFiUDP ntpUDP;
// Możesz zmienić offset czasowy na właściwy dla twojej strefy czasowej
// na przykład dla Polski będzie to 3600 sekund * liczba godzin przesunięcia
// CET = +1h, więc offset = 3600, CEST = +2h, więc offset = 7200
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 3600*1000);

volatile long seconds = 0; // Licznik sekund
hw_timer_t *timer0 = NULL; // Deklaracja timera
unsigned long lastSyncTime = 0; // Zmienna do śledzenia czasu ostatniej synchronizacji z NTP
unsigned long lastUpdateTime = 0; // Zmienna do śledzenia czasu ostatniej aktualizacji wyświetlacza


void IRAM_ATTR onTimer() {
  seconds++;
}

void setup() {
    Serial.begin(115200);
    Serial.println("ESP32");

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    // Inicjalizacja i połączenie z WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Połączono z WiFi");


    // Inicjalizacja klienta NTP
    timeClient.begin();
    // Synchronizacja czasu przy pierwszym uruchomieniu
    timeClient.update();
    seconds = timeClient.getEpochTime();

    // Ustawienie timera i przerwania
    timer0 = timerBegin(0, 80, true); // Ustawienie timera na 1 Hz
    timerAttachInterrupt(timer0, &onTimer, true);
    timerAlarmWrite(timer0, 1000000, true);
    timerAlarmEnable(timer0);

    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(10); // default 0...21

    Display.begin();
    Display.setFont(newFont);
    Display.setIntensity(0);
    Display.displayClear();
    //Display.displayScroll("Bardzo długi tekst", PA_RIGHT, PA_SCROLL_LEFT, 150);

  //audio.connecttohost("http://www.emsoft.ct8.pl/inne/anty.m3u");                                // m3u

  audio.connecttospeech("Połączono z internetem", "pl"); // Google TTS
}

void formatTime(long epochTime, char* buffer, size_t bufferSize) {
  struct tm *ptm = gmtime((time_t *)&epochTime);
  // Ensure the buffer is large enough for "HH:MM:SS\n\0"
  if (bufferSize >= 11) {
    // Use snprintf to safely format the string within buffer limits
    snprintf(buffer, bufferSize, "%02d:%02d:%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
  }
}

void loop() {
  audio.loop();
  unsigned long currentTimeMillis = millis();

  // Aktualizacja czasu co godzinę
  if (currentTimeMillis - lastSyncTime > 3600000) {
    timeClient.update();
    seconds = timeClient.getEpochTime();
    lastSyncTime = currentTimeMillis;
  }

  // Wyświetlanie czasu co sekundę
  if (currentTimeMillis - lastUpdateTime > 1000) {
    lastUpdateTime = currentTimeMillis; // Zapamiętujemy czas tej aktualizacji

    char timeStr[14]; // Buffer to hold the time string
    formatTime(seconds, timeStr, sizeof(timeStr));
    char *pText = new char[14];
    strcpy(pText, timeStr);
    Serial.print(pText);

    // Czyszczenie wyświetlacza i wyświetlanie czasu
    Display.displayClear();
    Display.displayText(pText, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT); // Testowy tekst
  }

  // Inkrementacja czasu - aktualizacja każdą sekundę
  if(seconds % 1000 == 0) {
    seconds++;
  }


  // Kontynuacja animacji (jeśli jest używana)
  if (Display.displayAnimate()) {
    Display.displayReset();
  }

}
