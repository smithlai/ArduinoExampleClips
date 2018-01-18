void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
  wifi_connect();
  wifi_server_init();

  pinMode(interruptA, INPUT);
  pinMode(interruptB, INPUT);
  attachInterrupt(interruptA, interruptFnA, FALLING);
  attachInterrupt(interruptB, interruptFnB, FALLING);
}
