void GestionAlarma(void) {
	
	if (EventoAlarma||EventoTiempo) ControlEstadoAlarma();

	if (CambioEstadoAlarma) {
		SAnteriorAlarma();
		SPosteriorAlarma();
	}
	else 
	if (EjecContinuaAcAlarma) SPosteriorAlarma();

	InicializaVariablesAlarma();
	
}

void ControlEstadoAlarma(void) {
	if (EstadoAlarma[ValorActual]==AlarmaDescon) {
		/* if (activaalarma) {
			AsignaTemporizador(TAlarma,RetardoConexion,prioridad1,TiempoEnPrearmada,0);
			SetMascTemp(TAlarma);
			ActualizaEstadoAlarma(AlarmaPreArmada);
		}	*/
	}
	else 
	if (EstadoAlarma[ValorActual]==AlarmaArmada) {
		if (CombinacionCorrecta)	{
			AsignaTemporizador(TAlarma,RetardoConexion,prioridad1,TiempoEnPendIdentif,0);
			SetMascTemp(TAlarma);
			ActualizaEstadoAlarma(AlarmaPendIdent);
		}
		else 
		if (ActivaAlarma) {
			AsignaTemporizador(TAlarma,RetardoConexion,prioridad1,TiempoAlarmaActiva,0);
			SetMascTemp(TAlarma);
			ActualizaEstadoAlarma(AlarmaActiva);
		}
	}
	else 
	if (EstadoAlarma[ValorActual]==AlarmaPreArmada) {
		if (CompruebaEstadoTemp(TAlarma)==1) {
			BorraTemporizador(TAlarma);
			ActualizaEstadoAlarma(AlarmaArmada);
		}
	}
	else 
	if (EstadoAlarma[ValorActual]==AlarmaActiva) {
		/*if (identificacionRFID) {
			ActualizaEstadoAlarma(AlarmaDescon);

		}
		else */
		if (CompruebaEstadoTemp(TAlarma)==1) {
			BorraTemporizador(TAlarma);
			ActualizaEstadoAlarma(AlarmaDescon);
		}
	}
	else 
	if (EstadoAlarma[ValorActual]==AlarmaPendIdent) {
		/*if (identificacionRFID) {
			ActualizaEstadoAlarma(AlarmaDescon);

		}
		else */
		if (CompruebaEstadoTemp(TAlarma)==1) {
			CambiarCuentaTemporizador(TAlarma,TiempoAlarmaActiva);
			ActualizaEstadoAlarma(AlarmaActiva);
		}
	}
}

void ActualizaEstadoAlarma(byte estado) {
	EstadoAlarma[ValorAnterior]=EstadoAlarma[ValorActual];
	EstadoAlarma[ValorActual]=estado;
	CambioEstadoAlarma=1;
}

void InicializaVariablesAlarma(void) {
	if (CambioEstadoAlarma) CambioEstadoAlarma=0;
	if (ActivaAlarma) ActivaAlarma=0;
	if (EventoAlarma) EventoAlarma=0;
}