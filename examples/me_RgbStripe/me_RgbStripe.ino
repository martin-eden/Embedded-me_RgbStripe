// [Demo/test] RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2026-01-10
*/

#include <me_RgbStripe.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_Delays.h>

me_RgbStripe::TRgbStripe Stripe;

// Display ad hoc pattern to visually determine borders of stripe
void DisplayTestPattern()
{
  Stripe.Clear();

  // Light up border and middle pixels
  {
    me_RgbStripe::TColor Blue = { .Red = 0, .Green = 0, .Blue = 0xFF };
    me_RgbStripe::TColor Green = { .Red = 0, .Green = 0xFF, .Blue = 0 };

    TUint_2 StripeLength = Stripe.GetLength();

    Stripe.SetPixel(1, Blue);
    Stripe.SetPixel(StripeLength / 2, Blue);
    Stripe.SetPixel(StripeLength / 2 + 1, Green);
    Stripe.SetPixel(StripeLength, Blue);
  }

  Stripe.Display();
}

// Blink test pattern several times
void RunTest()
{
  const TUint_1 OutputPin = 2;
  const TUint_2 StripeLength = 60;
  const TUint_2 DataMemSize = StripeLength * sizeof(me_RgbStripe::TColor);

  TUint_1 DataMem[DataMemSize];
  const TAddressSegment DataSeg = M_AsAddrSeg(DataMem);

  Console.Write("Output pin:");
  Console.Print(OutputPin);
  Console.EndLine();

  Console.Write("Stripe length:");
  Console.Print(StripeLength);
  Console.EndLine();

  Stripe.Init(OutputPin, DataSeg);

  Console.Print("We will blink test pattern on LED stripe for several seconds.");

  for (TUint_1 Iteration = 1; Iteration < 5; ++Iteration)
  {
    DisplayTestPattern();
    me_Delays::Delay_S(1);

    Stripe.Clear();
    Stripe.Display();
    me_Delays::Delay_S(1);
  }
  DisplayTestPattern();
}

void setup()
{
  me_Delays::Init();
  Console.Init();

  Console.Print("( [me_RgbStripe] test");
  Console.Indent();
  RunTest();
  Console.Unindent();
  Console.Print(") Done");
}

void loop()
{
}

/*
  2024-09-12
  2024-09-15
  2024-12-20
*/
