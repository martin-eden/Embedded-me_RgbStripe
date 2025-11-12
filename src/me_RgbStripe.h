// RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2025-11-12
*/

/*
  [me_Ws2812b] does not export class, it exports pixels record, state
  record and function for that state record.

  For more high-level code we want class with memory and
  common-sense methods.

  Here it is.
*/

/*
  Index of first pixel is 1 (one).
*/

#pragma once

#include <me_BaseTypes.h>

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
    public:
      // Set output pin and data buffer
      void Init(TUint_1 OutputPin, TAddressSegment DataSeg);
      // Get stripe length
      TUint_2 GetLength();
      // Get pixel
      TBool GetPixel(TColor * Color, TUint_2 Index);
      // Set pixel
      TBool SetPixel(TUint_2 Index, TColor Color);
      // Send data to RGB stripe
      void Display();
      // [Handy] Set all colors to black
      void Clear();
      // Check that index is valid. Method for wrappers
      TBool CheckIndex(TUint_2 Index);
    private:
      TUint_1 OutputPin;
      TAddressSegment PixelsMem;
      TUint_2 Length;

      void CalcLength();
  };
}

/*
  2024-09-12
  2024-09-15 Memory management
  2024-09-17 Init() contract now is also resets and display
  2024-09-18 Init() just resets, not displays
  2024-09-27 TColor, not TPixel
  2025-11-12 Interface reduction/review
*/
