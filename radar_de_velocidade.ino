/*   
 * Radar de velocidade usando célular solar e conversor AD.
 * Criado para demonstração da utilização do Arduino em vídeos do canal 
 * Mundo da Elétrica no Youtube.
 *  
 * Este software tem finalidade didática e demonstrativa, e portanto 
 * aspectos relacionados a eficiência NÃO são o objetivo. 
 * O progama é feito da maneira mais simples possível de entender e exigindo
 * apenas o conhecimento essencialmente necessário.
 *
 * Conheça o canal Mundo da Elétrica utilizando o link abaixo:
 * http://www.youtube.com/subscription_center?add_user=MundoDaEletrica
 *  
 * Autor: Alex Teixeira Benfica 
 * https://www.linkedin.com/in/alexbenfica   
 * 
 * Shield de interface (botões, leds e buzzer), conversor ADC e display:
 * https://www.circuitar.com.br/nanoshields/ * 
 * 
*/


// inclui os outros arquivos com códigos relativos a botoes, leds e buzzer
#include "botoes.h"
#include "leds.h"
#include "buzzer.h"

// https://www.arduino.cc/en/Reference/StringConstructor
// tem algumas funções básicas para lidar com texto
#include <String.h>

// permite a escrita em display utilizando o shield da Circuitar
#include "Nanoshield_LCD.h"

// Objeto lcd
Nanoshield_LCD lcd;

#include <Wire.h>
#include <Nanoshield_ADC.h>
Nanoshield_ADC adc;    

#define PINO_TESTE  A0
#define LED_AMARELO A1
#define LED_VERDE   A2
#define CANAL_ADC 3
#define N_MEDIDAS 100

int diferenca;
int medida_anterior = 0;
int medida_atual;

int n_conf = 5;
int descendo = 0;
int subindo = 0;

int aguardando = 0;


const float distancia = 10.0;
long tempo;
float velocidade;

int modo_radar = 1;



// Função executada continuamente enquanto o Arduino está ligado.
void loop() {


  if(modo_radar){
  
    if(adc.conversionDone()){
  
      medida_atual = adc.readNext();
      diferenca = medida_atual - medida_anterior;
      medida_anterior = medida_atual;
  
  
      if(abs(diferenca) >= 20){
        // detecta o vale
        if(diferenca < 0){
          descendo++;
          if(subindo >= n_conf){        
            subindo = 0;   
          }
        }
        else{
          subindo++;
          if(descendo >= n_conf){
            descendo = 0;
            pulsa_teste();
  
            if(aguardando){
              aguardando = 0;
              
              // Comeca a contar o tempo inicial
              tempo = millis();
            }
            else{
  
              // Calcula o tempo entre pulsos                    
              tempo = millis() - tempo;
              
              // Evita divisal por zero...
              if(tempo>0){                        
                velocidade = (distancia / tempo) * 100;
                
                lcd.setCursor(7, 0);
                lcd.print(tempo,DEC);
                lcd.print(" ms ");
                
                lcd.setCursor(7, 1);
                lcd.print(velocidade,2);
                lcd.print(" m/s  ");
  
                if(velocidade > 10){
                  digitalWrite(LED_AMARELO, 1);                             
                  tone(BUZZER,255);                
                  delay(800);                
                }
                else{
                  digitalWrite(LED_VERDE, 1);      
                  tone(BUZZER,155);                          
                }              
  
                delay(50);
                noTone(BUZZER);    
                digitalWrite(LED_VERDE, 0);                                           
                digitalWrite(LED_AMARELO, 0);                                         
              }
                          
              aguardando = 1;
            }          
          }
  
        }
      }
      
      
  
      // Tempo maximo de 2 segundos entre pulsos... ou zera e espera pelo primeiro pulso de novo...
      if(millis() - tempo > 2500){
        aguardando = 1;
      }
  
      if(subindo > 200){
        subindo = 0;
        descendo = 0;     
      }    
    }  
  }

  else{    
    lcd.clear();
    lcd.print(adc.readVoltage(CANAL_ADC));    
    lcd.print("V ");
    lcd.print(adc.readNext());
    delay(250);
  }

  
}





void pulsa_teste(){   
  digitalWrite(PINO_TESTE, 1);
  digitalWrite(PINO_TESTE, 0);           
}




// Chama as funções de inicialização necessárias a cada elemento utilizado no projeto.
// Roda apenas 1 vez na inicialização.
void setup() {    
    // Diversas inicializações de hardware e bibliotecas
    inicia_teclas();    
    inicia_leds();    
    inicia_buzzer();

    pinMode(PINO_TESTE,  OUTPUT); 
    pinMode(LED_AMARELO, OUTPUT); 
    pinMode(LED_VERDE,   OUTPUT); 

    adc.begin();
    adc.setGain(GAIN_TWOTHIRDS);    
    adc.setSampleRate(860);
    adc.setContinuous(true);
    adc.readADC_SingleEnded(CANAL_ADC);

    lcd.begin();  
    lcd.clear();    

    // Se inicializar com o painel solar escuro, modo radar desligado.    
    lcd.print(adc.readNext());
    delay(500);
    modo_radar = adc.readNext() > 2000;

    if(modo_radar){
      lcd.setCursor(0, 0);
      lcd.print("Tempo: ");
      
      lcd.setCursor(0, 1);
      lcd.print("Veloc.:");
    }
}
