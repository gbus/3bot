/// DEBUG
// Enable or disable serial debugging of motor speed (comment next line to disable)
//#define DEBUG_MOTORS

// FORWARD = 0, BACKWARD = 1
#define FW                      0
#define BW                      1

// Encoder settings (No. of ticks: 68, Wheel diameter in meters: 0.05549)
#define TICKS_PER_METER 390  // ticks/(diam*pi) = 68/(0.05549*3.14) 

/// ADJUST BRAKING AND FADING SPEED
#define SLOWCHANGEDELAY 10 // higher number: slower fading: 1=no fading
#define BRAKESPEED 3 // smaller number less abrupt braking (braking reuses FADESPEED)
