int f=150;
float dt=0;
unsigned long t=0, lt=0; 
int temp = 0;
float average=0;
float values[5];
void setup() {
  // initialize the serial communication:
  Serial.begin(19200);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  dt=(1000000.0/(float)f);
}
int i=0;
float signalecg=0;
float signalPPG=0;
void loop() {
  t=micros();
  
  if ((t-lt)>=dt) {
    
    signalecg=analogRead(A0);
    signalPPG=analogRead(A1);
    
    if(i<5){i=i+1;}else{
      if(i==5){
        average=(values[0]+values[1]+values[2]+values[3]+values[4])/5;
        i+=1;
      }else{
      average+=signalecg*1.0/5.0-values[0]/5.0;
      }
    }
    
    values[0]=values[1]; values[1]=values[2];values[2]=values[3]; values[3]=values[4];values[4]=signalecg;
    
    Serial.print((signalPPG)*10.0/1023);
    Serial.print(" , ");
    Serial.println(((average)/1023.0*5));
    
    lt=t;
  }
}
