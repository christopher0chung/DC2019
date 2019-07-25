
loop() {

	buttons.update();
	pots.update();
	linksUpdate();


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