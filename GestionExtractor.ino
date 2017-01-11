void GestionExtractor(void) {

	
}

void ActualizaEstadoExtractor(byte estado) {
	EstadoExtractor[ValorAnterior]=EstadoExtractor[ValorActual];
	EstadoExtractor[ValorActual]=estado;
}