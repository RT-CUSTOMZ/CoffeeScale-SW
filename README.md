# Firmware for coffee scale project

## Change flatpak permissions

tweaks for visualstudio code from flatpak

```bash
flatpak \
  --user override \
  --device=all \
  com.visualstudio.code.oss
```

## Updating perfect hash functions (gperf)

Some parts of this project use gperf generated hash functions for fast resolving from path to implementation.

```bash
gperf -L C \
  --output-file=http_path_lookup.c \
  http_path_lookup.gperf
```

## To build and upload the project

This project depends on PlatformioIO as buildsystem

To build the project

```bash
platformio run
```

To upload the project to an ESP8266:

```bash
platformio run \
  --target upload \
  --upload-port /dev/ttyACM0
```