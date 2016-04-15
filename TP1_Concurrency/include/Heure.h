/*************************************************************************
						   Heure.h  -  description
							 -------------------
	début                : Mercredi 03 février 2016
	copyright            : (C) 2016 par Mathieu Maranzana
	e-mail               : Mathieu.Maranzana@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tache <Heure> (fichier Heure.h) -------------
#ifndef HEURE_H
#define HEURE_H

//------------------------------------------------------------------------
// Rôle de la tache <Heure>
//    Cette tache est chargee de l'affichage periodique (toutes les
//    <PERIODE> secondes (on pose <PERIODE> = 1 seconde)) de l'heure
//    courante dans la zone adequate de l'ecran du TP (en haut, a droite).
//    La fin de la tache <Heure> est declenchee a la reception du
//    signal <SIGUSR2>.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisees

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
pid_t ActiverHeure(void);
// Mode d'emploi :
//    - cette fonction lance une tache fille <Heure> chargee de
//      l'affichage periodique (toutes les <PERIODE> secondes) de l'heure
//      courante dans la zone <HEURE> de l'ecran du TP
//    - la fin de la tache <Heure> est declenchee à la reception du
//      signal <SIGUSR2>
//    - renvoie le PID de la tache <Heure>, si sa creation se passe bien
//    - renvoie -1 en cas d'echec à la creation de la tache <Heure>
//
// Contrat : aucun
//


#endif // HEURE_H
