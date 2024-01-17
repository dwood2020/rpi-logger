#!/bin/sh

# Copyright (C) 2024  David Woodward
# SPDX-License-Identifier: GPL-3.0-or-later

# ==============================================================================
# Removes the installed start service from the system.
# ==============================================================================

SERVICE_NAME="startRpiLogger"
FILE_NAME=$SERVICE_NAME".service"

PATH1="/etc/systemd/system/${FILE_NAME}"
PATH2="/usr/lib/systemd/system/${FILE_NAME}"

systemctl stop "$SERVICE_NAME"
systemctl disable "$SERVICE_NAME"

rm "$PATH1"
rm "$PATH2"

systemctl daemon-reload
systemctl reset-failed
