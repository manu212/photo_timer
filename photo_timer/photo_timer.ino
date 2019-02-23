/* PhotoTimer for analog photography */

bool isDebug = false;

// ##### SevSeg
#include "SevSeg.h"
bool isError = false;


// ##### Timer
int buttonPins[4][3] = {{A0, 0}, {A1, 0}, {A2, 0}, {A3, 0}};
bool isLampOn = false;
bool isTimerRunning = false;
int lightTime = 0;
int btnReactionTimeLong = 500;
int btnReactionTimeShort = 100;

long unsigned realTime;



void setup() {
  setupTimer();
  setupSevSeg();
}

void loop() {
  loopTimer();
  loopSevSeg();

}
