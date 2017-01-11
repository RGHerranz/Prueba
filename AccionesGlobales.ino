boolean CambiaLuzExterior(boolean valor) {
	if (SenalLumExt!=valor) {
		if (valor) {
			digitalWrite(pinSenalLuminExt, HIGH);
			SenalLumExt=1;
		}
		else {
			digitalWrite(pinSenalLuminExt, LOW);
			SenalLumExt=0;
		}
		return(1);
	}
	return(0);
}