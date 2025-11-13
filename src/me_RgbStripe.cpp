// RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2025-11-12
*/

#include <me_RgbStripe.h>

#include <me_Ws2812b.h>

using namespace me_RgbStripe;

/*
  Color components order

  Our class uses normal RGB fields order.
  Implementation uses GRB order because device uses that order.

  We have our own memory and can store data there in whatever
  format we please.

  We are storing pixels in implementation format.
  Because we don't want to swap bytes in array at every Display().
*/

// ( Color components order
typedef me_Ws2812b::TPixel TDevicePixel;

static TDevicePixel ColorToDeviceFormat(
  TColor Color
)
{
  return (TDevicePixel) { Color.Green, Color.Red, Color.Blue };
}

static TColor ColorFromDeviceFormat(
  TDevicePixel Pixel
)
{
  return (TColor) { Pixel.Red, Pixel.Green, Pixel.Blue };
}
// ) Pixels order

/*
  [Internal] Calculate length from data segment

  Length and data segment are class fields.
*/
void TRgbStripe::CalcLength()
{
  Length = PixelsMem.Size / sizeof(TDevicePixel);
}

/*
  [Internal] Check index
*/
TBool TRgbStripe::CheckIndex(
  TUint_2 Index
)
{
  if (Index < 1)
    return false;
  if (Index > Length)
    return false;
  return true;
}

/*
  Get stripe length
*/
TUint_2 TRgbStripe::GetLength()
{
  return Length;
}

/*
  Set output pin and stripe length. Reset.
*/
void TRgbStripe::Init(
  TUint_1 OutputPin,
  TAddressSegment DataSeg
)
{
  this->OutputPin = OutputPin;
  this->PixelsMem = DataSeg;

  CalcLength();
}

/*
  Set pixel at index
*/
TBool TRgbStripe::SetPixel(
  TUint_2 Index,
  TColor Color
)
{
  if (!CheckIndex(Index))
    return false;

  TDevicePixel * DevicePixels = (TDevicePixel *) PixelsMem.Addr;

  DevicePixels[Index - 1] = ColorToDeviceFormat(Color);

  return true;
}

/*
  Get pixel at index
*/
TBool TRgbStripe::GetPixel(
  TColor * Color,
  TUint_2 Index
)
{
  if (!CheckIndex(Index))
    return false;

  TDevicePixel * Pixels = (TDevicePixel *) PixelsMem.Addr;

  *Color = ColorFromDeviceFormat(Pixels[Index - 1]);

  return true;
}

/*
  Send data to LED stripe
*/
void TRgbStripe::Display()
{
  using namespace me_Ws2812b;

  TLedStripeState StripeState;

  StripeState.Pixels = (TDevicePixel *) PixelsMem.Addr;
  StripeState.Length = Length;
  StripeState.Pin = OutputPin;

  SetLedStripeState(StripeState);
}

/*
  Set pixels to initial state (zeroes)
*/
void TRgbStripe::Clear()
{
  const TColor InitColor = { 0, 0, 0 };

  TUint_2 Index;
  TUint_2 Length = GetLength();

  for (Index = 1; Index <= Length; ++Index)
    SetPixel(Index, InitColor);
}

/*
  2024-09-12
  2025-11-12
*/
