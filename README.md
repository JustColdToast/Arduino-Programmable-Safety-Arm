# Arduino-Programmable-Safety-Arm
The software for a PIR, Servo, Potentiometer, and Arduino based robotic arm which reacts to proximety sensing of heat to provide autonomous safety functionality.
Included currently is only a software branch. Within it there are three different version, robotCodeV3 is the latest and most efficient version of the program.

The basic functions of the program can be tested at the following [link](https://www.tinkercad.com/things/hKVaefZe7dy-psa-programmable-safety-arm/editel?sharecode=Ip9xPsaTkJJnUsFyGO4d6exGM3i6lTsaoV6gpvMoA3U).
This is a version of the PSA on TinkerCad, running the software provided, and allowing control of the servos and various buttons.

# The Idea Behind The Project
## Summary of Key Points in Design Document
The Programmable Safety Arm, is intended to be an intelligent robotics system for use in a mixed variety of applications, ranging from industrial to hobby. It can, kinematically, be classified as a stationary robot. Running on a partially closed-loop system, the PSA’s use is dictated by the end effector attached to it. However, the most important focus of the PSA is safety.

The Programmable Safety Arm is designed to be used in assembly or personal assistance scenarios while reducing the risk of bodily harm to biological organisms within it’s working area. As such, the PSA is best-suited for jobs in which it will be working in close proximity to humans. This encompasses scenarios such as on a robot-human mixed assembly line, or even in a hobby situation where the robot acts as an assistant to a primary worker.

Unlike many robotics implementations of a similar sort, the Programmable Safety Arm is designed not to replace the human worker, but to aid them in a non-destructive--safe--manner. As such, it is not treated as its own standalone device, but as a specific type of robotic implementation: a human-assistance robot.

What is provided could at best be described as a prototype to associate with the concept of this project: a robot designed to help automate the workspaces without replacing the human worker, with the necessary safety mechanisms to do so.

If this concept were to be expanded to a real product, the following ideas must be implemented:
* A Larger Sensor Array (Perhaps using more PIR sensors, with a higher degree of accuracy and covering a larger area).
 * Would warrent a rewrite of software to accomodate for a wider area covered by sensors.
 * Concept would benefit from a programmatic implementation which does not immediately stop robot operations when workers are nearby, but only slows it until they are in what      may be classified as a "danger zone".
* Soft-shell Design: The physical prototype that I made of this project was made of softer materials. This is a core feature of the PSA, required to help it serve its purpose in   a mixed human-machine workspace.

## Below are some resources pertaining to this project
[Flow Chart](https://imgur.com/Bef4Oah)

[Tinkercad Circuit](https://imgur.com/RYxic7s)

[Circuit Diagram](https://imgur.com/zNoO7DK)

[Technical Drawing](https://drive.google.com/open?id=1qnlo1Zj92EqHDWku5DCsIvkkV9JtC5pn)

[Operation Handout](https://drive.google.com/open?id=1htvVKKVERs7gz3_1c18QGhfO6S7aqbLl) (The company I put at the bottom is just a little joke, not an actual company)

#### For an in-depth design report detailing the project, it's need, uses, and ability for expansion, refer to the attached Design Document
