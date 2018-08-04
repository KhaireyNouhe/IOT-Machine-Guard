# IOT-Machine-Guard
The IoT Machine-Guard is capable of guarding electrical machines, it tracks temperature, vibration, sound, smoke, and current values.

# DESCRIPTION
The IoT Machine-Guard is a newly developed open hardware & Software device that can track, and publish five physical and electrical characteristics of electrical machines. 
It can be used either for quality inspection, fault detection, performance analysis, or for safety requirements in the field of industry. 

The IoT Machine-Guard has the ability to guard and protect electric machines from damage under any circumstances, and accordingly, it is able to protect the whole industrial institution from fire hazards, or machine total-loss. 

It enables a factory manager/owner to view all data outputs of all machines in his factory on a neat and well-organized GUI with gauges and line charts anywhere in the world. 

The device enables factory managers,too, to control the power of their machines using an interactive power switch anywhere in the world. 

A database is also saved automatically containing all data readings for all feeds of a machine in a ratio of 1 reading/4 seconds.

Project Main Focus:

During my pilot study, I noticed an increasing lack of a good dependable device that can guard most industrial machines; track and analyze machinery data outputs, protect machines from damage or even fires caused by malfunction or obsolete machines in a factory.

For all mentioned reasons, and for the great advancement in the field of IIoT, I thought of building a monitoring and protection device (the size of a Raspberry Pi) and named it “IoT Machine-Guard.” That can be attached to many electrical machines for both monitoring data outputs, and for safety and quality requirements.

*The “IoT Machine-Guard” is able to perform the following tasks:

It has a connected Temperature Sensor that can measure temperature of values of 0-1024 Degrees Celsius, display the temperature of machine, detect any overheating, trigger an alarm, and cut off current from machine automatically for protection.
It has a connected Vibration Sensor that can display the vibration ratio of machine, detect any extra vibration (caused by malfunction, broken engine parts, or unstable current source), trigger an alarm, and cut off current from machine automatically for protection.
It has a connected Sound Sensor that can display the sound level of machine, detect any extra strange sound frequencies (caused by malfunction, broken engine parts, or unstable current source), trigger an alarm, and cut off current from machine automatically for protection.
It has a connected Smoke Sensor that can display the smoke level of machine, detect any extra smoke levels around machine’s high-current hot spots, engines, and motors (caused by malfunction, broken engine parts, or extra current withdrawal), trigger an alarm, and cut off current from machine automatically for protection.
It has a connected Current Sensor that can track and display the current withdrawal and Watt consumption levels of machine, detect any over-current levels drawn by machine (due to malfunction, broken engine parts, or extra current withdrawal), trigger an alarm, and cut off current from machine automatically for protection.
It has a connected Power Relay that functions as an on/off switch to control the power of machine.
The device can compare all sensors’ data inputs to a predefined normal level for each sensor, and control the power of machine accordingly. 
The device can also send these data outputs from the sensors to Adafruit.io web broker in a ratio of 1 data reading/4 seconds.
The state of the interactive online power switch changes according to machine power status, and it can also be used to power on/off a machine wirelessly anywhere in the world .
* The Adafruit.io web broker works as a GUI that includes gauges, line charts, toggle switches, and other useful data display tools.

It also stores all data readings of all feeds in a browsable & downloadable database. A dedicated Excel sheet can be downloaded for each feed containing feed ID, value, date, time, and location. 

Those database registers can be used for data analysis that, in turn, enables factory managers/owners  to perform quality inspection, machine history tracking, machine health investigation, and predict the best time for machine elimination and disposal. 

I've created a GUI dashboard to display the data outputs in a form of Gauges and Line Charts on Adafruit.io web broker.
I've also recorded a special trigger for each data feed on the web broker, which in turn will send an e-mail in case any data feed exceeds the pre-defined normal value of each sensor.
