#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#define MAX_PATIENTS 100  
#define MAX_NOM_LENGTH 100
#define MAX_PRENOM_LENGTH 100
//define quelque colors 
#define red "\033[1;31m"
#define fin "\033[0m"
// Tableau à 2 dimensions pour les informations des patients
// patients[i][0] -> Ref, patients[i][1] -> Nom, patients[i][2] -> Prenom, patients[i][3] -> Tel, patients[i][4] -> Age, patients[i][5] -> Statut, patients[i][6] -> Date
char patients[MAX_PATIENTS][7][100];  
int total_reservations = 12; // Total des réservations effectuées
int kb=12; //pour le Ref
void afficher_menue() {
    
    printf("\n\n\t\tBienvenue dans les options fournies par le programme: \n\n");
    printf("\t\t\t\t\033[1;36m1. Ajouter une reservation \n");
    printf("\t\t\t\t\033[1;36m2. Modifier ou supprimer une reservation \n");
    printf("\t\t\t\t\033[1;36m3. Afficher les details d'une reservation \n");
    printf("\t\t\t\t\033[1;36m4. Tri des reservations  \n");
    printf("\t\t\t\t\033[1;36m5. Recherche des reservations  \n");
    printf("\t\t\t\t\033[1;36m6. Statistiques  \n\033[0m");
    printf("\n\n\t\t**************************************************\n\n\n");
    
} 
void printYoucode() {
    printf("\n");
printf("\t\t\t\t");    printf("  Y     Y    OOOOO    U     U \033[1;34m CCCCC   OOOOO   DDDDD   EEEEE\n"fin);
printf("\t\t\t\t");    printf("   Y   Y    O     O   U     U \033[1;34m C      O     O  D    D  E\n"fin);
printf("\t\t\t\t");    printf("    Y Y     O     O   U     U  \033[1;34mC      O     O  D    D  EEEE\n"fin);
printf("\t\t\t\t");    printf("     Y      O     O   U     U \033[1;34m C      O     O  D    D  E\n"fin);
printf("\t\t\t\t");    printf("     Y       OOOOO     UUUUU  \033[1;34m CCCCC   OOOOO   DDDDD   EEEEE\n"fin);
printf("\t\t\t\t");    printf("\n\n\n");
printf(red"\t\t\t");    printf("  SSSSS     AAAAAA   SSSSS               SSSSS   AAAAAA   FFFFFF    IIIII\n");
printf(red"\t\t\t");    printf("  S         A    A   S                   S       A    A   F           I\n");
printf(red"\t\t\t");    printf("  SSSSS     AAAAAA   SSSSS               SSSSS   AAAAAA   FFFFFF      I\n");
printf(red"\t\t\t");    printf("      S     A    A       S                   S   A    A   F           I\n");
printf(red"\t\t\t");    printf("  SSSSS     A    A   SSSSS               SSSSS   A    A   F         IIIII\n");
printf(red"\t\t\t"fin);    printf("\n\n\n");
}
void afficher_tableau_patient(int max_patients) {
    
   printf("\n");
    printf("\t\t\033[1;34m----------------------------------------------------------------------------------------------------------\n\033[0m");
    printf("\t\t| %-12s | %-12s | %-12s | %-12s    |     %-14s %-12s | %-12s \n", 
       "Ref", "Nom", "Prenom", "Tel", "Age", "Statut", "Date");
    printf("\033[1;34m\t\t----------------------------------------------------------------------------------------------------------\n\033[0m");
    for (int i = 0; i < max_patients; i++) {
         if (strlen(patients[i][0]) > 0 && strlen(patients[i][1]) > 0 && strlen(patients[i][2]) > 0 && strlen(patients[i][3]) > 0) {
            printf("\t\t| %-12s | %-12s | %-12s | %-12s | %-12s | %-12s | %-12s \n",
                   patients[i][0], patients[i][1], patients[i][2], patients[i][3], patients[i][4], patients[i][5], patients[i][6]);
        }
        printf("\t\t\033[1;34m----------------------------------------------------------------------------------------------------------\n\033[0m"); 
    

}
}
int verifier_nombre_entier(char *chaine) {
    for (int i = 0; i < strlen(chaine); i++) {
        if (!isdigit(chaine[i])) {
            return 0; 
        }
    }
    int nombre = atoi(chaine);  
    return (nombre > 0 && nombre <= 6);
}
int verifier_alphabetique(char *chaine) { 
    if (strlen(chaine) == 0) {
        return 0;
    }
    for (int j = 0; j < strlen(chaine); j++) {
        if (!isalpha(chaine[j]) && chaine[j] != ' ') {  
            return 0;
        }
    }
    return 1;
}
void demander_saisie_nom_prenom(int i) {
    char buffer[MAX_NOM_LENGTH];  
    int valide = 0;

    while (!valide) {
        printf("\t\t\tDonner le nom du patient : ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  

        if (verifier_alphabetique(buffer)) {
            strncpy(patients[i][1], buffer, MAX_NOM_LENGTH - 1);
            patients[i][1][MAX_NOM_LENGTH - 1] = '\0';  
            valide = 1;
        } else {
            printf("\n\n\033[1;31m\n\n\t\t\tErreur : la chaîne \"%s\" contient des caractères non alphabétiques ou est vide.\n\033[0m\n\n\n", buffer);
        }
    }

    valide = 0;

    while (!valide) {
        printf("\t\t\tDonner le prenom du patient : ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (verifier_alphabetique(buffer)) {
            strncpy(patients[i][2], buffer, MAX_PRENOM_LENGTH - 1);
            patients[i][2][MAX_PRENOM_LENGTH - 1] = '\0';
            valide = 1;
        } else {
            printf("\t\t\t\033[1;31mErreur : la chaine \"%s\" contient des caracteres non alphabetiques ou est vide.\n\033[0m\n\n", buffer);
        }
    }
}
int verifier_age(char *chaine) {
    for (int i = 0; i < strlen(chaine); i++) {
        if (!isdigit(chaine[i])) {
            return 0;  // Non valide si ce n'est pas un chiffre
        }
    }
    int age = atoi(chaine);  
    return (age > 0 && age < 100);  // Vérifie si l'âge est dans la plage valide
}
void saisir_age(int i) {
    char age_str[10];  
    int valide = 0;

    while (!valide) {
        printf("\t\t\tDonner moi votre Age: ");
        fgets(age_str, sizeof(age_str), stdin);
        age_str[strcspn(age_str, "\n")] = '\0';  

        if (strlen(age_str) == 0) {
            printf("\033[1;31m\t\t\tErreur : vous devez entrer une valeur.\n\033[0m\n\n");
            continue;  
        }

        if (verifier_age(age_str)) {
            strncpy(patients[i][4], age_str, 10);
            valide = 1;  
        } else {
            printf("\n\n\033[1;31m\t\t\tErreur : veuillez entrer un âge valide (entre 1 et 99).\n\033[0m\n");
        }
    }
}
bool est_date_valide(const char *date_str) {
    int jour, mois, annee;
    if (sscanf(date_str, "%d/%d/%d", &jour, &mois, &annee) != 3) {
        return false;
    }
    if (annee < 2024) {
        return false;
    }

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int jour_actuel = tm_info->tm_mday;
    int mois_actuel = tm_info->tm_mon + 1;
    int annee_actuelle = tm_info->tm_year + 1900;

    if (annee < annee_actuelle ||
        (annee == annee_actuelle && mois < mois_actuel) ||
        (annee == annee_actuelle && mois == mois_actuel && jour < jour_actuel)) {
        return false;
    }

    if (mois < 1 || mois > 12 || jour < 1 || jour > 31) {
        return false;
    }

    if ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30) {
        return false;
    }

    if (mois == 2) {
        if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
            if (jour > 29) {
                return false;
            }
        } else {
            if (jour > 28) {
                return false;
            }
        }
    }

    return true;
}
void demander_date_reservation(int i) {
    while (1) {
        printf("\n\t\t\tDonner la date de reservation (JJ/MM/AAAA) : ");
        scanf("%s", patients[i][6]);
        while (getchar() != '\n');
        if (est_date_valide(patients[i][6])) { 
            break; 
        } else {
            printf("\n\t\t\t\033[1;31mLa date saisie est invalide\033[0m \n");
        }
    }
}
int verifierTel(char* tel) {
    if (strlen(tel) != 13) {
        return 0;
    }
    if (strncmp(tel, "+212", 4) != 0) {
        return 0;
    }
    if (tel[4] != '6' && tel[4] != '7') {
        return 0;
    }
    for (int i = 5; i < 13; i++) {
        if (!isdigit(tel[i])) {
            return 0;
        }
    }
    return 1;
}
void saisirTel(int i) {
    int valide = 0;
    do {
        printf("\t\t\tVeuillez entrer le N_Tel pour %s %s (format +2126xxxxxxxx ou +2127xxxxxxxx) : ", patients[i][1], patients[i][2]);
        scanf("%s", patients[i][3]);
        while (getchar() != '\n'); 
        if (verifierTel(patients[i][3])) {
            valide = 1;
        } else {
            printf("\n\n\t\t\033[1;31mNumero de telephone invalide.\033[0m\n\n");
        }
    } while (!valide);
}
void generer_reference(char *ref) {
    snprintf(ref, 10, "YC%04d", kb + 1);  // Formate la référence comme YC0001, YC0002, etc.
}
int convertirMoisEnNumero(char *mois) {
    if (strcmp(mois, "Janvier") == 0) return 1;
    if (strcmp(mois, "Février") == 0) return 2;
    if (strcmp(mois, "Mars") == 0) return 3;
    if (strcmp(mois, "Avril") == 0) return 4;
    if (strcmp(mois, "Mai") == 0) return 5;
    if (strcmp(mois, "Juin") == 0) return 6;
    if (strcmp(mois, "Juillet") == 0) return 7;
    if (strcmp(mois, "Août") == 0) return 8;
    if (strcmp(mois, "Septembre") == 0) return 9;
    if (strcmp(mois, "Octobre") == 0) return 10;
    if (strcmp(mois, "Novembre") == 0) return 11;
    if (strcmp(mois, "Décembre") == 0) return 12;
    return 0;  // Si le mois n'est pas valide
}
void extraireDate(char *date, int *jour, int *mois, int *annee) {
    // Extraire jour, mois, et année
    char jourStr[3], moisStr[10], anneeStr[5];
    
    sscanf(date, "%2s/%9s/%4s", jourStr, moisStr, anneeStr);  // Récupère jour, mois et année en texte
    
    *jour = atoi(jourStr);  // Convertir jour en entier
    *mois = convertirMoisEnNumero(moisStr);  // Convertir mois en entier
    *annee = atoi(anneeStr);  // Convertir année en entier
}
int comparerDates(char *date1, char *date2) {
    int jour1, mois1, annee1;
    int jour2, mois2, annee2;

    extraireDate(date1, &jour1, &mois1, &annee1);
    extraireDate(date2, &jour2, &mois2, &annee2);

    // Comparer année
    if (annee1 < annee2) return -1;
    if (annee1 > annee2) return 1;

    // Comparer mois
    if (mois1 < mois2) return -1;
    if (mois1 > mois2) return 1;

    // Comparer jour
    if (jour1 < jour2) return -1;
    if (jour1 > jour2) return 1;

    return 0;  // Les dates sont identiques
}


//

int main() {
    printYoucode();  
    printf("\n\n\t\t\033[1;34m Application permet de gerer les reservations de rendez-vous dentaires, offrant des fonctionnalites suivantes: \033[0m\n\n");

    int choix;
    kb=11;
    total_reservations = 11;  // Réinitialiser le total des réservations au démarrage du programme
    
   //data
    strcpy(patients[0][0], "YC0001");
    strcpy(patients[0][1], "Elhadi");
    strcpy(patients[0][2], "Amine");
    strcpy(patients[0][3], "+212612345678");
    strcpy(patients[0][4], "25");
    strcpy(patients[0][5], "Valider");
    strcpy(patients[0][6], "01/Jan/2024");

    strcpy(patients[1][0], "YC0002");
    strcpy(patients[1][1], "Bramid");
    strcpy(patients[1][2], "Oumayma");
    strcpy(patients[1][3], "+212612345679");
    strcpy(patients[1][4], "21");
    strcpy(patients[1][5], "Traiter");
    strcpy(patients[1][6], "14/Mar/2024");

    strcpy(patients[2][0], "YC0003");
    strcpy(patients[2][1], "Said");
    strcpy(patients[2][2], "Kamal");
    strcpy(patients[2][3], "+212612345680");
    strcpy(patients[2][4], "30");
    strcpy(patients[2][5], "Annuler");
    strcpy(patients[2][6], "05/Feb/2024");

    strcpy(patients[3][0], "YC0004");
    strcpy(patients[3][1], "Moulay");
    strcpy(patients[3][2], "Sara");
    strcpy(patients[3][3], "+212612345681");
    strcpy(patients[3][4], "28");
    strcpy(patients[3][5], "Valider");
    strcpy(patients[3][6], "22/Apr/2024");

    strcpy(patients[4][0], "YC0005");
    strcpy(patients[4][1], "Jalal");
    strcpy(patients[4][2], "Mohammed");
    strcpy(patients[4][3], "+212612345682");
    strcpy(patients[4][4], "32");
    strcpy(patients[4][5], "Reporter");
    strcpy(patients[4][6], "13/May/2024");

    strcpy(patients[5][0], "YC0006");
    strcpy(patients[5][1], "Benaissa");
    strcpy(patients[5][2], "Nour");
    strcpy(patients[5][3], "+212612345683");
    strcpy(patients[5][4], "27");
    strcpy(patients[5][5], "Traiter");
    strcpy(patients[5][6], "27/Jun/2024");

    strcpy(patients[6][0], "YC0007");
    strcpy(patients[6][1], "Alaoui");
    strcpy(patients[6][2], "Rania");
    strcpy(patients[6][3], "+212612345684");
    strcpy(patients[6][4], "24");
    strcpy(patients[6][5], "Annuler");
    strcpy(patients[6][6], "09/Jul/2024");

    strcpy(patients[7][0], "YC0008");
    strcpy(patients[7][1], "Fikri");
    strcpy(patients[7][2], "Youssef");
    strcpy(patients[7][3], "+212612345685");
    strcpy(patients[7][4], "35");
    strcpy(patients[7][5], "Valider");
    strcpy(patients[7][6], "30/Aug/2024");

    strcpy(patients[8][0], "YC0009");
    strcpy(patients[8][1], "Chakir");
    strcpy(patients[8][2], "Imane");
    strcpy(patients[8][3], "+212612345686");
    strcpy(patients[8][4], "29");
    strcpy(patients[8][5], "Reporter");
    strcpy(patients[8][6], "11/Sep/2024");

    strcpy(patients[9][0], "YC0010");
    strcpy(patients[9][1], "Haddad");
    strcpy(patients[9][2], "Omar");
    strcpy(patients[9][3], "+212612345687");
    strcpy(patients[9][4], "33");
    strcpy(patients[9][5], "Valider");
    strcpy(patients[9][6], "02/Oct/2024");

    strcpy(patients[10][0], "YC0011");
    strcpy(patients[10][1], "Belkadi");
    strcpy(patients[10][2], "Sana");
    strcpy(patients[10][3], "+212612345688");
    strcpy(patients[10][4], "26");
    strcpy(patients[10][5], "Traiter");
    strcpy(patients[10][6], "23/Nov/2024");
   
   
   //
    while (1) {
        afficher_menue();  // Affiche le menu des options
        printf("\t\t");
        printf("\t\t\t\n\n\033[1;32m\t\tChoisissez votre option parmi celles proposées : \033[0m");
        scanf("%d", &choix);  // Demande à l'utilisateur de faire un choix
        while(getchar() != '\n'); // Vide le buffer après la saisie d'un nombre

        switch (choix) {
            case 1:  // Ajouter une réservation
                if (total_reservations >= MAX_PATIENTS) {
                    printf("\033[1;31mLe maximum de réservations a été atteint. Impossible d'ajouter de nouveaux patients.\n\033[0m");
                    break;
                }

                printf("\n\t\t\033[1;34m *** Ajout d'une nouvelle réservation ***\t\t\n\n\033[0m");

                // Générer la référence unique pour le patient
                char ref[10];
                generer_reference(ref);

                // Saisie des informations du patient
                printf("\t\t\tRéférence : %s\n", ref);
                strncpy(patients[total_reservations][0], ref, 10);

                // Demande des informations personnelles
                demander_saisie_nom_prenom(total_reservations);
                saisir_age(total_reservations);
                saisirTel(total_reservations);
                demander_date_reservation(total_reservations);
                
                int valid = 0;  // Variable pour valider l'entrée

    while (!valid) {
        printf("\n\t\t\t\t\033[1;36mVeuillez entrer le statut du patient :\033[0m \n\n");
        printf("\t\t\t\t\033[1;34m1: \033[0mValider \n");
        printf("\t\t\t\t\033[1;34m2: \033[0mAnnuler \n");
        printf("\t\t\t\t\033[1;34m3: \033[0mReporter \n");
        printf("\t\t\t\t\033[1;34m4: \033[0mTraiter \n");
          
        printf("\n\n\t\t\tEntrer le statut du patient: ");
        if (scanf("%d", &choix) != 1) {  // Vérifier si la saisie est un entier
        while (getchar() != '\n');
            printf("\n\n\033[1;31m\t\t\tErreur: Vous devez entrer un chiffre entre 1 et 4.\033[0m\n\n");
            // Vider le buffer pour éviter une boucle infinie
            //while (getchar() != '\n');  // Ignorer les caractères restants dans le buffer
        } else if (choix < 1 || choix > 4) {
            printf("\n\n\033[1;31m\t\t\tErreur : Le choix doit être compris entre 1 et 4. Veuillez réessayer.\033[0m\n\n");

        } else {
            valid = 1;  // Si tout est correct, sortir de la boucle
        }
    }
               // while (getchar() != '\n'); 
                switch (choix) {
                    case 1:
                    strcpy(patients[total_reservations][5], "Valider");
                    break;
                    case 2:
                    strcpy(patients[total_reservations][5], "Annuler");
                    break;
                    case 3:
                    strcpy(patients[total_reservations][5], "Reporter");
                    break;
                    case 4:
                    strcpy(patients[total_reservations][5], "Traiter");
                    break;
                    default:
                    printf("Statut invalide.\n");
                    strcpy(patients[total_reservations][5], "inconnu");
                    break;}

                // Mise à jour du total des réservations
                total_reservations++;
                kb++;
                printf("\033[1;32m\n\n\t\tReservation ajoutee avec succes.\n\033[0m\n");
                break;

case 2:  // Modifier ou supprimer une réservation
    printf("\033[1;33m\n\n\t\tBienvenue dans la Phase de Modification ou Suppression : \n\n\033[0m");
    
    char buffer[100];  // Tampon pour stocker l'entrée utilisateur
    int valide = 0;
    int nombre = -1;

    printf("\tLe menu propose dans cette phase est le suivant :   \n\n");
    printf("\t\t0: Supprimer\n\t\t1: Modifier\n\n");

    while (!valide) {
        printf("\n\t\t\tEntrez un nombre (0 ou 1): ");
        fgets(buffer, sizeof(buffer), stdin);  // Lit l'entrée utilisateur
        buffer[strcspn(buffer, "\n")] = '\0';  // Supprime le retour à la ligne : fgets

        // Vérifier si l'entrée est vide
        if (strlen(buffer) == 0) {
            printf("\033[1;31mErreur : vous devez entrer une valeur.\n\033[0m");
            continue;  // Redemander la saisie
        }

        // Vérifier si l'entrée est un entier
        int est_entier = 1;
        for (int i = 0; i < strlen(buffer); i++) {
            if (!isdigit(buffer[i])) {  // Vérifie si chaque caractère est un chiffre
                est_entier = 0;
                break;
            }
        }

        if (!est_entier) {
            printf("\033[1;31m\n\n\t\tErreur : la saisie doit etre un entier.\n\n\033[0m");
            continue;  // Redemander la saisie
        }

        // Convertir la chaîne en entier
        nombre = atoi(buffer);

        // Vérifier si l'entier est bien 0 ou 1
        if (nombre != 0 && nombre != 1) {
            printf("\033[1;31mErreur : vous devez entrer 0 ou 1.\n\033[0m");
            continue;  // Redemander la saisie
        }

        // Si tout est correct, sortir de la boucle
        valide = 1;
    }

    if (nombre == 0) {  // Suppression d'une réservation
        char ref[50];
        printf("\t\tDonnez la référence du patient à supprimer : ");
        scanf("%s", ref);  // Demande la référence du patient à supprimer

        int found = 0;  // Variable pour vérifier si le patient existe
        for (int i = 0; i < total_reservations; i++) {
            // Si la référence correspond, on supprime la réservation
            if (strcmp(ref, patients[i][0]) == 0) {
                found = 1;
                // Décaler les réservations suivantes pour combler le vide
                for (int j = i; j < total_reservations - 1; j++) {
                    // Décaler toutes les informations d'un patient
                    strcpy(patients[j][0], patients[j + 1][0]);  // Référence
                    strcpy(patients[j][1], patients[j + 1][1]);  // Nom
                    strcpy(patients[j][2], patients[j + 1][2]);  // Prénom
                    strcpy(patients[j][3], patients[j + 1][3]);  // Age
                    strcpy(patients[j][4], patients[j + 1][4]);  // Téléphone
                    strcpy(patients[j][5], patients[j + 1][5]);  // Date
                }
                total_reservations--;  // Réduire le total des réservations
                printf("\033[1;32m\n\n\t\tReservation supprimee avec succes.\n\033[0m");
                break;
            }
        }

        if (!found) {
            printf("\033[1;31m\n\n\t\tErreur : Reference non trouvee.\n\n\033[0m");  // Si la référence n'existe pas
        }
    } 
    else if (nombre == 1) {  // Modification d'une réservation
        char ref[50];
        printf("\n\n\t\tDonnez la reference du patient a modifier : ");
        scanf("%s", ref);  // Demande la référence du patient à modifier

        int found = 0;  // Variable pour vérifier si le patient existe
        for (int i = 0; i < total_reservations; i++) {
            if (strcmp(ref, patients[i][0]) == 0) {
                found = 1;

                // Affichage des informations actuelles du patient
                printf("\n\033[1;36m\tInformations actuelles du patient:\n\033[0m");
                printf("\t\tReference: %s\n", patients[i][0]);
                printf("\t\tNom: %s\n", patients[i][1]);
                printf("\t\tPrenom: %s\n", patients[i][2]);
                printf("\t\tTelephone: %s\n", patients[i][3]);
                printf("\t\tAge: %s\n", patients[i][4]);
                printf("\t\tStatut: %s\n", patients[i][5]);
                printf("\t\tDate: %s\n", patients[i][6]);

                // Afficher le menu de modification
                printf("\n\033[1;32m\t\t\tQue souhaitez-vous modifier ?\n\n\033[0m");
                printf("\t\t\t\033[1;34m1:\033[0m Nom\n");
                printf("\t\t\t\033[1;34m2:\033[0mPrenom\n");
                printf("\t\t\t\033[1;34m3:\033[0m Telephone\n");
                printf("\t\t\t\033[1;34m4:\033[0m Age\n");
                printf("\t\t\t\033[1;34m5:\033[0m Statut\n");
                printf("\t\t\t\033[1;34m6:\033[0m Date\n");
                printf("\t\t\t\033[1;34m0:\033[0m Annuler\n");

                int choix_modif;
                printf("\n\t\tEntrez votre choix : ");
                scanf("%d", &choix_modif);

                switch (choix_modif) {
                    case 1:
                        printf("\t\t\tNouveau nom (actuel: %s) : ", patients[i][1]);
                        scanf("%s", patients[i][1]);
                        break;
                    case 2:
                        printf("\t\t\tNouveau prenom (actuel: %s) : ", patients[i][2]);
                        scanf("%s", patients[i][2]);
                        break;
                    case 3:
                        printf("\t\t\tNouveau telephone (actuel: %s) : ", patients[i][3]);
                        scanf("%s", patients[i][3]);
                        break;
                    case 4:
                        printf("\t\t\tNouvel Age (actuel: %s) : ", patients[i][4]);
                        scanf("%s", patients[i][4]);
                        break;
                    case 5:
                        printf("\t\t\tNouveau statut (actuel: %s) : ", patients[i][5]);
                        scanf("%s", patients[i][5]);
                        break;
                    case 6:
                        printf("Nouvelle date (actuelle: %s) : ", patients[i][6]);
                        scanf("%s", patients[i][6]);
                        break;
                    case 0:
                        printf("Modification annulee.\n");
                        break;
                    default:
                        printf("\t\t\t\033[1;31mChoix non valide.\n\n\n\033[0m");
                        break;
                }

                if (choix_modif >= 1 && choix_modif <= 6) {
                    printf("\n\n\t\t\t\033[1;32mReservation modifiee avec succes.\n\n\033[0m");
                }

                break;
            }
        }

        if (!found) {
            printf("\n\n\t\t\t\033[1;31mAucune reservation trouvee avec la reference donnee.\n\n\033[0m");
        }
    }

    else {
        printf("\n\n\t\t\t\033[1;31mChoix invalide. Veuillez essayer a nouveau.\n\n\033[0m");  // Gestion d'erreur pour un mauvais choix
    }
    break;


            case 3:  // Afficher les détails d'une réservation
                if (total_reservations == 0) {
                    printf("\n\n\t\t\t\033[1;31mAucune reservation a afficher.\n\n\033[0m");
                } else {
                    printf("\n\n\t\t\t\t\t\t***\033[1;34m Liste des reservations \033[0m***\n\n");

                    afficher_tableau_patient(total_reservations);
                }
                break;

         case 4:  // Tri des réservations
    printf("\n\n\t\033[1;33mMenu de tri des reservations\033[0m\n\n"); 
printf("\t\t\033[1;34m1.\033[0m Tri des reservations par Nom\n");
printf("\t\t\033[1;34m2.\033[0m Tri des reservations par Date\n");
printf("\t\t\033[1;34m3.\033[0m Tri des reservations par Statut\n");


    int choix;
    printf("\n\t\t\t\033[1;33mSelectionnez un type de tri : \033[0m");
    scanf("%d", &choix);

    if (choix == 1) {
        // Tri par nom déjà implémenté (croissant ou décroissant)
        printf("\n\t\033[1;34mTri par Nom :\033[0m\n\n");
        printf("\t\t\033[1;34m0\033[0m : Tri croissant \033[1;34m(A-Z)\033[0m\n");
        printf("\t\t\033[1;34m1\033[0m : Tri décroissant \033[1;34m(Z-A)\033[0m\n");

        int kl;
        printf("\n\t\033[1;34mChoisir un nombre d'option : \033[0m");
        scanf("%d", &kl);

        if (kl == 0) {
            // Tri croissant (A-Z)
            for (int i = 0; i < total_reservations - 1; i++) {
                for (int j = 0; j < total_reservations - i - 1; j++) {
                    if (strcmp(patients[j][1], patients[j + 1][1]) > 0) {
                        char temp[7][50];
                        for (int k = 0; k < 7; k++) {
                            strcpy(temp[k], patients[j][k]);
                            strcpy(patients[j][k], patients[j + 1][k]);
                            strcpy(patients[j + 1][k], temp[k]);
                        }
                    }
                }
            }
            printf("\n\n\033[1;32m\t\tReservations triees par nom (A-Z).\n\033[0m");
        } else if (kl == 1) {
            // Tri décroissant (Z-A)
            for (int i = 0; i < total_reservations - 1; i++) {
                for (int j = 0; j < total_reservations - i - 1; j++) {
                    if (strcmp(patients[j][1], patients[j + 1][1]) < 0) {
                        char temp[7][50];
                        for (int k = 0; k < 7; k++) {
                            strcpy(temp[k], patients[j][k]);
                            strcpy(patients[j][k], patients[j + 1][k]);
                            strcpy(patients[j + 1][k], temp[k]);
                        }
                    }
                }
            }
            printf("\t\t\033[1;32m\t\tReservations triees par nom (Z-A).\n\n\033[0m");
        } else {
            printf("\t\t\033[1;31mOption non valide.\n\n\033[0m");
        }

    } else if (choix == 2) {
        // Tri par date
        printf("\n\t\033[1;34mTri par Date :\033[0m\n\n");
        
        printf("\t\t\033[1;34m0\033[0m : Tri croissant \033[1;34m(plus ancienne -> plus recente)\033[0m\n");
        printf("\t\t\033[1;34m1\033[0m : Tri decroissant \033[1;34m(plus recente -> plus ancienne)\033[0m\n");
        

        int kl;
        printf("\n\t\t\t\033[1;33mChoisir un nombre d'option : \033[0m");
        scanf("%d", &kl);

        if (kl == 0) {
            // Tri croissant (plus ancienne -> plus récente)
            for (int i = 0; i < total_reservations - 1; i++) {
                for (int j = 0; j < total_reservations - i - 1; j++) {
                    if (comparerDates(patients[j][6], patients[j + 1][6]) > 0) {
                        char temp[7][50];
                        for (int k = 0; k < 7; k++) {
                            strcpy(temp[k], patients[j][k]);
                            strcpy(patients[j][k], patients[j + 1][k]);
                            strcpy(patients[j + 1][k], temp[k]);
                        }
                    }
                }
            }
            printf("\033[1;32m\t\t\n\n\t\tReservations triees par date (croissante).\n\033[0m");
        } else if (kl == 1) {
            // Tri décroissant (plus récente -> plus ancienne)
            for (int i = 0; i < total_reservations - 1; i++) {
                for (int j = 0; j < total_reservations - i - 1; j++) {
                    if (comparerDates(patients[j][6], patients[j + 1][6]) < 0) {
                        char temp[7][50];
                        for (int k = 0; k < 7; k++) {
                            strcpy(temp[k], patients[j][k]);
                            strcpy(patients[j][k], patients[j + 1][k]);
                            strcpy(patients[j + 1][k], temp[k]);
                        }
                    }
                }
            }
            printf("\t\t\033[1;32m\t\tReservations triees par date (decroissante).\n\n\033[0m");
        } else {
            printf("\n\n\t\t\033[1;31mOption non valide.\n\n\033[0m");
        }

    } else if (choix == 3) {
        // Tri par statut
        printf("\n\t\033[1;34mTri par Statut :\033[0m\n\n");
        printf("\t\t\t\t\033[1;34m1:\033[0m Valider\n");
        printf("\t\t\t\t\033[1;34m2:\033[0m Annuler\n");
        printf("\t\t\t\t\033[1;34m3:\033[0m Reporter\n");
        printf("\t\t\t\t\033[1;34m4:\033[0m Traiter\n");

        int kl;
        printf("\n\t\t\t\033[1;33mChoisir un numéro de statut : ");
        scanf("%d", &kl);

        char statutCherche[20];
        if (kl == 1) {
            strcpy(statutCherche, "Valider");
        } else if (kl == 2) {
            strcpy(statutCherche, "Annuler");
        } else if (kl == 3) {
            strcpy(statutCherche, "Reporter");
        } else if (kl == 4) {
            strcpy(statutCherche, "Traiter");
        } else {
            printf("\n\n\t\t\033[1;31mOption non valide.\n\n\033[0m");
            break;
        }

        // Afficher les réservations avec le statut sélectionné
        printf("\n\033[1;36m\tListe des reservations avec statut\033[0m : %s\n", statutCherche);
        int trouve = 0;
        for (int i = 0; i < total_reservations; i++) {
            if (strcmp(patients[i][5], statutCherche) == 0) {
                printf("\n\n\t\t\tReference: %s : Nom: %s, Prenom: %s\n",
                       patients[i][0], patients[i][1], patients[i][2]);
                trouve = 1;
            }
        }
        if (!trouve) {
            printf("\n\n\t\tAucune reservation avec le statut '%s' trouvee.\n\n", statutCherche);
        }

    } else {
        printf("\n\n\t\t\033[1;31mOption non valide.\n\n\033[0m");
    }

     //Affichage des résultats après tri
     printf("\n\033[1;36m\t\tListe des reservations triees:\n\033[0m");
    printf("\n");
    printf("\t\t\033[1;34m----------------------------------------------------------------------------------------------------------\n\033[0m");
    printf("\t\t| %-12s | %-12s | %-12s | %-12s    |     %-14s %-12s | %-12s \n", 
       "Ref", "Nom", "Prenom", "Tel", "Age", "Statut", "Date");
    printf("\033[1;34m\t\t----------------------------------------------------------------------------------------------------------\n\033[0m");

for (int i = 0; i < total_reservations; i++) {
    printf("\t\t| %-12s | %-12s | %-12s | %-12s | %-12s | %-12s | %-12s \n",
           patients[i][0],  // Référence
           patients[i][1],  // Nom
           patients[i][2],  // Prénom
           patients[i][3],  // Téléphone
           patients[i][4],  // Âge
           patients[i][5],  // Statut
           patients[i][6]); // Date
    printf("\t\t\033[1;34m----------------------------------------------------------------------------------------------------------\n\033[0m");
}
    break;


            case 5:  // Recherche des réservations
    printf("\033[1;33m\n\tRecherche\n\n\033[0m");
    printf("\t\tChoisir une méthode de recherche :\n");
    printf("\t\t\t\033[1;34m1:\033[0m Recherche par reference\n");
    printf("\t\t\t\033[1;34m2:\033[0m Recherche par nom\n");
    printf("\t\t\t\033[1;34m3:\033[0m Recherche par date (format jj/Mois/Année)\n");

    int choix_recherche;
    printf("\n\t\tEntrez votre choix : ");
    scanf("%d", &choix_recherche);

    // Variables de recherche
    char terme_recherche[50];
    int found = 0;  // Pour vérifier si une réservation correspond

    switch (choix_recherche) {
        case 1:
            // Recherche par référence
            printf("\t\t\tEntrez la reference du patient : ");
            scanf("%s", terme_recherche);
            break;
        case 2:
            // Recherche par nom
            printf("\t\t\tEntrez le nom du patient : ");
            scanf("%s", terme_recherche);
            break;
        case 3:
            // Recherche par date
            printf("\t\t\tEntrez la date de reservation (format jj/Mois/Annee) : ");
            scanf("%s", terme_recherche);
            break;
        default:
            printf("\n\n\t\t\t\033[1;31mChoix non valide.\n\n\033[0m");
            break;
    }

    // Affichage du tableau formaté
    printf("\t+-------+----------------+-------------+--------------------------+-----+--------------------+--------------------------+\n");
    printf("\t|  Ref  |      Nom       |   Prenom    |        Telephone         | Age |     Statut         |      Date                |\n");
    printf("\t+-------+----------------+-------------+--------------------------+-----+--------------------+--------------------------+\n");

    // Parcourir les réservations pour chercher une correspondance
    for (int i = 0; i < total_reservations; i++) {
        if ((choix_recherche == 1 && strcmp(patients[i][0], terme_recherche) == 0) ||  // Par référence
            (choix_recherche == 2 && strcmp(patients[i][1], terme_recherche) == 0) ||  // Par nom
            (choix_recherche == 3 && strcmp(patients[i][6], terme_recherche) == 0)) {  // Par date

            // Afficher la réservation trouvée
            printf("\t| %-5s | %-14s | %-11s | %-24s | %3s | %-14s | %-24s |\n",
                   patients[i][0], patients[i][1], patients[i][2], patients[i][3], patients[i][4], patients[i][5], patients[i][6]);
            found = 1;
        }
    }

    if (!found) {
        printf("\033[1;31mAucune reservation trouvee.\n\033[0m");
    }

    printf("\t+-------+----------------+-------------+--------------------------+-----+--------------------+--------------------------+\n");
    break;


            case 6:  // Statistiques 
    printf("\033[1;35m\n\n\tStatistiques de Notre Programme :\n\033[0m");
    printf("\n\t\tChoisir parmi les 3 options :\n\n");
    printf("\t\t\t\033[1;34m1:\033[0m Statistique par la moyenne d'age des patients ayant reserve\n");
    printf("\t\t\t\033[1;34m2:\033[0m Afficher le nombre de patients par tranche d'age (ex. : 0-18 ans, 19-35 ans, 36+ ans)\n");
    printf("\t\t\t\033[1;34m3:\033[0m Generer des statistiques pour connaître le nombre total de reservations par statut (Valider, Annuler, etc.)\n");

    int option;
    printf("\n\n\t\tEntrez votre choix : ");
    scanf("%d", &option);

    if (option == 1) {
        // Calculer la moyenne d'âge des patients ayant réservé
        int somme_age = 0;
        int nb_patients = 0;

        for (int i = 0; i < total_reservations; i++) {
            int age = atoi(patients[i][4]); // Conversion de l'âge en entier
            somme_age += age;
            nb_patients++;
        }

        if (nb_patients > 0) {
            float moyenne_age = (float)somme_age / nb_patients;
            printf("\n\n\033[1;33m\t\tMoyenne d'age des patients ayant reserve \033[0m: %.2f ans\n", moyenne_age);
        } else {
            printf("\n\n\033[1;31m\t\tAucune reservation trouvee pour calculer la moyenne d'age.\n\n\033[0m");
        }

    } else if (option == 2) {
        // Afficher le nombre de patients par tranche d'âge
        int tranche_0_18 = 0, tranche_19_35 = 0, tranche_36_plus = 0;

        for (int i = 0; i < total_reservations; i++) {
            int age = atoi(patients[i][4]); // Conversion de l'âge en entier
            if (age >= 0 && age <= 18) {
                tranche_0_18++;
            } else if (age >= 19 && age <= 35) {
                tranche_19_35++;
            } else if (age >= 36) {
                tranche_36_plus++;
            }
        }

        printf("\n\033[1;36m\tNombre de patients par tranche d'âge :\n\n\033[0m");
        printf("\t\t\033[1;32m0-18 ans :\033[0m %d patients\n", tranche_0_18);
        printf("\t\t\033[1;32m19-35 ans : \033[0m%d patients\n", tranche_19_35);
        printf("\t\t\033[1;32m36+ ans : %d\033[0m patients\n", tranche_36_plus);

    } else if (option == 3) {
        // Générer des statistiques pour connaître le nombre total de réservations par statut
        int valide = 0, annule = 0, reporte = 0, traite = 0;

        for (int i = 0; i < total_reservations; i++) {
            if (strcmp(patients[i][5], "Valider") == 0) {
                valide++;
            } else if (strcmp(patients[i][5], "Annuler") == 0) {
                annule++;
            } else if (strcmp(patients[i][5], "Reporter") == 0) {
                reporte++;
            } else if (strcmp(patients[i][5], "Traiter") == 0) {
                traite++;
            }
        }

        printf("\n\033[1;36m\n\tNombre total de reservations par statut :\n\n\033[0m");
        printf("\t\t\033[1;32mValider\033[0m  : %d reservations\n", valide);
        printf("\t\t\033[1;32mAnnuler\033[0m  : %d reservations\n", annule);
        printf("\t\t\033[1;32mReporter\033[0m : %d reservations\n", reporte);
        printf("\t\t\033[1;32mTraiter\033[0m  : %d reservations\n", traite);

    } else {
        printf("\n\n\t\t\033[1;31mOption non valide.\n\n\033[0m");
    }

    break;


            default:
                printf("\n\n\t\t\033[1;31mChoix invalide. Veuillez essayer à nouveau.\n\n\033[0m");
                break;
        }
    }

    return 0;
}
