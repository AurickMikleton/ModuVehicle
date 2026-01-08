# Modu-Vehicle: Modular Vehicle physics for Godot 4.45+ in C++

### Disclaimer: Work-in-progress, no ETA for completion

This is a modular vehicle system for Godot 4.5+. It is designed with the general concept of each part of a car's [powertrain](https://en.wikipedia.org/wiki/Powertrain) being represented as swappable Resource types, allowing for modular control over how the car is simulated in a way that makes ergonomic sense with how cars are designed in the real world. With this, users can build anything from basic and exaggerated calculations for arcade racers, to in-depth and specific calculations for realistic simulations.

# Features:
* Very good documentation, both of external APIs and internal code (WIP)
* Modular implementations for:
  * gas engine
  * transmission
  * wheels

# Credits
* [VitaVehicle](https://jreo.itch.io/rcp4): A lot of inspiration in design concepts and implementations
* [c08oprkiua's original version](https://github.com/c08oprkiua/ModuVehicle): Basis of project architecture
