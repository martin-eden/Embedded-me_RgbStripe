// [Demo/test] RGB LED stripe serial interface

/*
  Author: Martin Eden
  Last mod.: 2024-09-15
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
  TUint_1 OutputPin = A0;
  TUint_2 StripeLength = 60;

  printf("Output pin is (%u).\n", OutputPin);
  printf("Stripe length is (%u).\n", StripeLength);

  TBool InitIsDone = StripeManager.Init(OutputPin, StripeLength);
  if (!InitIsDone)
  {
    printf("Initialization failed. No memory for that stripe length?\n");
    return;
  }

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
  2024-09-15
*/
