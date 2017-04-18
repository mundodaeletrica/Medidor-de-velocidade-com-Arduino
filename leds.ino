

void inicia_leds(){
    pinMode(LED_AMARELO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
}


void led(int qual_led, int status){
    digitalWrite(qual_led, status);
}