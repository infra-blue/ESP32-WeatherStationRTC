#include <Arduino.h>

#include "Beep.h"

void beep_sound() {
  /**
   * @brief BEEP SOUND
   * generates a beep sound with the buzzer
   */

  int beep[] = {8156, 0, 8156};

  for (int thisNote = 0; thisNote < (sizeof(beep) / sizeof(beep[0])); thisNote++) {
    tone(buzzer, beep[thisNote], 110);
    noTone(buzzer);
  }
}
