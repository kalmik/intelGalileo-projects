#include "mraa.h"

int main(){
	mraa_spi_context spi;
	spi = mraa_spi_init(0);
	mraa_spi_frequency(spi,4000000);
	unsigned int response = 0;
	printf("Hello, SPI initialised\n");
	uint8_t data[] = { 0x00, 100 };
	int recv;
	uint8_t byte = 0x10;

	mraa_gpio_context cs1;
    cs1 = mraa_gpio_init(8);
    mraa_gpio_dir(cs1, MRAA_GPIO_OUT);
    mraa_gpio_write(cs1,1);

    mraa_gpio_context cs2;
    cs2 = mraa_gpio_init(9);
    mraa_gpio_dir(cs2, MRAA_GPIO_OUT);
    mraa_gpio_write(cs2,1);
	while(1){
		mraa_gpio_write(cs1,0);
	    recv = mraa_spi_write(spi, byte);
	    printf("Writing %i ", byte);
	    printf("RECIVED FROM SS1 %x\n", recv);
	    usleep(100000);
	    mraa_gpio_write(cs1,1);
	    mraa_gpio_write(cs2,0);
	    recv = mraa_spi_write(spi, byte);
	    printf("Writing %i ", byte);
	    printf("RECIVED FROM SS2 %x\n", recv);
	    usleep(100000);
	    mraa_gpio_write(cs2,1);
	}
}