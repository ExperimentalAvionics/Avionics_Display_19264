void Warning_lights() {

// This procedure called on every loop and check whether any flight or engine parameters are out of normal range
// There are 5 paremeters bands: red-low - yellow-low - green - yellow-high - red-high
// if any of the parameters fall into yellow band the yelow LED light up
// if any of the parameters fall into red band, the red LED light up
// some paremeters might have a separate/additional annunciator light
// the idea is to encourage the pilot to check flight and engine parameters
// primary focus of this warnings is engine and electric system

// there are two led control variables Warning_Yellow and Warning_Red
// each bit in the variable represents a parameter
// so is any of the bits is "1" (the variable is > 0)the relevant light will come on
// as the parameters are getting tested the relevant bitwise operation will be performed on the control variables

unsigned int Warning_Yellow = 0;
unsigned int Warning_Red = 0;


// Voltage
#define  Voltage_Bit 1    // 0b0000000000000001
#define VoltageLowRed 11.5       // the bands are for acid battery
#define VoltageLowYellow  12.1
#define VoltageHighYellow 15.0
#define VoltageHighRed 16.0

// Current battery
#define CurrentBattery_Bit 2
#define CurrentBatteryLowRed -10       // the bands are for acid battery - need adjustment
#define CurrentBatteryLowYellow 0
#define CurrentBatteryHighYellow 3
#define CurrentBatteryHighRed 6

// Current alternator
#define CurrentAlternator_Bit 4
#define CurrentAlternatorLowRed 0       // the bands are for acid battery - need adjustment
#define CurrentAlternatorLowYellow 0
#define CurrentAlternatorHighYellow 12
#define CurrentAlternatorHighRed 16


// Oil pressure
// According to the Rotax 912 ULS operator manual page 2-5 the considered normal pressures are:
// Max. 7 bar (102 psi) (Red)
// Min. 0.8 bar (12 psi) (below 3500 rpm) (Red)
// Normal 2.0 to 5.0 bar (29-73 psi) (above 3500 rpm) (Green)
#define OilPressure_Bit 8
#define OilPressureLowRed 0.8
#define OilPressureLowYellow 2
#define OilPressureHighYellow 5
#define OilPressureHighRed 7

// Oil Temperature 
// For Rotax 912
// Max 130C
// Min 50C
// normal range 90 - 110
#define OilTemperature_Bit 16
#define OilTemperatureLowRed 50
#define OilTemperatureLowYellow 90
#define OilTemperatureHighYellow 110
#define OilTemperatureHighRed 130


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
// ------------------- Voltage --------------------------------------------------
if ((EL_Volts < VoltageLowYellow * 1000 && EL_Volts > VoltageLowRed * 1000) or (EL_Volts > VoltageHighYellow * 1000 && EL_Volts < VoltageHighRed * 1000) ) {   // EL_Volts is oversized int, so the limit needs to be multiplied by 1000
  Warning_Yellow = Warning_Yellow | Voltage_Bit; // set bit 0, leave other what they were
} else {
  Warning_Yellow = Warning_Yellow & ~Voltage_Bit; // clear bit 0 leave other what they were
}

if ((EL_Volts < VoltageLowRed * 1000) or (EL_Volts > VoltageHighRed * 1000) ) {   // EL_Volts is oversized int, so the limit needs to be multiplied by 1000
  Warning_Red = Warning_Red | Voltage_Bit; // set bit 0, leave other what they were
} else {
  Warning_Red = Warning_Red & ~Voltage_Bit; // clear bit 0 leave other what they were
}
// ------------------------------------------------------------------------------

// ------------------- Oil Pressure ---------------------------------------------
// only if RPM > 0
if (((OilPressure < OilPressureLowYellow * 1000 && OilPressure > OilPressureLowRed * 1000) or (OilPressure > OilPressureHighYellow * 1000 && OilPressure < OilPressureHighRed * 1000)) and RPM > 0 ) {   
  Warning_Yellow = Warning_Yellow | OilPressure_Bit; // set bit 0, leave other what they were
} else {
  Warning_Yellow = Warning_Yellow & ~OilPressure_Bit; // clear bit 0 leave other what they were
}

if (((OilPressure < OilPressureLowRed * 1000) or (OilPressure > OilPressureHighRed * 1000)) and RPM > 0) {   
  Warning_Red = Warning_Red | OilPressure_Bit; // set bit 0, leave other what they were
} else {
  Warning_Red = Warning_Red & ~OilPressure_Bit; // clear bit 0 leave other what they were
}

// ------------------------------------------------------------------------------

// ------------------- Oil Temperature ---------------------------------------------
// only if RPM > 0
if (((OilTemperature < OilTemperatureLowYellow * 10 && OilTemperature > OilTemperatureLowRed * 10) or (OilTemperature > OilTemperatureHighYellow * 10 && OilTemperature < OilTemperatureHighRed * 10)) and RPM > 0 ) {   
  Warning_Yellow = Warning_Yellow | OilTemperature_Bit; // set bit 0, leave other what they were
} else {
  Warning_Yellow = Warning_Yellow & ~OilTemperature_Bit; // clear bit 0 leave other what they were
}

if (((OilTemperature < OilTemperatureLowRed * 10) or (OilTemperature > OilTemperatureHighRed * 10)) and RPM > 0) {   
  Warning_Red = Warning_Red | OilTemperature_Bit; // set bit 0, leave others as they were
} else {
  Warning_Red = Warning_Red & ~OilTemperature_Bit; // clear bit 0 leave others as they were
}

// testing lights
//Warning_Red =1;
//Warning_Yellow =1;


if (Warning_Yellow > 0) {
  YellowLightBlink(1);
} else {
  YellowLightBlink(0);
}

if (Warning_Red > 0) {
  RedLightBlink(1);
} else {
  RedLightBlink(0);
}
    
}
