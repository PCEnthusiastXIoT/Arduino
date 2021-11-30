// Which pins points to the buttons, order of Red Green Blue
const int btnsRGB[3] = {5, 6, 7};
int currentLED = 0;

// Which pins points to the leds, order of Red Green Blue
const int ledsRGB[3] = {10, 9, 11};

// Potentiometer pin
int potPin = A0;

// Button & variable to control wether to subtract or add to valueRGB
const int btnMode = 13;
bool modeAdd = false;


// To save current strength to display on RGB led
int valueRGB[3] = {0, 0, 0};

// Measure and store potentiometer value
int valuePot = 0;

void setup() {
  Serial.begin(9600);

  // Initialize buttons
  for(int i = 0; i < 2; i++){
    pinMode(btnsRGB[i], INPUT);
    analogWrite(btnsRGB[i], 0);
  }

  // Initialize led outputs
  for(int i = 0; i < 2; i++){
    pinMode(ledsRGB[i], INPUT);
  }

  // Initialize mode button
  pinMode(btnMode, INPUT);

  pinMode(potPin, INPUT);
}

void loop() {
    // If red button was pressed
  if(digitalRead(btnsRGB[0]) == HIGH){
    setLED(0);
  }
  
  // If green button was pressed
  if(digitalRead(btnsRGB[1]) == HIGH){
    setLED(1);
  }

  // If blue button was pressed
  if(digitalRead(btnsRGB[2]) == HIGH){
    setLED(2);
  }

  // If switch mode button was pressed
  if(digitalRead(btnMode) == HIGH){
    if(modeAdd == true){
      modeAdd = false;
    }else{
      modeAdd = true;
    }

    // Ugly way to stop button from unintentional press
    delay(1000);
  }

  //potentiometer turn detection
  if(analogRead(potPin)){
    updateValue(currentLED);
    }

  // no chill
  delay(30);
}

//Change current active LED
void setLED(int color){
  currentLED = color;
  modeAdd = false;
}


// Update valueRGB and write change
void updateValue(int colour){

  // Add or subtract depending on mode
  if(modeAdd == true){

    valuePot = analogRead(potPin);
    //Serial.print(valuePot);
    int brightness = map(valuePot, 10, 1023, 0, 255);
    // Don't let the value be more than 255
//    if(valueRGB[colour] >= 255){
//      valueRGB[colour] = 255;
//    }  else {
//
//      // Don't let the value be less than 0
//      if(valueRGB[colour] <= 0){
//        valueRGB[colour] = 0;
//      }
////      } else {
////        valueRGB[colour]--;
////      }
//    }
    if(valuePot <10){
      brightness = 0;
      }
    valueRGB[colour] = brightness;

    // Actually update the value of corresponding pin
    analogWrite(ledsRGB[colour], valueRGB[colour]);
  }
}
