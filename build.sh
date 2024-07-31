#!/bin/bash

pio run --target size
if [ $? -ne 0 ]; then
    echo "Error executing 'pio run --target size'."
    exit 1
fi

pio run --target upload
if [ $? -ne 0 ]; then
    echo "Error executing 'pio run --target upload'."
    exit 1
fi

pio run --target buildfs
if [ $? -ne 0 ]; then
    echo "Error executing 'pio run --target buildfs'."
    exit 1
fi

pio run --target uploadfs
if [ $? -ne 0 ]; then
    echo "Error executing 'pio run --target uploadfs'."
    exit 1
fi

echo "All commands executed successfully."
