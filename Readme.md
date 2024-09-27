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

For complete documentation [read code][Interface].


## Example interaction

[Example code][Example] blinks some test pattern on stripe.
Output is:
```
[me_RgbStripe] Hello there!
Output pin is (2).
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

* [Example][Example]
* [Interface][Interface]
* [Implementation][Implementation]


# See also

* [My other embedded C++ libraries](https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts)
* [My other repositories](https://github.com/martin-eden/contents)

[Example]: examples/me_RgbStripe/me_RgbStripe.ino
[Interface]: src/me_RgbStripe.h
[Implementation]: src/me_RgbStripe.cpp
