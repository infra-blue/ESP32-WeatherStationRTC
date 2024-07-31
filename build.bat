@echo off

pio run --target size
if %errorlevel% neq 0 (
    echo Error executing 'pio run --target size'.
    exit /b %errorlevel%
)

pio run --target buildfs
if %errorlevel% neq 0 (
    echo Error executing 'pio run --target buildfs'.
    exit /b %errorlevel%
)

echo Build completed successfully.
