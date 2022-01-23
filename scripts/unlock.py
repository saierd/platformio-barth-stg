from pydoc import describe


Import("env")

env.AddCustomTarget(
    "unlock",
    None,
    '"$PROJECT_PACKAGES_DIR/tool-openocd/bin/openocd" -f board/st_nucleo_f0.cfg -c "init; reset halt; stm32f1x unlock 0; reset run; exit"',
    title="Unlock",
    description="Unlock Microcontroller Flash",
)
