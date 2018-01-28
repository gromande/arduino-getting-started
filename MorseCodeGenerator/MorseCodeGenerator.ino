#include <telegraph.h>

const unsigned int OUTPUT_PIN = 13;
const unsigned int DIT_LENGTH = 400;
const unsigned MAX_MESSAGE_LENGTH = 128;
const unsigned BAUD_RATE = 9600;

const int LINE_FEED = 13;
char message_text[MAX_MESSAGE_LENGTH];
int index = 0;

Telegraph telegraph(OUTPUT_PIN, DIT_LENGTH);

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  if (Serial.available() > 0) {
    int current_char = Serial.read();
    if (current_char == LINE_FEED || index == MAX_MESSAGE_LENGTH - 1) {
      message_text[index] = 0;
      index = 0;
      telegraph.send_message(message_text);
    } else {
      message_text[index++] = current_char;
    }
  }

}
