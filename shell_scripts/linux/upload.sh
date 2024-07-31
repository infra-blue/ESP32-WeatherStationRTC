#!/bin/bash

pio run --target upload
if [ $? -ne 0 ]; then
    echo "Error executing 'pio run --target upload'."
    exit 1
fi

pio run --target uploadfs
if [ $? -ne 0 ]; then
    echo "Error executing 'pio run --target uploadfs'."
    exit 1
fi

echo "Upload completed successfully."
