// RGB LED stripe manager

/*
  Author: Martin Eden
  Last mod.: 2024-09-12
*/

#include "me_RgbStripeManager.h"

using
  me_RgbStripeManager::TRgbStripeManager,
  me_Ws2812b::TPixel;

// Initialize and reset
void TRgbStripeManager::Init(
  TUint_1 OutputPin,
  TUint_2 StripeLength
)
{
  TUint_1 DefaultOutputPin = A0;
  TUint_2 DefaultStripeLength = 60;

  if (!SetOutputPin(OutputPin))
    SetOutputPin(DefaultOutputPin);

  TUint_2 MaxIndex = StripeLength - 1;
  if (!CheckIndex(MaxIndex))
    StripeLength = DefaultStripeLength;
  this->StripeLength = StripeLength;

  Reset();
}

// Set pixels to initial state
void TRgbStripeManager::Reset()
{
  TPixel InitPixel = { .Green = 0, .Red = 0, .Blue = 0 };

  for (TUint_1 Index = 0; Index < this->StripeLength; ++Index)
    SetPixel(Index, InitPixel);

  Display();
}

// Update LED stripe
void TRgbStripeManager::Display()
{
  me_Ws2812b::TLedStripeState StripeState;

  StripeState.Pixels = Pixels;
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

// [maintenance] Set output pin
TBool TRgbStripeManager::SetOutputPin(TUint_1 Pin)
{
  // We can check for valid pin here if we want to

  OutputPin = Pin;

  return true;
}

// [maintenance] Get output pin
TUint_1 TRgbStripeManager::GetOutputPin()
{
  return OutputPin;
}

// )

/*
  2024-09-12
*/
