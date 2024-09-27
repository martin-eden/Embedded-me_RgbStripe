// [Demo/test] RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2024-09-27
*/

#include <me_BaseTypes.h>
#include <me_UartSpeeds.h>
#include <me_InstallStandardStreams.h>

#include <me_RgbStripe.h>

me_RgbStripe::TRgbStripe Stripe;

void setup()
{
  InstallStandardStreams();

  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);

  Serial.setTimeout(15);

  printf("[me_RgbStripe] Hello there!\n");
  RunTest();
  printf("[me_RgbStripe] Done.\n");
}

void loop()
{
}

// --

// Blink test pattern several times
void RunTest()
{
  TUint_1 OutputPin = 2;
  TUint_2 StripeLength = 60;

  printf("Output pin is (%u).\n", OutputPin);
  printf("Stripe length is (%u).\n", StripeLength);

  TBool InitIsDone = Stripe.Init(OutputPin, StripeLength);
  if (!InitIsDone)
  {
    printf("Initialization failed. No memory for that stripe length?\n");
    return;
  }

  printf("We will display test pattern on LED stripe for several seconds.\n");

  for (TUint_1 Iteration = 1; Iteration < 5; ++Iteration)
  {
    DisplayTestPattern();
    delay(1000);

    Stripe.Reset();
    Stripe.Display();
    delay(1000);
  }
  DisplayTestPattern();
}

// Display ad hoc pattern to visually determine borders of stripe
void DisplayTestPattern()
{
  Stripe.Reset();

  // Light up border and middle pixels
  {
    me_RgbStripe::TColor Blue = { .Red = 0, .Green = 0, .Blue = 0xFF };
    me_RgbStripe::TColor Green = { .Red = 0, .Green = 0xFF, .Blue = 0 };

    TUint_2 StripeLength = Stripe.GetLength();

    Stripe.SetPixel(0, Blue);
    Stripe.SetPixel(StripeLength / 2, Blue);
    Stripe.SetPixel(StripeLength / 2 + 1, Green);
    Stripe.SetPixel(StripeLength - 1, Blue);
  }

  Stripe.Display();
}

/*
  2024-09-12
  2024-09-15
*/
