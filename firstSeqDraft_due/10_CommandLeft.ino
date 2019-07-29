//struct noteExt {
//  byte note;
//  unsigned long noteStartTime;
//  bool lengthMode;
//};
//

int seq[4] = {4, 14, 20, 22};

struct toggler {

	bool tog;
	unsigned int interval;
	unsigned long previousMillis;
	int step;

	void autoTog() {

 		if (millis() - previousMillis >= interval) {

   			previousMillis = millis();

   			nodes[seq[step]].state = 0;
   			leds.drawPixel(nodes[seq[step]].ledx, nodes[seq[step]].ledy, LOW);
   			
   			step++;
   			step = step % 4;
   			
   			nodes[seq[step]].state = 1;
   			leds.drawPixel(nodes[seq[step]].ledx, nodes[seq[step]].ledy, HIGH);

 		}
	}
};

toggler tog1 = {0, 400};


// void autoTog() {
//  if (millis() - previousMillis >= interval) {
//    previousMillis = millis();
//    tog = !tog;
//    nodes[20].state = tog;
//    leds.drawPixel(nodes[20].ledx, nodes[20].ledy, tog);
//  }
// }
//
//void commandLeft() {
//  
//  for (int i = 0; i < 25; i++) {
//    if (buttons.hasChanged(piano[i].index)) {
//      
//      if (buttons.vals[piano[i].index] == 1) {
//
//        if (piano[i].state == 1) {
//          usbMIDI.sendNoteOff(piano[i].note, 0, 1);
//        }
//
//        if (lengthAdjust[0] > 15) {
//          if (piano[i].lengthMode == 1) {
//            usbMIDI.sendNoteOff(piano[i].note, 0, 1);
//          }
//          piano[i].noteStartTime = millis();
//          piano[i].lengthMode = 1;
//        }
//
//        piano[i].note = 48 + i + pitchAdjust[0];
//        int vel = velAdjust[0];
//        usbMIDI.sendNoteOn(piano[i].note, vel, 1);
//        leds.drawPixel(piano[i].ledx, piano[i].ledy, 1);
//      }
//
//      else {
//        if (piano[i].state == 0 && piano[i].lengthMode == 0) {
//          usbMIDI.sendNoteOff(piano[i].note, 0, 1);
//          leds.drawPixel(piano[i].ledx, piano[i].ledy, 0);
//        }
//
//
//      }
//      buttons.updateLastVals(piano[i].index);
//    }
//
//    piano[i].lengthMode = checkNoteEndTime(piano[i], lengthAdjust[0]);
//  }
//
//  for (int i = 0; i < 25; i++) {
//    if (piano[i].state != piano[i].lastState) {
//      if (piano[i].state == 1) {
//        if (buttons.vals[piano[i].index] == 1) {
//          usbMIDI.sendNoteOff(piano[i].note, 0, 1);
//        }
//        piano[i].note = 48 + i + pitchAdjust[0];
//        int vel = velAdjust[0];
//        usbMIDI.sendNoteOn(piano[i].note, vel, 1);
//        leds.drawPixel(piano[i].ledx, piano[i].ledy, 1);
//      }
//      else {
//        if (buttons.vals[piano[i].index] == 0) {
//          usbMIDI.sendNoteOff(piano[i].note, 0, 1);
//          leds.drawPixel(piano[i].ledx, piano[i].ledy, 0);
//        }
//      }
//      piano[i].lastState = piano[i].state;
//    }
//  }
//}
//
//bool checkNoteEndTime(struct node input, unsigned int noteLength) {
//  if (node.lengthMode == 1) {
//    if (node.state == 0) {
//      if (millis() - node.noteStartTime > noteLength && buttons.vals[node.index] != 1) {
//        usbMIDI.sendNoteOff(node.note, 0, 1);
//        leds.drawPixel(node.ledx, node.ledy, 0);
//        return 0;
//      }
//    }
//    return 1;
//  } 
//  else {
//    return 0;
//  }
//}
