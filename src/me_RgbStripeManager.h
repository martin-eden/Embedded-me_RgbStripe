// RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2024-09-12
*/

/*
  [me_Ws2812b] does not export class, it exports pixel structure and
  function. Function argument is state: pin, length and pixels.

  For more high-level code I want intermediate level that is class with
  some common-sense methods.

  Here it is.
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_Ws2812b.h>

#include <Arduino.h> // pin A0

namespace me_RgbStripeManager
{
  // RGB stripe manager
  class TRgbStripeManager
  {
    private:
      TUint_1 OutputPin;
      TUint_2 StripeLength;
      me_Ws2812b::TPixel Pixels[60]; // fuck this, I'm sketching!
      // [maintenance] Check index
      TBool CheckIndex(TUint_2 Index);
      // [maintenance] Set output pin
      TBool SetOutputPin(TUint_1 Pin);
      // [maintenance] Get output pin
      TUint_1 GetOutputPin();

    public:
      // Init and reset
      void Init(TUint_1 OutputPin, TUint_2 StripeLength);

      // Reset - make pixels black
      void Reset();

      // Actually display by sending data
      void Display();

      // Set pixel
      TBool SetPixel(TUint_2 Index, me_Ws2812b::TPixel Color);

      // Get pixel
      TBool GetPixel(TUint_2 Index, me_Ws2812b::TPixel * Color);

      // Ad hoc visual test to check borders and output pin
      void Test();
  };
}

/*
  2024-09-12
*/
