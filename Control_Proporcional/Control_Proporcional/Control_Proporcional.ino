/*
 Name:		Control_Proporcional.ino
 Created:	07/04/2019 17:23:59
 Author:	Borxo García
 Proyect:   Robot BoB
*/

//Habilitación DEBUG//
#define DEBUG 

//Constantes//
const int pin[] = { 13,3,4,5,6,7,8,9,12 };
const int InputD[] = { 14,15 };
const int InputI[] = { 16,17 };
const int enableD = 10;
const int enableI = 11;

//Variables//
int estado = 0;
int error = 0;
float control = 0;
float control1 = 0;

//Variables control Proporcional//
float velocidad = 50;
float kp = 6;




void setup() 
{
	for (int i = 8; i >= 0; i--) {
		pinMode(InputD[i], OUTPUT);
		pinMode(InputI[i], OUTPUT);
		pinMode(pin[i], INPUT);
	}

	#ifdef DEBUG
		Serial.begin(4800);
	#endif // DEBUG

	
}

void loop()
{   
	LecturaSensores();
	control = velocidad + (error*kp);
	control1 = velocidad - (error*kp);
	Motores();

	#ifdef DEBUG
		Serial.print("control:");
		Serial.print(control);
		Serial.print("   ");
		Serial.print("control1:");
		Serial.print(control1);
		Serial.print("   ");
	#endif // DEBUG

}

void LecturaSensores()
{   
	estado = 0;

	for (int i = 0; i <= 8; i++)
	{
		estado |= digitalRead(pin[i]) << i;
	}

	#ifdef DEBUG
		Serial.print("Bits =");
		Serial.println(estado);
	#endif // DEBUG


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