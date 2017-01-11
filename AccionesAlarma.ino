
void SPosteriorAlarma(void) {
	byte i;
	// Alarma Armada
	if (EstadoAlarma[ValorActual]==AlarmaArmada) {
		if (CambioEstadoAlarma) {

		}
	}
	else
	// Alarma Desconectada 
	if (EstadoAlarma[ValorActual]==AlarmaDescon) {
		if (CambioEstadoAlarma) {

		}
	}
	else
	// Alarma Pre-Armada 
	if (EstadoAlarma[ValorActual]==AlarmaPreArmada) {
		if (CambioEstadoAlarma) {

		}
	}
	else
	// Alarma Activa 
	if (EstadoAlarma[ValorActual]==AlarmaActiva) {
		if (CambioEstadoAlarma) {
			AsignaTemporizador(RelojAlarma,CiclosReloj,prioridad1,TiempoNivelAltoEnAlarma,TiempoNivelBajoEnAlarma);
			EjecContinuaAcAlarma=1;
		}
		if (EventoTiempo) {
			i=GetIndiceTemp(RelojAlarma);
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
	}
} 


void SAnteriorAlarma(void) {
	// Salimos de Alarma Armada
	if (EstadoAlarma[ValorAnterior]==AlarmaArmada) {

	}
	else
	// Salimos de Alarma Desconectada 
	if (EstadoAlarma[ValorAnterior]==AlarmaDescon) {

	}
	else
	// Salimos de Alarma Pre-Armada 
	if (EstadoAlarma[ValorAnterior]==AlarmaPreArmada) {

	}
	else
	// Salimos de Alarma Activa
	if (EstadoAlarma[ValorAnterior]==AlarmaActiva) {
		CambiaLuzExterior(LuzExteriorOFF);
		// desactiva sirena
		BorraTemporizador(RelojAlarma);
	}
}