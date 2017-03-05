// time to take samples to average
#define SAMPLE_TIME 1
#define SAMPLES (SAMPLE_TIME*50)

volatile unsigned long oldTime = 0, newTime = 0;
volatile unsigned long period[SAMPLES + 1];
volatile boolean flag = false;
volatile boolean start = false;
volatile uint8_t period_index = 0;
float frequency = 0;
unsigned long period_sum = 0;

void interrupt(){
  if(!flag){
    newTime = micros();
    // ignore overflows
    if(oldTime > newTime){
      // do nowt
    }
    // only do this once the interrupts have started
    else if(start){
      period[period_index] = newTime - oldTime;
      period_index++;
      if(period_index == SAMPLES){
        flag = true;
      }
    }
    else{
      start = true;
    }
    oldTime = newTime;
  }
}

void setup() {
  Serial.begin(115200);
  oldTime = micros();
  attachInterrupt(digitalPinToInterrupt(2), interrupt, RISING);
}

void loop() {
  if(flag){
    for(int n = 0; n < SAMPLES; n++){
      period_sum += period[n];
    }
    frequency = 50000000/(float)period_sum;
    Serial.println(frequency);
    period_index = 0;
    period_sum = 0;
    flag = false;
  }
}



