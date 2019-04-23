/*
 Name:		Control_Proporcional y Derivativo.ino
 Created:	07/04/2019 17:23:59
 Author:	Borxo García
 Proyect:   Robot BoB
*/

//Habilitación DEBUG//
#define DEBUG

//Constantes//
const int sensor[] = { 13,3,4,5,6,7,8,9,12 };
const int InputD[] = { 14,15 };
const int InputI[] = { 16,17 };
const int enableD = 10;
const int enableI = 11;

//Variables//
int estado = 0;
int error = 0;
int errorPasado = 0;
int Diferencia = 0;
float control = 0;
float control1 = 0;

//Variables Control Porporcional y Derivativo//
int velocidad = 90;
float kp = 9;
float kd = 15;



void setup() {

	for (int i = 8; i >= 0; i--) {
		pinMode(InputD[i], OUTPUT);
		pinMode(InputI[i], OUTPUT);
		pinMode(sensor[i], INPUT);
		//pinMode(led[i], OUTPUT);
	}
#ifdef DEBUG
	Serial.begin(4800);
#endif
}

void loop()
{
	errorPasado = error;

	#ifdef DEBUG
		Serial.print("  ");
		Serial.print("errorPasado:");
		Serial.print(errorPasado);
		Serial.print("  ");
	#endif // DEBUG

	LecturaSensores();
	Diferencia = error - errorPasado;

	#ifdef DEBUG
		Serial.print("Diferencia:");
		Serial.print(Diferencia);
		Serial.print("  ");
	#endif // DEBUG

	control = velocidad + ((error * kp) + (kd * Diferencia));
	control1 = velocidad - ((error * kp) + (kd * Diferencia));
	Motores();

#ifdef DEBUG
	Serial.print("control:");
	Serial.print(control);
	Serial.print("   ");
	Serial.print("control1:");
	Serial.print(control1);
	Serial.print("   ");
#endif

}
void LecturaSensores()
{
	estado = 0;

	for (int i = 0; i <= 8; i++)
	{
		estado |= digitalRead(sensor[i]) << i;
	}

#ifdef DEBUG
	Serial.print("Bits =");
	Serial.println(estado);
#endif

	switch (estado)
	{
	case 0B000000001:
		#ifdef DEBUG
			Serial.print("+8  ");
		#endif // DEBUG
		error = 8;
		break;

	case 0B000000011:
		#ifdef DEBUG
			Serial.print("+7  ");
		#endif // DEBUG
		error = 7;
		break;

	case 0B000000010:
		#ifdef DEBUG
			Serial.print("+6  ");
		#endif // DEBUG
		error = 6;
		break;

	case 0B000000110:
		#ifdef DEBUG
			Serial.print("+5  ");
		#endif // DEBUG
		error = 5;
		break;

	case 0B000000100:
		#ifdef DEBUG
			Serial.print("+4  ");
		#endif // DEBUG
		error = 4;
		break;

	case 0B000001100:
		#ifdef DEBUG
			Serial.print("+3  ");
		#endif // DEBUG
		error = 3;
		break;

	case 0B000001000:
		#ifdef DEBUG
			Serial.print("+2  ");
		#endif // DEBUG
		error = 2;
		break;

	case 0B000011000:
		#ifdef DEBUG
			Serial.print("+1  ");
		#endif // DEBUG
		error = 1;
		break;

	case 0B000010000:
		#ifdef DEBUG
			Serial.print("0  ");
		#endif // DEBUG
		error = 0;
		break;

	case 0B000110000:
		#ifdef DEBUG
			Serial.print("-1  ");
		#endif // DEBUG
		error = -1;
		break;

	case 0B000100000:
		#ifdef DEBUG
			Serial.print("-2  ");
		#endif // DEBUG
		error = -2;
		break;

	case 0B001100000:
		#ifdef DEBUG
			Serial.print("-3  ");
		#endif // DEBUG
		error = -3;
		break;

	case 0B001000000:
		#ifdef DEBUG
			Serial.print("-4  ");
		#endif // DEBUG
		error = -4;
		break;

	case 0B011000000:
		#ifdef DEBUG
			Serial.print("-5  ");
		#endif // DEBUG
		error = -5;
		break;

	case 0B010000000:
		#ifdef DEBUG
			Serial.print("-6  ");
		#endif // DEBUG
		error = -6;
		break;

	case 0B110000000:
		#ifdef DEBUG
			Serial.print("-7  ");
		#endif // DEBUG
		error = -7;
		break;

	case 0B100000000:
		#ifdef DEBUG
			Serial.print("-8  ");
		#endif // DEBUG
		error = -8;
		break;

	default:
		#ifdef DEBUG
			Serial.print("Fuera  ");
		#endif // DEBUG
		break;
	}

}

void Motores()
{

	digitalWrite(InputD[0], HIGH);
	digitalWrite(InputD[1], LOW);
	digitalWrite(InputI[0], HIGH);
	digitalWrite(InputI[1], LOW);

	analogWrite(enableD, control);
	analogWrite(enableI, control1);

	if (control < 0)
	{
		control = abs(control);
		digitalWrite(InputI[0], LOW);
		digitalWrite(InputI[1], HIGH);
	}

	else if (control1 < 0)
	{
		control1 = abs(control1);
		digitalWrite(InputD[0], LOW);
		digitalWrite(InputD[1], HIGH);
	}

}