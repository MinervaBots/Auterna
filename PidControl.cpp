# include  "PidControl.h"
# include  <Arduino.h>

PID :: PID ()
{

}

void  PID :: setOutputLimits ( float minOutput, float maxOutput)
{
  _minOutput = minOutput;
  _maxOutput = maxOutput;

  _lastOutput = constrain (_lastOutput, _minOutput, _maxOutput);
  _integrativeSum = constrain (_integrativeSum, _minOutput, _maxOutput);
}

void  PID :: setTunings ( float  kP , float  kI , float  kD )
{
  _kP = kP ;
  _kI = kI ;
  _kD = kD ;
}

void  PID :: setSampleTime ( unsigned  long newSampleTime)
{
  if (newSampleTime> 0 )
  {
    _sampleTime = newSampleTime;
  }
}

void  PID :: setSetPoint ( float setPoint)
{
  _setPoint = setPoint;
}

float  PID :: compute ( float input )
{
  unsigned long now = millis ();
  unsigned long timeChange = (now - _lastRunTime);
  if (timeChange <_sampleTime)
  {
    return _lastOutput;
  }

  float error = _setPoint - input;

  // Salva o valor acumulado do fator integrativo
  // Isso torna uma possibilidade variável constante busca por grupo
  // na saída, já que o coeficiente que multiplica o acumulo do erro já não é mais o mesmo.
  // Se o Ki muda, então não podemos deixar de integrar como um dos dos meus
  // PID clássico logo nossa equação para o termo integrativo fica:
  //
  //             Integral [t0 = 0, tf = agora] {Ki (t) * e (t) * dt}
  //
  // Na verdade essa equação é o "jeito certo" de se fazer PID, mas considerando Ki constante,
  // uma constante é integral e simplifica o calculo.
  //
  // Com uma otimização de uma variação do tempo multiplicado a uma constante de integração,
  // temos que um integral integral não erro multiplicado apenas pela constante de integração:
  _integrativeSum += error * _kI * _sampleTime;
  // Limita a integraçao para evitar que continue integrando além do permitido pelo sistema
  // Ex: PWM (0 ~ 255)
  _integrativeSum = constrain (_integrativeSum, _minOutput, _maxOutput);

  // Faz uma derivada da entrada para evitar o "chute derivado", que ocorre mudando
  // o setPoint. Esse fenomeno ocorre por mudar o valor do setPoint causa uma
  // variação instantânea no erro, e derivada
  // ao tempo é "infinito" (na prática não é então mesmo que acaba sendo um valor muito muito grande).
  // Esse número entra no PID sem um sinal de saída.
  //
  // Solução:
  //         d (E (t)) / dt = (d (SetPoint (t)) / dt) - (d (Entrada (t)) / dt)
  //
  // Considere que o setPoint é uma função constante em relação ao tempo, logo:
  //                       d SP (t) / dt = 0
  //
  // Como uma constante de derivação já está em uma variação do tempo, multiplamos ela pela diferença
  // da entrada atual com a ultima entrada, e então a derivada do erro é simplesmente igual a
  // menos uma derivada do sinal de entrada:
  float dInput = (_kD * (input - _lastInput)) / _sampleTime;
  float dError = -dInput;

  // Cálculo a saída do PID e salva numa váriavel
  _lastOutput = (_kP * error) + (_integrativeSum) + (dError);
  // Limite a saída de acordo com o valor definido pelo usuário.
  // Cada sistema tem um valor de saída mínimo e máximo.
  _lastOutput = constrain (_lastOutput, _minOutput, _maxOutput);

  _lastInput = input;
  _lastRunTime = now;

  return _lastOutput;
}
