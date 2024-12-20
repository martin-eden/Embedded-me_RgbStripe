// [Demo/test] RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2024-12-20
*/

#include <me_RgbStripe.h>

#include <me_BaseTypes.h>
#include <me_Uart.h>
#include <me_Console.h>

me_RgbStripe::TRgbStripe Stripe;

void setup()
{
  me_Uart::Init(me_Uart::Speed_115k_Bps);

  Console.Print("[me_RgbStripe] Hello there!");
  RunTest();
  Console.Print("[me_RgbStripe] Done.");
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

  Console.Write("Output pin:");
  Console.Print(OutputPin);
  Console.EndLine();

  Console.Write("Stripe length:");
  Console.Print(StripeLength);
  Console.EndLine();

  TBool InitIsDone = Stripe.Init(OutputPin, StripeLength);
  if (!InitIsDone)
  {
    Console.Print("Initialization failed. No memory for that stripe length?");
    return;
  }

  Console.Print("We will blink test pattern on LED stripe for several seconds.");

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
  2024-12-20
*/
