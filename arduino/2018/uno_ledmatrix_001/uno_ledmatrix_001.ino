#include <LedControl.h>

const uint64_t IMAGES[] = {
  0x6666667e66663c00,
  0x3e66663e66663e00,
  0x3c66060606663c00,
  0x3e66666666663e00,
  0x7e06063e06067e00,
  0x0606063e06067e00,
  0x3c66760606663c00,
  0x6666667e66666600,
  0x3c18181818183c00,
  0x1c36363030307800,
  0x66361e0e1e366600,
  0x7e06060606060600,
  0xc6c6c6d6feeec600,
  0xc6c6e6f6decec600,
  0x3c66666666663c00,
  0x06063e6666663e00,
  0x603c766666663c00,
  0x66361e3e66663e00,
  0x3c66603c06663c00,
  0x18181818185a7e00,
  0x7c66666666666600,
  0x183c666666666600,
  0xc6eefed6c6c6c600,
  0xc6c66c386cc6c600,
  0x1818183c66666600,
  0x7e060c1830607e00,
  0x0000000000000000,
  0x7c667c603c000000,
  0x3e66663e06060600,
  0x3c6606663c000000,
  0x7c66667c60606000,
  0x3c067e663c000000,
  0x0c0c3e0c0c6c3800,
  0x3c607c66667c0000,
  0x6666663e06060600,
  0x3c18181800180000,
  0x1c36363030003000,
  0x66361e3666060600,
  0x1818181818181800,
  0xd6d6feeec6000000,
  0x6666667e3e000000,
  0x3c6666663c000000,
  0x06063e66663e0000,
  0xf0b03c36363c0000,
  0x060666663e000000,
  0x3e403c027c000000,
  0x1818187e18180000,
  0x7c66666666000000,
  0x183c666600000000,
  0x7cd6d6d6c6000000,
  0x663c183c66000000,
  0x3c607c6666000000,
  0x3c0c18303c000000,
  0x3c66666e76663c00,
  0x7e1818181c181800,
  0x7e060c3060663c00,
  0x3c66603860663c00,
  0x30307e3234383000,
  0x3c6660603e067e00,
  0x3c66663e06663c00,
  0x1818183030667e00,
  0x3c66663c66663c00,
  0x3c66607c66663c00
};
const int IMAGES_LEN = sizeof(IMAGES) / 8;
LedControl g_ledControl = LedControl(12, 11, 10, 1);
int g_pos = 0;
int g_min = 0;
String g_text = " Sintiendo a la tierra con ARDUINO ";
bool g_intense = false;
bool g_speed = false;
String g_newText = g_text;
bool g_newIntense = g_intense;
bool g_newSpeed = g_speed;

String fixedString(String value) {
  int separator = value.indexOf(":");

  if (separator < 1) {
    return "";
  }

  int size = value.substring(0, separator).toInt();
  String string = value.substring(separator + 1);

  if ((String("") + size + ":" + string) == value) {
    return string;
  }
  return "";
}

void displayImage(uint64_t image, int pos) {
  if (pos <= -8) {
    return;
  }
  if (pos >= 8) {
    return;
  }
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;

    for (int j = 0; j < 8; j++) {
      if ((j + pos) < 0) {
        continue;
      }
      if ((j + pos) > 8) {
        continue;
      }
      g_ledControl.setLed(0, i, j + pos, bitRead(row, j));
    }
  }
}

void displayString(String value, int pos) {
  int i = 0;
  int j = 0;

  while (value[i]) {
    if ((value[i] >= 'A') && (value[i] <= 'Z')) {
      j = value[i] - 'A';
    } else if ((value[i] >= 'a') && (value[i] <= 'z')) {
      j = value[i] - 'a' + 27;
    } else if ((value[i] >= '0') && (value[i] <= '9')) {
      j = value[i] - '0' + 53;
    } else {
      j = 26;
    }
    displayImage(IMAGES[j], pos);
    pos += 8;
    ++i;
  }
}

void updateLimit() {
  g_min = -8 * (g_text.length() - 1);
}

void setup() {
  g_ledControl.shutdown(0, false);
  g_ledControl.setIntensity(0, 10);
  g_ledControl.clearDisplay(0);
  updateLimit();
  g_pos = g_min - 1;
}

void loop() {
  if (g_pos < g_min) {
    g_intense = g_newIntense;
    g_speed = g_newSpeed;
    g_text = g_newText;
    g_ledControl.setIntensity(0, g_intense ? 10 : 2);
    updateLimit();
    g_pos = 0;
  }
  displayString(g_text, g_pos--);
  delay(g_speed ? 50 : 100);
}
