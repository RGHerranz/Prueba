

void LecturaEntradas(void) {
		
	// Identificacion
	EventoGlobal=LecturaRFID();
	
	if (EstadoAlarma[ValorActual]==AlarmaDescon) {
		// Puerta grande
		EventoMando=LeeMandoRemotoNormal();
		if (AlimenCelula) EventoCelula=LecturaCelula(); else EventoCelula=0;
		EventoPuerta=LecturaPuertaPorton()||EvaluaPosicionPuerta();
		// Cerrojos
		if (ManiobraCerrojos[ValorActual]!=none) EventoCerrojos=EvaluaPosicionCerrojos();
		// Luz
		if (ModoIluminacion[ValorActual]==IlumModoManual) EventoLuz=EvaluaEstadoCircLuz();
		// Extractor
		if (ModoExtractor[ValorActual]==ExtractModoManual) EventoExtractor=EvaluaEstadoExtractor();
		// Puertas
		EventoPuertaAM=LeeEstadoPuertaAM();
		EventoPuertaPeqPor=LeeEstadoPuertaPeqPor();
	}
	else 
	if (EstadoAlarma[ValorActual]==AlarmaPreArmada) {

	}
	else 
	if (EstadoAlarma[ValorActual]==AlarmaArmada) {
		// Puerta
		if (LeeMandoRemotoAlarma()) EventoMando=CompruebaPulsacionMandoRemoto();
		if (AlimenCelula) EventoCelula=LecturaCelula(); else EventoCelula=0;
		EventoPuerta=LecturaPuertaPorton()||EvaluaPosicionPuerta();
		// Cerrojos
		if (ManiobraCerrojos[ValorActual]!=none) EventoCerrojos=EvaluaPosicionCerrojos();
		// Alarma
		EventoAlarma=LecturaSensoresAlarma();
		// Luz
		EventoLuz=EvaluaEstadoCircLuz();
		// Extractor
		if (ModoExtractor[ValorActual]==ExtractModoManual) EventoExtractor=EvaluaEstadoExtractor();
		// Puertas
		EventoPuertaAM=LeeEstadoPuertaAM();
		EventoPuertaPeqPor=LeeEstadoPuertaPeqPor();
	}
	else 
	if (EstadoAlarma[ValorActual]==AlarmaPendIdent) {
		// Puerta
		EventoMando=LeeMandoRemotoNormal();
		if (AlimenCelula) EventoCelula=LecturaCelula(); else EventoCelula=0;
		EventoPuerta=LecturaPuertaPorton()||EvaluaPosicionPuerta();
		// Cerrojos
		if (ManiobraCerrojos[ValorActual]!=none) EventoCerrojos=EvaluaPosicionCerrojos();
		// Luz
		if (ModoIluminacion[ValorActual]==IlumModoManual) EventoLuz=EvaluaEstadoCircLuz();
		// Extractor
		if (ModoExtractor[ValorActual]==ExtractModoManual) EventoExtractor=EvaluaEstadoExtractor();
	}
	else 
	if (EstadoAlarma[ValorActual]==AlarmaActiva) {

	}
}

boolean EvaluaPosicionPuerta(void) {
	boolean resultado=0;
	
	if (PosicionPuerta[ValorAnterior]!=ValorInicial) PosicionPuerta[ValorAnterior]=PosicionPuerta[ValorActual];
   
	if (digitalRead(pinPuertaAbajo)) PosicionPuerta[ValorActual]=PuertaAbajo;
	else 
	if (digitalRead(pinPuertaArriba)) PosicionPuerta[ValorActual]=PuertaArriba;
	else PosicionPuerta[ValorActual]=PuertaEnMedio;

	if (PosicionPuerta[ValorAnterior]!=ValorInicial) {
		if (PosicionPuerta[ValorActual]!=PosicionPuerta[ValorAnterior]) resultado=1;
	}
	return(resultado);
}

boolean LeeMandoRemotoAlarma(void) {
	unsigned long int tiempo;
	if (!TiempoRebMando) TiempoRebMando=TiempoRebotesMando;
	tiempo=random(TiempoRebMando,TiempoRebMando+TiempoAdicMaxMando);

	if (CompruebaEstadoTemp(TPulsacionMando)==VueltaError) {
		LeeBoton1Mando();
		LeeBoton2Mando();
		if (Boton1Mando[ValorActual]&&!Boton1Mando[ValorAnterior]) {
			FlancoBoton1Mando=1;
			AsignaTemporizador(TPulsacionMando,RetardoConexion,prioridad1,tiempo,0);	
			SetMascTemp(TPulsacionMando);
			CambiaLuzExterior(LuzExteriorON);
			return(1);
		}
		else 
		if (Boton2Mando[ValorActual]&&!Boton2Mando[ValorAnterior]) {
			FlancoBoton2Mando=1;
			AsignaTemporizador(TPulsacionMando,RetardoConexion,prioridad1,tiempo,0);
			SetMascTemp(TPulsacionMando);
			CambiaLuzExterior(LuzExteriorON);
			return(1);
		}
		else {
			if (FlancoBoton1Mando) FlancoBoton1Mando=0;
			if (FlancoBoton2Mando) FlancoBoton2Mando=0;
			return(0);
		}
	}
	else 
	if (CompruebaEstadoTemp(TPulsacionMando)==1) {
		BorraTemporizador(TPulsacionMando);
		if (FlancoBoton1Mando) FlancoBoton1Mando=0;
		if (FlancoBoton2Mando) FlancoBoton2Mando=0;
		CambiaLuzExterior(LuzExteriorOFF);
		return(0);
	}
	else {
		if (CompruebaCuentaTemp(TPulsacionMando,TiempoRebMando)==1) {
			LeeBoton1Mando();
			LeeBoton2Mando();
			//Si hay un flanco antes de tiempo
			if (Boton1Mando[ValorActual]&&!Boton1Mando[ValorAnterior]
				||Boton2Mando[ValorActual]&&!Boton2Mando[ValorAnterior]) {
				if (CombinacionCorrecta) CombinacionCorrecta=0;
				NumPulsacionesMando=0;
				NumIntentosMando++;
				if (NumIntentosMando==NumIntentosMandoMax) {
					EventoAlarma=1;
					ActivaAlarma=1;
				}		
			}
		}
		if (FlancoBoton1Mando) FlancoBoton1Mando=0;
		if (FlancoBoton2Mando) FlancoBoton2Mando=0;
		return(0);
	}
}

boolean LeeMandoRemotoNormal(void) {
	unsigned long int tiempo;
	if (!NumPulsaCalMando) {
		if (CompruebaEstadoTemp(TRebotes)==VueltaError) {
			LeeBoton1Mando();
			LeeBoton2Mando();
			if (Boton1Mando[ValorActual]&&!Boton1Mando[ValorAnterior]) {
				FlancoBoton1Mando=1;
				if (TiempoRebMando) tiempo=TiempoRebMando; else tiempo=TiempoRebotesMando;
				AsignaTemporizador(TRebotes,RetardoConexion,prioridad1,tiempo,0);	
				SetMascTemp(TRebotes);
				CambiaLuzExterior(LuzExteriorON);
				CombinacionCorrecta=1;
				return(1);
			}
			else 
			if (Boton2Mando[ValorActual]&&!Boton2Mando[ValorAnterior]) {
				FlancoBoton2Mando=1;
				if (TiempoRebMando) tiempo=TiempoRebMando; else tiempo=TiempoRebotesMando;
				AsignaTemporizador(TRebotes,RetardoConexion,prioridad1,tiempo,0);
				SetMascTemp(TRebotes);
				CombinacionCorrecta=1;
				return(1);
			}
			else {
				if (FlancoBoton1Mando) FlancoBoton1Mando=0;
				if (FlancoBoton2Mando) FlancoBoton2Mando=0;
				return(0);
			}
		}
		else 
		if (CompruebaEstadoTemp(TRebotes)==1) {
			BorraTemporizador(TRebotes);
			return(0);
		}
		else {
			if (FlancoBoton1Mando) FlancoBoton1Mando=0;
			if (FlancoBoton2Mando) FlancoBoton2Mando=0;
			return(0);
		}	
	}
	else return(CalTiempMando());	
}

boolean CalTiempMando(void) {
	LeeBoton1Mando();
	LeeBoton2Mando();
	
	if (!Boton1Mando[ValorActual]&&Boton1Mando[ValorAnterior]||
				Boton1Mando[ValorActual]&&!Boton1Mando[ValorAnterior]) {
		// Flanco es de subida
		if (Boton1Mando[ValorActual]&&!Boton1Mando[ValorAnterior]) {
			// Se inicia la estimación de la duración del pulso
			if (Cuenta1Tiempo==VueltaError) {
				FlancoBoton1Mando=1;
				Cuenta1Tiempo=AsignaCuentaTiempo();
				return(1);
			}
		}
		else {
			// Flanco es de bajada
			// Se lanza o se resetea temporización
			if (CompruebaEstadoTemp(TRebotes)==VueltaError) {
				AsignaTemporizador(TRebotes,RetardoConexion,prioridad1,50,0);
				SetMascTemp(TRebotes);
			}
			else RelanzarTemporizador(TRebotes);
			if (FlancoBoton1Mando) FlancoBoton1Mando=0;
			return(0);
		}
	}
	else { 
		// No hay flanco
		if (CompruebaEstadoTemp(TRebotes)==1) {
			if (!Boton1Mando[ValorActual]) {
				ArrayTempReb[NumPulsaCalMando-1]=ValorCuentaTiempo(Cuenta1Tiempo);
				NumPulsaCalMando--;
				BorraTemporizador(TRebotes);
				if (!NumPulsaCalMando) {
					TiempoRebMando=CalculaMaximoRebMando();
					Cuenta1Tiempo==VueltaError;
				}
			}
		}
		if (FlancoBoton1Mando) FlancoBoton1Mando=0;
		return(0);
	}
	
	if (!Boton2Mando[ValorActual]&&Boton2Mando[ValorAnterior]||
				Boton2Mando[ValorActual]&&!Boton2Mando[ValorAnterior]) {
		// Flanco es de subida
		if (Boton2Mando[ValorActual]&&!Boton2Mando[ValorAnterior]) {
			// Se inicia la estimación de la duración del pulso
			if (Cuenta2Tiempo==VueltaError) {
				FlancoBoton2Mando=1;
				Cuenta2Tiempo=AsignaCuentaTiempo();
				return(1);
			}
		}
		else {
			// Flanco es de bajada
			// Se lanza o se resetea temporización
			if (CompruebaEstadoTemp(TRebotes2)==VueltaError) {
				AsignaTemporizador(TRebotes2,RetardoConexion,prioridad1,50,0);
				SetMascTemp(TRebotes2);
			}
			else RelanzarTemporizador(TRebotes2);
			if (FlancoBoton2Mando) FlancoBoton2Mando=0;
			return(0);
		}
	}
	else { 
		// No hay flanco
		if (CompruebaEstadoTemp(TRebotes2)==1) {
			if (!Boton2Mando[ValorActual]) {
				ArrayTempReb[NumPulsaCalMando-1]=ValorCuentaTiempo(Cuenta2Tiempo);
				NumPulsaCalMando--;
				BorraTemporizador(TRebotes2);
				if (!NumPulsaCalMando) {
					TiempoRebMando=CalculaMaximoRebMando();
					Cuenta2Tiempo==VueltaError;
				}
			}
		}
		if (FlancoBoton2Mando) FlancoBoton2Mando=0;
		return(0);
	}
}

unsigned long int CalculaMaximoRebMando(void) {
	byte i;
	unsigned long int mayor;
	mayor=ArrayTempReb[0];
	for (i=1;i<(NumPulsaCalMandoMax-1);i++) {
		if (ArrayTempReb[i]>mayor) mayor=ArrayTempReb[i];
	}
	return(mayor);
}
 
void LeeBoton1Mando(void) {
	Boton1Mando[ValorAnterior]=Boton1Mando[ValorActual];
	Boton1Mando[ValorActual]=digitalRead(pinBoton1MandoPuerta);
}

void LeeBoton2Mando(void) {
	Boton2Mando[ValorAnterior]=Boton2Mando[ValorActual];
	Boton2Mando[ValorActual]=digitalRead(pinBoton2MandoPuerta);
}



boolean EvaluaPosicionCerrojos(void) {
	if (PosicionCerrojos[ValorAnterior]!=ValorInicial) PosicionCerrojos[ValorAnterior]=PosicionCerrojos[ValorActual];
	ConsultaCerrojos();
	CalculaNumCerrojos();
	
	if (NumCerrojos[CerrojArriba]>2) {
		PosicionCerrojos[ValorActual]=CerrojArriba;
		if (NumCerrojos[CerrojArriba]<4) falloCerroj=1; else falloCerroj=0;
	}
	else
	if (NumCerrojos[CerrojAbajo]>2) {
		PosicionCerrojos[ValorActual]=CerrojAbajo;
		if (NumCerrojos[CerrojAbajo]<4) falloCerroj=1; else falloCerroj=0;
	}
	else PosicionCerrojos[ValorActual]=CerrojEnMedio;

	if (PosicionCerrojos[ValorAnterior]==CerrojEnMedio) {
		if (PosicionCerrojos[ValorActual]==CerrojArriba||
			PosicionCerrojos[ValorActual]==CerrojAbajo) return(1);
	}
	return(0);
}

void ConsultaCerrojos(void) {
	unsigned short int i=0;
	unsigned short int j=0;
	
	if (PosicionCerrojos[ValorAnterior]==ValorInicial) {
		for (i=0;i<3;i++) {
    	for (j=0;i<4;j++) {
      	PosicionCerrojo[ValorAnterior][i][j]=0;
      }
    }
  }		
  else {
  	for (i=0;i<3;i++) {
			for (j=0;j<4;j++) {
				PosicionCerrojo[ValorAnterior][i][j]=PosicionCerrojo[ValorActual][i][j];	
			}
		}
	}

	if (digitalRead(pinSensorSupCer1)) PosicionCerrojo[ValorActual][CerrojArriba][0]=1;
  else 
  if (digitalRead(pinSensorInfCer1)) PosicionCerrojo[ValorActual][CerrojAbajo][0]=1;
  else PosicionCerrojo[ValorActual][CerrojEnMedio][0]=1;
  
  if (digitalRead(pinSensorSupCer2)) PosicionCerrojo[ValorActual][CerrojArriba][1]=1;
  else 
  if (digitalRead(pinSensorInfCer2)) PosicionCerrojo[ValorActual][CerrojAbajo][1]=1;
  else PosicionCerrojo[ValorActual][CerrojEnMedio][1]=1;
     
  if (digitalRead(pinSensorSupCer3)) PosicionCerrojo[ValorActual][CerrojArriba][2]=1;
  else 
  if (digitalRead(pinSensorInfCer3)) PosicionCerrojo[ValorActual][CerrojAbajo][2]=1;
  else PosicionCerrojo[ValorActual][CerrojEnMedio][2]=1;
  
  if (digitalRead(pinSensorSupCer4)) PosicionCerrojo[ValorActual][CerrojArriba][3]=1;
  else 
  if (digitalRead(pinSensorInfCer4)) PosicionCerrojo[ValorActual][CerrojAbajo][3]=1;
  else PosicionCerrojo[ValorActual][CerrojEnMedio][3]=1;
}

void CalculaNumCerrojos(void) {
	unsigned short int i=0;
	unsigned short int num=0;

	for (i=0;i<4;i++) {
		if (PosicionCerrojo[ValorActual][CerrojArriba][i]) num++;
	}
	
	NumCerrojos[CerrojArriba]=num;

	if (num<4) {
		num=0;
		for (i=0;i<4;i++) {
			if (PosicionCerrojo[ValorActual][CerrojAbajo][i]) num++;
		}
		NumCerrojos[CerrojAbajo]=num;
	}

	if ((NumCerrojos[0]+NumCerrojos[1])<4) {
		num=0;
		for (i=0;i<4;i++) {
			if (PosicionCerrojo[ValorActual][CerrojEnMedio][i]) num++;
		}
		NumCerrojos[CerrojEnMedio]=num;
	}
}

void CalculaFlancosCerrojos(void) {
	unsigned short int i=0;
	boolean a=0,b=0;
	
	for (i=0;i<4;i++) {
		a=PosicionCerrojo[ValorActual][CerrojArriba][i];
		b=PosicionCerrojo[ValorAnterior][CerrojArriba][i];
		if (a&&!b) FlancoSCerrojoArriba[i]=1; else FlancoSCerrojoArriba[i]=0;
	}

	for (i=0;i<4;i++) {
		a=PosicionCerrojo[ValorActual][CerrojAbajo][i];
		b=PosicionCerrojo[ValorAnterior][CerrojAbajo][i];
		if (a&&!b) FlancoSCerrojoAbajo[i]=1; else FlancoSCerrojoAbajo[i]=0;
	}

}

boolean LecturaCelula(void) {
	boolean resultado=0;
	CelulaPuerta[ValorAnterior]=CelulaPuerta[ValorActual];
	CelulaPuerta[ValorActual]=digitalRead(pinCelulaPuerta);
	if (CelulaPuerta[ValorActual]&&!CelulaPuerta[ValorAnterior]) {
		FlancoCelula=1;
		resultado=1;
	}
	else {
		if (FlancoCelula) FlancoCelula=0;
	}
	
	if (!CelulaPuerta[ValorActual]&&CelulaPuerta[ValorAnterior]) resultado=1;
	return(resultado); 
}

boolean LecturaPuertaPorton(void) {
	PuertPorton[ValorAnterior]=PuertPorton[ValorActual];
	PuertPorton[ValorActual]=digitalRead(pinPuertaPeqPorton);
	if (PuertPorton[ValorActual]&&!PuertPorton[ValorAnterior]) {
		FlancoPuertPorton=1;
		return(1);
	}
	else FlancoPuertPorton=0;
	return(0);
}

boolean EvaluaEstadoCircLuz(void) {
	byte i;
	boolean resultado=0;

	for (i=0;i<7;i++) {
		EstadoCircIlum[ValorAnterior][i]=EstadoCircIlum[ValorActual];
		CambioEstadoLuz[i]=0;
	}
  
  if (digitalRead(pinEstLuzTechoElev)) EstadoCircIlum[ValorActual][CircTechoElev]=1;
  else EstadoCircIlum[ValorActual][CircTechoElev]=0;

  if (digitalRead(pinEstLuzLatIzqElev)) EstadoCircIlum[ValorActual][CircLatIzqElev]=1;
  else EstadoCircIlum[ValorActual][CircLatIzqElev]=0;

  if (digitalRead(pinEstLuzLatDerElev)) EstadoCircIlum[ValorActual][CircLatDerElev]=1;
  else EstadoCircIlum[ValorActual][CircLatDerElev]=0;

  if (digitalRead(pinEstLuzTechoEntC1)) EstadoCircIlum[ValorActual][Circ1TechoEnt]=1;
  else EstadoCircIlum[ValorActual][Circ1TechoEnt]=0;

  if (digitalRead(pinEstLuzTechoEntC2)) EstadoCircIlum[ValorActual][Circ2TechoEnt]=1;
  else EstadoCircIlum[ValorActual][Circ2TechoEnt]=0;

  if (digitalRead(pinEstLuzEntLatDer)) EstadoCircIlum[ValorActual][CircEntLatDer]=1;
  else EstadoCircIlum[ValorActual][CircEntLatDer]=0;

  if (digitalRead(pinEstLuzEntLatIzq)) EstadoCircIlum[ValorActual][CircEntLatIzq]=1;
  else EstadoCircIlum[ValorActual][CircEntLatIzq]=0;

  if (digitalRead(pinEstLuzBano)) EstadoCircIlum[ValorActual][CircLuzBano]=1;
  else EstadoCircIlum[ValorActual][CircLuzBano]=0;

  for (i=0;i<7;i++) {
  	if (EstadoCircIlum[ValorActual]!=EstadoCircIlum[ValorAnterior]) {
  		CambioEstadoLuz[i]=1;
  		resultado=1;
  	}
  }
  return(resultado);
}

boolean EvaluaEstadoExtractor(void) {
	boolean resultado=0;
	EstadoExtractor[ValorAnterior]=EstadoExtractor[ValorActual];
		
	if (digitalRead(pinEstExtractVel1)) EstadoExtractor[ValorActual]=ExtractorVel1;
  else 
  if (digitalRead(pinEstExtractVel2)) EstadoExtractor[ValorActual]=ExtractorVel2;
  else EstadoExtractor[ValorActual]=ExtractorApagado;

	if (EstadoExtractor[ValorActual]!=EstadoExtractor[ValorAnterior]) resultado=1;
	
	return(resultado);
}

boolean LecturaSensoresAlarma(void) {
	
	LeerPuertaEntAM();
	if (EstadoPuertaEntAM[ValorActual]&&!EstadoPuertaEntAM[ValorAnterior]) return(1);

	LeerDetectorPres();
	if (EstadoDetectorPres[ValorActual]&&!EstadoDetectorPres[ValorAnterior]) return(1);

}

void LeerPuertaEntAM(void) {
	EstadoPuertaEntAM[ValorAnterior]=EstadoPuertaEntAM[ValorActual];
	EstadoPuertaEntAM[ValorActual]=digitalRead(pinPuertaEntAM);
}

void LeerDetectorPres(void) {
	EstadoDetectorPres[ValorAnterior]=EstadoDetectorPres[ValorActual];
	EstadoDetectorPres[ValorActual]=digitalRead(pinDetectorPres);
}