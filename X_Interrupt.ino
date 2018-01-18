const int interruptA = D6;           // interruptA 0 在 gpio6 上
const int interruptB = D7;           // interruptA 0 在 gpio6 上

void interruptFnA(){
  Serial.println("A");
}
void interruptFnB(){
  Serial.println("B");
}
