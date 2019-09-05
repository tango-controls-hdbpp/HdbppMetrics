# HdbppMetrics

WIP

Hdbpp metrics work. Currently depends on  the unmerged CMake branches in the hdbpp-es/libhdbpp projects.

## Metrics Library

A small metrics library has been added to the hdbpp-es project to record when events occur. This currently just records event in three cases:

* Event received
* Before back-end storage
* After back-end storage

The library creates two log files, a "received.log" and a "db_insertion.log". These can then be used by scripts to start extracting interesting information.

## Building

The event subscriber project downloads and links again libhdbpp (experimental version 2) automatically. It is also patched as part of the build process.

To build the hdbpp-es project, do the following:

```bash
cd event-subscirber
mkdir build
cd build
cmake ..
make
```

The build system uses pkg-config to find some dependencies, for example Tango. If Tango is not installed to a standard location, set PKG_CONFIG_PATH, i.e.

```bash
export PKG_CONFIG_PATH=/non/standard/tango/install/location
cmake ../
...
```