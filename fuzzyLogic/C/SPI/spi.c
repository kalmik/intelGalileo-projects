#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
# define RX_LEN 1


static const char *device = "/dev/spidev1.0";
static short unsigned int mode = 0;
static short unsigned int bits = 8;
static unsigned long speed = 8000000;
static unsigned int delay=0;



void setupSPI(int fd)
{
	int ret;
	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);

	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
	
}
void setGPIOPin(char* pin, char* dir, char* drive, char* val)
{
	char buf[256];
	int fd;

	// Open the GPIO Export file
	fd = open("/sys/class/gpio/export",O_WRONLY);
	
	// Export chosen pin
	write(fd, pin, strlen(pin)); // Export GPIO pin
	close(fd);
	
	// Open exported pin DIRECTION file
	sprintf(buf,"/sys/class/gpio/gpio%s/direction",pin);
	fd = open(buf,O_WRONLY); // open GPIOxx direction file

	// write out the direction
	write(fd,dir,strlen(dir)); // set GPIOxx direction to out
	close(fd);

	// open the drive file
	sprintf(buf,"/sys/class/gpio/gpio%s/drive",pin);
	fd = open(buf,O_WRONLY); // open GPIO drive strength file
	
	write(fd,drive,strlen(drive)); // set GPIO drive
	close(fd);
	
	sprintf(buf,"/sys/class/gpio/gpio%s/value",pin);
	fd = open(buf,O_WRONLY);
	
	write(fd,val,strlen(val)); // set GPIO value
	close(fd);
	
}

void setMux(void)
{
	
	// Switch all the SPI1 pins through to the header pins. And enable level shifter.
	setGPIOPin("4","out","strong","1"); // Level shifter OE
	setGPIOPin("42","out","strong","0"); // SPI1_CS Mux
	setGPIOPin("43","out","strong","0"); // SPI1_MOSI mux
	setGPIOPin("54","out","strong","0"); // SPI1_MISO mux
	setGPIOPin("55","out","pullup","0"); // SPI1_CLK mux
	
}

int main(){


	struct spi_ioc_transfer xfer[1];
	unsigned char buf[1];
	unsigned char rbuf[1];

	//memset(xfer, 0, sizeof xfer);
	//memset(buf, 0, sizeof buf);

	int fd = open(device, O_RDWR);

	setupSPI(fd);
	setMux();

	memset(buf, 0, sizeof buf);
    memset(rbuf, 0, sizeof rbuf);
	buf[0] = 0xAA;

	memset(&xfer,0,sizeof(xfer));
	
	xfer[0].rx_buf = (unsigned long)rbuf;
	xfer[0].len = 1;
	
	int ret = ioctl (fd, SPI_IOC_MESSAGE(1), &xfer);

	printf("%.2x\n", rbuf[0]);

	return 0;
}