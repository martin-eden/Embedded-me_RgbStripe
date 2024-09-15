#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_RgbStripe

# Uninstall dependencies
arduino-cli lib uninstall \
  me_UartSpeeds \
  me_InstallStandardStreams \
  me_ManagedMemory \
  me_MemorySegment \
  me_MemoryPoint \
  me_BaseTypes
