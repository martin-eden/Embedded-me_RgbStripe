// RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2024-09-27
*/

/*
  [me_Ws2812b] does not export class, it exports pixel structure and
  function. Function argument is state record: pin, length and pixels.

  For more high-level code I want intermediate level that is class with
  own memory and some common-sense methods.

  Here it is.
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_ManagedMemory.h>

namespace me_RgbStripe
{
  /*
    Color definition

    Using common color components order: red, green, blue.
  */
  struct TColor
  {
    TUint_1 Red;
    TUint_1 Green;
    TUint_1 Blue;
  };

  // RGB stripe manager
  class TRgbStripe
  {
    private:
      TUint_1 OutputPin;
      TUint_2 Length;
      me_ManagedMemory::TManagedMemory PixelsMem;

    public:
      // Set output pin and stripe length. Reset.
      TBool Init(TUint_1 OutputPin, TUint_2 StripeLength);

      // Reset - make pixels black
      void Reset();

      // Actually display by sending data
      void Display();

      // Set pixel
      TBool SetPixel(TUint_2 Index, TColor Color);

      // Get pixel
      TBool GetPixel(TUint_2 Index, TColor * Color);

      // [maintenance] Set stripe length
      TBool SetLength(TUint_2 StripeLength);

      // [maintenance] Get stripe length
      TUint_2 GetLength();

    private:
      // [maintenance] Check index
      TBool CheckIndex(TUint_2 Index);

      // [maintenance] Allocate memory for pixels
      TBool ReservePixelsMem(TUint_2 NumPixels);
  };
}

/*
  2024-09-12
  2024-09-15 Memory management
  2024-09-17 Init() contract now is also resets and display
  2024-09-18 Init() just resets, not displays
  2024-09-27 TColor, not TPixel
*/
