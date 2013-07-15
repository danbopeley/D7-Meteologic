# Meteologic

This is an api/framework module which makes it easy to provider customized weather information.

The idea is that this module will handle all of the heavy lifting and that submodules can easily add providers and feeds by implementing a simple hook.

## Terminology

* A provider is a company or service which provides one or more meteorologic feeds, for example: NOAA, MesoWest or Custom Weather.
* A feed is basically some specific information such as "Current Conditions", "Point Forecast" or "Radar".

## Developers

* Check out the meteologic.api.php file for information on the hooks provided.
* Check out the "Meteologic NOAA" module for an example implementation.

## History

Started off as a port of the "NOAA Weather" module, by Dan the Weather man.
