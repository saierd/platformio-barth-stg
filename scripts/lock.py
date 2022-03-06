from pydoc import describe


Import("env")

env.AddCustomTarget(
    "lock",
    None,
    '"$PROJECT_PACKAGES_DIR/tool-openocd/bin/openocd" -f board/st_nucleo_f0.cfg -c "init; reset_config none separate; reset halt; stm32f1x lock 0; reset halt; exit"',
    title="Lock",
    description="Lock Microcontroller Flash",
)
