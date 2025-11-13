## What

(2024-09, 2025-11)

Wrapper class over my [WS2812B][me_Ws2812b] RGB LED stripe driver.

Base library exports pixel definition, state structure and state setter
function. (And I'm happy with that!)

State is output pin, stripe length and pointer to pixels data.

This class manages that state.

## Interface

For real interface read code. Here is more high-level description.

Class provides higher-level interface to RGB stripe.

**Init()** takes output pin number and description of RAM memory
region to store data.

Accessors are **GetPixel()** and **SetPixel()**.

**GetLength()** returns length of stripe in pixels (depends of
memory size provided in Init()).

**Display()** actually sends data to stripe.

## Code

* [Interface][Interface]
* [Implementation][Implementation]
* [Example][Example]

## Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```

## Requirements

  * arduino-cli
  * bash

## Install/remove

Easy way is to clone [GetLibs][GetLibs] repo and run it's code.

## See also

* [me_Ws2812b][me_Ws2812b]
* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]

[Interface]: src/me_RgbStripe.h
[Implementation]: src/me_RgbStripe.cpp
[Example]: examples/me_RgbStripe/me_RgbStripe.ino

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[me_Ws2812b]: https://github.com/martin-eden/Embedded-me_Ws2812b
[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
