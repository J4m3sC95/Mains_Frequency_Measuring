uint16_t data[1001];

void setup() {
  Serial.begin(115200);
  for(int n = 0; n < 1000; n++){
    data[n] = analogRead(A0);
  }

  for(int n = 0; n < 1000; n++){
    Serial.println(data[n]);
  }
  
}

void loop() {
  
}
