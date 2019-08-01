void setup() {

    potsInit();
    ledsInit();
    screenInit();
    linksInit();

    nodes[299].state = 1;
    screenPrint(screenUserMode[userMode]);
}

void loop() {

    // UPDATE STATES -----------------------------------------------------------------

    /* Controller Messages */ 
    buttons.update();
    pots.update();

    /* Links Messages */
    linkStateUpdate();


    // TEST ZONE ---------------------------------------------------------------------

    // testButtons();
    // testPots();
    tog.autoTog();


    // CHECK FOR BUTTON PRESSES ------------------------------------------------------

    for (int i = 0; i < buttonsMax; i++) {

        leds.drawPixel(nodes[i].ledx, nodes[i].ledy, nodes[i].state);

        if (buttons.hasChanged(i)) {

            if (userMode == 2) {

            }
            else if (userMode == 0 || userMode == 1)
                patch(i);

            userModeSelect();
            comCtrlSelect();

        }
    }

    
    // UPDATES AND OUTPUTS -----------------------------------------------------------

    buttons.updateLastVals(); 

    if (userMode == 0) 
        ledsAllLinks(); 

    displayLinks();
    
    leds.write();

}


