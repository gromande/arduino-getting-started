#include <Bounce2.h>

const unsigned int LED_BIT0 = 12;
const unsigned int LED_BIT1 = 11;
const unsigned int LED_BIT2 = 10;
const unsigned int ROLL_BUTTON = 7;
const unsigned int GUESS_BUTTON = 5;
const unsigned int BAUD_RATE = 9600;
const unsigned int DEBOUNCE_DELAY = 20;

Bounce roll_bouncer = Bounce();
Bounce guess_bouncer = Bounce();

int guess_counter = 0;

void setup() {
  pinMode(LED_BIT0, OUTPUT);
  pinMode(LED_BIT1, OUTPUT);
  pinMode(LED_BIT2, OUTPUT);
  pinMode(ROLL_BUTTON, INPUT);
  pinMode(GUESS_BUTTON, INPUT);
  randomSeed(analogRead(A0));
  roll_bouncer.attach(ROLL_BUTTON);
  roll_bouncer.interval(DEBOUNCE_DELAY);
  guess_bouncer.attach(GUESS_BUTTON);
  guess_bouncer.interval(DEBOUNCE_DELAY);
  Serial.begin(BAUD_RATE);
}

void loop() {
  handle_guess_button();
  handle_roll_button();
}

void handle_guess_button() {
  if (guess_bouncer.update() && guess_bouncer.read() == HIGH) {
    Serial.println("Guess button pressed");
    guess_counter = (guess_counter % 6) + 1;
  }
}

void handle_roll_button() {
  if (roll_bouncer.update() && roll_bouncer.read() == HIGH) {
    int result = random(1, 7);
    output_result(result);
    Serial.println("Roll button pressed");
    Serial.print("Guess: ");
    Serial.println(guess_counter);
    Serial.print("Result: ");
    Serial.println(result);
    if (guess_counter == result) {
      Serial.println("You win!");
      hooray();
    } else {
      Serial.println("You lose!");
    }
    delay(2000);
    guess_counter = 0;
  }
}

void output_result(const long result) {
  digitalWrite(LED_BIT0, result & B001);
  digitalWrite(LED_BIT1, result & B010);
  digitalWrite(LED_BIT2, result & B100);
}

void hooray() {
  for (unsigned int i = 0; i < 3; i++) {
    output_result(7);
    delay(500);
    output_result(0);
    delay(500);
  }
}

