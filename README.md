# PlatformIO Example for Barth STG-820 and STG-850 Boards

The board definitions in `boards/` were created from this [Arduino board definition](https://github.com/jasysdotde/STG-8xx). They use the same pin numbering. See https://barth-elektronik.com/downloads/9022-0022-A.pdf for more information.

* IO and EEPROM work with the usual Arduino functions when using the `arduino` framework.
* Additionally this repository includes headers with pin names as they are written on the boards (e.g. [`src/pins_stg_820.h`](src/pins_stg_820.h)).
* A simple interface for using the CAN bus is implemented in [`src/can.h`](src/can.h).

## Unlock the Microcontroller Flash

Before flashing your own firmware, you need to unlock the microcontroller's flash. **Note that this will remove the original firmware!**

To unlock the flash run

```bash
pio run -t unlock
```

and power cycle the board.
