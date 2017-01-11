
boolean LecturaRFID(void) {

}

boolean ComprobacionClaveRFID(void) {

}

// Registra pulsaciones mando remoto
boolean CompruebaPulsacionMandoRemoto(void) {
	byte i;
	if (FlancoBoton1Mando) ClaveTempMando[NumPulsacionesMando]=1; else ClaveTempMando[NumPulsacionesMando]=2;
	NumPulsacionesMando++;
	if (NumPulsacionesMando==4) {
		for (i=0;i<NumPulsacionesCodigoMando;i++) {
			if (ClaveMandoRemoto[i]!=ClaveTempMando[i]) {
				i=4;
				NumPulsacionesMando=5;
				if (CombinacionCorrecta) CombinacionCorrecta=0;
				NumIntentosMando++;
			}
		}

		if (NumPulsacionesMando==4) {
			CombinacionCorrecta=1;
			NumIntentosMando=0;
			NumPulsacionesMando=0;
			return(1);
		}
		else {
			if (NumIntentosMando==NumIntentosMandoMax) {
				EventoAlarma=1;
				ActivaAlarma=1;
				return(0);	
			}
		}
	} 
	return(0);
}

boolean LeeEstadoPuertaAM(void) {

}

boolean LeeEstadoPuertaPeqPor(void) {
	
}