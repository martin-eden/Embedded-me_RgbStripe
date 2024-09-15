# What

(2024-09)

Wrapper class over RGB LED stripe
([me_Ws2812b.h](https://github.com/martin-eden/Embedded-me_Ws2812b)
library).

Base library exports pixel definition, state structure and state setter
function. (And I'm happy with that!)

State is output pin, stripe length and pointer to pixels data.

This class manages that state. So you can change stripe length at
runtime and pixels memory will grow or shrink.

Plus set pixel/get pixel of course. Plus init, reset and display.


## Interface

* Set output pin and stripe length

  ```C
  TBool Init(TUint_1 OutputPin, TUint_2 StripeLength);
  ```

* Reset - make pixels black

  ```C
  void Reset();
  ```

* Set pixel

  ```C
  TBool SetPixel(TUint_2 Index, me_Ws2812b::TPixel Color);
  ```

* Get pixel

  ```C
  TBool GetPixel(TUint_2 Index, me_Ws2812b::TPixel * Color);
  ```

* Actually display by sending data

  ```C
  void Display();
  ```


## Example interaction

It blinks some test pattern on stripe. Output is:
```
[me_RgbStripe] Hello there!
Output pin is (14).
Stripe length is (60).
[me_RgbStripe] Done.
```


## Requirements

  * arduino-cli
  * bash


## Install

Run [Install.sh](Install.sh).


## Remove

Run [Remove.sh](Remove.sh).


# Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```

# Code

* [Example](examples/me_RgbStripe/me_RgbStripe.ino)
* [Interface](src/me_RgbStripe.h)
* [Implementation](src/me_RgbStripe.cpp)


# See also

* [My other embedded C++ libraries](https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts)
* [My other repositories](https://github.com/martin-eden/contents)
