#define BUZZER_PIN 25 // Define el pin del zumbador
//Menu Theme
#define NOTE_Do5 523.25 
#define NOTE_Si4 493.88 
#define NOTE_ReMib5 622.25
#define NOTE_Sol4 392.00 
#define NOTE_LaSib4 466.16 
//Game Theme
#define NOTE_Fa3 174.61
#define NOTE_Sol3 196.00
#define NOTE_Mi3 164.81
#define NOTE_Do4 261.62
#define NOTE_Si3 246.94
#define NOTE_DoReb4 277.18
#define NOTE_Re4 293.66
#define NOTE_La3 220.00
#define NOTE_Mi4 329.62
#define NOTE_Fa4 349.22


uint8_t Juego = 0;

const int arribaPin = 13; 
const int abajoPin = 12;
const int izquierdaPin = 14;
const int derechaPin = 27;
const int accionPin = 26;

const unsigned long debounceDelay = 50; 
const unsigned long serialInterval = 100; // 1 second

int arribaState = HIGH; 
int abajoState = HIGH;
int izquierdaState = HIGH; 
int derechaState = HIGH;
int accionState = HIGH;

int lastArribaState = HIGH;
int lastAbajoState = HIGH;
int lastIzquierdaState = HIGH;
int lastDerechaState = HIGH;
int lastAccionState = HIGH;

unsigned long lastDebounceTime1 = 0; 
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0; 
unsigned long lastDebounceTime4 = 0;
unsigned long lastDebounceTime5 = 0;

unsigned long lastSerialSendTime1 = 0;
unsigned long lastSerialSendTime2 = 0;
unsigned long lastSerialSendTime3 = 0;
unsigned long lastSerialSendTime4 = 0;
unsigned long lastSerialSendTime5 = 0;

void setup() {

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(arribaPin, INPUT_PULLUP);
  pinMode(abajoPin, INPUT_PULLUP);
  pinMode(izquierdaPin, INPUT_PULLUP);
  pinMode(derechaPin, INPUT_PULLUP);
  pinMode(accionPin, INPUT_PULLUP);
  Serial.begin(9600);

 

}

void loop() {
  int reading1 = digitalRead(arribaPin);
  int reading2 = digitalRead(abajoPin);
  int reading3 = digitalRead(izquierdaPin);
  int reading4 = digitalRead(derechaPin);
  int reading5 = digitalRead(accionPin);


  if (reading1 != lastArribaState) {
    lastDebounceTime1 = millis(); 
  }
  if (reading2 != lastAbajoState) {
    lastDebounceTime2 = millis(); 
  }
  if (reading3 != lastIzquierdaState) {
    lastDebounceTime3 = millis(); 
  }
  if (reading4 != lastDerechaState) {
    lastDebounceTime4 = millis(); 
  }
  if (reading5 != lastAccionState) {
    lastDebounceTime5 = millis(); 
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != arribaState) {
      arribaState = reading1;
      if (arribaState == LOW) {
        lastSerialSendTime1 = millis(); 
        Serial.write(10);
      } else if (lastArribaState == LOW) {
        Serial.write(01); 
      }
    }
  }
  
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != abajoState) {
      abajoState = reading2;
      if (abajoState == LOW) {
        lastSerialSendTime2 = millis();
        Serial.write(20);
      } else if (lastAbajoState == LOW) {
        Serial.write(02); 
      }
    }
  }
  
  if ((millis() - lastDebounceTime3) > debounceDelay) {
    if (reading3 != izquierdaState) {
      izquierdaState = reading3;
      if (izquierdaState == LOW) {
        lastSerialSendTime3 = millis(); 
        Serial.write(30);
      } else if (lastIzquierdaState == LOW) {
        Serial.write(03); 
      }
    }
  }
  
  if ((millis() - lastDebounceTime4) > debounceDelay) {
    if (reading4 != derechaState) {
      derechaState = reading4;
      if (derechaState == LOW) {
        lastSerialSendTime4 = millis(); 
        Serial.write(40);
      } else if (lastDerechaState == LOW) {
        Serial.write(04); 
      }
    }
  }

  if ((millis() - lastDebounceTime5) > debounceDelay) {
    if (reading5 != accionState) {
      accionState = reading5;
      if (accionState == LOW) {
        delay(1000);
        Juego = 1;
        lastSerialSendTime5 = millis();
        Serial.write(50);
        Serial.println(Juego);
      } else if (lastAccionState == LOW) {
        Serial.write(05); 
        
      }
    }
  }

  // Chequear si volvemos a enviar un serial
  if (arribaState == LOW && (millis() - lastSerialSendTime1) >= serialInterval) {
    Serial.write(10);
    lastSerialSendTime1 = millis();
  }
  if (abajoState == LOW && (millis() - lastSerialSendTime2) >= serialInterval) {
    Serial.write(20);
    lastSerialSendTime2 = millis();
  }
  if (izquierdaState == LOW && (millis() - lastSerialSendTime3) >= serialInterval) {
    Serial.write(30);
    lastSerialSendTime3 = millis();
  }
  if (derechaState == LOW && (millis() - lastSerialSendTime4) >= serialInterval) {
    Serial.write(40);
    lastSerialSendTime4 = millis();
  }
  if (accionState == LOW && (millis() - lastSerialSendTime5) >= serialInterval) {
    Serial.write(50);
    lastSerialSendTime5 = millis();
  }

  lastArribaState = reading1;
  lastAbajoState = reading2;
  lastIzquierdaState = reading3;
  lastDerechaState = reading4;
  lastAccionState = reading5;

  
  
  if (Juego == 0){
    int melody []= {NOTE_Do5, 0,NOTE_Do5, NOTE_Do5, NOTE_Do5, NOTE_ReMib5, NOTE_Do5, NOTE_Sol4, NOTE_LaSib4, NOTE_Sol4, NOTE_LaSib4};
    int noteDurations []= {4,6,4,6,8,2,4,10,10,10,10};

    for (int x = 0; x < sizeof(melody) / sizeof(melody[0]); x++) {
      int noteDuration = 1000 / noteDurations[x];
      tone(BUZZER_PIN, melody[x], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.20;
      delay(pauseBetweenNotes);
      noTone(BUZZER_PIN);
   
    }
    delay(200);



  }
  

  else if(Juego == 1){
    int melody []= {
      NOTE_Sol3, NOTE_Mi3, NOTE_Fa3, NOTE_Sol3, 0, NOTE_Do4, NOTE_Si3, NOTE_Do4, NOTE_Si3, NOTE_Do4, NOTE_Sol3, NOTE_Mi3, NOTE_Fa3, NOTE_Sol3, 0, NOTE_Do4, NOTE_Si3, NOTE_Do4, NOTE_Si3, NOTE_Do4,
      NOTE_La3, NOTE_Fa3, NOTE_Sol3, NOTE_La3, 0, NOTE_Re4, NOTE_DoReb4, NOTE_Re4, NOTE_DoReb4, NOTE_Re4, NOTE_La3, NOTE_Fa3, NOTE_Sol3, NOTE_La3, 0, NOTE_Re4, NOTE_DoReb4, NOTE_Re4, NOTE_DoReb4, NOTE_Re4,
      NOTE_Si3, NOTE_Sol3, NOTE_La3, NOTE_Si3, 0, NOTE_Fa4, NOTE_Mi4, NOTE_Fa4, NOTE_Mi4, NOTE_Fa4, NOTE_Si3, NOTE_Sol3, NOTE_La3, NOTE_Si3, 0, NOTE_Fa4, NOTE_Mi4, NOTE_Fa4, NOTE_Mi4, NOTE_Fa4
    };
    int noteDurations []= {
      6,12,6,12,4,12,12,12,12,12,6,10,6,12,4,12,12,12,12,12,
      6,10,6,12,4,10,12,12,12,12,6,12,6,12,4,12,12,12,12,12,
      6,10,6,12,4,12,12,12,12,12,6,12,6,12,4,12,12,12,12,12
    };

    for (int x = 0; x < sizeof(melody) / sizeof(melody[0]); x++) {
      int noteDuration = 1000 / noteDurations[x];
      tone(BUZZER_PIN, melody[x], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(BUZZER_PIN);
   
    }
    delay(200);
  }

  


  
 
}

