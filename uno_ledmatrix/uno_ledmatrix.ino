#include "LedControl.h"

const int g_chars[] PROGMEM = {
  ' ', B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 8,
  ':', B00000000, B00000110, B00000110, B00000000, B00000110, B00000110, B00000000, B00000000, 3,
  '0', B00011100, B00100010, B00100110, B00101010, B00110010, B00100010, B00011100, B00000000, 6,
  '1', B00000100, B00001100, B00000100, B00000100, B00000100, B00000100, B00001110, B00000000, 4,
  '2', B00011100, B00100010, B00000010, B00000100, B00001000, B00010000, B00111110, B00000000, 6,
  '3', B00111110, B00000100, B00001000, B00000100, B00000010, B00100010, B00011100, B00000000, 6,
  '4', B00000100, B00001100, B00010100, B00100100, B00111110, B00000100, B00000100, B00000000, 6,
  '5', B00111110, B00100000, B00111100, B00000010, B00000010, B00100010, B00011100, B00000000, 6,
  '6', B00001100, B00010000, B00100000, B00111100, B00100010, B00100010, B00011100, B00000000, 6,
  '7', B00111110, B00000010, B00000100, B00001000, B00010000, B00010000, B00010000, B00000000, 6,
  '8', B00011100, B00100010, B00100010, B00011100, B00100010, B00100010, B00011100, B00000000, 6,
  '9', B00011100, B00100010, B00100010, B00011110, B00000010, B00000100, B00011000, B00000000, 6,
  'A', B00011100, B00100010, B00100010, B00100010, B00111110, B00100010, B00100010, B00000000, 6,
  'B', B00111100, B00100010, B00100010, B00111100, B00100010, B00100010, B00111100, B00000000, 6,
  'C', B00011100, B00100010, B00100000, B00100000, B00100000, B00100010, B00011100, B00000000, 6,
  'D', B00111000, B00100100, B00100010, B00100010, B00100010, B00100100, B00111000, B00000000, 6,
  'E', B00111110, B00100000, B00100000, B00111100, B00100000, B00100000, B00111110, B00000000, 6,
  'G', B00011100, B00100010, B00100000, B00101110, B00100010, B00100010, B00011110, B00000000, 6,
  'I', B00001110, B00000100, B00000100, B00000100, B00000100, B00000100, B00001110, B00000000, 4,
  'L', B00100000, B00100000, B00100000, B00100000, B00100000, B00100000, B00111110, B00000000, 6,
  'M', B00100010, B00110110, B00101010, B00101010, B00100010, B00100010, B00100010, B00000000, 6,
  'N', B00100010, B00100010, B00110010, B00101010, B00100110, B00100010, B00100010, B00000000, 6,
  'O', B00011100, B00100010, B00100010, B00100010, B00100010, B00100010, B00011100, B00000000, 6,
  'R', B00111100, B00100010, B00100010, B00111100, B00101000, B00100100, B00100010, B00000000, 6,
  'T', B00111110, B00001000, B00001000, B00001000, B00001000, B00001000, B00001000, B00000000, 6,
  'V', B00100010, B00100010, B00100010, B00100010, B00100010, B00010100, B00001000, B00000000, 6,
  'Y', B00100010, B00100010, B00100010, B00010100, B00001000, B00001000, B00001000, B00000000, 6,
  NULL
};
LedControl g_lc = LedControl(10, 12, 11, 1);
String g_serial = "";
String g_message = " READY ";
int g_pos = 0;
unsigned long g_speed = 75;
unsigned long g_time = 0;

void setup() {
  Serial.begin(9600);
  g_lc.shutdown(0, false);
  g_lc.clearDisplay(0);
  g_lc.setIntensity(0, 1);
  g_lc.setLed(0, 0, 7, true);
}

void loop() {
  if (Serial.available()) {
    g_serial = Serial.readStringUntil('\n');
    if (g_serial.startsWith("m:")) {
      g_message = g_serial.substring(2);
      g_pos = 0;
    }
    if (g_serial.startsWith("i:")) {
      g_lc.setIntensity(0, g_serial.substring(2).toInt());
    }
    if (g_serial.startsWith("s:")) {
      g_speed = g_serial.substring(2).toInt();
    }
  }
  if (millis() < g_time) {
    return;
  }
  g_time = millis() + g_speed;

  int i, m, pos, j, k, o, row, mask, value, l;

  for (i = 0, m = g_message.length(), pos = 0; i < m; ++i) {
    for (j = 0; pgm_read_byte_near(g_chars + j); j += 10) {
      if (g_message[i] == pgm_read_byte_near(g_chars + j)) {
        for (k = 0, o = pgm_read_byte_near(g_chars + j + 9); k < o; ++k) {
          row = pos + k - g_pos;
          if ((row > -1) && (row < 8)) {
            mask = bit(o - k - 1);
            value = 0;
            for (l = 0; l < 8; ++l) {
              if (mask & pgm_read_byte_near(g_chars + l + j + 1)) {
                value +=  bit(l);
              }
            }
            g_lc.setRow(0, row, value);
          }
        }
        pos += o;
        break;
      }
    }
  }
  g_pos = ((g_pos + 8) >= pos) ? 0 : g_pos + 1;
}
