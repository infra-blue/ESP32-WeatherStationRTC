@echo off

pio run --target upload
if %errorlevel% neq 0 (
    echo Error executing 'pio run --target upload'.
    exit /b %errorlevel%
)

pio run --target uploadfs
if %errorlevel% neq 0 (
    echo Error executing 'pio run --target uploadfs'.
    exit /b %errorlevel%
)

echo Upload completed successfully.
