#include <stdio.h>
#include <string.h>
#include <time.h>
     //+++++++++++++++++++++++++++++STRUCTURES+++++++++++++++++++++++++++++++++++++++++
	 
	 
	  
                struct Tache {
                        int id;
                        char titre[50];
                        char description[200];
                        char deadline[11]; 
                        char statut[20];
                           };

// ===================================D�clarations =========================================
           struct Tache taches[1000];
            int nbTaches = 0;
            int prochainID = 1;
//++++++++++++++++++++++++++++++++++AFFICHAGE+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void afficherMenu() {
    printf("\nMenu :\n");
    printf("1. Ajouter une nouvelle t�che\n");
    printf("2. jouter plusieurs taches\n");
    printf("3. Afficher la liste de toutes les t�ches\n");
    printf("4. Modifier une t�che\n");
    printf("5. Supprimer une t�che\n");
    printf("6. Rechercher des t�ches\n");
    printf("7. Afficher les statistiques\n");
    printf("8. Trier les Taches par titre\n");
    printf("9. Trier les Taches par deadline\n");
    printf("0. Quitter\n");
}

//+++++++++++++++++++AJOUTERTACHE+++++++++++++++++++++++++++++

  void ajouterTache() {
    struct Tache nouvelleTache;
    nouvelleTache.id = prochainID++;
    printf("Titre de la t�che : ");
    scanf(" %[^\n]s", nouvelleTache.titre);
    printf("Description de la t�che : ");
    scanf(" %[^\n]s", nouvelleTache.description);
    printf("Deadline (YYYY-MM-DD) : ");
    scanf("%s", nouvelleTache.deadline);
    printf("Statut de la t�che (� r�aliser, en cours de r�alisation, finalis�e) : ");
    scanf(" %[^\n]s", nouvelleTache.statut); // Utilisez %[^\n]s pour collecter toute la ligne, y compris les espaces.

    taches[nbTaches++] = nouvelleTache;
    printf("T�che ajout�e avec succ�s.\n");
}

//++++++++++++++++++AJOUTERPLUSIEURSTACHES+++++++++++++++++++++++++++
  
  void ajouterplusieurstaches(){
  	 {
  	 	int i;
        int nombreTachesAAjouter;
        printf("Combien de t�ches voulez-vous ajouter ? : ");
        scanf("%d", &nombreTachesAAjouter);
        for( i= 0; i < nombreTachesAAjouter; i++){
            ajouterTache();
        }

        printf("%d t�ches ajout�es avec succ�s.\n", nombreTachesAAjouter);
    }
  }
  
  //+++++++++++++++++++++++++++++AFFICHAGE++++++++++++++++++++++++++++++++++
  
  
void afficherToutesLesTaches() {
    printf("\nListe de toutes les t�ches :\n");
    int i;
    for(i = 0; i < nbTaches; i++) {
        printf("ID : %d\n", taches[i].id);
        printf("Titre : %s\n", taches[i].titre);
        printf("Description : %s\n", taches[i].description);
        printf("Deadline : %s\n", taches[i].deadline);
        printf("Statut : %s\n", taches[i].statut);
        printf("-----------\n");
    }
}
  //++++++++++++++++++++++++++++++++++ Tri ++++++++++++++++++++
void trierTachesParTitre() {
	int i,j;
    for (i = 0; i < nbTaches - 1; i++) {
        for (j = i+1; j < nbTaches ; j++) {
            if (strcmp(taches[j].titre, taches[j + 1].titre) > 0) {
                // �changer les t�ches
                struct Tache temp = taches[j];
                taches[j] = taches[i];
                taches[i] = temp;
            }
        }
    }
    printf("T�ches tri�es par ordre alphab�tique du titre :\n");
    afficherToutesLesTaches();
}

// +++++++++++++++++++++++++++++++Fonction pour trier les t�ches par deadline+++++++++++++++++++++++++++++++++++++
void trierTachesParDeadline() {
	int i,j;
    for (i = 0; i < nbTaches - 1; i++) {
        for ( j = 0; j < nbTaches - i - 1; j++) {
            if (strcmp(taches[j].deadline, taches[j + 1].deadline) > 0) {
                // �changer les t�ches
                struct Tache temp = taches[j];
                taches[j] = taches[j + 1];
                taches[j + 1] = temp;
            }
        }
    }
    printf("T�ches tri�es par deadline :\n");
    afficherToutesLesTaches();
}

//+++++++++++++++++++MOFIFICATION++++++++++++++++++++++++++++++++++++++++

void modifierTache(int id) {
	int i;
    for (i = 0; i < nbTaches; i++) {
        if (taches[i].id == id) {
            printf("Nouveau titre de la t�che : ");
            scanf(" %[^\n]s", taches[i].titre);
            printf("Nouvelle description de la t�che : ");
            scanf(" %[^\n]s", taches[i].description);
            printf("Nouveau deadline (YYYY-MM-DD) : ");
            scanf("%s", taches[i].deadline);
            printf("Nouveau statut de la t�che (� r�aliser, en cours de r�alisation, finalis�e) : ");
            scanf("%s", taches[i].statut);
            printf("T�che modifi�e avec succ�s.\n");
            return;
        }
    }
    printf("T�che avec l'ID %d non trouv�e.\n", id);
}


//+++++++++++++++++++++++++++++++++++SUPPRESSSION++++++++++++++++++++++++++++++++


void supprimerTache(int id) {
	int i,j;
    for (i = 0; i < nbTaches; i++) {
        if (taches[i].id == id) {
            for (j = i; j < nbTaches - 1; j++) {
                taches[j] = taches[j + 1];
            }
            nbTaches--;
            printf("T�che supprim�e avec succ�s.\n");
            return;
        }
    }
    printf("T�che avec l'ID %d non trouv�e.\n", id);
}



//++++++++++++++++++++++++++++++DEADLINE+++++++++++++++++++++++++++++++++++++++
void afficherTachesDeadlineProche() {
    time_t maintenant;
    time(&maintenant);
    int i;
    printf("\nT�ches dont le deadline est dans 3 jours ou moins :\n");
    for (i = 0; i < nbTaches; i++) {
        struct tm dateDeadline;
        sscanf(taches[i].deadline, "%4d-%2d-%2d", &dateDeadline.tm_year, &dateDeadline.tm_mon, &dateDeadline.tm_mday);
        dateDeadline.tm_year -= 1900; 
        dateDeadline.tm_mon--; 
        double diff = difftime(maintenant, mktime(&dateDeadline));
        int joursRestants = (int)(diff / (24 * 3600)); 

        if (joursRestants <= 3) {
            printf("ID : %d\n", taches[i].id);
            printf("Titre : %s\n", taches[i].titre);
            printf("Deadline : %s\n", taches[i].deadline);
            printf("Jours restants : %d\n", joursRestants);
            printf("-----------\n");
        }
    }
}
//++++++++++++++++++++++++++++++++++++++++modifierDescriptionTache++++++++++++++++++++++++++++++++++++++++++++++++++

void modifierDescriptionTache(int id) {
	int i;
    for (i = 0; i < nbTaches; i++) {
        if (taches[i].id == id) {
            printf("Entrez la nouvelle description pour la t�che %d : ", id);
            scanf("%s", taches[i].description);
            printf("Description mise � jour avec succ�s.\n");
            return;
        }
    }
    printf("Aucune t�che avec l'identifiant %d n'a �t� trouv�e.\n", id);
}
//++++++++++++++++++++++++++++++++++++++++modifierDeadlineTache++++++++++++++++++++++++++++++++++++++++++++++++++

void modifierDeadlineTache(int id) {
	int i;
    for (i = 0; i < nbTaches; i++) {
        if (taches[i].id == id) {
            printf("Entrez la nouvelle deadline (date limite) pour la t�che %d : ", id);
            scanf("%s", taches[i].deadline);
            printf("Deadline mise � jour avec succ�s.\n");
            return;
        }
    }
    printf("Aucune t�che avec l'identifiant %d n'a �t� trouv�e.\n", id);
}

//++++++++++++++++++++++++++++++++++++++++modifierStatutTache++++++++++++++++++++++++++++++++++++++++++++++++++

void modifierStatutTache(int id) {
	int i;
    for (i = 0; i < nbTaches; i++) {
        if (taches[i].id == id) {
            printf("Entrez le nouveau statut pour la t�che %d : ", id);
            scanf("%s", taches[i].statut);
            printf("Statut mis � jour avec succ�s.\n");
            return;
        }
    }
    printf("Aucune t�che avec l'identifiant %d n'a �t� trouv�e.\n", id);
}
//++++++++++++++++++++++++++++++++++++++++rechercherTacheParId++++++++++++++++++++++++++++++++++++++++++++++++++


void rechercherTacheParId(int id) {
    printf("\nRecherche de la t�che par identifiant %d :\n", id);
    printf("ID\tTitre\tDescription\tDeadline\tStatut\n");
    int i;
    for (i = 0; i < nbTaches; i++) {
        struct Tache tache = taches[i];
        if (tache.id == id) {
            printf("%d\t%s\t%s\t%s\t%s\n", tache.id, tache.titre, tache.description, tache.deadline, tache.statut);
            return;
        }
    }
    printf("Aucune t�che avec l'identifiant %d n'a �t� trouv�e.\n", id);
}



//++++++++++++++++++++++++++++++++++++++++rechercherTacheParTitre++++++++++++++++++++++++++++++++++++++++++++++++++
void rechercherTacheParTitre(char titre[100]) {
    printf("\nRecherche de la t�che par titre '%s' :\n", titre);
    printf("ID\tTitre\tDescription\tDeadline\tStatut\n");
    int trouve = 0;
    int i;
    for (i = 0; i < nbTaches; i++) {
        if (strcmp(taches[i].titre, titre) == 0) {
            printf("%d\t%s\t%s\t%s\t%s\n", taches[i].id, taches[i].titre, taches[i].description, taches[i].deadline, taches[i].statut);
            trouve = 1;
        }
    }
    if (!trouve) {
        printf("Aucune t�che avec le titre '%s' n'a �t� trouv�e.\n", titre);
    }
}

// +++++++++++++++++++++++++STATISTIQUES+++++++++++++++++++++++++++
void afficherStatistiques() {
    printf("\nStatistiques :\n");
    printf("Nombre total de t�ches : %d\n", nbTaches);

    int tachesTerminees = 0;
    int tachesNonTerminees = 0;

    // Obtenir la date actuelle en secondes
    time_t maintenant;
    time(&maintenant);
	int i;
    printf("\nJours restants jusqu'au d�lai de chaque t�che :\n");

    for (i = 0; i < nbTaches; i++) {
        struct tm dateDeadline;
       // memset(&dateDeadline, 0, sizeof(struct tm)); // Initialisation � z�ro pour �viter des valeurs ind�finies

        // Utiliser sscanf pour extraire l'ann�e, le mois et le jour de la date de la t�che
        int annee, mois, jour;
        if (sscanf(taches[i].deadline, "%4d-%2d-%2d", &annee, &mois, &jour) == 3) {
            dateDeadline.tm_year = annee - 1900;
            dateDeadline.tm_mon = mois - 1;
            dateDeadline.tm_year = jour;
        } else {
            // G�rer les erreurs d'analyse de la date ici, si n�cessaire
        }

        // Convertir la date limite en time_t
        time_t deadline = mktime(&dateDeadline);

        // Calculer la diff�rence en secondes entre la date limite et la date actuelle
        double diff = difftime(deadline, maintenant);

        // Convertir la diff�rence en jours (en prenant en compte les secondes par jour)
        int joursRestants = (int)(diff / (24 * 3600));

        if (joursRestants < 0) {
            printf("ID : %d\n", taches[i].id);
            printf("Titre : %s\n", taches[i].titre);
            printf("Deadline : %s\n", taches[i].deadline);
            printf("La t�che est en retard de : %d jours\n", -joursRestants);
            printf("-----------\n");
        } else {
            printf("ID : %d\n", taches[i].id);
            printf("Titre : %s\n", taches[i].titre);
            printf("Deadline : %s\n", taches[i].deadline);
            printf("Jours restants : %d\n", joursRestants);
            printf("-----------\n");
        }

        if (strcmp(taches[i].statut, "finalis�e") == 0) {
            tachesTerminees++;
        } else {
            tachesNonTerminees++;
        }
    }

    printf("Nombre de t�ches termin�es : %d\n", tachesTerminees);
    printf("Nombre de t�ches non termin�es : %d\n", tachesNonTerminees);
}

//++++++++++++++++++++++MAIN+++++++++++++++++++++++//


int main() {
    
	int choix;

    do {
       afficherMenu();
        
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
		int choixModification;
		int idSuppression;
		int choixRecherche;
		int idRecherche;
		int choixstatut;
		char titreRecherche[100];
		
		

		
		switch (choix) {
            case 1:
                ajouterTache();
                break;
            case 2:
            	ajouterplusieurstaches();
            case 3:
                afficherToutesLesTaches();
                break;
            case 4:
                // Sous-menu pour la modification
                
                printf("Menu de modification :\n");
                printf("1. Modifier la description d'une t�che\n");
                printf("2. Modifier le statut d'une t�che\n");
                printf("3. Modifier le deadline d'une t�che\n");
                printf("Entrez votre choix : ");
                scanf("%d", &choixModification);

                int idModification;
                printf("Entrez l'identifiant de la t�che � modifier : ");
                scanf("%d", &idModification);

                switch (choixModification) {
                    case 1:
                        modifierDescriptionTache(idModification);
                        break;
                    case 2:
                        modifierStatutTache(idModification);
                        break;
                    case 3:
                        modifierDeadlineTache(idModification);
                        break;
                    default:
                        printf("Choix invalide pour la modification.\n");
                }
                break;
            case 5:
                
                printf("Entrez l'identifiant de la t�che � supprimer : ");
                scanf("%d", &idSuppression);
                supprimerTache(idSuppression);
                break;
            case 6:
                // Sous-menu pour la recherche
                
                printf("Menu de recherche :\n");
                printf("1. Rechercher une t�che par son Identifiant\n");
                printf("2. Rechercher une t�che par son Titre\n");
				printf("3.Rechercher une tt�che par  "); 
                printf("Entrez votre choix : ");
        
                scanf("%d", &choixRecherche);

                switch (choixRecherche) {
                    case 1:
                        
                        printf("Entrez l'identifiant de la t�che � rechercher : ");
                        scanf("%d", &idRecherche);
                        rechercherTacheParId(idRecherche);
                        break;
                    case 2:
                        
                        printf("Entrez le titre de la t�che � rechercher : ");
                        scanf(" %[^\n]s", titreRecherche);
                        rechercherTacheParTitre(titreRecherche);
                       break;
                    default:
                        printf("Choix invalide pour la recherche.\n");
                }        	
		
                break;
            case 7:
                afficherStatistiques();
                break;
            case 0:
                printf("Au revoir !\n");
            case 8:
            	printf("\ntrier les taches par titre");
            	trierTachesParTitre();
                break;
            case 9:
            	printf("\ntrier les tache par deadline");
            	trierTachesParDeadline();
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}


