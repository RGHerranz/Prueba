void SPosteriorCerrojos(void) {
	byte i;
	
	if (EstadoCerrojos[ValorActual]==CerrojAbajo) {
		// CERROJOS ABAJO
		if (CambioEstadoCerrojos) {
			if (ExisteTemporizador(TCerrojEspera)) {
		  	EjecContinuaAcCerrojos=1;
		  }
		}
		if (ExisteTemporizador(TCerrojEspera)) {
			i=GetIndiceTemp(RelojPuerta);
			if (i!=VueltaError&&CambioTempor[i]&&EstadoReloj[i]) {
				CambiaLuzExterior(LuzExteriorON);
			}
			else {
				CambiaLuzExterior(LuzExteriorOFF);
			}
		}
		else {
			CambiaLuzExterior(LuzExteriorOFF);
			EjecContinuaAcCerrojos=0;
		}
	}
	else
	// CERROJOS SUBEN 
	if (EstadoCerrojos[ValorActual]==CerrojSube) {
		if (CambioEstadoCerrojos) {
			SubirCerrojos();
		}
	}
	else
	// CERROJOS ARRIBA 
	if (EstadoCerrojos[ValorActual]==CerrojArriba) {
		if (CambioEstadoCerrojos) {
			
		}
	}
	else
	// CERROJOS BAJAN 
	if (EstadoCerrojos[ValorActual]==CerrojBaja) {
		if (CambioEstadoCerrojos) {
			BajarCerrojos();
			if (ManiobraPuerta[ValorActual]==ManiobraAperturaPuerta) {
				AsignaTemporizador(RelojPuerta,CiclosReloj,prioridad1,TiempoRelojPuertaON,TiempoRelojPuertaOFF);
				EjecContinuaAcCerrojos=1;
			}
		}
		if (ManiobraPuerta[ValorActual]==ManiobraAperturaPuerta) {
			i=GetIndiceTemp(RelojPuerta);
			if (i!=VueltaError&&CambioTempor[i]&&EstadoReloj[i]) {
				CambiaLuzExterior(LuzExteriorON);
			}
			else {
				CambiaLuzExterior(LuzExteriorOFF);
			}
		}
	}
	else
	// CERROJOS EN MEDIO 
	if (EstadoCerrojos[ValorActual]==CerrojEnMedio) {
		if (CambioEstadoCerrojos) {

		}
	}
	else 
	// ERROR CERROJOS
	if (EstadoCerrojos[ValorActual]==CerrojError) {
		if (CambioEstadoCerrojos) {
			PararCerrojos();
		}
	}
}

void SAnteriorCerrojos(void) {
	if (EstadoCerrojos[ValorAnterior]==CerrojAbajo) {

	}
	else 
	if (EstadoCerrojos[ValorAnterior]==CerrojSube) {
		PararCerrojos();
	}
	else 
	if (EstadoCerrojos[ValorAnterior]==CerrojArriba) {

	}
	else 
	if (EstadoCerrojos[ValorAnterior]==CerrojBaja) {
		PararCerrojos();
	}
	else 
	if (EstadoCerrojos[ValorAnterior]==CerrojEnMedio) {

	}
	else 
	if (EstadoCerrojos[ValorActual]==CerrojError) {

	}
}


void PararCerrojos(void) {
	digitalWrite(pinMotorCerAlim,LOW);
	delay(80);
	digitalWrite(pinMotorCerSubeBaja,LOW);
	BorraTemporizador(TPerroGuardianCerrojos);
}

void SubirCerrojos(void) {
	digitalWrite(pinMotorCerSubeBaja,HIGH);
	delay(80);
	digitalWrite(pinMotorCerAlim,HIGH);
	AsignaTemporizador(TPerroGuardianCerrojos,RetardoConexion,prioridad1,TiempoMaxSubidaCerrojos,0);
	SetMascTemp(TPerroGuardianCerrojos);
}

void BajarCerrojos(void) {
	digitalWrite(pinMotorCerSubeBaja,LOW);
	delay(80);
	digitalWrite(pinMotorCerAlim,HIGH);
	AsignaTemporizador(TPerroGuardianCerrojos,RetardoConexion,prioridad1,TiempoMaxBajadaCerrojos,0);
	SetMascTemp(TPerroGuardianCerrojos);
}