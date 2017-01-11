
void SPosteriorPuerta(void) {
	byte i;
	// PUERTA ABAJO
	if (EstadoPuerta[ValorActual]==PuertaAbajo) {
		if (CambioEstadoPuerta) {
		  AlimentaCelula(celulaOFF);
		  if (ManiobraPuerta[ValorActual]==none) {
		  	if (ExisteTemporizador(RelojPuerta)) {
		  		BorraTemporizador(RelojPuerta);
		  		CambiaLuzExterior(LuzExteriorOFF);
		  		EjecContinuaAcPuerta=0;
		  	}
		  }
		}
	}
	else 
	// PUERTA SUBE
	if (EstadoPuerta[ValorActual]==PuertaSube) {
		if (CambioEstadoPuerta) {
			SubirPuerta();
			if (!ExisteTemporizador(RelojPuerta)) { 
				AsignaTemporizador(RelojPuerta,CiclosReloj,prioridad1,TiempoRelojPuertaON,TiempoRelojPuertaOFF);
			}
			EjecContinuaAcPuerta=1;
		}
		// Luz intermitente
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
	// PUERTA ARRIBA
	if (EstadoPuerta[ValorActual]==PuertaArriba) {
		if (CambioEstadoPuerta) {
			if (ManiobraPuerta[ValorActual]==ManiobraAperturaPuerta) {
				AlimentaCelula(celulaON);
				EjecContinuaAcPuerta=1;
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

		if (ManiobraPuerta[ValorActual]==none) {
			EjecContinuaAcPuerta=0;
			CambiaLuzExterior(LuzExteriorOFF);
		}
	}
	else
	// PUERTA BAJA 
	if (EstadoPuerta[ValorActual]==PuertaBaja) {
		if (CambioEstadoPuerta) {
			BajarPuerta();
			if (!ExisteTemporizador(RelojPuerta)) { 
				AsignaTemporizador(RelojPuerta,CiclosReloj,prioridad1,TiempoRelojPuertaON,TiempoRelojPuertaOFF);
			}
			EjecContinuaAcPuerta=1;
		}
		// Luz intermitente
		i=GetIndiceTemp(RelojPuerta);
		if (CambioTempor[i]) {
			if (EstadoReloj[i]) {
				CambiaLuzExterior(LuzExteriorON);
				//activar sirena
			}
			else {
				CambiaLuzExterior(LuzExteriorOFF);
				//desactivar sirena
			}
		}
	}
	else
	// PUERTA EN MEDIO 
	if (EstadoPuerta[ValorActual]==PuertaEnMedio) {
		if (CambioEstadoPuerta) {

		}
	}
	else
	// ERROR EN PUERTA
	if (EstadoPuerta[ValorActual]==PuertaError) {
		if (CambioEstadoPuerta) {
			PararPuerta(TodasOpciones);
		}
	}
}

void SAnteriorPuerta(void) {
	// SALGO DE PUERTA ABAJO
	if (EstadoPuerta[ValorAnterior]==PuertaAbajo) {
		AlimentaCelula(celulaON);
	}
	else 
	// SALGO DE PUERTA SUBE
	if (EstadoPuerta[ValorAnterior]==PuertaSube) {
		PararPuerta(PuertaSube);
	}
	else 
	// SALGO DE PUERTA ARRIBA
	if (EstadoPuerta[ValorAnterior]==PuertaArriba) {
		
	}
	else 
	// SALGO DE PUERTA BAJA
	if (EstadoPuerta[ValorAnterior]==PuertaBaja) {
		PararPuerta(PuertaBaja);
	}
	else 
	// SALGO DE PUERTA EN MEDIO
	if (EstadoPuerta[ValorAnterior]==PuertaEnMedio) {

	}
	else 
	// SALGO DE ERROR
	if (EstadoPuerta[ValorAnterior]==PuertaError) {

	}
}

void PararPuerta(byte accion) {
	if (accion==PuertaSube) digitalWrite(pinMotorPuertaSube,LOW);
	else 
	if (accion==PuertaBaja) digitalWrite(pinMotorPuertaBaja,LOW);
	else {
		digitalWrite(pinMotorPuertaSube,LOW);
		digitalWrite(pinMotorPuertaBaja,LOW);
	}
	BorraTemporizador(TPerroGuardianPuerta);
}

void SubirPuerta(void) {
	digitalWrite(pinMotorPuertaBaja,LOW);
	delay(50);
	digitalWrite(pinMotorPuertaSube,HIGH);
	AsignaTemporizador(TPerroGuardianPuerta,RetardoConexion,prioridad1,TiempoMaxSubidaPuerta,0);
	SetMascTemp(TPerroGuardianPuerta);
}

void BajarPuerta(void) {
	digitalWrite(pinMotorPuertaSube,LOW);
	delay(50);
	digitalWrite(pinMotorPuertaBaja,HIGH);
	AsignaTemporizador(TPerroGuardianPuerta,RetardoConexion,prioridad1,TiempoMaxBajadaPuerta,0);
	SetMascTemp(TPerroGuardianPuerta);
}

void AlimentaCelula(boolean estado) {
	if (estado) {
		if (!AlimenCelula) digitalWrite(pinAlimCelula,HIGH);
		AlimenCelula=1;
	}
	else {
		if (AlimenCelula) digitalWrite(pinAlimCelula,LOW);
		AlimenCelula=0;
	}
}