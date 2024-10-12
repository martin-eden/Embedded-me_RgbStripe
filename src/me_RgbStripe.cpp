// RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2024-10-12
*/

#include "me_RgbStripe.h"

#include <me_Ws2812b.h>

using namespace me_RgbStripe;

/*
  Color components order

  Our class uses normal RGB fields order.
  Implementation uses GRB order because device uses that order.

  We have our own memory and can store data there in whatever
  format we want.

  We are storing pixels in implementation format.
  Because we don't want to swap bytes in array at every Display().
*/

// ( Color components order
typedef me_Ws2812b::TPixel TDevicePixel;

TDevicePixel ColorToDeviceFormat(
  TColor Color
)
{
  return
    { .Green = Color.Green, .Red = Color.Red, .Blue = Color.Blue };
}

TColor ColorFromDeviceFormat(
  TDevicePixel Pixel
)
{
  return
    { .Red = Pixel.Red, .Green = Pixel.Green, .Blue = Pixel.Blue };
}
// ) Pixels order

/*
  Set output pin and stripe length. Reset.
*/
TBool TRgbStripe::Init(
  TUint_1 OutputPin_arg,
  TUint_2 Length_arg
)
{
  if (!SetOutputPin(OutputPin_arg))
    return false;

  if (!SetLength(Length_arg))
    return false;

  Reset();

  return true;
}

/*
  Set pixels to initial state (zeroes)
*/
void TRgbStripe::Reset()
{
  TColor InitColor = { .Red = 0, .Green = 0, .Blue = 0 };

  for (TUint_1 Index = 0; Index < Length; ++Index)
    SetPixel(Index, InitColor);
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

  TDevicePixel * DevicePixels = (TDevicePixel *) PixelsMem.GetData().Start.Addr;

  DevicePixels[Index] = ColorToDeviceFormat(Color);

  return true;
}

/*
  Get pixel at index
*/
TBool TRgbStripe::GetPixel(
  TUint_2 Index,
  TColor * Color
)
{
  if (!CheckIndex(Index))
    return false;

  TDevicePixel * Pixels = (TDevicePixel *) PixelsMem.GetData().Start.Addr;

  *Color = ColorFromDeviceFormat(Pixels[Index]);

  return true;
}

/*
  Send data to LED stripe
*/
void TRgbStripe::Display()
{
  using namespace me_Ws2812b;

  TLedStripeState StripeState;

  StripeState.Pixels = (TDevicePixel *) PixelsMem.GetData().Start.Addr;
  StripeState.Length = Length;
  StripeState.Pin = OutputPin;

  SetLedStripeState(StripeState);
}

// ( Maintenance

/*
  [maintenance] Check index
*/
TBool TRgbStripe::CheckIndex(
  TUint_2 Index
)
{
  return (Index <= Length - 1);
}

/*
  [maintenance] Set stripe length and allocate memory for pixels
*/
TBool TRgbStripe::SetLength(
  TUint_2 Length_arg
)
{
  TUint_2 PixelsMemSize = Length_arg * sizeof(TDevicePixel);

  if (PixelsMem.ResizeTo(PixelsMemSize))
  {
    Length = Length_arg;
    return true;
  }

  return false;
}

/*
  [maintenance] Get stripe length
*/
TUint_2 TRgbStripe::GetLength()
{
  return Length;
}

/*
  [design burden] Get output pin
*/
TUint_1 TRgbStripe::GetOutputPin()
{
  return OutputPin;
}

// [design burden] Set output pin
TBool TRgbStripe::SetOutputPin(
  TUint_1 OutputPin_arg
)
{
  /*
    We can check here that pin value makes sense.

    But any pin value makes sense here, as we are not doing job.
    We are just collecting data to call implementation.
  */

  OutputPin = OutputPin_arg;

  return true;
}

// ) Maintenance

/*
  2024-09-12
  2024-09-12 Memory management, renamed to "RgbStripe" from "..Manager"
*/
