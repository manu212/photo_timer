SevSeg sevseg; //Instantiate a seven segment controller object

String errMsg = "";

void setupSevSeg() {
  byte numDigits = 4; //Hier wird die Anzahl der Ziffern angegeben
  byte digitPins[] = {2, 3, 4, 5}; //Die Pins zu den Ziffern werden festgelegt
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; //Die Pins zu den //Segmenten werden festgelegt
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(10);
}

//countdown
static int deciSeconds = 0;
static unsigned long timer = 0;

unsigned long timerMsg = 0;
int duration = 1000;

void loopSevSeg() {
  if (isTimerRunning) {
    CountDown();
    digitalWrite(A4, HIGH); // turn exposure lamp on
  } else {
    if (isError == false) {
      //sevseg.blank();
      SetTime();
      timer = millis();
      deciSeconds = 0;
    }
    if (isLampOn == false) {
      digitalWrite(A4, LOW);
    }
    deciSeconds = 0;
  }
  if (isError == true) {
    ShowErrMsg();
  }
  sevseg.refreshDisplay(); // Must run repeatedly
}


void SetErrMsg(String msg) {
  isError = true;
  errMsg = msg;
  timerMsg = millis();
}


void ShowErrMsg() {
  char chars[4];
  errMsg.toCharArray(chars, 4);
  sevseg.setChars(chars);
  if (millis() >= timerMsg + duration) {
    isError = false;
  }
}


void CountDown() {
  if (millis() >= timer) {
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    timer += 100;
    sevseg.setNumber(lightTime - deciSeconds, 1);
    if ( deciSeconds >= lightTime ) {
      deciSeconds = 0;
      isTimerRunning = false;
      Serial.print("realTime: ");
      Serial.println(millis() - realTime);
    }
  }
}

void SetTime() {
  sevseg.setNumber(lightTime, 1);
}
