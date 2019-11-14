#define LEN(x) (sizeof(x)/sizeof(*x))

#define FORWARD 1
#define BACKWARD -1

// YELLOW: 4; ORANGE: 5; BLACK: 6; BROWN: 7;
const int motorPins[] = {7, 6, 5, 4};

/* 
 * As far as I can make out this is how to move the motor 
 * counter-clockwise. Clockwise is when you approach it from 
 * the back.
 * 
 * For the purpose of this exercise the following wire-bit 
 * mapping applies:
 *   0 1 2 3
 *   Y O B R
 */
const int motorSequence[] = {1, 5, 4, 6, 2, 10, 8, 9};
const int onOffPin = 8;
const int diagnosticLedPin = 13;
const int potentiometerInput = 5;
const int piezoPin = 3;

const int musicalNotes[] = { /*0: c*/ 1915, /*1: d*/ 1700, /*2: e*/ 1519, /*3: f*/ 1432, /*4: g*/ 1275, /*5: a*/ 1136, /*6: h*/ 1014, /*7: C*/ 956 };


int currentPosition = 0;
int expectedPosition = 0;
int currentMotor = 0;
int positionAchieved = false;

void setup() {
  for (int i = 0, l = LEN(motorPins); i < l; i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);
  }
  
  pinMode(onOffPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  
  pinMode(diagnosticLedPin, OUTPUT);
  digitalWrite(diagnosticLedPin, HIGH); 
  delay(2000);
  digitalWrite(diagnosticLedPin, LOW);
  delay(500); 
}

void loop() {
  if (digitalRead(onOffPin) == LOW) {
    digitalWrite(diagnosticLedPin, LOW);
  } else {
    digitalWrite(diagnosticLedPin, HIGH);
    runMotor();
  }  
  delay(50);
}

void runMotor() {
  expectedPosition = readPotentiometer();
  if (expectedPosition > currentPosition) {
    currentPosition++;
    move(BACKWARD);
    sound();
  } else if (expectedPosition < currentPosition) {
    currentPosition--;
    move(FORWARD);
    sound();
  } 
}

void sound() {
  if (expectedPosition == currentPosition) {
    int beat = 5;
    //play(0, beat);
    //play(2, beat);
    play(4, beat);
    play(7, beat);
  }
}

void move(int d) {
  // Possibly a micro step.
  rotate(d);
  // Allow the motor to get to grips with reality.
  delay(5);
  // Large step.
  rotate(d);
}

void rotate(int d) {
  int oldBits[4], newBits[4];
  convertToBits(motorSequence[currentMotor], oldBits, 4);
  currentMotor = (currentMotor + d) % (LEN(motorSequence));
  convertToBits(motorSequence[currentMotor], newBits, 4);
  
  for (int i = 0, l = LEN(motorPins); i < l; i++) {
    if (oldBits[i] != newBits[i]) {
      digitalWrite(motorPins[i], newBits[i]);
    }
  }
}

int readPotentiometer() {
  // Read value between 0 and 5V as a number between 0 and 1023.
  int analog = analogRead(potentiometerInput);
  // 360 degrees should be 48 steps of the motor (7.5 degrees each).
  return map(analog, 0, 1023, 0, 48);
}

void convertToBits(int number, int bits[], int length) {
  for (int i = 0; i < length; i++) {
    bits[i] = number % 2;
    number = number >> 1;
  }  
}

void play(int note /* 0 - 8 */, int duration) {
  for (long i = 0; i < duration * 1000L; i += note * 2) {
    digitalWrite(piezoPin, HIGH);
    delayMicroseconds(note);
    digitalWrite(piezoPin, LOW);
    delayMicroseconds(note);
  }
}