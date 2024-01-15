#include <SD.h> //Load SD library
#include <TMRpcm.h> //Load TMRpcm library for audio playing
#include <Wire.h>
int chipSelect = 10; //chip select pin for the MicroSD Card Adapter
File file; // file object that is used to read and write data
int svar; //result
const int numValuesToRead = 5; //number of values for history
uint8_t lastValues[numValuesToRead];
int before;
int resultat1;
int resultat2;
int resultat3;
int x[5];
TMRpcm tmrpcm;

void setup() {
  Serial.begin(9600); // start serial connection to print out debug messages and data
  
  pinMode(chipSelect, OUTPUT); // chip select pin must be set to OUTPUT mode
  if (!SD.begin(chipSelect)) { // Initialize SD card
    Serial.println("Could not initialize SD card."); // if return value is false, something went wrong.
  }
  pinMode(9,OUTPUT);
  tmrpcm.speakerPin=9;
  tmrpcm.volume(9);
  tmrpcm.play("xp.wav");
  delay(5000);
  if(tmrpcm.isPlaying()== true){
  Serial.println("spelar");
  }

  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  

  Serial.println("Creating example.txt...");
  File myFile;
  file = SD.open("FILE.txt", FILE_WRITE);
  file.close();
  Wire.begin();
  SD.begin();
  

  //readValuesFromFile();
}
//function to read the values as string to put them into an array
int splitString(const String &input, char separator, String *output, int maxValues) {
  int itemCount = 0;
  int start = 0;
  int end = input.indexOf(separator);

  while (end >= 0 && itemCount < maxValues) {
    output[itemCount++] = input.substring(start, end);
    start = end + 1;
    end = input.indexOf(separator, start);
  }

  // Add the last part of the string
  if (itemCount < maxValues) {
    output[itemCount++] = input.substring(start);
  }

  return itemCount;
}
//checking if history or measure is called
void loop() {
  //Serial.println("H");
  if (digitalRead(4) == HIGH   ) { // generate random number between 0 and 9
    file = SD.open("FILE.txt", FILE_WRITE); // open "file.txt" to write data
    //Wire.beginTransmission(9);
    //tmrpcm.play("whatis.wav");
    //tmrpcm.stopPlayback();
    Serial.println("Startar");
    delay(1000);
    before = analogRead(A2);

    tone(tmrpcm.speakerPin, 490, 400);  // Play the specified note
    delay(400 + 50);  // Add a short delay to avoid cutting off the note abruptly
    noTone(tmrpcm.speakerPin);
    delay(3000);
    
    resultat1 = analogRead(A2);
    delay(1000);
    resultat2 = analogRead(A2);
    delay(1000);
    resultat3 = analogRead(A2);
    tone(tmrpcm.speakerPin, 490, 400);  // Play the specified note
    delay(400 + 50);  // Add a short delay to avoid cutting off the note abruptly
    noTone(tmrpcm.speakerPin);  // Stop playing the note
    svar = (resultat1 + resultat2 + resultat3)/3-before+20;
   
    delay(1000);
    if (svar <30){
      tmrpcm.play("spik.wav");
      
    }
    else if (svar < 1500){
      tmrpcm.play("billl.wav");
    }
    else if (svar> 150){
      tmrpcm.play("plask.wav");
    }
    //tmrpcm.stopPlayback();
    //Wire.write(svar);
    file.print('\n');
    file.print(svar); // write number to file
    //Wire.endTransmission();
    file.close();
    Serial.print("Wrote number: "); // debug output: show written number in serial monitor
    Serial.println(svar);
    //readValuesFromFile(); // close file
    delay(3000);
    
    
    }
    else{
      file.close();
    }
  file.close();
  if (digitalRead(5) == HIGH) {
  file = SD.open("FILE.txt", FILE_READ); // open "file.txt" to read data
  if (file) {
    // Read the entire file into a buffer
    String fileContent = file.readString();
    Serial.println("Work");
    // Close the file
    file.close();

    // Split the content into lines
    String lines[fileContent.length()]; // Dynamic array based on file length
    int numLines = splitString(fileContent, '\n', lines, fileContent.length());

    // Initialize a dynamic array to store all values
    int* allValues = new int[numLines];

    // Process each line and convert it to an integer
    for (int i = 0; i < numLines; ++i) {
      allValues[i] = lines[i].toInt();

      // Print detailed information to Serial for debugging
      Serial.print("Read value as integer: ");
      Serial.println(allValues[i]);
      Serial.println("---");
    }

    // Reverse the order of allValues array
    for (int i = 0; i < numLines / 2; ++i) {
      int temp = allValues[i];
      allValues[i] = allValues[numLines - i - 1];
      allValues[numLines - i - 1] = temp;
    }

    // Send the first 5 reversed values via I2C
    Wire.beginTransmission(9);
    for (int j = 0; j < min(numLines, numValuesToRead); ++j) {
      Wire.write(allValues[j]);
      Serial.println(allValues[j]);
    }
    Wire.endTransmission();

    Serial.println(); // Print a newline for better readability in the serial monitor
  }
  else{Serial.print("error");}
  }


  file.close();



  //Serial.println(analogRead(A2));












    //Serial.println(analogRead(A2));
  
  
  delay(5); // wait for 5000ms
  
}

//a file reader to examine any fault
void readValuesFromFile() {
  file = SD.open("FILE.txt", FILE_READ);

  if (file) {
    Serial.println("Reading values from file:");

    // Read each line from the file and print it
    for (int i = 0; i < file.size()/2 ; ++i) {
      String line = file.readStringUntil('\n');
      Serial.println(line);
    }

    file.close();
  } else {
    Serial.println("Error opening file.");
  }
}
