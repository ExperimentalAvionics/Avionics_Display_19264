# Avionics Display Module

Arduino software for the Display module based on 192x64 FSTN LCD display (KS0107/KS0108)

The unit diplays both EFIS and EMS information.

Details are here: http://experimentalavionics.com/efis-display-unit/
 
Unzip libraries.zip to the "libraries" folder in your Arduino environment.

## Release Notes: ##

### 2021-06-16 ###
* Enabled warning lights (LEDs) for monitoring Voltage, Oil Pressure and Oil Temperature. Yellow and Red bands defined in the Warning_lights() function

### 2021-06-08 ###
* Bug fix for QNH setting

### 2021-06-04 ###
* Added third scrollable screen for TAS data (includes TAS, OAT, and Wind). Wind calculation is not included yet. Just a placeholder;
* Fixed bug - G-loading appeared on other screens screen;
* Altitude figure on display will change only if it is different from previous value by 5ft or more. Reason is to stabilize display and avoid flicker of the numbers.
* VSI figure on display will change only if it is different from previous value by 20 ft/min or more. If VSI is within +/- 70ft/min the VSI will display Zero. Reason is to stabilize display and avoid flicker of the numbers.
* Removed the flicker on Airspeed, Heading numbers and the slip/skid ball.
