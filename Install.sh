#!/bin/bash

# Install dependencies
arduino-cli \
  lib install \
    --git-url \
      https://github.com/martin-eden/Embedded-me_BaseTypes \
      https://github.com/martin-eden/Embedded-me_UartSpeeds \
      https://github.com/martin-eden/Embedded-me_InstallStandardStreams \
      https://github.com/martin-eden/Embedded-me_MemorySegment \
      https://github.com/martin-eden/Embedded-me_ManagedMemory

# Install library
arduino-cli \
  lib install \
    --git-url \
      https://github.com/martin-eden/Embedded-me_RgbStripe
