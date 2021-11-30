// Which pins points to the buttons, order of Red Green Blue
const int btnsRGB[3] = {5, 6, 7};
int currentLED = 0;

// Which pins points to the leds, order of Red Green Blue
const int ledsRGB[3] = {10, 9, 11};

// Potentiometer pin
int potPin = A0;

// Button & variable to control whether to change or save valueRGB
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

  // Initialize potentiometer
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

  // reset mode to automatically save state
  modeAdd = false;
}


// Update valueRGB and write change
void updateValue(int colour){

  // button needs pressed and to be in change mode to use pot. input
  if(modeAdd == true){

    valuePot = analogRead(potPin);

    //Scaling the potentiometer input to fit LED range
    int brightness = map(valuePot, 0, 1023, 0, 255);
    
    //potentiometer won't do a clean 0 so this works
    if(valuePot <10){
      brightness = 0;
      }

    valueRGB[colour] = brightness;

    // Actually update the value of corresponding pin
    analogWrite(ledsRGB[colour], valueRGB[colour]);
  }
}
