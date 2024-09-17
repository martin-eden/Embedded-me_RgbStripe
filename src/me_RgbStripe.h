// RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2024-09-17
*/

/*
  [me_Ws2812b] does not export class, it exports pixel structure and
  function. Function argument is state: pin, length and pixels.

  For more high-level code I want intermediate level that is class with
  own memory and some common-sense methods.

  Here it is.
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_ManagedMemory.h>
#include <me_Ws2812b.h>

namespace me_RgbStripe
{
  // RGB stripe manager
  class TRgbStripe
  {
    private:
      TUint_1 OutputPin;
      TUint_2 Length;
      me_ManagedMemory::TManagedMemory PixelsMem;

      // [maintenance] Check index
      TBool CheckIndex(TUint_2 Index);

      // [maintenance] Allocate memory for pixels
      TBool ReservePixelsMem(TUint_2 NumPixels);

    public:
      // Set output pin and stripe length. Reset and display
      TBool Init(TUint_1 OutputPin, TUint_2 StripeLength);

      // Reset - make pixels black
      void Reset();

      // Actually display by sending data
      void Display();

      // Set pixel
      TBool SetPixel(TUint_2 Index, me_Ws2812b::TPixel Color);

      // Get pixel
      TBool GetPixel(TUint_2 Index, me_Ws2812b::TPixel * Color);

      // [maintenance] Set stripe length
      TBool SetLength(TUint_2 StripeLength);
      // [maintenance] Get stripe length
      TUint_2 GetLength();
  };
}

/*
  2024-09-12
  2024-09-15 Memory management
  2024-09-17 Init() contract now is also resets and display
*/
