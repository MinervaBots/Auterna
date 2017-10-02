//Possible PID Control


//Tempo para a integral e derivada (precisa ser testado)
#define DT 0.002
int millis(){
}
//vari�veis globais
float integral = 0;
float derivative = 0;
float proportional = 0;
float lastError= 0;
float PID_ERRO= 0;
float lastRun = 0;

//Seria uma boa colocar uma fun��o para dar set nas v�riaveis?
float Ki = 20;// numeros hipot�ticos
float Kp = 1;
float Kd = 21;


//fun��o para controle PID. A ideia � que receba como argumento o erro gerado pelo controle de sensores
float PID (float error){
	// evita que fa�a verifica��o desnecess�rias
	//precisamos conseguir que o millis funcione como previsto
	if(millis()- lastRun>DT*100){	
		integral += Ki * error * DT;
 		derivative = Kd * (error -lastError) / DT;
   		lastError = error;
  		proportional = Kp * error;
    	lastRun = millis();
    	PID_ERRO = proportional + integral + derivative;
		return PID_ERRO;
	}
		return PID_ERRO;
}	



