#include "Inkplate5.h"
Inkplate display(INKPLATE_1BIT);

#define BUFFER_SIZE 1000
char commandBuffer[BUFFER_SIZE + 1];
char strTemp[2001];
void setup() {
  display.begin();
  Serial.begin(115200);
  memset(commandBuffer, 0, BUFFER_SIZE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    while (Serial.available()) {
      for (int i = 0; i < (BUFFER_SIZE - 1); i++) {
        commandBuffer[i] = commandBuffer[i + 1];
      }
      commandBuffer[BUFFER_SIZE - 1] = Serial.read();
    }
  }
  char *s = NULL;
  char *e = NULL;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (commandBuffer[i] == '#' && s == NULL) s = &commandBuffer[i];
    if (commandBuffer[i] == '*' && e == NULL) e = &commandBuffer[i];
  }
  if (s != NULL && e != NULL) {
    if ((e - s) > 0) {
      int x, x1, x2, y, y1, y2, x3, y3, l, c, w, h, r, n;
      char b;
      char temp[150];
      switch (*(s + 1)) {
        case '?':
          Serial.print("OK");
          break;

        case '0':
          sscanf(s + 3, "%d,%d,%d", &x, &y, &c);
          //sprintf(temp, "display.drawPixel(%d, %d, %d)\n\r", x, y, c);
          //Serial.print(temp);
          display.drawPixel(x, y, c);
          break;

        case '1':
          sscanf(s + 3, "%d,%d,%d,%d,%d", &x1, &y1, &x2, &y2, &c);
          //sprintf(temp, "display.drawLine(%d, %d, %d, %d, %d)\n\r", x1, y1, x2, y2, c);
          //Serial.print(temp);
          display.drawLine(x1, y1, x2, y2, c);
          break;

        case '2':
          sscanf(s + 3, "%d,%d,%d,%d", &x, &y, &l, &c);
          //sprintf(temp, "display.drawFastVLine(%d, %d, %d, %d)\n\r", x, y, l, c);
          //Serial.print(temp);
          display.drawFastVLine(x, y, l, c);
          break;

        case '3':
          sscanf(s + 3, "%d,%d,%d,%d", &x, &y, &l, &c);
          //sprintf(temp, "display.drawFastHLine(%d, %d, %d, %d)\n\r", x, y, l, c);
          //Serial.print(temp);
          display.drawFastHLine(x, y, l, c);
          break;

        case '4':
          sscanf(s + 3, "%d,%d,%d,%d,%d", &x, &y, &w, &h, &c);
          //sprintf(temp, "display.drawRect(%d, %d, %d, %d, %d)\n\r", x, y, w, h, c);
          //Serial.print(temp);
          display.drawRect(x, y, w, h, c);
          break;

        case '5':
          sscanf(s + 3, "%d,%d,%d,%d", &x, &y, &r, &c);
          //sprintf(temp, "display.drawCircle(%d, %d, %d, %d)\n\r", x, y, r, c);
          //Serial.print(temp);
          display.drawCircle(x, y, r, c);
          break;

        case '6':
          sscanf(s + 3, "%d,%d,%d,%d,%d,%d,%d", &x1, &y1, &x2, &y2, &x3, &y3, &c);
          //sprintf(temp, "display.drawTriangle(%d, %d, %d, %d, %d, %d, %d)\n\r", x1, y1, x2, y2, x3, y3, c);
          //Serial.print(temp);
          display.drawTriangle(x1, y1, x2, y2, x3, y3, c);
          break;

        case '7':
          sscanf(s + 3, "%d,%d,%d,%d,%d,%d", &x, &y, &w, &h, &r, &c);
          //sprintf(temp, "display.drawRoundRect(%d, %d, %d, %d, %d, %d)\n\r", x, y, w, h, r, c);
          //Serial.print(temp);
          display.drawRoundRect(x, y, w, h, r, c);
          break;

        case '8':
          sscanf(s + 3, "%d,%d,%d,%d,%d", &x, &y, &w, &h, &c);
          //sprintf(temp, "display.fillRect(%d, %d, %d, %d, %d)\n\r", x, y, w, h, c);
          //Serial.print(temp);
          display.fillRect(x, y, w, h, c);
          break;

        case '9':
          sscanf(s + 3, "%d,%d,%d,%d", &x, &y, &r, &c);
          //sprintf(temp, "display.fillCircle(%d, %d, %d, %d)\n\r", x, y, r, c);
          //Serial.print(temp);
          display.fillCircle(x, y, r, c);
          break;

        case 'A':
          sscanf(s + 3, "%d,%d,%d,%d,%d,%d,%d", &x1, &y1, &x2, &y2, &x3, &y3, &c);
          //sprintf(temp, "display.fillTriangle(%d, %d, %d, %d, %d, %d, %d)\n\r", x1, y1, x2, y2, x3, y3, c);
          //Serial.print(temp);
          display.fillTriangle(x1, y1, x2, y2, x3, y3, c);
          break;

        case 'B':
          sscanf(s + 3, "%d,%d,%d,%d,%d,%d", &x, &y, &w, &h, &r, &c);
          //sprintf(temp, "display.fillRoundRect(%d, %d, %d, %d, %d, %d)\n\r", x, y, w, h, r, c);
          //Serial.print(temp);
          display.fillRoundRect(x, y, w, h, r, c);
          break;

        case 'C':
          sscanf(s + 3, "\"%2000[^\"]\"", strTemp);
          n = strlen(strTemp);
          for (int i = 0; i < n; i++) {
            strTemp[i] = toupper(strTemp[i]);
          }
          for (int i = 0; i < n; i += 2) {
            strTemp[i / 2] = (hexToChar(strTemp[i]) << 4) | (hexToChar(strTemp[i + 1]) & 0x0F);
          }
          strTemp[n / 2] = 0;
          //Serial.print("display.print(\"");
          //Serial.print(strTemp);
          //Serial.println("\");");
          display.print(strTemp);
          break;

        case 'D':
          sscanf(s + 3, "%d", &c);
          //sprintf(temp, "display.setTextSize(%d)\n", c);
          //Serial.print(temp);
          display.setTextSize(c);
          break;

        case 'E':
          sscanf(s + 3, "%d,%d", &x, &y);
          //sprintf(temp, "display.setCursor(%d, %d)\n", x, y);
          //Serial.print(temp);
          display.setCursor(x, y);
          break;

        case 'F':
          sscanf(s + 3, "%c", &b);
          //sprintf(temp, "display.setTextWrap(%s)\n", b == 'T' ? "True" : "False");
          //Serial.print(temp);
          if (b == 'T') display.setTextWrap(true);
          if (b == 'F') display.setTextWrap(false);
          break;

        case 'G':
          sscanf(s + 3, "%d", &c);
          c &= 3;
          //sprintf(temp, "display.setRotation(%d)\n", c);
          //Serial.print(temp);
          display.setRotation(c);
          break;

        case 'H':
          sscanf(s + 3, "%d,%d,\"%149[^\"]\"", &x, &y, strTemp);
          n = strlen(strTemp);
          for (int i = 0; i < n; i++) {
            strTemp[i] = toupper(strTemp[i]);
          }
          for (int i = 0; i < n; i += 2) {
            strTemp[i / 2] = (hexToChar(strTemp[i]) << 4) | (hexToChar(strTemp[i + 1]) & 0x0F);
          }
          strTemp[n / 2] = 0;
          r = display.sdCardInit();
          if (r) {
            r = display.drawBitmapFromSD(strTemp, x, y);
            Serial.print("#H(");
            Serial.print(r, DEC);
            Serial.println(")*");
            Serial.flush();
            //sprintf(temp, "display.drawBitmap(%d, %d, %s)\n", x, y, strTemp);
            //Serial.print(temp);
          } else {
            Serial.println("#H(-1)*");
            Serial.flush();
          }
          break;

        case 'I':
          sscanf(s + 3, "%d", &c);
          //sprintf(temp, "display.setDisplayMode(%s)\n", c == 0 ? "INKPLATE_1BIT" : "INKPLATE_3BIT");
          //Serial.print(temp);
          if (c == INKPLATE_1BIT) display.selectDisplayMode(INKPLATE_1BIT);
          if (c == INKPLATE_3BIT) display.selectDisplayMode(INKPLATE_3BIT);
          break;

        case 'J':
          sscanf(s + 3, "%c", &b);
          if (b == '?') {
            //if (0 == 0) {
            //  Serial.println("#J(0)*");
            //} else {
            //  Serial.println("#J(1)*");
            //}
            if (display.getDisplayMode() == INKPLATE_1BIT) {
              Serial.println("#J(0)*");
              Serial.flush();
            }
            if (display.getDisplayMode() == INKPLATE_3BIT) {
              Serial.println("#J(1)*");
              Serial.flush();
            }
          }
          break;

        case 'K':
          sscanf(s + 3, "%c", &b);
          if (b == '1') {
            //Serial.print("display.clearDisplay();\n");
            display.clearDisplay();
          }
          break;

        case 'L':
          sscanf(s + 3, "%c", &b);
          if (b == '1') {
            //Serial.print("display.display();\n");
            display.display();
          }
          break;

        case 'M':
          sscanf(s + 3, "%d,%d,%d", &y1, &x2, &y2);
          //sprintf(temp, "display.partialUpdate(%d, %d, %d);\n", y1, x2, y2);
          //Serial.print(temp);
          display.partialUpdate();
          break;

        case 'N':
          sscanf(s + 3, "%c", &b);
          if (b == '?') {
            Serial.print("#N(");
            Serial.print(display.readTemperature(), DEC);
            //Serial.print(23, DEC);
            Serial.println(")*");
            Serial.flush();
          }
          break;

        case 'O':
          sscanf(s + 3, "%d", &c);
          if (c >= 0 && c <= 2) {
            Serial.print("#O(");
            Serial.print(display.readTouchpad(c), DEC);
            //Serial.print(0, DEC);
            Serial.println(")*");
            Serial.flush();
          }
          break;

        case 'P':
          sscanf(s + 3, "%c", &b);
          if (b == '?') {
            Serial.print("#P(");
            Serial.print(display.readBattery(), 2);
            //Serial.print(3.54, 2);
            Serial.println(")*");
            Serial.flush();
          }
          break;

        case 'Q':
          sscanf(s + 3, "%d", &c);
          c &= 1;
          //if (c == 0) Serial.print("display.einkOff();\n");
          //if (c == 1) Serial.print("display.einkOn();\n");
          if (c == 0) display.einkOff();
          if (c == 1) display.einkOn();
          break;

        case 'R':
          sscanf(s + 3, "%c", &b);
          if (b == '?') {
            Serial.print("#R(");
            Serial.print(display.getPanelState(), DEC);
            //Serial.print(1, DEC);
            Serial.println(")*");
            Serial.flush();
          }
          break;
      }
      *s = 0;
      *e = 0;
    }
  }
}

int hexToChar(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;
  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  return -1;
}
