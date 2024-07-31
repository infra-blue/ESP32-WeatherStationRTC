@echo off

pio run --target size
if %errorlevel% neq 0 (
    echo "Error executing 'pio run --size'."
    exit /b %errorlevel%
)

pio run --target upload
if %errorlevel% neq 0 (
    echo "Error executing 'pio run --target upload'."
    exit /b %errorlevel%
)

pio run --target buildfs
if %errorlevel% neq 0 (
    echo "Error executing 'pio run --target buildfs'."
    exit /b %errorlevel%
)

pio run --target uploadfs
if %errorlevel% neq 0 (
    echo "Error executing 'pio run --target uploadfs'."
    exit /b %errorlevel%
)

echo "All commands executed successfully."
