const unsigned int LED_BIT0 = 12;
const unsigned int LED_BIT1 = 11;
const unsigned int LED_BIT2 = 10;
const unsigned int ROLL_BUTTON = 7;
const unsigned int GUESS_BUTTON = 5;
const unsigned int BAUD_RATE = 9600;

int curr_roll_value = LOW;
int old_roll_value = LOW;
int curr_guess_value = LOW;
int old_guess_value = LOW;
long guess_counter = 0;

void setup() {
  pinMode(LED_BIT0, OUTPUT);
  pinMode(LED_BIT1, OUTPUT);
  pinMode(LED_BIT2, OUTPUT);
  pinMode(ROLL_BUTTON, INPUT);
  pinMode(GUESS_BUTTON, INPUT);
  randomSeed(analogRead(A0));
  Serial.begin(BAUD_RATE);
}

void loop() {
  curr_guess_value = digitalRead(GUESS_BUTTON);
  if (curr_guess_value != old_guess_value && curr_guess_value == HIGH) {
    Serial.println("Guess button pressed");
    guess_counter++;
    delay(50);
  }
  old_guess_value = curr_guess_value;
  
  curr_roll_value = digitalRead(ROLL_BUTTON);
  if (curr_roll_value != old_roll_value && curr_roll_value == HIGH) {
    long result = random(1, 7);
    Serial.println("Roll button pressed");
    Serial.print("Guess: ");
    Serial.println(guess_counter);
    Serial.print("Result: ");
    Serial.println(result);
    if (guess_counter == result) {
      output_result(result);
    } else {
      output_result(0l);
    }
    guess_counter = 0l;
    delay(50);
  }
  old_roll_value = curr_roll_value;
}

void output_result(const long result) {
  digitalWrite(LED_BIT0, result & B001);
  digitalWrite(LED_BIT1, result & B010);
  digitalWrite(LED_BIT2, result & B100);
}
