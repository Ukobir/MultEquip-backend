
void shortCal() {
  mike.begin();
  for(int i = 0; i < 200; i++){
    calOffset += mike.read();
  }
  mike.end();
  calOffset =  calOffset/200;
}