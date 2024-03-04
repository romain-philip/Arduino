const int buttonPin = 4;  // le numéro de la broche du bouton-poussoir
const int ledPin = 2;    // le numéro de la broche de la LED

// variables qui vont changer :
int buttonState = 0;  // variable pour lire l'état du bouton-poussoir
int lastButtonState = HIGH;  // variable pour mémoriser l'état précédent du bouton-poussoir
unsigned long lastDebounceTime = 0;  // la dernière fois où le bouton a été lu
unsigned long debounceDelay = 50;    // le temps de rebondissement du bouton en millisecondes

int clickCounter = 0;  // compteur du nombre d'appuis sur le bouton
bool isLongPress = false;  // indicateur d'appui prolongé

void setup() {
  // initialise la broche de la LED en tant que sortie :
  pinMode(ledPin, OUTPUT);
  // initialise la broche du bouton-poussoir en tant qu'entrée avec résistance de tirage activée :
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // lis l'état du bouton-poussoir :
  int reading = digitalRead(buttonPin);

  // vérifie le rebondissement du bouton :
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // vérifie si le temps de rebondissement a expiré :
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // met à jour l'état du bouton-poussoir si changement détecté :
    if (reading != buttonState) {
      buttonState = reading;

      // incrémente le compteur si le bouton est enfoncé :
      if (buttonState == LOW) {
        clickCounter++;

        // remet à zéro le compteur si le nombre d'appuis dépasse 3 :
        if (clickCounter > 3) {
          clickCounter = 0;
        }

        // vérifie le nombre d'appuis pour déterminer le comportement :
        if (clickCounter == 1) {
          // En appuyant une fois sur le bouton, la LED reste allumée
          digitalWrite(ledPin, LOW);
        } else if (clickCounter == 3) {
          // En appuyant trois fois sur le bouton, la LED clignote
          blinkLED();
        }
      } else {
        // Réinitialise l'indicateur d'appui prolongé lors du relâchement du bouton :
        isLongPress = false;
      }
    }
  }

  // vérifie l'appui prolongé sur le bouton :
  if (buttonState == LOW && (millis() - lastDebounceTime) > 1000) {
    // En cas d'appui prolongé sur le bouton, la LED s'éteint
    isLongPress = true;
    digitalWrite(ledPin, HIGH);
  } else if (isLongPress && buttonState == HIGH) {
    // Réinitialise l'indicateur d'appui prolongé lors du relâchement du bouton :
    isLongPress = false;
  }

  // mémorise l'état actuel du bouton-poussoir :
  lastButtonState = reading;
}

void blinkLED() {
  // Fonction pour faire clignoter la LED
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}

