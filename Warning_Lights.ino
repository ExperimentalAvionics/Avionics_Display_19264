void Warning_lights() {

// This procedure called on every loop and check whether any flight or engine parameters are out of normal range
// There are 5 paremeters bands: red-low - yellow-low - green - yellow-high - red-high
// if any of the parameters fall into yellow band the yelow LED light up
// if any of the parameters fall into red band, the red LED light up
// some paremeters might have a separate annunciator light
// the idea is to encourage the pilot to check flight and engine parameters
// primary focus of this warnings is engine and electric system

// there are two led control variables Warning_Yellow and Warning_Red
// each bit in the variable represents a parameter
// so is any of the bits are "1" (the variable is > 0)the relevant light will come on
// as the parameters are getting tested the relevant bitwise operation will be performed on the control variables

unsigned int Warning_Yellow = 0;
unsigned int Warning_Red = 0;


// Voltage
#define  Voltage_Bit = 1;
#define VoltageLowRed = 11.5;       // the bands are for acid battery
#define VoltageLowYellow = 13.9;
#define VoltageHighYellow = 14.5;
#define VoltageHightRed = 16.0;

// Current battery
#define CurrentBattery_Bit = 2;
#define CurrentBatteryLowRed = -10;       // the bands are for acid battery - need adjustment
#define CurrentBatteryLowYellow = 0;
#define CurrentBatteryHighYellow = 3;
#define CurrentBatteryHightRed = 6;

// Current alternator
#define CurrentAlternator_Bit = 4;
#define CurrentAlternatorLowRed = 0;       // the bands are for acid battery - need adjustment
#define CurrentAlternatorLowYellow = 0;
#define CurrentAlternatorHighYellow = 12;
#define CurrentAlternatorHightRed = 16;


// Oil pressure
// According to the Rotax 912 ULS operator manual page 2-5 the considered normal pressures are:
// Max. 7 bar (102 psi) (Red)
// Min. 0.8 bar (12 psi) (below 3500 rpm) (Red)
// Normal 2.0 to 5.0 bar (29-73 psi) (above 3500 rpm) (Green)


// Oil Temperature 
// For Rotax 912
// Max 130C
// Min 50C
// normal range 90 - 110


// Fuel pressure
// Rotax 912 ULS:
// Max 0.4 Bar (5.8 PSI)
// Min 0.15 Bar (2.2 PSI)
// The new style pump creates around 4.5 PSI for most people. 
// If you run an aux electric pump then that number may be .5 to 1.0 psi higher. 



// Fuel flow



// EGT



// CHT
// Max 135C
// Normal range 75 - 110C


// RPM




//============= CODE STARTS HERE ================================================



    
}
