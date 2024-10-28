## What

(2024-09)

Wrapper class over mine [WS2812B][me_Ws2812b] RGB LED stripe driver.

Base library exports pixel definition, state structure and state setter
function. (And I'm happy with that!)

State is output pin, stripe length and pointer to pixels data.

This class manages that state. So you can change stripe length at
runtime and pixels memory will grow or shrink.

Plus set pixel/get pixel of course. Plus init, reset and display.


## Interface

RGB stripe for us is _*Output pin*_, _*Length*_ (number of LEDs) and
_*Data*_ (pixels memory that is not directly exposed).

We have trivial methods

  * `TBool Init(Output_Pin, Length)`
  * Get/set output pin
  * Get/set length (changes size of _Data_)

We are working with data by

  * `TBool GetPixel(Index, *Color)`
  * `TBool SetPixel(Index, Color)`
  * `Display()` to actually send data to LED stripe
  * `Reset()` to set all pixels to zeroes

So we are also exporting `TColor` struct which is typical RGB.


## Sample output

Example code blinks some test pattern on stripe.
Output is:

```
[me_RgbStripe] Hello there!
Output pin is (2).
Stripe length is (60).
We will blink test pattern on LED stripe for several seconds.
[me_RgbStripe] Done.

```

## Code

* [Example][Example]
* [Interface][Interface]
* [Implementation][Implementation]


## Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```


## Requirements

  * arduino-cli
  * bash


## Install

Run [Install.sh](Install.sh).


## Remove

Run [Remove.sh](Remove.sh).


## See also

* [me_Ws2812b][me_Ws2812b]
* [My other embedded C++ libraries](https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts)
* [My other repositories](https://github.com/martin-eden/contents)

[Example]: examples/me_RgbStripe/me_RgbStripe.ino
[Interface]: src/me_RgbStripe.h
[Implementation]: src/me_RgbStripe.cpp
[me_Ws2812b]: https://github.com/martin-eden/Embedded-me_Ws2812b
