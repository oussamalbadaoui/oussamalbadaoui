#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int ID = 0;

typedef struct {
    int id;
    char marque[50];
    char modele[50];
    char type_carburant[20];
    int nombre_places;
    char transmission[20];
    float prix_location_par_jour;
    int disponibilite;
} Voiture;

void afficher_menu_principal() {
    printf("\nBienvenue dans l'application de gestion de location de voitures\n");
    printf("1. Ajouter une voiture\n");
    printf("2. Modifier une voiture\n");
    printf("3. Supprimer une voiture\n");
    printf("4. Afficher la liste des voitures disponibles\n");
    printf("5. Rechercher des voitures par marque\n");
    printf("6. Rechercher des voitures par disponibilité\n");
    printf("7. Trier les voitures par marque\n");
    printf("8. Trier les voitures par prix de location par jour\n");
    printf("9. Quitter\n");
    printf("Choisissez une option : ");
}

void ajouter_voiture(Voiture *voitures, FILE *file) {
    printf("\nVeuillez saisir les informations de la voiture :\n");
    printf("Marque : ");
    scanf("%s", voitures->marque);
    fprintf(file, "%s ", voitures->marque);
    printf("Modèle : ");
    scanf("%s", voitures->modele);
    fprintf(file, "%s ", voitures->modele);
    printf("Type de carburant : ");
    scanf("%s", voitures->type_carburant);
    fprintf(file, "%s ", voitures->type_carburant);
    printf("Nombre de places : ");
    scanf("%d", &voitures->nombre_places);
    fprintf(file, "%d ", voitures->nombre_places);
    printf("Transmission (automatique ou manuelle) : ");
    scanf("%s", voitures->transmission);
    fprintf(file, "%s ", voitures->transmission);
    printf("Prix de location par jour : ");
    scanf("%f", &voitures->prix_location_par_jour);
    fprintf(file, "%.2f ", voitures->prix_location_par_jour);
    do {
        printf("Disponibilité (1 pour disponible / 0 pour non disponible) : ");
        scanf("%d", &voitures->disponibilite);
        if (voitures->disponibilite > 1 || voitures->disponibilite < 0) {
            printf("Disponibilité non valide! Entrez une disponibilité entre 0 et 1\n");
        }
    } while (voitures->disponibilite > 1 || voitures->disponibilite < 0);
    fprintf(file, "%d\n", voitures->disponibilite);

    printf("\nLa voiture a été ajoutée avec succès.\n");
    voitures->id = ID;
    ID++;
}

void sauvegarder_voitures(Voiture *voitures, int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour sauvegarde.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d %s %s %s %d %s %.2f %d\n", voitures[i].id, voitures[i].marque,
                voitures[i].modele, voitures[i].type_carburant, voitures[i].nombre_places,
                voitures[i].transmission, voitures[i].prix_location_par_jour, voitures[i].disponibilite);
    }

    fclose(file);
}

void charger_voitures(Voiture *voitures, int *n, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour chargement.\n");
        return;
    }

    while (fscanf(file, "%d %s %s %s %d %s %f %d", &voitures[*n].id, voitures[*n].marque,
                  voitures[*n].modele, voitures[*n].type_carburant, &voitures[*n].nombre_places,
                  voitures[*n].transmission, &voitures[*n].prix_location_par_jour, &voitures[*n].disponibilite) == 8) {
        (*n)++;
    }

    fclose(file);
}

Voiture modifier_voiture(Voiture *voitures, int n, FILE *file) {
    int id_modification;
    printf("\nEntrez l'ID de la voiture que vous souhaitez modifier : ");
    scanf("%d", &id_modification);

    int i;
    for (i = 0; i < n; i++) {
        if (voitures[i].id == id_modification) {
            printf("\nEntrez les nouvelles informations :\n");
            printf("Marque : ");
            scanf("%s", voitures[i].marque);
            fprintf(file, "%s ", voitures[i].marque);
            printf("Modèle : ");
            scanf("%s", voitures[i].modele);
            fprintf(file, "%s ", voitures[i].modele);
            printf("Type de carburant : ");
            scanf("%s", voitures[i].type_carburant);
            fprintf(file, "%s ", voitures[i].type_carburant);
            printf("Nombre de places : ");
            scanf("%d", &voitures[i].nombre_places);
            fprintf(file, "%d ", voitures[i].nombre_places);
            printf("Transmission (automatique ou manuelle) : ");
            scanf("%s", voitures[i].transmission);
            fprintf(file, "%s ", voitures[i].transmission);
            printf("Prix de location par jour : ");
            scanf("%f", &voitures[i].prix_location_par_jour);
            fprintf(file, "%.2f ", voitures[i].prix_location_par_jour);
            do {
                printf("Disponibilité (1 pour disponible / 0 pour non disponible) : ");
                scanf("%d", &voitures[i].disponibilite);
                if (voitures[i].disponibilite > 1 || voitures[i].disponibilite < 0) {
                    printf("Disponibilité non valide! Entrez une disponibilité entre 0 et 1\n");
                }
            } while (voitures[i].disponibilite > 1 || voitures[i].disponibilite < 0);
            fprintf(file, "%d\n", voitures[i].disponibilite);

            printf("\nLa voiture a été modifiée avec succès.\n");
            return voitures[i];
        }
    }

    printf("\nAucune voiture avec cet ID n'a été trouvée.\n");
    return *voitures;
}

void supprimer_voiture(Voiture *voitures, int *n, FILE *file) {
    int id_suppression;
    printf("\nEntrez l'ID de la voiture que vous souhaitez supprimer : ");
    scanf("%d", &id_suppression);

    int i;
    for (i = 0; i < *n; i++) {
        if (voitures[i].id == id_suppression) {
            int j;
            for (j = i; j < *n - 1; j++) {
                voitures[j] = voitures[j + 1];
            }

            (*n)--;

            printf("\nLa voiture a été supprimée avec succès.\n");

            fclose(file);
            file = fopen("voitures.txt", "w");
            for (int k = 0; k < *n; k++) {
                fprintf(file, "%d %s %s %s %d %s %.2f %d\n", voitures[k].id, voitures[k].marque,
                        voitures[k].modele, voitures[k].type_carburant, voitures[k].nombre_places,
                        voitures[k].transmission, voitures[k].prix_location_par_jour, voitures[k].disponibilite);
            }
            fclose(file);

            return;
        }
    }

    printf("\nAucune voiture avec cet ID n'a été trouvée.\n");
}

void afficher_voitures_disponibles(Voiture *voitures, int n) {
    printf("\nListe des voitures disponibles :\n");
    printf("ID | Marque | Modèle | Type de carburant | Nombre de places | Transmission | Prix de location par jour | Disponibilité\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (voitures[i].disponibilite == 1) {
            printf("%d | %s | %s | %s | %d | %s | %.2f | %d\n", voitures[i].id, voitures[i].marque,
                   voitures[i].modele, voitures[i].type_carburant, voitures[i].nombre_places, voitures[i].transmission,
                   voitures[i].prix_location_par_jour, voitures[i].disponibilite);
        }
    }
}

void rechercher_par_marque(const char *marque_recherchee, Voiture *voitures, int n) {
    printf("\nVoitures de la marque '%s' :\n", marque_recherchee);
    printf("ID | Marque | Modèle | Type de carburant | Nombre de places | Transmission | Prix de location par jour | Disponibilité\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(voitures[i].marque, marque_recherchee) == 0) {
            printf("%d | %s | %s | %s | %d | %s | %.2f | %d\n", voitures[i].id, voitures[i].marque,
                   voitures[i].modele, voitures[i].type_carburant, voitures[i].nombre_places, voitures[i].transmission,
                   voitures[i].prix_location_par_jour, voitures[i].disponibilite);
        }
    }
}

void rechercher_par_disponibilite(int disponible, Voiture *voitures, int n) {
    printf("Voitures ");
    if (disponible) {
        printf("non ");
    }
    printf("disponibles :\n");
    printf("ID | Marque | Modèle | Type de carburant | Nombre de places | Transmission | Prix de location par jour | Disponibilité\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (voitures[i].disponibilite == disponible) {
            printf("%d | %s | %s | %s | %d | %s | %.2f | %d\n", voitures[i].id, voitures[i].marque,
                   voitures[i].modele, voitures[i].type_carburant, voitures[i].nombre_places, voitures[i].transmission,
                   voitures[i].prix_location_par_jour, voitures[i].disponibilite);
        }
    }
}

void trier_par_marque_fichier(int nn,const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int n = 0;
    Voiture voitures[nn];
    while (fscanf(file, "%d %s %s %s %d %s %f %d", &voitures[n].id, voitures[n].marque, voitures[n].modele,
                  voitures[n].type_carburant, &voitures[n].nombre_places, voitures[n].transmission,
                  &voitures[n].prix_location_par_jour, &voitures[n].disponibilite) == 8) {
        n++;
    }

    fclose(file);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(voitures[j].marque, voitures[j + 1].marque) > 0) {
                Voiture temp = voitures[j];
                voitures[j] = voitures[j + 1];
                voitures[j + 1] = temp;
            }
        }
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour l'écriture.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d %s %s %s %d %s %.2f %d\n", voitures[i].id, voitures[i].marque,
                voitures[i].modele, voitures[i].type_carburant, voitures[i].nombre_places,
                voitures[i].transmission, voitures[i].prix_location_par_jour, voitures[i].disponibilite);
    }

    fclose(file);

    printf("Les voitures ont été triées par marque et les données ont été mises à jour dans le fichier.\n");
}

void trier_par_prix_location_fichier(int nn,const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int n = 0;
    Voiture voitures[nn];
    while (fscanf(file, "%d %s %s %s %d %s %f %d", &voitures[n].id, voitures[n].marque, voitures[n].modele,
                  voitures[n].type_carburant, &voitures[n].nombre_places, voitures[n].transmission,
                  &voitures[n].prix_location_par_jour, &voitures[n].disponibilite) == 8) {
        n++;
    }

    fclose(file);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (voitures[j].prix_location_par_jour > voitures[j + 1].prix_location_par_jour) {
                Voiture temp = voitures[j];
                voitures[j] = voitures[j + 1];
                voitures[j + 1] = temp;
            }
        }
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour l'écriture.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d %s %s %s %d %s %.2f %d\n", voitures[i].id, voitures[i].marque,
                voitures[i].modele, voitures[i].type_carburant, voitures[i].nombre_places,
                voitures[i].transmission, voitures[i].prix_location_par_jour, voitures[i].disponibilite);
    }

    fclose(file);

    printf("Les voitures ont été triées par prix de location par jour et les données ont été mises à jour dans le fichier.\n");
}


int main() {
    int choix;
    int n = 0;
    char utilisateur[30];
    printf("Entrer votre nom: ");
    scanf("%s", utilisateur);
    fflush(stdin);
    fflush(stdin);
    printf("Entrer le nombre de voitures : ");
    scanf("%d", &n);
    Voiture voitures[n];

    const char *filename = "vitures.txt";
    charger_voitures(voitures, &n, filename);

    do {
        afficher_menu_principal();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_voiture(&voitures[n], fopen(filename, "a"));
                n++;
                break;
            case 2:
                modifier_voiture(voitures,n,fopen(filename, "w"));
                break;
            case 3:
                supprimer_voiture(voitures, &n, fopen(filename, "w"));
                break;
            case 4:
                afficher_voitures_disponibles(voitures, n);
                break;
            case 5:
                char marque_recherchee[20];
                printf("Entrer la marque à rechercher : ");
                scanf("%s", marque_recherchee);
                rechercher_par_marque(marque_recherchee, voitures, n);
                break;
            case 6:
                int disponible;
                printf("Entrer la disponibilité à rechercher (1 pour disponible / 0 pour non disponible) : ");
                scanf("%d", &disponible);
                rechercher_par_disponibilite(disponible, voitures, n);
                break;
            case 7:
                trier_par_marque_fichier(n,filename);
                break;
            case 8:
                trier_par_prix_location_fichier(n,filename);
                break;
            case 9:
                printf("\n\nAu Revoir %s!.", utilisateur);
                printf("\nMerci d'avoir utilisé notre application de gestion de location de voitures!\n");
                sauvegarder_voitures(voitures, n, filename);
                break;
            default:
                printf("Option invalide. Veuillez choisir une option valide.\n");
                break;
        }
    } while (choix != 9);

    return 0;
}
