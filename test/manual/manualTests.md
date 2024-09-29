
How to set up the test scenario:
    1) Compile the project.
    2) Flash the board with the project, connect pico with bootsel pressed
        a) use command: picotool load build/src/hello_freertos.elf
How to exercise the system:
    1) Use command: picotool reboot
        this will reboot into application mode.

Expected behavior:
    Should blink at something like 500ms.
