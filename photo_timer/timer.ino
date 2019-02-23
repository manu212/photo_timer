
int onOffPinOldVal = 0;

bool keyPressed = false;
bool keyPressedOld = false;
unsigned long keyPressedTime = 0;

int deciScnds = 10;

void setupTimer() {
  Serial.begin(9600); //also affects brightness, sine brightness is only turn on/off leds
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i][0], INPUT_PULLUP);
  }
  pinMode(A4, OUTPUT);
  digitalWrite(A4, LOW);
}


void loopTimer() {
  onOffPinOldVal = buttonPins[0][1];

  if (isTimerRunning == false) {
    ReadValues(); // get values from input
  }

  ControlLamp(); // usage of control lamp

  if ( (buttonPins[2][1] < 100) && (buttonPins[3][1] < 100) ) { // only press one setlight time button at once
    SetErrMsg("err");
  } else {
    SetLightTime();
  }

  if ( (buttonPins[1][1] < 100) && (isError == false) && (isLampOn == false) && (isTimerRunning == false) ) { // check conditions if we are allowed to expose
    if (lightTime > 0) {
      isTimerRunning = true; // expose!
      Serial.print("lightTime: ");
      Serial.print(lightTime);
      Serial.println("00");
      realTime = millis();
    } else {
      SetErrMsg("err");
    }
  }
}


void ReadValues() {
  for (int i = 0; i < 4; i++) {
    buttonPins[i][1] = analogRead(buttonPins[i][0]);
    if (buttonPins[i][1] < 100) {
      if (isDebug == true) {
        Serial.print("button [A");
        Serial.print(i);
        Serial.print("|");
        Serial.print(buttonPins[i][1]);
        Serial.println("]");
      }
    }
  }
}


void SetLightTime() {
  keyPressedOld = keyPressed;
  if  (lightTime < 0) {
    lightTime = 0;
  }

  if (keyPressed == false) {
    keyPressedTime = millis();
  } else {
    if (isDebug == true) {
      Serial.print("buttonPins[2][1]: ");
      Serial.println(buttonPins[2][1]);
      Serial.print("buttonPins[3][1]: ");
      Serial.println(buttonPins[3][1]);
    }
  }
  if ( (isTimerRunning == false) && (isError == false) ) {
    if ( (buttonPins[2][1] < 100) || (buttonPins[3][1] < 100) ) {
      keyPressed = true;
    } else {
      keyPressed = false;
    }
    if ( keyPressed && (keyPressedTime + btnReactionTime < millis()) ) { // count keypress via long press **
      if (buttonPins[2][1] < 100) {
        lightTime -= deciScnds;
      } else if (buttonPins[3][1] < 100) {
        lightTime += deciScnds;
      }
    }

    if ( (keyPressed != keyPressedOld) || ((millis() > keyPressedTime + btnReactionTime)) ) { //** automatically trigger keypress after btnReactionTime
      if (isDebug == true) {
        Serial.print("kreyPressed: ");
        Serial.println(keyPressed);
      }
      keyPressedTime = millis();
    }
  }
}


void ControlLamp() {
  if ( (isTimerRunning == false) && (onOffPinOldVal > 100 ) && (buttonPins[0][1] < 100) && (isError == false) ) {
    isLampOn = !isLampOn;

    if (isLampOn) {
      digitalWrite(A4, HIGH);
    } else {
      digitalWrite(A4, LOW);
    }
  }
  if ( (buttonPins[1][1] < 100) && (isError == false) && (isLampOn == true)) {
    SetErrMsg("err");
  }
}
