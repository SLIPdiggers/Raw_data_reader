byte data_array[256];

#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

populate_array(data_array, NUMITEMS(data_array));
display_frame(data_array, NUMITEMS(data_array));

}

void loop() {}



void populate_array(byte passed_array[], word array_size){
  for (int i=0; i<array_size; ++i){
    passed_array[i]=(random(256));
    //delay(2);
  }
}

void display_frame(byte passed_array[], word array_size){
  for (int i=0; i<array_size/8; ++i){
    byte data_row[8];
    int multiplier = i*8;
    
    for (int j=0; j<8; ++j){    //peels off rows of 8 bytes from data_array
      data_row[j] = data_array[j+multiplier]; 
    }
    
    if (i<10)Serial.print(' ');
    Serial.print(i);
    Serial.print(' ');
    display_chunk(data_row, NUMITEMS(data_row), 'b');
    display_chunk(data_row, NUMITEMS(data_row), 'h');
    display_chunk(data_row, NUMITEMS(data_row), 'a');
    Serial.println();
  }    
}

void display_chunk(byte istr[], word array_length, char display_mode){
  //display_mode: 'h'=hex, 'b'=byte, 'a'=ascii
  
  Serial.print(" ");
  //Serial.println(sizeof(istr)/sizeof(istr[0]));
  for (int i=0; i<array_length; ++i){
    //if((istr[i]<10 && display_mode=='b')||(istr[i]<16 && display_mode=='h'))Serial.print(' ');
    //if(istr[i]<100 && display_mode=='b')Serial.print(' ');
    switch (display_mode) {
      case 'h':
        if(istr[i]<16)Serial.print('0');
        Serial.print(istr[i], HEX);
        break;
      case 'a':
        if(istr[i]<33||istr[i]>126)Serial.print('.');
        else Serial.write(istr[i]);
        break;
      default:
        if(istr[i]<10)Serial.print(' ');
        if(istr[i]<100)Serial.print(' ');
        Serial.print(istr[i]);
        break;
      }
    Serial.print(' ');
  }
}
