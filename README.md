# Battery-Capacity-Tester-PCB-Board-with-Arduino
Battery Capacity Tester which measures mAh by controlled discharge of lithium ion battery .It works with Arduino.
# Battery Capacity Tester — Arduino

A simple battery capacity tester that measures the 
capacity of a lithium-ion battery in mAh using 
controlled discharge through a resistor.

## How It Works

The battery is discharged through a load resistor (R1 = 10Ω) 
controlled by an NMOS transistor (Q2). The Arduino monitors 
the battery voltage and calculates the discharged capacity 
over time. LED (with R2= 330Ω) indicates that test is running.

## Components

Component 
Arduino Uno ,  Q2(IRFZ44N),  R1(10Ω)  , R2 R3(330Ω) , LED(5mm) 

## Schematic

See `Schematic.pdf`

## PCB

Designed in KiCad 9.0.7

## Output

Capacity result displayed on Serial Monitor in mAh.

## License

MIT
