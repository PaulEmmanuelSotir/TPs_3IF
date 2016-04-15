/*************************************************************************
						   Menu.h  -  description
							 -------------------
	debut                : Mercredi 03 fevrier 2016
	copyright            : (C) 2016 par Mathieu Maranzana
	e-mail               : Mathieu.Maranzana@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Menu> (fichier Menu.h) -----------------
#ifndef MENU_H
#define MENU_H

//------------------------------------------------------------------------
// Rôle du module <Menu>
//    Ce module est en charge de la gestion du menu (interface homme - machine)
//    de l'application multitâche gerant le parking.
//    Les commandes autorisees sont :
//      1. e|E : declenche la fin de l'application multitâche
//      2. p|P : declenche l'arrivee d'un usager prof
//      3. a|A : declenche l'arrivee d'un usager autre
//      4. s|S : declenche la sortie d'un vehicule du parking
//    Ce module se charge aussi de la mise a jour de l'ecran du TP
//    (zone <Commande> et <Message>).
//------------------------------------------------------------------------

////////////////////////////////////////////////////////////////// INCLUDE
//--------------------------------------------------- Interfaces utilisees

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

/////////////////////////////////////////////////////////////////// PUBLIC
//---------------------------------------------------- Fonctions publiques
void Menu(void);
// Mode d'emploi :
//    - les commandes autorisees sont :
//      1. e|E : declenche la fin de l'application multitâche
//      2. p|P : saisie de l'arrivee d'un usager prof
//               un usager prof peut se presenter a la porte Blaise Pascal
//               (file PROFS) ou a la porte Gaston Berger (pas de file
//               particulière)
//               le choix de cette porte suit immediatement le declenchement
//               de l'arrivee d'un usager prof
//               en cas d'erreur de saisie du numero de la porte, on reitère
//               la demande
//      3. a|A : saisie de l'arrivee d'un usager autre
//               un usager autre peut se presenter a la porte Blaise Pascal
//               (file AUTRES) ou a la porte Gaston Berger (pas de file
//               particulière)
//               le choix de cette porte suit immediatement le declenchement
//               de l'arrivee d'un usager autre
//               en cas d'erreur de saisie du numero de la porte, on reitère
//               la demande
//      4. s|S : declenchement de la sortie d'un vehicule du parking
//               ce declenchement est suivi de la saisie du numero de la place
//               de parking ([1,8], limite graphique) (choix de la voiture qui
//               quittera le parking)
//               bien evidemment, il est conseille de choisir une place
//               actuellement occupee par un vehicule
//      toutes les autres commandes genèrent une erreur et declenchent une
//      nouvelle saisie
//      pour les quatre commandes licites, le menu appelle la procedure
//      <Commande> en respectant la convention suivante pour les paramètres
//      (=> interfaçage possible avec le menu)
//        1. e|E : code = 'E' et valeur = 0
//        2. p|P : code = 'P' et valeur = numero de la porte
//        3. a|A : code = 'A' et valeur = numero de la porte
//        4. s|S : code = 'S' et valeur = numero de la place
//      => le prototype impose de <Commande> est donc le suivant :
//            void Commande ( char code, unsigned int valeur );
//
// Contrat : aucun
//


#endif // MENU_H
