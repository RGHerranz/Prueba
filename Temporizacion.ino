boolean AsignaTemporizador(byte ident, boolean tipo, byte prioridad, unsigned long int tiempo1, unsigned long int tiempo2) {
  boolean resultado=0;
  byte numtotal=numtempoRC+numrelojes;
  if (numtotal<NumTempMax) {
    ArrayTemp[CuentaInicialTempor][numtotal]=millis();
    ArrayTemp[CuentaFinal1Tempor][numtotal]=tiempo1;
    TipoTemporizador[numtotal]=tipo;
    IdentificadorTemp[numtotal]=ident;
    prioridadesTemp[numtotal]=prioridad;

    if (tipo==CiclosReloj) {
      ArrayTemp[CuentaFinal2Tempor][numtotal]=tiempo2;
      EstadoReloj[numtotal]=1;
      CambioTempor[numtotal]=1;
      numrelojes++;
    }
    else {
      if(FinCuenta[numtotal]) FinCuenta[numtotal]=0;
      numtempoRC++;
      CuentasPendientes++;
      mascaraTemp[NumTempMax]=0;
    }
    resultado=1;
  }
  return(resultado);
}  
  
boolean ActualizaCuentaTempor(void) {
  byte i;
  byte numtotal=numtempoRC+numrelojes;
  unsigned long int TActual;
  unsigned long int intervalo;
  unsigned long int valorinicial;
  unsigned long int cuenta;
  boolean resultado=0;

  for (i=0;i<numtotal;i++) {
    if (CambioTempor[i]) CambioTempor[i]=0;
  }

  TActual=millis();
  for (i=0;i<numtotal;i++) {
    valorinicial=ArrayTemp[CuentaInicialTempor][i];
    if (TipoTemporizador[i]==CiclosReloj) {
      if (TActual>=valorinicial) intervalo=TActual-valorinicial; 
      else intervalo=4294967295-valorinicial+TActual;
      
      if (EstadoReloj[i]) cuenta=ArrayTemp[CuentaFinal1Tempor][i];
      else cuenta=ArrayTemp[CuentaFinal2Tempor][i];

      if (intervalo>=cuenta) {
        EstadoReloj[i]=!EstadoReloj[i];
        ArrayTemp[CuentaInicialTempor][i]=TActual;
        CambioTempor[i]=1;
        if (!resultado) resultado=1;
      }
    }
    else 
    if (!FinCuenta[i]) {
      cuenta=ArrayTemp[CuentaFinal1Tempor][i];
      if (TActual>=valorinicial) intervalo=TActual-valorinicial;
      else intervalo=4294967295-valorinicial+TActual;
      if (intervalo>=cuenta) {
         FinCuenta[i]=1;
         CambioTempor[i]=1;
         CuentasPendientes--;
         if (!resultado) resultado=1;
      }
    }
    else resultado=1;
  }
  return(resultado);  
}
  
byte CompruebaEstadoTemp(byte ident) {
  byte i;
  if (numtempoRC) {
    i=GetIndiceTemp(ident);
    if(i!=VueltaError) {
      if (TipoTemporizador[i]==RetardoConexion) {
        if (FinCuenta[i]&&mascaraTemp[i]) return(1); else return(0);
      }
      else return(VueltaError);
    }
    else return(VueltaError);
  }
  else return(VueltaError);
}

byte CompruebaCuentaTemp(byte ident, unsigned long int cuenta) {
  byte i;
  unsigned long int TActual;
  unsigned long int valorinicial;
  unsigned long int intervalo;
  
  if (numtempoRC) {
    i=GetIndiceTemp(ident);
    if(i!=VueltaError) {
      if (TipoTemporizador[i]==RetardoConexion) {
        TActual=millis();
        valorinicial=ArrayTemp[CuentaInicialTempor][i];
        if (TActual>=valorinicial) intervalo=TActual-valorinicial;
        else intervalo=4294967295-valorinicial+TActual;
        if (intervalo>=cuenta) return(1); else return(0);
      }
      else return(VueltaError);
    }
    else return(VueltaError);
  }
  else return(VueltaError);
}

byte GetPrioridadTemp(byte ident) {
  byte i;
  byte num=numtempoRC+numrelojes;
  if (num) {
    for (i=0;i<num;i++) {
      if (IdentificadorTemp[i]==ident) return(prioridadesTemp[i]);
    }  
  }
  return(VueltaError);
}


byte GetIndiceTemp(byte ident) {
  byte i;
  byte num=numtempoRC+numrelojes;
  if (num) {
    for (i=0;i<(num);i++) {
      if (IdentificadorTemp[i]==ident) return(i);
    }
  }
  return(VueltaError);
}

boolean BorraTemporizador(byte ident) {
  byte i;
  byte num=numtempoRC+numrelojes;
  if (num) { 
    i=GetIndiceTemp(ident);
    if(i!=VueltaError) {
      if (TipoTemporizador[i]==RetardoConexion) {
        numtempoRC--; 
        if (!FinCuenta[i]) CuentasPendientes--; else FinCuenta[i]=0;
      }
      else {
        CambioTempor[i]=0;
        numrelojes--;
      }
      IdentificadorTemp[i]=none;
      if (num) OrdenaArrayTemporizadores(i);
      return(1);
    }
  }  
  return(0);  
}

boolean BorrarTodosTemporizadores(void) {
  byte i;
  byte num=numtempoRC+numrelojes;
  if (num) {
    for (i=0;i<num;i++) {
      IdentificadorTemp[i]=none;
      FinCuenta[i]=0;
    }
    if (numtempoRC) numtempoRC=0;
    if (numrelojes) numrelojes=0;
    if (CuentasPendientes) CuentasPendientes=0;
    CambioTempor[i]=0;
    return(1);
  }
  else return(0);  
}

//Borra todos los temporizadores que hayan finalizado su cuenta
byte BorrarTempFinalizadaCuenta(void) {
  byte i;
  byte j=0;
  byte num;
  byte temp;
  byte numtotal=numtempoRC+numrelojes;
  if (numtempoRC) {
    temp=numtempoRC-CuentasPendientes;
    if (temp>0) {
      for (num=0;num<temp;num++) {  
        for (i=j;i<numtotal;i++) {
          if (TipoTemporizador[i]==RetardoConexion) {
            if (FinCuenta[i]) break;
          }
        }
        j=i;  
        IdentificadorTemp[j]=none;
        FinCuenta[j]=0;
        if (numtempoRC>0) numtempoRC--;
        OrdenaArrayTemporizadores(j);
      }
      return(temp);
    }
    else
    if (!temp) return(0);
    else return(VueltaError);
  }    
}  

boolean OrdenaArrayTemporizadores(byte pos) {
  byte i;
  byte numtotal=numtempoRC+numrelojes;
  if (numtotal&&(numtotal<NumTempMax)) {
    if (pos==numtotal) return(0);
    
    for (i=pos;i<numtotal;i++) {
      ArrayTemp[CuentaInicialTempor][i]=ArrayTemp[CuentaInicialTempor][i+1];
      ArrayTemp[CuentaFinal1Tempor][i]=ArrayTemp[CuentaFinal1Tempor][i+1];
      ArrayTemp[CuentaFinal2Tempor][i]=ArrayTemp[CuentaFinal2Tempor][i+1];
      IdentificadorTemp[i]=IdentificadorTemp[i+1];
      FinCuenta[i]=FinCuenta[i+1];
      mascaraTemp[i]=mascaraTemp[i+1];
      prioridadesTemp[i]=prioridadesTemp[i+1];
      if (TipoTemporizador[i+1]==CiclosReloj) EstadoReloj[i]=EstadoReloj[i+1]; 
      TipoTemporizador[i]=TipoTemporizador[i+1];
    }
    return(1);
  }
  return(0);
}  

boolean ResetMascTemp(byte ident) {
  byte i;
  if (numtempoRC) { 
    i=GetIndiceTemp(ident);
    if (i!=VueltaError) {
     if (mascaraTemp[i]) mascaraTemp[i]=0;
     return(1);
    }
    else return(0);
  }
}

boolean SetMascTemp(byte ident) {
  byte i;
  if (numtempoRC) {
    i=GetIndiceTemp(ident);
    if (i!=VueltaError) {
     if (!mascaraTemp[i]) mascaraTemp[i]=1;
     return(1);
    }
    else return(0);
  }
}
  
boolean InhibirTodosTemp(void) {
  byte i;
  byte numtotal=numtempoRC+numrelojes;
  if (numtempoRC) {
    for (i=0;i<numtotal;i++) {
      if (TipoTemporizador[i]==RetardoConexion) {
        if (mascaraTemp[i]) mascaraTemp[i]=0;
      }
    }
    return(1);
  }
  else return(0);
}

byte GetPrioridadTEmp(byte ident) {
  byte i;
  byte numtotal=numtempoRC+numrelojes;
  for (i=0;i<numtotal;i++) {
    if (IdentificadorTemp[i]==ident) return(prioridadesTemp[i]);
  }
  return(0);
}

boolean ExisteTemporizador(byte ident) {
  byte i;
  i=GetIndiceTemp(ident);
  if (i!=VueltaError) return(1); else return(0);
}

boolean RelanzarTemporizador(byte ident) {
  byte i;
  boolean resultado=0;
  
  i=GetIndiceTemp(ident);
  if(i!=VueltaError) {
    ArrayTemp[CuentaInicialTempor][i]=millis();
    if (TipoTemporizador[i]==RetardoConexion) {
      if (FinCuenta[i]) {
        CuentasPendientes++;
        FinCuenta[i]=0;
      }
    }
    else {
      CambioTempor[i]=1;
      EstadoReloj[i]=1;
    }
    resultado=1;
  }
  return(resultado);
}

boolean CambiarCuentaTemporizador(byte ident, unsigned long int cuenta) {
  byte i;
  i=GetIndiceTemp(ident);
  if(i!=VueltaError) {
    if (TipoTemporizador[i]==RetardoConexion) {
      ArrayTemp[CuentaInicialTempor][i]=millis();
      ArrayTemp[CuentaFinal1Tempor][i]=cuenta;
      if (FinCuenta[i]) {
        CuentasPendientes++;
        FinCuenta[i]=0;
      }
    }
  }
}

byte AsignaCuentaTiempo(void) {
  byte i;
  if (NumActCuentas<NumMaxCuentas) {
    for (i=0;i<NumMaxCuentas;i++) {
      if (ArrayCuentas[i]==0) {
        ArrayCuentas[i]==millis();
        NumActCuentas++;
        return(i);
      }
    }
    return(VueltaError);
  }
  else return(VueltaError);
}

boolean ResetCuentaTiempo(byte identif) {
  if (identif<NumMaxCuentas) {
    ArrayCuentas[identif]=0;
    NumActCuentas--;
    return(1);
  } 
  else return(0);
}

unsigned long int ValorCuentaTiempo(byte identif) {
  unsigned long int TActual;
  unsigned long int valorinicial;
  unsigned long int intervalo;
  
  if (identif<NumMaxCuentas) {
    TActual=millis();
    valorinicial=ArrayCuentas[identif];
    if (TActual>=valorinicial) intervalo=TActual-valorinicial;
    else intervalo=4294967295-valorinicial+TActual;
    return(intervalo);
  }
  else return(VueltaError);
}