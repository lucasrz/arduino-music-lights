// const int ledPin =  9;     
// const int analogInPin = A2; 

// int tempo;
// int sensorValue = 0;


// void setup() {
//   Serial.begin(9600);
// }

// void loop()
// {
//   sensorValue = analogRead(analogInPin);
  
//   Serial.print("Sensor = ");
//   Serial.print(sensorValue);
//   Serial.print("\t Tempo = ");
//   Serial.println(tempo);
  
//   tempo = map(sensorValue, 0, 1023, 40, 210); //map in the range of 40 to 210 BPM

  
//   float bpm = (1000/tempo)*60/2; //algorithm to convert tempo into BPM
//   Serial.print("\t Bom = ");
//   Serial.println(bpm);

// }