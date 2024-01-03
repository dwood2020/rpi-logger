#!/bin/bash

# Installation path of executable
APP_PATH="/home/username/logger/rpi-logger"

(crontab -l 2>/dev/null; echo "@reboot $APP_PATH") | crontab -
echo "Cron job set up successfully. App will be launched automatically on every reboot."

# Make this script executable on the target hardware with 
# chmod +x cronJobSetup.sh
