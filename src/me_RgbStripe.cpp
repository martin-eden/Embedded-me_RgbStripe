// RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2024-09-27
*/

#include "me_RgbStripe.h"

using namespace me_RgbStripe;

/*
  Set output pin and stripe length. Reset.
*/
TBool TRgbStripe::Init(
  TUint_1 OutputPin_arg,
  TUint_2 StripeLength_arg
)
{
  OutputPin = OutputPin_arg;

  if (!SetLength(StripeLength_arg))
    return false;

  Reset();

  return true;
}

/*
  Set pixels to initial state (zeroes)
*/
void TRgbStripe::Reset()
{
  TPixel InitPixel = { .Green = 0, .Red = 0, .Blue = 0 };

  for (TUint_1 Index = 0; Index < Length; ++Index)
    SetPixel(Index, InitPixel);
}

/*
  Send data to LED stripe
*/
void TRgbStripe::Display()
{
  using namespace me_Ws2812b;

  TLedStripeState StripeState;

  StripeState.Pixels = (TPixel *) PixelsMem.Start.Addr;
  StripeState.Length = Length;
  StripeState.Pin = OutputPin;

  SetLedStripeState(StripeState);
}

/*
  Set pixel at index
*/
TBool TRgbStripe::SetPixel(
  TUint_2 Index,
  TPixel Color
)
{
  if (!CheckIndex(Index))
    return false;

  TPixel * Pixels = (TPixel *) PixelsMem.Start.Addr;

  Pixels[Index] = Color;

  return true;
}

/*
  Get pixel at index
*/
TBool TRgbStripe::GetPixel(
  TUint_2 Index,
  TPixel * Color
)
{
  if (!CheckIndex(Index))
    return false;

  TPixel * Pixels = (TPixel *) PixelsMem.Start.Addr;

  *Color = Pixels[Index];

  return true;
}

// ( Maintenance

/*
  [maintenance] Check index
*/
TBool TRgbStripe::CheckIndex(TUint_2 Index)
{
  return (Index <= Length - 1);
}

/*
  [maintenance] Set stripe length and allocate memory for pixels
*/
TBool TRgbStripe::SetLength(TUint_2 StripeLength_arg)
{
  Length = StripeLength_arg;

  if (!ReservePixelsMem(Length))
  {
    /*
      No memory for pixels block of our length.
      We will set stripe length to zero.
    */
    Length = 0;

    return false;
  }

  return true;
}

/*
  [maintenance] Get stripe length
*/
TUint_2 TRgbStripe::GetLength()
{
  return Length;
}

/*
  [maintenance] Reserve memory for pixels

  Previous memory segment is released.

  If memory cannot be allocated, return false.
*/
TBool TRgbStripe::ReservePixelsMem(TUint_2 NumPixels)
{
  TUint_2 PixelsMemSize = NumPixels * sizeof(TPixel);

  /*
    If you try to allocate already busy TMemorySegment, Reserve() will
    just return false.

    If you try to free already empty memory segment, Release() will
    just return false.

    So it is safe to call Release() before Reserve().
  */

  PixelsMem.Release();

  return PixelsMem.Reserve(PixelsMemSize);
}

// ) Maintenance

/*
  2024-09-12
  2024-09-12 Memory management, renamed to "RgbStripe" from "..Manager"
*/
