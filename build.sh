#!/bin/bash

pio run --target size
if [ $? -ne 0 ]; then
    echo "Error executing 'pio run --target size'."
    exit 1
fi

pio run --target buildfs
if [ $? -ne 0 ]; then
    echo "Error executing 'pio run --target buildfs'."
    exit 1
fi

echo "Build completed successfully."
