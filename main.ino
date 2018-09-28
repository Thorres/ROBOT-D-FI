/*
Projet: Déplacement Robot B Défi parcours
Equipe: P-10
Auteurs: Simon Torres, 
Description: Permet de compléter le défi du parcours
Date: 2018-09-27
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include <LibRobus.h> // Essentielle pour utiliser RobUS



/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces


/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup()
{
  BoardInit();
  Serial.println("Hello");
  delay(2000);
  AvancerCorriger(10);
  Serial.println("Hello 35 !");
}


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() {
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU
}
/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void AvancerCorriger(int distance)
{
  float VG = 0.01;
  float VD = 0.01; 
  Serial.println("Hello 2 !");
  for(int i = 0; i < 30; i++) 
  {
    MOTOR_SetSpeed(LEFT, VG);
    MOTOR_SetSpeed(RIGHT, VD);

    delay(100);

    VD = AjustTrajec(VD);

    RenitClics();

    VG += 0.01;
    VD += 0.01; 
    int h = 3 + i;
    Serial.print("Hello  ");
    Serial.print(h);
    Serial.print(" !");
  }
  delay(3000);
  ReinitMoteurs();
}
void ReinitMoteurs()
{
  MOTOR_SetSpeed(LEFT, 0.0);
  MOTOR_SetSpeed(RIGHT, 0.0);
  ENCODER_ReadReset(LEFT);
  ENCODER_ReadReset(RIGHT);
  Serial.println("Hello 34 !");
}

void RenitClics () {
  ENCODER_ReadReset(LEFT);
  ENCODER_ReadReset(RIGHT);
}

float AjustTrajec(float vintD) 
{
  float leftClic = ENCODER_Read(LEFT);
  float rightClic = ENCODER_Read(RIGHT);
  float modifMoteur = 0, diffClic = 0, diffPond = 0, kP = 0.0001;
/*Serial.print("Nombre de clics gauche ajustment : ");
  Serial.println(leftClic);
  Serial.print("Nombre de clics droit ajustment : ");
  Serial.println(rightClic);
  Serial.println("---------------------------------");*/

  //Calcul de la difference de clic en moteur droit et gauche
  diffClic = leftClic - rightClic;
  diffPond = diffClic * kP;
  modifMoteur = diffPond + vintD;
  return modifMoteur;
}


