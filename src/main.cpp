/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "hal/bcm2835/Gpio.h"
#include "hal/hosted/Gpio.h"
#include "application/App.h"


int main(void) {

#if HOSTED
    hal::hosted::Gpio gpio;
#else
    hal::bcm2835::Gpio gpio;
#endif /* HOSTED */

    App app(gpio);
    if (app.init()) {
        app.run();
    }

    return 0;
}
