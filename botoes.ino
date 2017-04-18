


void inicia_teclas(){
  pinMode(BOTOES, INPUT);
}



int tecla_pressionada(){
    // Realiza a leitura do valor analógico da tecla
    int valor = analogRead(BOTOES);
    
    // Cada tecla gera um valor de leitura no pino analógico.
    // Veja na documentação do shield a tabela para quais valores representam cada tecla.
    // Como o código é didático, é feito da maneira mais simples possível de entender, mesmo que não seja a mais eficiente.

    if(valor > 897) return SEM_TECLA;
    if(valor > 630) return TECLA_SEL;
    if(valor > 408) return TECLA_ESQ;
    if(valor > 230) return TECLA_BAIXO;
    if(valor > 69) return TECLA_CIMA;
    return TECLA_DIR;    
}
