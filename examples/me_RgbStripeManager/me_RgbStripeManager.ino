// [Demo/test] RGB LED stripe serial interface

/*
  Author: Martin Eden
  Last mod.: 2024-09-12
*/

#include <me_BaseTypes.h>
#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>

#include <me_RgbStripeManager.h>

me_RgbStripeManager::TRgbStripeManager StripeManager;

void setup()
{
  InstallStandardStreams();

  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);

  Serial.setTimeout(15);

  printf("[me_RgbStripeManager] Hello there!\n");
  RunTest();
  printf("[me_RgbStripeManager] Done.\n");
}

void loop()
{
}

// --

// Blink test pattern several times
void RunTest()
{
  StripeManager.Init(A0, 60);

  for (TUint_1 Iteration = 1; Iteration < 5; ++Iteration)
  {
    StripeManager.Test();
    delay(1000);
    StripeManager.Reset();
    delay(1000);
  }
  StripeManager.Test();
}

/*
  2024-09-12
*/
