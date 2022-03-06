# PlatformIO Example for Barth STG-820 and STG-850 Boards

The board definitions in `boards/` were created from this [Arduino board definition](https://github.com/jasysdotde/STG-8xx). They use the same pin numbering. See https://barth-elektronik.com/downloads/9022-0022-A.pdf for more information.

## Unlock the Microcontroller Flash

Before flashing your own firmware, you need to unlock the microcontroller's flash. **Note that this will remove the original firmware!**

To unlock the flash run

```bash
pio run -t unlock
```

and power cycle the board.
