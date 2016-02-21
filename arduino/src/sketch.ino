#include <CmdMessenger.h>

// Outputs

#define LEFT_FOOT_FORWARD 3 // Verified
#define LEFT_FOOT_BACKWARD 24 // Not working
#define RIGHT_FOOT_FORWARD 2 // Verifed
#define RIGHT_FOOT_BACKWARD 22 // Not working

#define LEFT_LEG_FORWARD 10 // Not working
#define RIGHT_LEG_FORWARD 11 // Not working

#define TILT_LEFT 26
#define TILT_RIGHT 28 // Maybe?

#define TWIST_LEFT 30 // Verified
#define TWIST_RIGHT 32 // Verified

#define BODY_FORWARD 6 // Verified
#define BODY_BACKWARD 7 // Verified

#define LEFT_SHOULDER_UP 13 // Verified
#define LEFT_SHOULDER_DOWN 12 // Verified
#define LEFT_ELBOW_IN 34
#define LEFT_ELBOW_OUT 36

#define RIGHT_SHOULDER_UP 42 // Verified
#define RIGHT_SHOULDER_DOWN 40 // Verified
#define RIGHT_ELBOW_IN 30
#define RIGHT_ELBOW_OUT 32

#define LEFT_FINGERS_IN 9 // Verified
#define RIGHT_FINGERS_IN 8 // Verified

#define HEAD_UP 4 // Verified
#define HEAD_DOWN 5 // Not working
#define EYES_LEFT 39
#define EYES_RIGHT 41

int outputs[] = {
	LEFT_FOOT_FORWARD,
	LEFT_FOOT_BACKWARD,
	RIGHT_FOOT_FORWARD,
	RIGHT_FOOT_BACKWARD,
	LEFT_LEG_FORWARD,
	RIGHT_LEG_FORWARD,
	TILT_LEFT,
	TILT_RIGHT,
	TWIST_LEFT,
	TWIST_RIGHT,
	BODY_FORWARD,
	BODY_BACKWARD,
	LEFT_SHOULDER_UP,
	LEFT_SHOULDER_DOWN,
	LEFT_ELBOW_IN,
	LEFT_ELBOW_OUT,
	RIGHT_SHOULDER_UP,
	RIGHT_SHOULDER_DOWN,
	RIGHT_ELBOW_IN,
	RIGHT_ELBOW_OUT,
	LEFT_FINGERS_IN,
	RIGHT_FINGERS_IN,
	HEAD_UP,
	HEAD_DOWN,
	EYES_LEFT,
	EYES_RIGHT
};

void init_outputs() {
	for (int i = 0; i < sizeof(outputs) - 1; i++) {
		pinMode(outputs[i], OUTPUT);
	}
}

// Digital Inputs

#define LEFT_FOOT_TILT_SENSOR 52
#define LEFT_FOOT_FRONT_SENSOR 53
#define LEFT_FOOT_BACK_SENSOR 51

#define RIGHT_FOOT_TILT_SENSOR 50
#define RIGHT_FOOT_FRONT_SENSOR 49
#define RIGHT_FOOT_BACK_SENSOR 47

#define BODY_TILT_SENSOR 48
#define WAIST_LEAN_LEFT_SENSOR 46
#define WAIST_LEAN_RIGHT_SENSOR 44

int inputs[] = {
	LEFT_FOOT_TILT_SENSOR,
	LEFT_FOOT_FRONT_SENSOR,
	LEFT_FOOT_BACK_SENSOR,
	RIGHT_FOOT_TILT_SENSOR,
	RIGHT_FOOT_FRONT_SENSOR,
	RIGHT_FOOT_BACK_SENSOR,
	BODY_TILT_SENSOR,
	WAIST_LEAN_LEFT_SENSOR,
	WAIST_LEAN_RIGHT_SENSOR
};

void init_inputs() {
	for (int i = 0; i < sizeof(inputs) - 1; i++) {
		pinMode(inputs[i], INPUT_PULLUP);
	}
}

// Analog Inputs

#define LEFT_SHOULDER_SENSOR A0
#define RIGHT_SHOULDER_SENSOR A1

#define HEAD_UP_DOWN_SENSOR A2
#define BODY_ROTATE_SENSOR A3

CmdMessenger cmdMessenger = CmdMessenger(Serial);

enum {
	kSetOutput
};

void attachCallbackCommands() {
	cmdMessenger.attach(kSetOutput, onSetOutput);
}

void onSetOutput() {
	int pin = cmdMessenger.readInt16Arg();
	int value = cmdMessenger.readBoolArg();
	if (is_valid_output(pin)) {
		Serial.print(pin);
		Serial.print(":");
		Serial.println(value);
	}
}

void setup() {
	init_inputs();
	init_outputs();
	Serial.begin(115200);
	cmdMessenger.printLfCr();
	attachCallbackCommands();
}

void loop() {
	// print_inputs();
	cmdMessenger.feedinSerialData();
}


void print_pin(int pin) {
	int val = digitalRead(pin);
	Serial.print(pin);
	Serial.print(':');
	Serial.println(val);
}

void print_inputs() {
	for (int i = 0; i < sizeof(inputs) - 1; i++) {
		print_pin(inputs[i]);
	}
}

boolean is_valid_output(int pin) {
	boolean valid = false;
	for (int i = 0; i < sizeof(outputs); i++) {
		if (outputs[i] == pin) {
			valid = true;
			break;
		}
	}
	return valid;
}

