:: Create a test.bat file
@echo off
echo Testing Arduino connection...

:: Try different baud rates
echo Testing 115200 baud...
avrdude.exe -v -p atmega2560 -c wiring -P COM1 -b 115200 -D

if %ERRORLEVEL% NEQ 0 (
    echo Testing 57600 baud...
    avrdude.exe -v -p atmega2560 -c wiring -P COM1 -b 57600 -D
)

if %ERRORLEVEL% NEQ 0 (
    echo Testing 9600 baud...
    avrdude.exe -v -p atmega2560 -c wiring -P COM1 -b 9600 -D
)