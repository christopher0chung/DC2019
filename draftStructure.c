
loop() {

	buttons.update();
	pots.update();
	linkStateUpdate();


	if (patchMode) {

		for (int i=0; i<304; i++) {

			if (buttons.risingEdge(i)) {

				linkInputCheck(i);
				leds.drawPixel(nodes[i].ledx, nodes[i].ledy, 1);

			}

	}

	if (playMode) {



	}
}

  //         if (isNodeOutput(i)) 

  //           if (newLinkBuffer.sender == 999 && buttons.risingEdge(i)) { 
  //             leds.fillScreen(0);    
  //             newLinkBuffer.sender == i;
  //           }
  //           else if (newLinkBuffer.sender == i && buttons.fallingEdge(i)) {  
  //             newLinkBuffer.sender == 999;
  //           }
            
  //         }





  //     }
      
  //       if (isNodeInput(i)) {
  //         if (newLinkBuffer.receiver == 999 && buttons.vals[i] == 1) {       // if reciever is empty, store new input based on first held input
  //           newLinkBuffer.receiver == i;
  //         }
  //         else if (newLinkBuffer.receiver == i && buttons.vals[i] == 0) {    // if reciever is filled and button is released, clear it
  //           newLinkBuffer.receiver == 999;
  //         }
  //       }
  //       else 
      
  //     if (!readyForNextFlag && simultaneousHold < 2)
  //       readyForNextFlag = true;
  //   }
  // }
  // else if (currentGlobalMode == EDITPATCH) {
  //   //TBD
  // }   
  // else {
  //   clearNewLinkBuffer();
  // }