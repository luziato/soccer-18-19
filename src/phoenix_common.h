/**
 * phoenix_common.h
 */
#pragma once

// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

#define NUM_MOTORS 3
#define NUM_LINEADC 4 // Numbers of ADS1015 modules 
#define NUM_LINEDETECTORS 8 // Total number of line detectors

