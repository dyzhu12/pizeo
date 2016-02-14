
/**
 * Piezo Sound
 */
int speakerPin = 9;
int length = 15;
char notes[] = "ccggaagffeeddc";
int beats[] = {1,1,1,1,1,1,2,1,1,1,1,1,1,2,4};
int tempo = 300;

/**
 * Piezo Vibration
 */
int sensePin = 1;
int threshold = 1000;


int groundPin = 0;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i+= tone*2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c','d','e','f','g','a','b','c'};
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Pizeo");
  pinMode(groundPin, OUTPUT);
  digitalWrite(groundPin, LOW);
  pinMode(speakerPin, OUTPUT);
}

bool stopMusic = false;
bool holdingDown = false;
int timer = 0;
void loop() {
  int reading = analogRead(sensePin);
  if (reading > threshold) {
    holdingDown = true;
  } else if (!stopMusic) {
    digitalWrite(speakerPin, HIGH);
  }

  if (holdingDown) {
    timer++;
  }
  if (timer > 500) {
    stopMusic = true;
    digitalWrite(speakerPin, LOW);
  }
}
