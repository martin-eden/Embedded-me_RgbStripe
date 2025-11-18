// Display readings from analog pin as grayscale on LED stripe

/*
  Author: Martin Eden
  Last mod.: 2025-11-18
*/

#include <me_RgbStripe.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_Delays.h>

const TUint_1 Stripe_OutputPin = 2;
const TUint_1 Stripe_Length = 60;
const TUint_2 DataMemSize = Stripe_Length * sizeof(me_RgbStripe::TColor);

TUint_1 DataMem[DataMemSize];
const TAddressSegment DataSeg = AsAddrSeg_M(DataMem);

me_RgbStripe::TRgbStripe Stripe;

/*
  Display value as pixel in LED stripe

  We're displaying in grayscale.
  But fancier palettes may be used.

  We expect integer in range [0, 1023].
*/
void DisplayValue(
  TUint_2 Value
)
{
  const TUint_2 MaxValue = 1023;

  /*
    Maximum brightness [0, 255]

    Full 255 yields to brownout if stripe is getting power from USB.
  */
  const TUint_1 MaxColorComponentValue = 100;

  static TUint_2 PrevPixelIndex = 0;
  TUint_2 CurPixelIndex;
  TUint_1 ColorComponentValue;
  me_RgbStripe::TColor Color;

  if (Value > MaxValue)
    return;

  CurPixelIndex = PrevPixelIndex + 1;

  if (!Stripe.CheckIndex(CurPixelIndex))
    CurPixelIndex = 1;

  // Map [0, 1023]
  ColorComponentValue = map(Value, 0, MaxValue, 0, MaxColorComponentValue);

  Console.Print(ColorComponentValue);

  Color.Red = ColorComponentValue;
  Color.Green = ColorComponentValue;
  Color.Blue = ColorComponentValue;

  Stripe.SetPixel(CurPixelIndex, Color);
  Stripe.Display();

  PrevPixelIndex = CurPixelIndex;
}

/*
  Process analog reading value
*/
void DisplayReadings(
  TUint_2 AnalogValue
)
{
  const TUint_2 MaxGapToIgnore = 20;

  static TUint_2 PrevPrintedValue = 0;

  TUint_2 Gap;

  Gap = GetGap(AnalogValue, PrevPrintedValue);

  if (Gap > MaxGapToIgnore)
  {
    // Console.Print(Gap);

    DisplayValue(AnalogValue);

    PrevPrintedValue = AnalogValue;
  }
}

TUint_2 GetGap(
  TUint_2 A,
  TUint_2 B
)
{
  if (A < B)
    return B - A;

  return A - B;
}

void setup()
{
  me_Delays::Init();
  Console.Init();
  Stripe.Init(Stripe_OutputPin, DataSeg);
  Stripe.Clear();
}

void loop()
{
  const TUint_1 ReadingPin = A0;
  const TUint_1 ReadingInterval_ms = 40;

  TUint_2 ReadingValue = analogRead(ReadingPin);

  DisplayReadings(ReadingValue);

  me_Delays::Delay_Ms(ReadingInterval_ms);
}

/*
  2024-12-17
*/
