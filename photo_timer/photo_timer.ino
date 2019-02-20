/* PhotoTimer for analog photography */

bool isDebug = false;

// ##### SevSeg
#include "SevSeg.h"
bool isError = false;


// ##### Timer
int buttonPins[4][2] = {{A0, 0}, {A1, 0}, {A2, 0}, {A3, 0}};
bool isLampOn = false;
bool isTimerRunning = false;
int lightTime = 0;
int btnReactionTime = 500;

long unsigned realTime;



void setup() {
  setupTimer();
  setupSevSeg();
}

void loop() {
  loopTimer();
  loopSevSeg();

}
