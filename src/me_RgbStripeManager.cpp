// RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2024-09-15
*/

#include "me_RgbStripeManager.h"

using
  me_RgbStripeManager::TRgbStripeManager,
  me_Ws2812b::TPixel;

// Initialize and reset
TBool TRgbStripeManager::Init(
  TUint_1 OutputPin_arg,
  TUint_2 StripeLength_arg
)
{
  OutputPin = OutputPin_arg;

  if (!SetStripeLength(StripeLength_arg))
    return false;

  Reset();

  return true;
}

// Set pixels to initial state
void TRgbStripeManager::Reset()
{
  TPixel InitPixel = { .Green = 0, .Red = 0, .Blue = 0 };

  for (TUint_1 Index = 0; Index < StripeLength; ++Index)
    SetPixel(Index, InitPixel);

  Display();
}

// Update LED stripe
void TRgbStripeManager::Display()
{
  me_Ws2812b::TLedStripeState StripeState;

  StripeState.Pixels = (me_Ws2812b::TPixel *) PixelsMem.Start.Addr;
  StripeState.Length = StripeLength;
  StripeState.Pin = OutputPin;

  me_Ws2812b::SetLedStripeState(StripeState);
}

// Set pixel at index
TBool TRgbStripeManager::SetPixel(
  TUint_2 Index,
  me_Ws2812b::TPixel Color
)
{
  if (!CheckIndex(Index))
    return false;

  using me_Ws2812b::TPixel;

  TPixel * Pixels = (TPixel *) PixelsMem.Start.Addr;

  Pixels[Index] = Color;

  return true;
}

// Get pixel at index
TBool TRgbStripeManager::GetPixel(
  TUint_2 Index,
  me_Ws2812b::TPixel * Color
)
{
  if (!CheckIndex(Index))
    return false;

  using me_Ws2812b::TPixel;

  TPixel * Pixels = (TPixel *) PixelsMem.Start.Addr;

  *Color = Pixels[Index];

  return true;
}

// Display ad hoc pattern to visually determine borders of stripe
void TRgbStripeManager::Test()
{
  Reset();

  {
    me_Ws2812b::TPixel Blue, Green;

    Blue = { .Green = 0, .Red = 0, .Blue = 0xFF };
    Green = { .Green = 0xFF, .Red = 0, .Blue = 0 };

    SetPixel(0, Blue);
    SetPixel(StripeLength / 2, Blue);
    SetPixel(StripeLength / 2 + 1, Green);
    SetPixel(StripeLength - 1, Blue);
  }

  Display();
}

// ( Maintenance

// [maintenance] Check index
TBool TRgbStripeManager::CheckIndex(TUint_2 Index)
{
  return (Index <= StripeLength - 1);
}

// [maintenance] Set stripe length and allocate memory for pixels
TBool TRgbStripeManager::SetStripeLength(TUint_2 StripeLength_arg)
{
  StripeLength = StripeLength_arg;

  if (!ReservePixelsMem(StripeLength))
  {
    /*
      No memory for pixels block of our length.
      We will set stripe length to zero.
    */
    StripeLength = 0;

    return false;
  }

  return true;
}

// [maintenance] Get stripe length
TUint_2 TRgbStripeManager::GetStripeLength()
{
  return StripeLength;
}

/*
  [maintenance] Reserve memory for pixels

  Previous memory segment is released.

  If memory cannot be allocated, return false.
*/
TBool TRgbStripeManager::ReservePixelsMem(TUint_2 NumPixels)
{
  /*
    If you try to allocate already busy TMemorySegment, Reserve() will
    just return false.

    However, it is safe to call Release() before Reserve().

    If the segment is already free, Release() will just return false.
  */
  PixelsMem.Release();

  TUint_2 PixelsMemSize = NumPixels * sizeof(me_Ws2812b::TPixel);

  return PixelsMem.Reserve(PixelsMemSize);
}

// )

/*
  2024-09-12
  2024-09-12 Memory management
*/
