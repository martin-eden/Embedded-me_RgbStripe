// Display readings from analog pin as grayscale on LED stripe

/*
  Author: Martin Eden
  Last mod.: 2024-12-17
*/

#include <me_RgbStripe.h>

#include <me_BaseTypes.h>
#include <me_Uart.h>
#include <me_UartSpeeds.h>
#include <me_Console.h>

const TUint_1 Stripe_OutputPin = 2;
const TUint_1 Stripe_Length = 60;

me_RgbStripe::TRgbStripe Stripe;

void setup()
{
  me_Uart::Init(me_UartSpeeds::Bps_115k);
  Stripe.Init(Stripe_OutputPin, Stripe_Length);
}

void loop()
{
  const TUint_1 ReadingPin = A0;
  const TUint_1 ReadingInterval_ms = 40;

  TUint_2 ReadingValue = analogRead(ReadingPin);

  DisplayReadings(ReadingValue);

  delay(ReadingInterval_ms);
}

/*
  Process analog reading value
*/
void DisplayReadings(
  TUint_2 AnalogValue
)
{
  const TUint_2 MaxGapToIgnore = 20;

  static TUint_2 LastPrintedValue = 0;

  TUint_2 Gap;

  Gap = GetGap(AnalogValue, LastPrintedValue);

  if (Gap > MaxGapToIgnore)
  {
    // Console.Print(Gap);

    DisplayValue(AnalogValue);

    LastPrintedValue = AnalogValue;
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

  static TUint_2 LastPixelIndex = 0;
  TUint_2 CurPixelIndex;
  TUint_1 ColorComponentValue;
  me_RgbStripe::TColor Color;

  if (Value > MaxValue)
    return;

  if (LastPixelIndex == Stripe.GetLength() - 1)
    CurPixelIndex = 0;
  else
    CurPixelIndex = LastPixelIndex + 1;

  // Map [0, 1023]
  ColorComponentValue = map(Value, 0, MaxValue, 0, MaxColorComponentValue);

  Console.Print(ColorComponentValue);

  Color.Red = ColorComponentValue;
  Color.Green = ColorComponentValue;
  Color.Blue = ColorComponentValue;

  Stripe.SetPixel(CurPixelIndex, Color);
  Stripe.Display();

  LastPixelIndex = CurPixelIndex;
}

/*
  2024-12-17
*/
