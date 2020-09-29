#!/usr/bin/env bash
MGBA="/Applications/Emulators/mGBA-0.8.3-osx/bin/mgba"
make clean && make
${MGBA} -3 starfield_mb.gba
