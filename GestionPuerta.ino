void GestionPuerta(void) {
	if (EventoMando||EventoCelula||EventoPuerta||EventoTiempo||EventoCerrojos) {
		if (EventoCerrojos) ControlEstadoCerrojos();
		if (MemoriaPeticion||EventoMando||EventoCelula||EventoPuerta||EventoTiempo) ControlEstadoPuerta();
				
		if (CambioEstadoCerrojos) {
			SAnteriorCerrojos();
			SPosteriorCerrojos();
		}
		if (CambioEstadoPuerta) {
			SAnteriorPuerta();
			SPosteriorPuerta();
		}
		
		InicializaVariablesCerrojos();
		InicializaVariablesPuerta();
		
	}
	if (!CambioEstadoPuerta&&EjecContinuaAcPuerta) SPosteriorPuerta();
	if (!CambioEstadoCerrojos&&EjecContinuaAcCerrojos) SPosteriorCerrojos();
}


void ControlEstadoPuerta(void) {
	// PUERTA ABAJO CERRADA
	if (EstadoPuerta[ValorActual]==PuertaAbajo) {
		// Se actúa sobre el mando
		if (CombinacionCorrecta&&(ManiobraPuerta[ValorActual]=none))	{
			if (!PuertPorton[ValorActual]) {
				ActualizaManiobraPuerta(ManiobraAperturaPuerta);
				if (EstadoCerrojos[ValorActual]!=CerrojAbajo) {
					ActualizaEstadoCerrojos(CerrojBaja);
					ActualizaManiobraCerrojos(ManiobraAperturaCerrojos);
				}
				else ActualizaEstadoPuerta(PuertaSube);
			}
			else MemoriaPeticion=1;
		}
		else 
		if (MemoriaPeticion) {
			if (!PuertPorton[ValorActual]) {
				AsignaTemporizador(TPuertaPorton,RetardoConexion,prioridad1,TiempoEspPuertaPorton,0);
				SetMascTemp(TPuertaPorton);
				MemoriaPeticion=0;
			}
		}
		else 
		if (CompruebaEstadoTemp(TPuertaPorton)==1) {
			BorraTemporizador(TPuertaPorton);
			ActualizaManiobraPuerta(ManiobraAperturaPuerta);
			if (EstadoCerrojos[ValorActual]!=CerrojAbajo) {
				ActualizaEstadoCerrojos(CerrojBaja);
				ActualizaManiobraCerrojos(ManiobraAperturaCerrojos);
			}
			else ActualizaEstadoPuerta(PuertaSube);
		}
		else 
		if (CompruebaEstadoTemp(TCerrojEspera)==1) {
			BorraTemporizador(TCerrojEspera);
			ActualizaEstadoPuerta(PuertaSube);
		}
		else 
		// Activar cierre de cerrojos transcurrido un tiempo de haber cerrado la puerta
		if (CompruebaEstadoTemp(TPuertaAlCerrar)==1) {
			BorraTemporizador(TPuertaAlCerrar);
			ActualizaManiobraCerrojos(ManiobraCierreCerrojos);
			ActualizaEstadoCerrojos(CerrojSube);
			ActualizaManiobraPuerta(none);
		}
	}
	else
	// PUERTA SUBE
	if (EstadoPuerta[ValorActual]==PuertaSube) {
		// La puerta llegó arriba
		if (PosicionPuerta[ValorActual]==PuertaArriba) {
			ActualizaEstadoPuerta(PuertaArriba);
			AsignaTemporizador(TPuertaEspArriba,RetardoConexion,prioridad1,TiempoEsperaArriba,0);
			SetMascTemp(TPuertaEspArriba);
		}
		else
		if (FlancoPuertPorton) {
			AsignaTemporizador(TPuertaPorton,RetardoConexion,prioridad1,TiempoEspPuertaPorton,0);
			SetMascTemp(TPuertaPorton);
			ActualizaEstadoPuerta(PuertaEnMedio);
		}
		else
		// Se actúa sobre el mando
		if (FlancoBoton1Mando) {
			ActualizaEstadoPuerta(PuertaEnMedio);
		}
		else 
		if (FlancoBoton2Mando) {
			AsignaTemporizador(TPuertaCambioManiobra,RetardoConexion,prioridad1,TimempoInversionGiro,0);
			SetMascTemp(TPuertaCambioManiobra);
			ActualizaEstadoPuerta(PuertaEnMedio);
		}
		else 
		if (CompruebaEstadoTemp(TPerroGuardianPuerta)==1) {
			ActualizaEstadoPuerta(PuertaError);
			ActualizaManiobraPuerta(none);
		}
	}
	else 
	// PUERTA ARRIBA
	if (EstadoPuerta[ValorActual]==PuertaArriba) {
		// Se actúa sobre el mando
		if (FlancoBoton2Mando)	{
			if (!CelulaPuerta[ValorActual]) {
				ActualizaEstadoPuerta(PuertaBaja);
				ActualizaManiobraPuerta(ManiobraCierrePuerta);
				if (ExisteTemporizador(TPuertaEspArriba)) BorraTemporizador(TPuertaEspArriba);
			}
			else MemoriaPeticion=1;
		}
		else
		// Guardada petición de bajada con FlancoBoton2Mando 
		if (MemoriaPeticion) {
			ActualizaManiobraPuerta(ManiobraCierrePuerta);
			ActualizaEstadoPuerta(PuertaBaja);
			if (ExisteTemporizador(TPuertaEspArriba)) BorraTemporizador(TPuertaEspArriba);
			MemoriaPeticion=0;
		}
		else
		// Paramos maniobra de apertura-cierre con el botón 1 del mando 
		if (FlancoBoton1Mando) {
			ActualizaManiobraPuerta(none);
			BorraTemporizador(TPuertaEspArriba);
		}
		else
		// Finaliza tiempo de espera abierta
		if (CompruebaEstadoTemp(TPuertaEspArriba)==1) {
			if (!CelulaPuerta[ValorActual]) {
				if (EstadoCerrojos[ValorActual]==CerrojAbajo) {
					BorraTemporizador(TPuertaEspArriba);
					ActualizaManiobraPuerta(ManiobraCierrePuerta);
					ActualizaEstadoPuerta(PuertaBaja);
				}
				else
				if (EstadoCerrojos[ValorActual]!=CerrojBaja) {
					ActualizaEstadoCerrojos(CerrojBaja);
     		 	ActualizaManiobraCerrojos(ManiobraAperturaCerrojos);
     		} 	
      }
		}
	}
	else
	// PUERTA BAJA
	if (EstadoPuerta[ValorActual]==PuertaBaja) {
		// Se activa la célula
		if (FlancoCelula) {
			AsignaTemporizador(TCelula,RetardoConexion,prioridad1,TiempoEsperaCelula,0);
			SetMascTemp(TCelula);
			ActualizaEstadoPuerta(PuertaEnMedio);
		}
		else
		if (FlancoPuertPorton) {
			AsignaTemporizador(TPuertaPorton,RetardoConexion,prioridad1,TiempoEspPuertaPorton,0);
			SetMascTemp(TPuertaPorton);
			ActualizaEstadoPuerta(PuertaEnMedio);
		}
		// Se llega a cerrar -> parar la bajada
 		if (PosicionPuerta[ValorActual]==PuertaAbajo) {
			ActualizaEstadoPuerta(PuertaAbajo);
			if (cerrojosON) {
				AsignaTemporizador(TPuertaAlCerrar,RetardoConexion,prioridad1,TiempoPuertaAlCerrar,0);
				SetMascTemp(TPuertaAlCerrar);
			}
			else ActualizaManiobraPuerta(none);
		}
		else 
		if (FlancoBoton1Mando) {
			AsignaTemporizador(TPuertaCambioManiobra,RetardoConexion,prioridad1,TimempoInversionGiro,0);
			SetMascTemp(TPuertaCambioManiobra);
			ActualizaEstadoPuerta(PuertaEnMedio);
		}
		else
		if (FlancoBoton2Mando) {
			ActualizaEstadoPuerta(PuertaEnMedio);
		}
		else 
		if (CompruebaEstadoTemp(TPerroGuardianPuerta)==1) {
			ActualizaEstadoPuerta(PuertaError);
			ActualizaManiobraPuerta(none);
		}
	}
	else 
	// PUERTA EN MEDIO
	if (EstadoPuerta[ValorActual]==PuertaEnMedio) {
		// Inversión sentido de apertura-cierre tras temporización
		if (CompruebaEstadoTemp(TPuertaCambioManiobra)==1) {
			BorraTemporizador(TPuertaCambioManiobra);
			// Si bajaba sube
			if (ManiobraPuerta[ValorActual]==ManiobraCierrePuerta) {
				ActualizaEstadoPuerta(PuertaSube);
				ActualizaManiobraPuerta(ManiobraAperturaPuerta);
			}
			else
			// Si subía baja
			if (ManiobraPuerta[ValorActual]==ManiobraAperturaPuerta) {
				ActualizaEstadoPuerta(PuertaBaja);
				ActualizaManiobraPuerta(ManiobraCierrePuerta);
			}
		}
		else
		// Tras interrumpir la célula en bajada 
		if (CompruebaEstadoTemp(TCelula)==1) {  
			// Continua bajando si se libera
			if (!CelulaPuerta[ValorActual]) {
				BorraTemporizador(TCelula);
				ActualizaEstadoPuerta(PuertaBaja);
				ActualizaManiobraPuerta(ManiobraCierrePuerta);
			}
		}
		else 
		if (CompruebaEstadoTemp(TPuertaPorton)==1) {
			if (!PuertPorton[ValorActual]) {
				BorraTemporizador(TPuertaPorton);
				if (EstadoPuerta[ValorAnterior]==PuertaBaja) ActualizaEstadoPuerta(PuertaBaja);
				else
				if (EstadoPuerta[ValorAnterior]==PuertaSube) ActualizaEstadoPuerta(PuertaSube);
			}
			else RelanzarTemporizador(TPuertaPorton);
		}
		else
		// Si se pulsa botón 2 baja
		if (FlancoBoton2Mando)	{
			ActualizaManiobraPuerta(ManiobraCierrePuerta);
			EvaluaPosicionCerrojos();
			if (PosicionCerrojos[ValorActual]==CerrojAbajo) {
				ActualizaEstadoPuerta(PuertaBaja);
			}
			else {
				ActualizaEstadoCerrojos(CerrojBaja);
				ActualizaManiobraCerrojos(ManiobraCierreCerrojos);
			}
		}
		else
		// Si se pulsa botón 1 sube 	
		if (FlancoBoton1Mando) {
			ActualizaEstadoPuerta(PuertaSube);
			ActualizaManiobraPuerta(ManiobraAperturaPuerta);
		}
		else
		// Tras temporizar TiempoEsperaEnMedio
		if (CompruebaEstadoTemp(TPuertaEspEnMedio)==1) {
			BorraTemporizador(TPuertaEspEnMedio);
			ActualizaManiobraPuerta(ManiobraCierrePuerta);
			if (PosicionCerrojos[ValorActual]==CerrojAbajo) ActualizaEstadoPuerta(PuertaBaja);
      else {
      	ActualizaEstadoCerrojos(CerrojBaja);
      	ActualizaManiobraCerrojos(ManiobraCierreCerrojos);
      }
		}
	}
	else 
	// AVERIA
	if (EstadoPuerta[ValorActual]==PuertaError) {

	}
}

void ActualizaManiobraPuerta(byte maniobra) {
	ManiobraPuerta[ValorAnterior]=ManiobraPuerta[ValorActual];
	ManiobraPuerta[ValorActual]=maniobra;
	CambioManiobraPuerta=1;		
}

void ActualizaEstadoPuerta(byte estado) {
	ManiobraPuerta[ValorAnterior]=ManiobraPuerta[ValorActual];
	ManiobraPuerta[ValorActual]=estado;
	CambioEstadoPuerta=1;		
}

void InicializaPuerta(void) {
	if (EstadoPuerta[ValorActual]==PuertaEnMedio) {
		if (PosicionCerrojos[ValorActual]==CerrojAbajo) {
			ActualizaEstadoPuerta(PuertaBaja);
			SPosteriorPuerta();
		}
		else {
			ActualizaEstadoCerrojos(CerrojBaja);
			ActualizaManiobraCerrojos(ManiobraCierreCerrojos);
			SPosteriorCerrojos();
		}
		
	}
	else 
	if (EstadoPuerta[ValorActual]==PuertaAbajo) {

	}
	else 
	if (EstadoPuerta[ValorActual==PuertaArriba]) {

	}
	
}

void InicializaVariablesPuerta(void) {
	if (EventoPuerta) EventoPuerta=0;
	if (CambioManiobraPuerta) CambioManiobraPuerta=0;
	if (CambioEstadoPuerta) CambioEstadoPuerta=0;
	if (CombinacionCorrecta) CombinacionCorrecta=0;
}