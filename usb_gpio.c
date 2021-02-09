#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define USB_CDEV "/dev/ttyGS0"
#define GPIO_CDEV "/dev/gpio_test1"

void send_to_cdev(const char *cdev, char ch)
{
	FILE *cdev_file;
	cdev_file = fopen(cdev, "w");
	if (NULL == cdev_file) {
		printf("Can't open %s\n", cdev_file);
		return;
	}

	fprintf(cdev_file, "%c\n", ch);
	fclose(cdev_file);
}

char read_from_cdev(const char *cdev)
{
	FILE *cdev_file;
	char ch;

	cdev_file = fopen(cdev, "r");
	if (NULL == cdev_file) {
		printf("Can't open %s\n", cdev_file);
		return '\0';
	}

	ch = fgetc(cdev_file);
	fclose(cdev_file);
	return ch;
}

int main(int argc, char *argv[])
{
	char val_usb;
	char val_gpio;

	while (1) {
		val_usb = read_from_cdev(USB_CDEV);
		if (val_usb == '0' || val_usb == '1') {
			printf("usb to gpio: %c\n", val_usb);
			send_to_cdev(GPIO_CDEV ,val_usb);
		} else if (val_usb == 'r') {
			val_gpio = read_from_cdev(GPIO_CDEV);
			printf("gpio ot usb: %c\n", val_gpio);
			send_to_cdev(USB_CDEV ,val_gpio);
		}
	}
}

