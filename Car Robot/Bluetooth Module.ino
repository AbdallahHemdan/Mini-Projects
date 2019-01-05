int izqA = 5; 
int izqB = 6; 
int derA = 9; 
int derB = 10; 
int vel = 255; 		// Velocidad de los motores (0-255)
int estado = 'g'; 	// inicia detenido

void setup() { 
	Serial.begin(9600); // inicia el puerto serial para comunicacion con el Bluetooth
	pinMode(derA, OUTPUT);
	pinMode(derB, OUTPUT);
	pinMode(izqA, OUTPUT);
	pinMode(izqB, OUTPUT);
} 

void loop() { 
	if(Serial.available()>0){ 
		estado = Serial.read(); // lee el bluetooth y almacena en estado
	}
	if(estado=='a'){ // Forward
		Serial.println(estado);
		analogWrite(derB, 0); 
		analogWrite(izqB, 0); 
		analogWrite(derA, vel); 
		analogWrite(izqA, vel); 
	}
	// Right
	if(estado=='d'){ 
	    Serial.println(estado);
		analogWrite(derB, vel); 
		analogWrite(izqB, 0); 
		analogWrite(derA, 0); 
		analogWrite(izqA, vel); 
	}
	if(estado=='c'){ // Stop
	    Serial.println(estado);
		analogWrite(derB, 0); 
		analogWrite(izqB, 0); 
		analogWrite(derA, 0); 
		analogWrite(izqA, 0); 
	}
	if(estado=='b'){ // left
	    Serial.println(estado);
		analogWrite(derB, 0); 
		analogWrite(izqB, vel);
		analogWrite(izqA, 0);
		analogWrite(derA, vel); 
	} 

	if(estado=='e'){ // Reverse
	    Serial.println(estado);
		analogWrite(derA, 0); 
		analogWrite(izqA, 0);
		analogWrite(derB, vel); 
		analogWrite(izqB, vel); 
	}
	if (estado =='f'){ // Boton ON se mueve sensando distancia }
	if (estado=='g'){ // Boton OFF, detiene los motores no hace nada }
}
