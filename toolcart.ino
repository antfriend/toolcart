#define NUM_SWITCHES 9  // Number of switches
const int switchPins[NUM_SWITCHES] = {D1, D7};  // GPIO pins for switches
// const int LED_BUILTIN = 13;

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // Set all switch pins as INPUT_PULLUP
    for (int i = 0; i < NUM_SWITCHES; i++) {
        pinMode(switchPins[i], INPUT_PULLUP);
    }
}

void loop() {
    Serial.print("Switch: ");
    int LED_on = LOW;
    for (int i = 0; i < NUM_SWITCHES; i++) {
        int switchState = digitalRead(switchPins[i]);  // Reads HIGH (unpressed) or LOW (pressed)
        if(switchState == LOW){
          LED_on = HIGH;
        }
        Serial.print(switchPins[i]);
        Serial.print(switchState == LOW ? " Press " : "  ");
    }
    digitalWrite(LED_BUILTIN, LED_on);
    Serial.println();
    delay(100);  // Small debounce delay
    digitalWrite(LED_BUILTIN, HIGH);
}
