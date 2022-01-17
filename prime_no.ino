int i = 1;
int c = 0;
int count = 1;

void setup() {
  Serial.begin(115200);
  delay (500);
  
while (count <= 30) {
  for (c = 2;c < i; c++)
  {
    if (i % c == 0)
           break;
  }
  if (c == i)
  { 
    Serial.print( count);
    Serial.print (":");
    Serial.println(i);
    count++;
  }
  i++;
 }
}
  
  
