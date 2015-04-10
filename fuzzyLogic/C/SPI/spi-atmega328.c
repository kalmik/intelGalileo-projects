#include <avr\io.h>

int main()
{

//Ajusta o pino MISO (PB4) como saída
DDRB = _BV(PB4);

//bit SPE habilita o SPI
SPCR = _BV(SPE);

//Ajustando o pino D0, D1 e D2 como saída
DDRD = 0b00000111; 
PORTD = 0;

	while(1)
	{
		// Dados para serem enviados ao mestre
	     SPDR = 0b00010010;
		//Recebendo dados do mestre
	 	while (!(SPSR & (1<<SPIF)));
		PORTD = SPDR;
	}

}

