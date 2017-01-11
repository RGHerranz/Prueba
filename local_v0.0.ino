#include <Wire.h>

//local_v0.0.ino
#define NumTempMax 6

// Resultado
#define VueltaError 255

// Seleccion
#define TodasOpciones 254

// Temporizadores
// ArrayTemp[0] Temporizador
// ArrayTemp[1] Cuenta1
// ArrayTemp[2] Cuenta2

unsigned long int ArrayTemp[3][NumTempMax];

#define CuentaInicialTempor 0
#define CuentaFinal1Tempor 1
#define CuentaFinal2Tempor 2

boolean TipoTemporizador[NumTempMax];
byte prioridadesTemp[NumTempMax];
byte IdentificadorTemp[NumTempMax];
boolean FinCuenta[NumTempMax];
boolean mascaraTemp[NumTempMax];
boolean EstadoReloj[NumTempMax];
boolean CambioTempor[NumTempMax];
byte CuentasPendientes=0;
byte numtempoRC=0;
byte numrelojes=0;

// Identificador Temporizador
#define none 0
#define TPuertaEspArriba 1
#define TPuertaCambioManiobra 2
#define TPuertaEspEnMedio 3
#define TPuertaAlCerrar 4
#define TPuertaPorton 5
//#define TMuestreoPosPuerta 6
#define TPulsacionMando 7
#define RelojPuerta 8
#define TCelula 9
#define TCerrojEspera 20
#define TRebotes 25
#define TRebotes2 26
#define RelojAlarma 30
#define TAlarma 31
#define TLuz 40
#define TExtractor 50
#define TMemoriaPeticion 100
#define TPerroGuardianPuerta 150
#define TPerroGuardianCerrojos 151

// Prioridades
//#define prioridad0 0
#define prioridad1 1
#define prioridad2 2
#define prioridad3 3
#define prioridad4 4
#define prioridad5 5
#define prioridad6 6
#define prioridad7 7

// Tipo temporizador
#define RetardoConexion 0
#define CiclosReloj 1


// Cuentas de tiempo
#define NumMaxCuentas 6
unsigned long int ArrayCuentas[NumMaxCuentas];
byte NumActCuentas=0;

byte Cuenta1Tiempo=VueltaError;
byte Cuenta2Tiempo=VueltaError;

// Identificador cuenta
/*
#define none 0
#define cuenta1 1
#define cuenta2 2
#define cuenta3 3
#define cuenta4 4
*/

// Valores
#define ValorInicial 128
#define ValorAnterior 0
#define ValorActual 1
/*
#define Estado0 0
#define Estado1 1
#define Estado2 2
*/
#define ModoManual 1
#define ModoAutomatico 2

byte ModoSistema=ModoManual;
// Eventos
boolean EventoPuerta=0, EventoMando=0, EventoCerrojos=0, EventoExtractor=0, EventoLuz=0,
EventoGlobal=0, EventoTiempo=0, EventoAlarma=0, EventoPuertaPeqPor=0, EventoPuertaAM=0,
EventoCelula=0;

// Maniobra Puerta
	//Variables
	// Estado
  byte PosicionPuerta[2];
  byte EstadoPuerta[2];
  byte ManiobraPuerta[2];
  // Maniobra
  boolean Boton1Mando[2]={0,0},FlancoBoton1Mando=0;
  boolean Boton2Mando[2]={0,0},FlancoBoton2Mando=0;
  boolean MemoriaPeticion=0;
  boolean PuertPorton[2]={0,0},FlancoPuertPorton=0;
  
  //boolean FlancoSenPuertaArriba=0;
  //boolean FlancoSenPuertaAbajo=0;
  boolean CelulaPuerta[2]={0,0};
  boolean FlancoCelula=0;
  boolean AlimenCelula=0;
  boolean CambioEstadoPuerta=0;
  boolean CambioManiobraPuerta=0;
  boolean EjecContinuaAcPuerta=0;
    
	// Definición de estados
	#define PuertaArriba 0
	#define PuertaEnMedio 1
  #define PuertaAbajo 2
	#define PuertaSube 3
  #define PuertaBaja 4
  #define PuertaError 5
	 
  // Definición de modos de maniobra
  #define ManiobraAperturaPuerta 1
  #define ManiobraCierrePuerta 2

  // Valores variables
  #define celulaOFF 0
  #define celulaON 1 

	// Tiempos
	#define TiempoMaxSubidaPuerta 150000
	#define TiempoMaxBajadaPuerta 150000
  #define TiempoEsperaArriba  20000
  #define TiempoEsperaEnMedio 10000
  #define TimempoInversionGiro 500
  #define TiempoEsperaCelula 1000
  #define TiempoAdicMaxMando 401
  #define TiempoRebotesMando 1200
  #define TiempoRelojPuertaON 200
  #define TiempoRelojPuertaOFF 800
  #define TiempoPuertaAlCerrar 300
  #define TiempoEspPuertaPorton 3000
  #define TiempoMaxSubidaPuerta 20000
  #define TiempoMaxBajadaPuerta 20000
  //#define TiempoMuestreoPosPuerta 120000

  #define NumPulsaCalMandoMax 10
  byte NumPulsaCalMando=NumPulsaCalMandoMax;
  unsigned long int ArrayTempReb[NumPulsaCalMandoMax];
  unsigned long int TiempoRebMando=0;
  

	// Pines de entradas
	#define pinBoton1MandoPuerta 1 		// pin mando remoto apertura puerta
	#define pinBoton2MandoPuerta 2
  #define pinPuertaArriba 3		// pin puerta arriba
	#define pinPuertaAbajo 4		// pin puerta abajo
  #define pinCelulaPuerta 5
  #define pinPuertaPeqPorton 6

	// Pines de salida
  #define pinMotorPuertaSube 1  
  #define pinMotorPuertaBaja 2
  #define pinAlimCelula 3
  
	
// Maniobra cerrojos
	// Variables
	// Estado
	boolean PosicionCerrojo[2][3][4];
  byte NumCerrojos[3];              // Número de cerrojos Arriba - En medio - Abajo
  boolean FlancoSCerrojoArriba[4];
  boolean FlancoSCerrojoAbajo[4];
	
  byte PosicionCerrojos[2];
  byte EstadoCerrojos[2];
  byte ManiobraCerrojos[2];
  boolean CambioEstadoCerrojos=0;
  boolean CambioManiobraCerrojos=0;
  boolean EjecContinuaAcCerrojos=0;
   
  // Habilitar o inhibir uso
  boolean cerrojosON=1;
  // Fallo
  boolean falloCerroj=0;

	// Definición de estados
	#define CerrojArriba 0
  #define CerrojEnMedio 1
	#define CerrojAbajo 2
  #define CerrojSube 3
  #define CerrojBaja 4
  #define CerrojError 7
	
  // Definición de modos de maniobra
  #define ManiobraAperturaCerrojos 1
  #define ManiobraCierreCerrojos 2

 	// Tiempos
	#define TiempoMaxSubidaCer 3000
	#define TiempoEsperaCerrojo 300
  #define TiempoMaxSubidaCerrojos 3000
  #define TiempoMaxBajadaCerrojos 3000

	// Pines de entradas
	#define pinSensorSupCer1 7
  #define pinSensorInfCer1 8
  #define pinSensorSupCer2 9
  #define pinSensorInfCer2 10
  #define pinSensorSupCer3 11
  #define pinSensorInfCer3 12
  #define pinSensorSupCer4 13
  #define pinSensorInfCer4 14

  // Pines de salidas
  #define pinMotorCerSubeBaja 4 // 1:Sube 0:Baja
  #define pinMotorCerAlim 5 // 1:Alimentado 0:Sin tensión

  
// Extractor
  // Variables
  // Estado
  byte EstadoExtractor[2];
  boolean CambioEstadoExtractor=0;
  byte ModoExtractor[2];
	
  // Definición de estados
	#define ExtractorApagado 1
	#define ExtractorVel1 2
	#define ExtractorVel2 3

  // Definicion de modo
  #define ExtractModoManual 0
  #define ExtractModoAuto 1

  // Pines de entrada
  #define pinEstExtractVel1 15 //i2c
  #define pinEstExtractVel2 16 //i2c

  // Pines de salida
  #define pinMotorExtractVel1 6 //i2c
  #define pinMotorExtractVel2 7 //i2c
    
  
// Iluminación
  //Variables
  // Estado
  // EstadoIluminacion[x][0] Techo del elevador
  // EstadoIluminacion[x][1] Lateral del elevador
  // EstadoIluminacion[x][2] Techo entrada circuito 1
  // EstadoIluminacion[x][3] Techo entrada circuito 2
  // EstadoIluminacion[x][4] Entrada lateral derecho
  // EstadoIluminacion[x][5] Entrada lateral izquierdo
  boolean EstadoCircIlum[2][8];
  byte ModoIluminacion[2][7];
  boolean CambioEstadoLuz[7];
    
	// Definición de modos
	#define IlumDesact 0
  #define IlumModoManual 1
  #define IlumModoTemp 2
  #define IlumModoAuto 3
	
  // Definición de circuitos
  #define CircTechoElev 0
  #define CircLatIzqElev 1
  #define CircLatDerElev 2
  #define Circ1TechoEnt 3
  #define Circ2TechoEnt 4
  #define CircEntLatDer 5
  #define CircEntLatIzq 6
  #define CircLuzBano 7

  // Pines de entrada
  #define pinEstLuzTechoElev 17   //i2c
  #define pinEstLuzLatIzqElev 18  //i2c
  #define pinEstLuzLatDerElev 19  //i2c   
  #define pinEstLuzTechoEntC1 20  //i2c
  #define pinEstLuzTechoEntC2 21  //i2c       
  #define pinEstLuzEntLatDer 22   //i2c
  #define pinEstLuzEntLatIzq 23   //i2c
  #define pinEstLuzBano 24        //i2c
  #define pinCelulaExt 25         //i2c

  // Pines de salida
  #define pinLuzTechoElev 8       //i2c
  #define pinLuzLatIzqElev 9      //i2c
  #define pinLuzLatDerElev 10     //i2c
  #define pinLuzTechoEntC1 11     //i2c
  #define pinLuzTechoEntC2 12     //i2c
  #define pinLuzEntLatDer 13      //i2c
  #define pinLuzEntLatIzq 14      //i2c
  #define pinLuzBano 15           //i2c
  

// Alarma - identificación
	// Variables
  // Estados
  // Matriz estados alarma
  byte EstadoAlarma[2];
  // Variables
  boolean SenalLumExt=0;
  #define LuzExteriorOFF 0
  #define LuzExteriorON 1 
  boolean CambioEstadoAlarma=0;
  boolean EjecContinuaAcAlarma=0;

  // Sensores alarma:
  // 0 PuertaAM, 1 DetectorHumos, 2 Detector Pres, 3 PuertaPorton, 4 PuertaGrande
  #define PuertaAM 0
  #define DHumos 1
  #define DPresencia 2
  #define PuertaPorton 3
  #define PuertaGrande 4
   
  boolean EstadoSensoresAlarma[2][5];
  // 1: Botón 1 - 2: Botón 2
  // B1 B2 B1 B2 B1 B2: 1 2 1 2 1 2
  #define NumPulsacionesCodigoMando 6
  byte ClaveMandoRemoto[NumPulsacionesCodigoMando]={1,1,2,1,1,2};
  byte ClaveTempMando[NumPulsacionesCodigoMando]={0,0,0,0,0,0};
  byte NumPulsacionesMando=0;
  byte NumIntentosMando=0;
  boolean CombinacionCorrecta=0;
  boolean ActivaAlarma=0;
  #define NumIntentosMandoMax 3

  boolean EstadoPuertaEntAM[2]={0,0};
  boolean EstadoDetectorPres[2]={0,0};
  

  // Tiempos
  #define TiempoEnPreArmada 60000
  #define TiempoEnPendIdentif 150000
  #define TiempoAlarmaActiva 120000
  #define TiempoNivelAltoEnAlarma 300
  #define TiempoNivelBajoEnAlarma 700

  // Estados
	#define AlarmaDescon 1
	#define AlarmaPreArmada 2
	#define AlarmaArmada 3
  #define AlarmaActiva 4
  #define AlarmaPendIdent 5

  // Pines de entrada
  #define pinPuertaEntAM 26
  #define pinDetectorHumos 27
  #define pinDetectorPres 28
  
  // Pines de salida
  #define pinSirena 16
  #define pinSenalLuminExt 17

// Se necesitan 5 pines para la RFID

// Otros 2 mínimo para el display-teclado


void setup() {
  byte i;
  byte j;

	DefineES();

  randomSeed(A0);

  // Inicialización temporizadores
  for (j=0;j<NumTempMax;i++) {
    for (i=0;i<3;i++) {
      ArrayTemp[i][j]=0;
    }
    TipoTemporizador[j]=0;
    IdentificadorTemp[j]=none;
    prioridadesTemp[j]=prioridad1;
    FinCuenta[j]=0;
    mascaraTemp[j]=0;
    EstadoReloj[j]=0;
    CambioTempor[j]=0;
  }

  // Inicialización cuentas
  for (i=0;i<NumMaxCuentas;i++) ArrayCuentas[i]=0;

  // Inicialización estado de la puerta
  
  PararPuerta(TodasOpciones);

  EstadoPuerta[ValorAnterior]=ValorInicial;
  ManiobraPuerta[ValorAnterior]=ValorInicial;
  PosicionPuerta[ValorAnterior]=ValorInicial;
  
  ManiobraPuerta[ValorActual]=none;

  // Definir PosicionPuerta[ValorActual]
  EvaluaPosicionPuerta();
  
  // Fija el estado de la puerta inicial
  if (PosicionPuerta[ValorActual]==PuertaAbajo) EstadoPuerta[ValorActual]=PuertaAbajo;
  else 
  if (PosicionPuerta[ValorActual]==PuertaArriba) EstadoPuerta[ValorActual]=PuertaArriba;
  else EstadoPuerta[ValorActual]=PuertaEnMedio;

  
  // Inicialización estado cerrojos
  
  PararCerrojos();

  PosicionCerrojos[ValorAnterior]=ValorInicial;
  EstadoCerrojos[ValorAnterior]=ValorInicial;
  ManiobraCerrojos[ValorAnterior]=ValorInicial;
  
  ManiobraCerrojos[ValorActual]=none;
  
  // Evalua PosicionCerrojos[ValorActual]
  EvaluaPosicionCerrojos();

  // Fijar estado inicial de los cerrojos
  if (PosicionCerrojos[ValorActual]==CerrojArriba) EstadoCerrojos[ValorActual]=CerrojArriba;
  else
  if (PosicionCerrojos[ValorActual]==CerrojAbajo) EstadoCerrojos[ValorActual]=CerrojAbajo;
  else EstadoCerrojos[ValorActual]=CerrojEnMedio;

  // Acción inicial puerta/cerrojos

  if (EstadoPuerta[ValorActual]==PuertaEnMedio) {
    AsignaTemporizador(TPuertaEspEnMedio,RetardoConexion,prioridad1,TiempoEsperaEnMedio,0);
    SetMascTemp(TPuertaEspEnMedio);
  }
  else 
  if (EstadoPuerta[ValorActual]==PuertaArriba) {
    AsignaTemporizador(TPuertaEspArriba,RetardoConexion,prioridad1,TiempoEsperaArriba,0);
    SetMascTemp(TPuertaEspArriba);
  }

  // Inicialización estado extractor
  EstadoExtractor[ValorAnterior]=ValorInicial;
  ModoExtractor[ValorAnterior]=ValorInicial;
  ModoExtractor[ValorActual]=ExtractModoManual;
  
  if (digitalRead(pinEstExtractVel1)) EstadoExtractor[ValorActual]=ExtractorVel1;
  else 
  if (digitalRead(pinEstExtractVel2)) EstadoExtractor[ValorActual]=ExtractorVel2;
  else EstadoExtractor[ValorActual]=ExtractorApagado;
  

  // Inicialización estado luz
  for (i=0;i<7;i++) {
    ModoIluminacion[ValorAnterior][i]=ValorInicial;
    ModoIluminacion[ValorActual][i]=IlumModoManual;
    EstadoCircIlum[ValorAnterior][i]=0;
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

  // Inicializacion estado alarma
  EstadoAlarma[ValorAnterior]=ValorInicial;
  EstadoAlarma[ValorActual]=AlarmaDescon;

  for (i=0;i<4;i++) EstadoSensoresAlarma[ValorAnterior][i]=0;

  if (digitalRead(pinPuertaEntAM)) EstadoSensoresAlarma[ValorActual][PuertaAM]=1;
  else EstadoSensoresAlarma[ValorActual][PuertaAM]=0;

  if (digitalRead(pinDetectorHumos)) EstadoSensoresAlarma[ValorActual][DHumos]=1;
  else EstadoSensoresAlarma[ValorActual][DHumos]=0;

  if (digitalRead(pinDetectorPres)) EstadoSensoresAlarma[ValorActual][DPresencia]=1;
  else EstadoSensoresAlarma[ValorActual][DPresencia]=0;

  if (digitalRead(pinPuertaPeqPorton)) EstadoSensoresAlarma[ValorActual][PuertaPorton]=1;
  else EstadoSensoresAlarma[ValorActual][PuertaPorton]=0;

  if (digitalRead(!pinPuertaAbajo)) EstadoSensoresAlarma[ValorActual][PuertaGrande]=1;
  else EstadoSensoresAlarma[ValorActual][PuertaGrande]=0;
}

void loop() {

  if (ModoSistema==ModoAutomatico) {
    // Comprobar entradas y disparo eventos
    LecturaEntradas();

    // Gestión temporizadores
    if (numrelojes||numtempoRC) {
      EventoTiempo=ActualizaCuentaTempor();
    }

    //if (EstadoAlarma[ValorActual]==)

    GestionAlarma();
    GestionPuerta();
    GestionLuz();
    GestionExtractor(); 
     
    PuestaCeroVarCiclo();
  }
  else
  if (ModoSistema==ModoManual) {
    


    
  }

  // Peticiones teclado y visualización
  
}
