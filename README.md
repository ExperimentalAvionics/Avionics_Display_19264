# Avionics Display Module

Arduino software for the Display module based on 192x64 FSTN LCD display (KS0107/KS0108)

The unit diplays both EFIS and EMS information.

Details are here: http://experimentalavionics.com/efis-display-unit/
 
Unzip libraries.zip to the "libraries" folder in your Arduino environment.

## Release Notes: ##

### 2023-12-23 ###
* Minor bug fixes for GPS display.

### 2023-12-14 ###
* Changed presentation of GPS information. Now all the number in the GPS screen are aligned to the right.
* GPS altitude now has the thousands separator (comma) making it easier to read
* Track is now prefixed with T or M (True or Magnetic)
* Added number of satellites being received with the signal bar graph for the first (strongest) 14 satellites. Left number and the bar graph at the bottom of the GPS screen represents GCP constellation (USA) and the right number and bar graph represent GLONASS constellation (Russia)

### 2023-06-27 ###
* Implemented backlight and LEDs brightness dimmer for night flying. The change is effective only with the Display PCB board ver 5 and above (blue or black). The brightness is voltage controlled via Arduino port A8 (DSUB pin 10). Photoresistor or a potentiometer can be used to supply the control voltage.
* Implemented backup battery status display section in EMS screen. Module-A software needs to be updated for this feature to be functional.
* Flight timer bug (timer stopped in EMS mode of display) has been fixed.
* Fixed clock issue when clock was occasionally setting itself to random time and date.
* Setting the clock on one display automatically sets the same time on another and keep the clocks in synch.

### 2021-10-23 ###
* Bug fix. Outside air temperature was not displaying correct figures above 25C

### 2021-06-24 ###
* Minor change to display ground speed correctly

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
