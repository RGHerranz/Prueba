void ControlEstadoCerrojos(void) {
	// CERROJOS ABAJO
	if (EstadoCerrojos[ValorActual]==CerrojAbajo) {
				
	}
	else
	// CERROJOS SUBEN
	if (EstadoCerrojos[ValorActual]==CerrojSube) {
		if (PosicionCerrojos[ValorActual]==CerrojArriba) {
			ActualizaEstadoCerrojos(CerrojArriba);
			ActualizaManiobraCerrojos(none);
			if (EstadoPuerta[ValorActual]==PuertaAbajo) ActualizaManiobraPuerta(none);
		}
		else 
		if (CompruebaEstadoTemp(TPerroGuardianPuerta)==1) {
			ActualizaEstadoPuerta(CerrojError);
			ActualizaManiobraPuerta(none);
		}
	}
	else
	// CERROJOS ARRIBA
	if (EstadoCerrojos[ValorActual]==CerrojArriba) {
		
	}
	else
	// CERROJOS BAJAN
	if (EstadoCerrojos[ValorActual]==CerrojBaja) {
		if (PosicionCerrojos[ValorActual]==CerrojAbajo) {
			ActualizaEstadoCerrojos(CerrojAbajo);
			if (ManiobraPuerta[ValorActual]==ManiobraAperturaPuerta) {
				AsignaTemporizador(TCerrojEspera,RetardoConexion,prioridad1,TiempoEsperaCerrojo,0);
				SetMascTemp(TCerrojEspera);
				ActualizaManiobraCerrojos(none);
			}
		}
		if (CompruebaEstadoTemp(TPerroGuardianPuerta)==1) {
			ActualizaEstadoPuerta(CerrojError);
			ActualizaManiobraPuerta(none);
		}
	}
	else
	// CERROJOS EN MEDIO
	if (EstadoCerrojos[ValorActual]==CerrojEnMedio) {
		
	}
	else 
	// AVERIA CERROJOS
	if (EstadoCerrojos[ValorActual]==CerrojError) {

	}
}

void ActualizaEstadoCerrojos(byte estado) {
	EstadoCerrojos[ValorAnterior]=EstadoCerrojos[ValorActual];
	EstadoCerrojos[ValorActual]=estado;
	CambioEstadoCerrojos=1;
}

void ActualizaManiobraCerrojos(byte maniobra) {
	ManiobraCerrojos[ValorAnterior]=ManiobraCerrojos[ValorActual];
	ManiobraCerrojos[ValorActual]=maniobra;
	CambioManiobraCerrojos=1;
}

void InicializaVariablesCerrojos(void) {
	if (EventoCerrojos) EventoCerrojos=0;
	if (CambioEstadoCerrojos) CambioEstadoCerrojos=0;
	if (CambioManiobraCerrojos) CambioManiobraCerrojos=0;
}

void InicializaCerrojos(void) {

	
}