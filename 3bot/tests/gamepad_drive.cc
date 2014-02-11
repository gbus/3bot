
#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include "../src/hbridgelib.h"

// GPIO output pins
#define GPIO_M1_IN1             17      // Right wheel
#define GPIO_M1_IN2             27
#define GPIO_M2_IN3             18      // Left wheel
#define GPIO_M2_IN4             23
// Motor speed control (pwm)
#define PWM_CH_M1_ENA           12
#define PWM_CH_M2_ENB           13

using namespace std;

int print_usage(int exit_code) {
	cout << "Usage: gamepad_drive -w widget -c command -e event -v value/angle [-i intensity]" << endl;
	return exit_code;
}

int main(int argc, char* argv[])
{
	char *widget, *command, *event, *value;
	float intensity;
	int next_option;


	const char* const short_options = "hw:c:e:v:i:";
	const struct option long_options[] = {
		{ "help", 0, NULL, 'h' },
		{ "widget", 1, NULL, 'w' },
		{ "command", 1, NULL, 'c' },
		{ "event", 1, NULL, 'e' },
		{ "value", 1, NULL, 'v' },
		{ "intensity", 1, NULL, 'i' },
		{ NULL, 0, NULL, 0 }
	};


	do {
		next_option = getopt_long (argc, argv, short_options, long_options, NULL);
		switch (next_option)
		{
			case 'h':
				print_usage (0);
			case 'w':
				widget = optarg;
				break;
			case 'c':
				command = optarg;
				break;
			case 'e':
				event = optarg;
				break;
			case 'v':
				value = optarg;
				break;
			case 'i':
				intensity = atof(optarg);
				break;
			case '?': /* The user specified an invalid option. */
				print_usage (1);
			case -1: /* Done with options. */
				break;
			default:
				abort ();
		}
	} while (next_option != -1);


	GamePadHBridge	gphb(	GPIO_M1_IN1, GPIO_M1_IN2, GPIO_M2_IN3, GPIO_M2_IN4, 
			PWM_CH_M1_ENA, PWM_CH_M2_ENB );
	if (widget=="gamepad"){
		gphb.setCommand(command, event, value, intensity);
		if (!gphb.runCommand()) {
			cout << "Command not recognized." << endl;
			return -1;
		}
	} else {
		cout << "Widget not supported." << endl;
		return -1;
	}
	

	return 0; 
}

