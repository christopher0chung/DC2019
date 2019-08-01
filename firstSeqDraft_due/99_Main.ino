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

    comCtrlUpdate();

    // CHECK FOR BUTTON PRESSES ------------------------------------------------------



    /* Black Panel Nodes */
    userModeSelect();
    comCtrlSelect();

    /* White Panel Nodes */

    if (userMode == 2) 
        commandLeftButtons();
    else if (userMode == 0 || userMode == 1)
        patch();
    

    leds.drawPixel(nodes[i].ledx, nodes[i].ledy, nodes[i].state);
    


    // MODULE LOGIC ------------------------------------------------------------------

    // testButtons();
    // testPots();
    tog.autoTog();
        
    // UPDATES AND OUTPUTS -----------------------------------------------------------

    buttons.updateLastVals(); 
    pots.updateLastVals();

    if (userMode == 0) 
        ledsAllLinks(); 

    displayLinks();
    
    leds.write();

}


