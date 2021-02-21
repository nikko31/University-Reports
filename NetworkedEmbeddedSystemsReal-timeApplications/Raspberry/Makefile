blink:
	gcc -std=c11 0_blink.c -o blink -lwiringPi
	./blink

toggle_gpio:
	gcc -std=c11 1_toggle_gpio.c -o toggle_gpio -lwiringPi

gpio_perf:
	gcc -std=c11 -lrt 2_gpio_perf.c -o gpio_perf -lwiringPi

clean:
	rm -f ./blink
	rm -f ./toggle_gpio
	rm -f ./gpio_perf
