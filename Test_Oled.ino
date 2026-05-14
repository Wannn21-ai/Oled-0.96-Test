#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int p1x = 10;
int p2x = 100;

int hp1 = 20;
int hp2 = 20;

bool hitEffect = false;

// ================= DRAW CHARACTER =================
void drawPlayer(int x, int y, bool punch) {

  // kepala
  display.fillCircle(x, y, 3, WHITE);

  // badan
  display.drawLine(x, y + 3, x, y + 12, WHITE);

  // kaki
  display.drawLine(x, y + 12, x - 3, y + 16, WHITE);
  display.drawLine(x, y + 12, x + 3, y + 16, WHITE);

  // tangan
  if (punch) {
    display.drawLine(x, y + 6, x + 6, y + 4, WHITE);
    display.drawLine(x, y + 6, x - 4, y + 6, WHITE);
  }
  else {
    display.drawLine(x, y + 6, x + 4, y + 8, WHITE);
    display.drawLine(x, y + 6, x - 4, y + 8, WHITE);
  }
}

// ================= HIT EFFECT =================
void drawHit(int x, int y) {
  display.setTextSize(1);
  display.setCursor(x, y);
  display.print("POW!");
}

void setup() {

  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED gagal");
    while (true);
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  // ================= MASUK ARENA =================
  for (int i = 0; i < 30; i++) {

    display.clearDisplay();

    p1x++;
    p2x--;

    drawPlayer(p1x, 30, false);
    drawPlayer(p2x, 30, false);

    display.setTextSize(1);
    display.setCursor(35, 0);
    display.print("PIXEL FIGHT");

    display.display();
    delay(40);
  }

  // ================= FIGHT =================
  for (int r = 0; r < 8; r++) {

    // PLAYER 1 HIT
    display.clearDisplay();

    drawPlayer(p1x, 30, true);
    drawPlayer(p2x, 30, false);

    drawHit(58, 25);

    hp2 -= 2;

    // HP BAR
    display.drawRect(5, 5, 40, 5, WHITE);
    display.fillRect(5, 5, hp1 * 2, 5, WHITE);

    display.drawRect(83, 5, 40, 5, WHITE);
    display.fillRect(83 + (40 - hp2 * 2), 5, hp2 * 2, 5, WHITE);

    display.display();
    delay(250);

    // PLAYER 2 HIT
    display.clearDisplay();

    drawPlayer(p1x, 30, false);
    drawPlayer(p2x, 30, true);

    drawHit(50, 25);

    hp1 -= 2;

    // HP BAR
    display.drawRect(5, 5, 40, 5, WHITE);
    display.fillRect(5, 5, hp1 * 2, 5, WHITE);

    display.drawRect(83, 5, 40, 5, WHITE);
    display.fillRect(83 + (40 - hp2 * 2), 5, hp2 * 2, 5, WHITE);

    display.display();
    delay(250);
  }

  // ================= KO =================
  display.clearDisplay();

  display.setTextSize(3);
  display.setCursor(20, 20);
  display.print("K.O!");

  display.display();

  delay(3000);

  // RESET
  p1x = 10;
  p2x = 100;

  hp1 = 20;
  hp2 = 20;
}
