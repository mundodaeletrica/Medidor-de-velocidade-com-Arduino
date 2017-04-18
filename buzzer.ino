



// inicializa o pino do buzzer
void inicia_buzzer(){
    pinMode(BUZZER, OUTPUT);   
}




void buzzer(unsigned char pwm){
  analogWrite(BUZZER, pwm);  
}