#!/bin/sh

# ==============================================================================
# Creates a systemd service which launches the `rpi-logger` executable after
# every system reboot.
# 
# Usage: Copy this script to *exactly* the installation directory of the
# rpi-logger executable and run from there with
# `sudo ./installStartService.sh` (chmod +x may be necessary).
# ==============================================================================

# Create service file.
SERVICE_NAME="startRpiLogger"
FILE_NAME=$SERVICE_NAME".service"
DEST_PATH="/etc/systemd/system/${FILE_NAME}"

FILE_CONTENT="[Unit]
Description=Launches rpi-logger.

[Service]
WorkingDirectory="$PWD"
StandardOutput=null
ExecStart="$PWD"/rpi-logger

[Install]
WantedBy=multi-user.target"

echo "$FILE_CONTENT" > $FILE_NAME


# Install and setup service.
mv "$FILE_NAME" "$DEST_PATH"
chmod 644 "$DEST_PATH"

systemctl start "$SERVICE_NAME"
systemctl status "$SERVICE_NAME"

STATUS_RESULT=$?
echo "Status result:"
echo "$STATUS_RESULT"

systemctl enable "$SERVICE_NAME"
