// define the GPIO connected with Relays
#define RelayPin1 3//D3

float calibration_value = 21.34;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
float ph_act;

void automation()
{
    if (ph_act > 7)
    {
      digitalWrite(RelayPin1, LOW); // turn off relay 1
      Serial.println("Pump OFF");
    }

    else if (ph_act < 6)
    {
      digitalWrite(RelayPin1, HIGH); // turn on relay 1
      Serial.println("Pump ON");
    }
}

void setup()
{
  Serial.begin(9600); /* Define baud rate for serial communication */
  
  //Relay Pin
  pinMode(RelayPin1, OUTPUT);

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, LOW);

  Serial.println("Simple pH Sense");
}

void loop()
{
  for(int i=0;i<10;i++) 
  { 
    buffer_arr[i]=analogRead(A0);
    delay(30);
  }
  
  for(int i=0;i<9;i++)
  {
    for(int j=i+1;j<10;j++)
    {
      if(buffer_arr[i]>buffer_arr[j])
      {
        temp=buffer_arr[i];
        buffer_arr[i]=buffer_arr[j];
        buffer_arr[j]=temp;
      }
    }
  }
 
  avgval=0;
 
  for(int i=2;i<8;i++)
 
  avgval+=buffer_arr[i];
  float volt=(float)avgval*5.0/1024/6;
  ph_act = -5.70 * volt + calibration_value;

  Serial.println("pH Level:");
  Serial.print(ph_act);

  automation();
}
