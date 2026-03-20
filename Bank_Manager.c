#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCLIENT 150
#define MAX_HISTORIQUE 100
#define TAILLE_LIGNE 100

// Structure d'un compte bancaire
typedef struct compte
{
    int solde;
    char Type_de_Compte;
    int numero;
} COMPTE;

// Structure d'un client avec ses comptes
typedef struct client
{
    char nom[30];
    COMPTE Tab_de_Compte[5];
    int Nbre_de_Compte;
} CLIENT;

// Structure qui remplace les 3 anciennes variables globales
// recup_indice_client, recup_indice_compte, success_fn
typedef struct
{
    int recup_indice_client;
    int recup_indice_compte;
    int success_fn;
} RESULTAT_RECHERCHE;

// Structure qui remplace les 2 anciennes variables globales
// Historique et NbTransactions
typedef struct
{
    char lignes[MAX_HISTORIQUE][TAILLE_LIGNE];
    int nb_transactions;
} HISTORIQUE;

// Affiche les informations d'un client : nom, nombre de comptes,
// et pour chaque compte son solde, son type et son numero
void AfficherUnClient(CLIENT C1)
{
    int j;
    printf(" Nom du client : \t");
    puts(C1.nom);
    printf("Nombre de comptes du client :\t %d \n\n", C1.Nbre_de_Compte);
    for (j = 0; j < C1.Nbre_de_Compte; j++)
    {
        printf("\t\tCOMPTE N%d \n", j+1);
        printf("\t\tSolde du Compte : \t %d \n", C1.Tab_de_Compte[j].solde);
        printf("\t\tType du compte : Compte de Type\t %c\n", C1.Tab_de_Compte[j].Type_de_Compte);
        printf("\t\tIl s'agit du compte Numero %d. \n\n", C1.Tab_de_Compte[j].numero);
    }
    printf("\n\n");
}

// Affiche les informations de tous les clients
// Se sert de AfficherUnClient()
void AfficherToutClient(CLIENT TabClient[MAXCLIENT], int nbClient)
{
    printf("INFORMATION SUR TOUS LES CLIENTS:  \n \n");
    int i;
    for (i = 0; i < nbClient; i++)
    {
        printf("INFORMATION SUR LE CLIENT N%d:  \n ", i+1);
        AfficherUnClient(TabClient[i]);
    }
}

// Redemande une saisie tant que la valeur est <= 0
// Retourne la valeur valide
// Utilisee dans NouveauCompte() pour le solde
int ValidationSaisiePositif(char *message)
{
    int valeur;
    do
    {
        printf("%s : ", message);
        scanf("%d", &valeur);
        if (valeur <= 0)
            printf("Erreur : la valeur doit etre superieure a 0. Reessayez.\n");
    }
    while (valeur <= 0);
    return valeur;
}

// Cree un nouveau compte pour un client
// Le solde est valide via ValidationSaisiePositif()
void NouveauCompte(CLIENT *C)
{
    printf("CREATION D'UN COMPTE : .....\n\n");
    printf("Entrer le numero du Compte:\t");
    scanf("%d", &C->Tab_de_Compte[C->Nbre_de_Compte].numero);
    printf("Entrer le type de Compte( A / B / C / D ) : ");
    scanf(" %c", &C->Tab_de_Compte[C->Nbre_de_Compte].Type_de_Compte);
    C->Tab_de_Compte[C->Nbre_de_Compte].solde = ValidationSaisiePositif("Entrer le solde du Compte");
    printf("\n\nDone...\n\n");
    C->Nbre_de_Compte += 1;
    printf("LE COMPTE A ETE CREE AVEC SUCCES\n\n");
}

// Cree un nouveau client et ses comptes
// Le tableau de clients et nbClient sont mis a jour
void NouveauClient(CLIENT TabClient[], int *nbClient)
{
    CLIENT C;
    int found = 0;
    int i, nbCompte;
    printf("CREATION D'UN NOUVEAU CLIENT \n\n\n");
    do
    {
        printf("\tVeuillez rentrer son Nom : \t ");
        fflush(stdin);
        gets(C.nom);
        for (i = 0; i < MAXCLIENT; i++)
        {
            if (strcmp(C.nom, TabClient[i].nom) == 0)
                found = 1;
        }
    }
    while (found == 1);
    printf("\tVeuillez rentrer le nombre de compte du client: \t");
    scanf(" %d", &nbCompte);
    C.Nbre_de_Compte = 0;
    for (i = 0; i < nbCompte; i++)
    {
        NouveauCompte(&C);
    }
    printf("FIN DE CREATION DU CLIENT\n\n\n");
    TabClient[*nbClient] = C;
    *nbClient += 1;
    printf("RAJOUT DU NOUVEAU CLIENT A LA BASE DE DONNEES\n\n");
    printf("___BASE DE DONNEES MISE A JOUR___\n\n");
    system("pause");
}

// Recherche un client par son nom et affiche ses informations
void RechercheClient(CLIENT TClient[])
{
    int j;
    int trouve = 0;
    char nom[20];
    printf("\n\n___RECHERCHE DE CLIENT___\n\n\n");
    printf("\t Veuillez rentrer le nom du client :");
    scanf(" %s", &nom);
    for (j = 0; j < MAXCLIENT; j++)
    {
        if (strcmp(nom, TClient[j].nom) == 0)
        {
            printf("\n\nRecherche....\n");
            system("pause");
            printf("\t Client retrouve \n");
            trouve = 1;
            system("pause");
            AfficherUnClient(TClient[j]);
            break;
        }
    }
    if (trouve == 0)
        printf(" \n\n Le Client N'est Pas Dans la base de Donnees ");
}

// Recherche un compte par nom de client et numero de compte
// Remplit la structure RESULTAT_RECHERCHE a la place des anciennes variables globales
void RechercheCompte(CLIENT TClient[], int c, RESULTAT_RECHERCHE *r)
{
    int i, j;
    int trouve = 0;
    char nom[20];
    printf("\n\n___RECHERCHE DE COMPTE D'UN CLIENT___\n\n\n");
    printf("\t Veuillez rentrer le nom du client :");
    scanf(" %s", &nom);
    for (j = 0; j < MAXCLIENT; j++)
    {
        if (strcmp(nom, TClient[j].nom) == 0)
        {
            r->recup_indice_client = j;
            printf("\n\nRecherche....\n");
            system("pause");
            printf("\n\t Client retrouve \n");
            trouve = 1;
            system("pause");
            printf("\n Recherche du compte ....");
            for (i = 0; i < TClient[j].Nbre_de_Compte; i++)
            {
                if (TClient[j].Tab_de_Compte[i].numero == c)
                {
                    r->recup_indice_compte = i;
                    printf("\t\t\nN DU COMPTE :  %d \n", c);
                    printf("\t\tSolde du Compte : \t %d \n", TClient[j].Tab_de_Compte[j].solde);
                    printf("\t\tType du compte : Compte de Type\t %c\n", TClient[j].Tab_de_Compte[j].Type_de_Compte);
                }
                else
                {
                    trouve = 0;
                }
                break;
            }
        }
    }
    r->success_fn = trouve;
    if (trouve == 0)
        printf(" \n\n Le Client N'est Pas Dans la base de Donnees Ou alors Numero de Compte errone \n");
    system("pause");
}

// Ajoute une ligne dans l'historique des transactions
// type : "VERSEMENT", "RETRAIT", "TRANSFERT DEBIT" ou "TRANSFERT CREDIT"
void AjouterHistorique(HISTORIQUE *h, char *type, char *nom_client, int num_compte, int montant)
{
    if (h->nb_transactions >= MAX_HISTORIQUE)
    {
        // Tableau plein : on decale pour garder les plus recentes
        int i;
        for (i = 0; i < MAX_HISTORIQUE - 1; i++)
            strcpy(h->lignes[i], h->lignes[i + 1]);
        h->nb_transactions = MAX_HISTORIQUE - 1;
    }
    sprintf(h->lignes[h->nb_transactions], "[%-16s] Client: %-15s | Compte N%d | Montant: %d",
            type, nom_client, num_compte, montant);
    h->nb_transactions++;
}

// Effectue un versement sur un compte apres recherche
// Enregistre l'operation dans l'historique
void Versement(CLIENT TClient[], int num_compte, RESULTAT_RECHERCHE *r, HISTORIQUE *h)
{
    int vers;
    RechercheCompte(TClient, num_compte, r);
    if (r->success_fn != 0)
    {
        printf("\n\n\n _____VERSEMENT____\n\n");
        do
        {
            printf("Veuillez rentrer le montant a verser sur le compte : ");
            scanf("%d", &vers);
        }
        while (vers <= 0);
        TClient[r->recup_indice_client].Tab_de_Compte[r->recup_indice_compte].solde += vers;
        printf("Nouveau Solde : %d \t\n\n", TClient[r->recup_indice_client].Tab_de_Compte[r->recup_indice_compte].solde);
        AjouterHistorique(h, "VERSEMENT", TClient[r->recup_indice_client].nom, num_compte, vers);
        system("pause");
    }
    else
    {
        printf("\n Erreur lors de la Recherche de compte \n\n");
        system("pause");
    }
}

// Effectue un transfert entre deux comptes
// Enregistre le debit et le credit dans l'historique
void Transfert(CLIENT TClient[], int num_compte, RESULTAT_RECHERCHE *r, HISTORIQUE *h)
{
    int transf;
    RechercheCompte(TClient, num_compte, r);
    if (r->success_fn != 0)
    {
        printf("\n\n\n _____TRANSFERT____\n\n");
        do
        {
            printf("Veuillez rentrer le montant a transferer : ");
            scanf("%d", &transf);
        }
        while (transf <= 0 || transf > TClient[r->recup_indice_client].Tab_de_Compte[r->recup_indice_compte].solde);
        TClient[r->recup_indice_client].Tab_de_Compte[r->recup_indice_compte].solde -= transf;
        printf("Nouveau Solde : %d \t", TClient[r->recup_indice_client].Tab_de_Compte[r->recup_indice_compte].solde);
        AjouterHistorique(h, "TRANSFERT DEBIT", TClient[r->recup_indice_client].nom, num_compte, transf);
        int numCompteTrans;
        printf("\n\nVous allez maintenant rentrer le nom et le numero du compte destinataire : \n");
        printf("\t\t Numero : ");
        scanf("%d", &numCompteTrans);
        RechercheCompte(TClient, numCompteTrans, r);
        if (r->success_fn != 0)
        {
            printf("\t\t___Preparation de la transaction ___");
            TClient[r->recup_indice_client].Tab_de_Compte[r->recup_indice_compte].solde += transf;
            system("pause");
            printf("Nouveau Solde : %d \t\n\n", TClient[r->recup_indice_client].Tab_de_Compte[r->recup_indice_compte].solde);
            AjouterHistorique(h, "TRANSFERT CREDIT", TClient[r->recup_indice_client].nom, numCompteTrans, transf);
            system("pause");
        }
        else
        {
            printf("\n Erreur lors de la Recherche de compte \n\n");
            system("pause");
        }
    }
    else
    {
        printf("\n Erreur lors de la Recherche de compte \n\n");
        system("pause");
    }
}

// Effectue un retrait sur un compte apres recherche
// Enregistre l'operation dans l'historique
void Retrait(CLIENT TClient[], int num_compte, RESULTAT_RECHERCHE *r, HISTORIQUE *h)
{
    int retire;
    RechercheCompte(TClient, num_compte, r);
    if (r->success_fn != 0)
    {
        printf("\n\n\n _____RETRAIT____\n\n");
        do
        {
            printf("Veuillez rentrer le montant a retirer sur le compte : ");
            scanf("%d", &retire);
        }
        while (retire <= 0 || retire > TClient[r->recup_indice_client].Tab_de_Compte[r->recup_indice_compte].solde);
        TClient[r->recup_indice_client].Tab_de_Compte[r->recup_indice_compte].solde -= retire;
        printf("Nouveau Solde : %d \t\n\n", TClient[r->recup_indice_client].Tab_de_Compte[r->recup_indice_compte].solde);
        AjouterHistorique(h, "RETRAIT", TClient[r->recup_indice_client].nom, num_compte, retire);
        system("pause");
    }
    else
    {
        printf("\n Erreur lors de la Recherche de compte \n\n");
        system("pause");
    }
}

// Applique une taxe de 5% sur tous les comptes de tous les clients
void AppliquerTaxe(CLIENT TabClient[], int nbClient)
{
    int i, j;
    for (i = 0; i < nbClient; i++)
    {
        for (j = 0; j < nbClient; j++)
        {
            TabClient[i].Tab_de_Compte[j].solde *= 0.95;
        }
    }
    printf("\n\n La Taxe de 5%% a ete appliquee automatiquement par la Banque");
}

// Modifie le numero, le type et le solde d'un compte
// Identification par nom du client puis numero de compte
void ModifierCompte(CLIENT TClient[], int nbClient)
{
    int i, j;
    int trouve_client = 0;
    int trouve_compte = 0;
    char nom[30];
    int num_compte;
    printf("\n\n___MODIFICATION D'UN COMPTE___\n\n");
    printf("Entrez le nom du client : ");
    scanf(" %s", nom);
    for (i = 0; i < nbClient; i++)
    {
        if (strcmp(nom, TClient[i].nom) == 0)
        {
            trouve_client = 1;
            printf("Entrez le numero du compte a modifier : ");
            scanf("%d", &num_compte);
            for (j = 0; j < TClient[i].Nbre_de_Compte; j++)
            {
                if (TClient[i].Tab_de_Compte[j].numero == num_compte)
                {
                    trouve_compte = 1;
                    printf("\nInfos actuelles du compte :\n");
                    printf("  Numero  : %d\n", TClient[i].Tab_de_Compte[j].numero);
                    printf("  Type    : %c\n", TClient[i].Tab_de_Compte[j].Type_de_Compte);
                    printf("  Solde   : %d\n", TClient[i].Tab_de_Compte[j].solde);
                    printf("\nNouveau numero du compte : ");
                    scanf("%d", &TClient[i].Tab_de_Compte[j].numero);
                    printf("Nouveau type du compte (A / B / C / D) : ");
                    scanf(" %c", &TClient[i].Tab_de_Compte[j].Type_de_Compte);
                    printf("Nouveau solde du compte : ");
                    scanf("%d", &TClient[i].Tab_de_Compte[j].solde);
                    printf("\nCompte modifie avec succes.\n");
                    break;
                }
            }
            if (trouve_compte == 0)
                printf("\nErreur : numero de compte introuvable pour ce client.\n");
            break;
        }
    }
    if (trouve_client == 0)
        printf("\nErreur : client introuvable dans la base de donnees.\n");
}

// Modifie le nom d'un client
// Identification par son nom actuel
void ModifierClient(CLIENT TClient[], int nbClient)
{
    int i;
    int trouve = 0;
    char nom[30];
    char nouveau_nom[30];
    printf("\n___MODIFICATION D'UN CLIENT___\n\n");
    printf("Entrez le nom du client a modifier : ");
    scanf(" %s", nom);
    for (i = 0; i < nbClient; i++)
    {
        if (strcmp(nom, TClient[i].nom) == 0)
        {
            trouve = 1;
            printf("Nom actuel : %s\n", TClient[i].nom);
            printf("Nouveau nom : ");
            scanf(" %s", nouveau_nom);
            strcpy(TClient[i].nom, nouveau_nom);
            printf("\nClient modifie avec succes.\n");
            break;
        }
    }
    if (trouve == 0)
        printf("\nErreur : client introuvable dans la base de donnees.\n");
}

// Supprime un compte d'un client
// Decale les comptes restants pour garder le tableau compact
void SuppressionCompte(CLIENT TClient[], int nbClient)
{
    int i, j, k;
    int trouve_client = 0;
    int trouve_compte = 0;
    char nom[30];
    int num_compte;
    printf("\n\n___SUPPRESSION D'UN COMPTE___\n\n");
    printf("Entrez le nom du client : ");
    scanf(" %s", nom);
    for (i = 0; i < nbClient; i++)
    {
        if (strcmp(nom, TClient[i].nom) == 0)
        {
            trouve_client = 1;
            printf("Entrez le numero du compte a supprimer : ");
            scanf("%d", &num_compte);
            for (j = 0; j < TClient[i].Nbre_de_Compte; j++)
            {
                if (TClient[i].Tab_de_Compte[j].numero == num_compte)
                {
                    trouve_compte = 1;
                    for (k = j; k < TClient[i].Nbre_de_Compte - 1; k++)
                        TClient[i].Tab_de_Compte[k] = TClient[i].Tab_de_Compte[k + 1];
                    TClient[i].Nbre_de_Compte -= 1;
                    printf("\nCompte supprime avec succes.\n");
                    break;
                }
            }
            if (trouve_compte == 0)
                printf("\nErreur : numero de compte introuvable pour ce client.\n");
            break;
        }
    }
    if (trouve_client == 0)
        printf("\nErreur : client introuvable dans la base de donnees.\n");
}

// Supprime un client du tableau
// Decale les clients restants pour garder le tableau compact
void SuppressionClient(CLIENT TClient[], int *nbClient)
{
    int i, j;
    int trouve = 0;
    char nom[30];
    printf("\n\n___SUPPRESSION D'UN CLIENT___\n\n");
    printf("Entrez le nom du client a supprimer : ");
    scanf(" %s", nom);
    for (i = 0; i < *nbClient; i++)
    {
        if (strcmp(nom, TClient[i].nom) == 0)
        {
            trouve = 1;
            for (j = i; j < *nbClient - 1; j++)
                TClient[j] = TClient[j + 1];
            *nbClient -= 1;
            printf("\nClient supprime avec succes.\n");
            break;
        }
    }
    if (trouve == 0)
        printf("\nErreur : client introuvable dans la base de donnees.\n");
}

// Retourne et affiche la somme de tous les comptes de tous les clients
int TotalComptesTousClients(CLIENT TClient[], int nbClient)
{
    int i, j;
    int total = 0;
    for (i = 0; i < nbClient; i++)
        for (j = 0; j < TClient[i].Nbre_de_Compte; j++)
            total += TClient[i].Tab_de_Compte[j].solde;
    printf("\nMontant total de tous les comptes : %d\n", total);
    return total;
}

// Retourne et affiche la somme de tous les comptes d'un seul client
int TotalCompteUnClient(CLIENT TClient[], int nbClient)
{
    int i, j;
    int trouve = 0;
    int total = 0;
    char nom[30];
    printf("\n___TOTAL DES COMPTES D'UN CLIENT___\n\n");
    printf("Entrez le nom du client : ");
    scanf(" %s", nom);
    for (i = 0; i < nbClient; i++)
    {
        if (strcmp(nom, TClient[i].nom) == 0)
        {
            trouve = 1;
            for (j = 0; j < TClient[i].Nbre_de_Compte; j++)
                total += TClient[i].Tab_de_Compte[j].solde;
            printf("Total des comptes de %s : %d\n", TClient[i].nom, total);
            break;
        }
    }
    if (trouve == 0)
        printf("\nErreur : client introuvable dans la base de donnees.\n");
    return total;
}

// Affiche toutes les transactions enregistrees dans l'historique
void AfficherHistorique(HISTORIQUE *h)
{
    int i;
    printf("\n\n     ____HISTORIQUE DES TRANSACTIONS____\n\n");
    if (h->nb_transactions == 0)
        printf("Aucune transaction enregistree.\n");
    else
        for (i = 0; i < h->nb_transactions; i++)
            printf("  %d. %s\n", i + 1, h->lignes[i]);
    printf("========================================\n");
}

// Remet le compteur de transactions a zero
void EffacerHistorique(HISTORIQUE *h)
{
    h->nb_transactions = 0;
    printf("\nHistorique efface avec succes.\n");
}

// Demande un code PIN au demarrage
// Bloque apres 3 tentatives ratees et quitte le programme
void Authentification()
{
    int PIN_SECRET = 1234;
    int pin_saisi;
    int tentatives = 0;
    printf("\n\t\t===========================================\n");
    printf("\t\t       ACCES SECURISE - DODO'S BANK\n");
    printf("\t\t\t     AUTHENTIFICATION \n");
    printf("\t\t===========================================\n");
    do
    {
        printf("\n\n\t\tEntrez le code PIN administrateur (04 Chiffres): ");
        scanf("%d", &pin_saisi);
        tentatives++;
        if (pin_saisi != PIN_SECRET)
            printf("\t\tCode incorrect. Tentatives restantes : %d\n", 3 - tentatives);
    }
    while (pin_saisi != PIN_SECRET && tentatives < 3);
    if (pin_saisi != PIN_SECRET)
    {
        printf("\n\t\tAcces refuse. Programme termine.\n");
        system("pause");
        exit(0);
    }
    printf("\n\t\tAcces autorise. Bienvenue !\n\n");
    system("pause");
}

// Trouve et affiche le client dont la somme de tous ses comptes est la plus elevee
void ClientLePlusRiche(CLIENT TClient[], int nbClient)
{
    int i, j;
    int total_courant;
    int total_max = 0;
    int indice_max = 0;
    printf("\n\n       ____CLIENT LE PLUS RICHE____\n\n");
    if (nbClient == 0)
    {
        printf("Aucun client dans la base de donnees.\n");
        return;
    }
    for (i = 0; i < nbClient; i++)
    {
        total_courant = 0;
        for (j = 0; j < TClient[i].Nbre_de_Compte; j++)
            total_courant += TClient[i].Tab_de_Compte[j].solde;
        if (total_courant > total_max)
        {
            total_max  = total_courant;
            indice_max = i;
        }
    }
    printf("Client le plus riche : %s\n", TClient[indice_max].nom);
    printf("Total de ses comptes : %d\n", total_max);
    printf("========================================\n");
}

// Trouve et affiche le compte avec le solde le plus eleve, tous clients confondus
void CompteLePlusRiche(CLIENT TClient[], int nbClient)
{
    int i, j;
    int solde_max = 0;
    int indice_client_max = 0;
    int indice_compte_max = 0;
    printf("\n\n       ______COMPTE LE PLUS RICHE_____\n\n");
    if (nbClient == 0)
    {
        printf("Aucun client dans la base de donnees.\n");
        return;
    }
    for (i = 0; i < nbClient; i++)
    {
        for (j = 0; j < TClient[i].Nbre_de_Compte; j++)
        {
            if (TClient[i].Tab_de_Compte[j].solde > solde_max)
            {
                solde_max         = TClient[i].Tab_de_Compte[j].solde;
                indice_client_max = i;
                indice_compte_max = j;
            }
        }
    }
    printf("Client        : %s\n", TClient[indice_client_max].nom);
    printf("Numero compte : %d\n", TClient[indice_client_max].Tab_de_Compte[indice_compte_max].numero);
    printf("Type compte   : %c\n", TClient[indice_client_max].Tab_de_Compte[indice_compte_max].Type_de_Compte);
    printf("Solde         : %d\n", solde_max);
    printf("========================================\n");
}

// Trie les clients par richesse decroissante (tri a bulles)
// Travaille sur une copie du tableau, l'original n'est pas modifie
void TriClientsParRichesse(CLIENT TClient[], int nbClient)
{
    int i, j, k;
    int totaux[MAXCLIENT];
    CLIENT copie[MAXCLIENT];
    CLIENT temp_client;
    int temp_total;
    printf("\n\n  ____CLASSEMENT DES CLIENTS PAR RICHESSE____\n\n");
    if (nbClient == 0)
    {
        printf("Aucun client dans la base de donnees.\n");
        return;
    }
    for (i = 0; i < nbClient; i++)
    {
        copie[i] = TClient[i];
        totaux[i] = 0;
        for (k = 0; k < TClient[i].Nbre_de_Compte; k++)
            totaux[i] += TClient[i].Tab_de_Compte[k].solde;
    }
    for (i = 0; i < nbClient - 1; i++)
    {
        for (j = 0; j < nbClient - 1 - i; j++)
        {
            if (totaux[j] < totaux[j + 1])
            {
                temp_total  = totaux[j];
                totaux[j]   = totaux[j + 1];
                totaux[j+1] = temp_total;
                temp_client = copie[j];
                copie[j]    = copie[j + 1];
                copie[j+1]  = temp_client;
            }
        }
    }
    for (i = 0; i < nbClient; i++)
        printf("  %d. %-20s | Total : %d\n", i + 1, copie[i].nom, totaux[i]);
    printf("========================================\n");
}

// Menu principal - tourne en boucle jusqu'au choix 0 (Quitter)
// RESULTAT_RECHERCHE et HISTORIQUE sont declares ici et passes aux fonctions
void Menu(CLIENT TClient[], int *nbClient)
{
    int choix;
    int num_compte;
    RESULTAT_RECHERCHE r;
    HISTORIQUE h;
    h.nb_transactions = 0;

    do
    {
        printf("\n\n\t\t\t====================================================================\n");
        printf("\t\t\t         WELCOME IN THE DODO'S BANK A FIRM OF A DODO'S GROUP\n");
        printf("\t\t\t====================================================================\n\n\n\n");
        printf("\t\t\t\t========================================\n");
        printf("\t\t\t\t       GESTIONNAIRE DE BANQUE\n");
        printf("\t\t\t\t========================================\n\n\n");
        printf("\t\t  1.  Afficher un client \t\t\t  11. Versement\n");
        printf("\t\t  2.  Afficher tous les clients \t\t  12. Retrait\n");
        printf("\t\t  3.  Nouveau client \t\t\t\t  13. Transfert\n");
        printf("\t\t  4.  Nouveau compte \t\t\t\t  14. Total de tous les comptes (tous clients)\n");
        printf("\t\t  5.  Rechercher un client \t\t\t  15. Total des comptes d'un client\n");
        printf("\t\t  6.  Rechercher un compte \t\t\t  16. Historique des transactions\n");
        printf("\t\t  7.  Modifier un client \t\t\t  17. Effacer l'historique\n");
        printf("\t\t  8.  Modifier un compte \t\t\t  18. Client le plus riche\n");
        printf("\t\t  9.  Supprimer un client \t\t\t  19. Compte le plus riche\n");
        printf("\t\t  10. Supprimer un compte \t\t\t  20. Classement des clients par richesse\n\n");
        printf("\t\t\t\t\t  0.  Quitter\n\n\n");
        printf("\t\t\t\t========================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
        {
            char nom[30];
            int i, trouve = 0;
            printf("\nEntrez le nom du client : ");
            scanf(" %s", nom);
            for (i = 0; i < *nbClient; i++)
            {
                if (strcmp(nom, TClient[i].nom) == 0)
                {
                    AfficherUnClient(TClient[i]);
                    trouve = 1;
                    break;
                }
            }
            if (trouve == 0)
                printf("\nErreur : client introuvable.\n");
            system("pause");
            break;
        }
        case 2:
            AfficherToutClient(TClient, *nbClient);
            system("pause");
            break;
        case 3:
            NouveauClient(TClient, nbClient);
            break;
        case 4:
        {
            char nom[30];
            int i, trouve = 0;
            printf("\nEntrez le nom du client auquel ajouter un compte : ");
            scanf(" %s", nom);
            for (i = 0; i < *nbClient; i++)
            {
                if (strcmp(nom, TClient[i].nom) == 0)
                {
                    if (TClient[i].Nbre_de_Compte >= 5)
                        printf("\nErreur : ce client a deja atteint le maximum de 5 comptes.\n");
                    else
                        NouveauCompte(&TClient[i]);
                    trouve = 1;
                    break;
                }
            }
            if (trouve == 0)
                printf("\nErreur : client introuvable.\n");
            system("pause");
            break;
        }
        case 5:
            RechercheClient(TClient);
            system("pause");
            break;
        case 6:
            printf("\nEntrez le numero du compte a rechercher : ");
            scanf("%d", &num_compte);
            RechercheCompte(TClient, num_compte, &r);
            break;
        case 7:
            ModifierClient(TClient, *nbClient);
            system("pause");
            break;
        case 8:
            ModifierCompte(TClient, *nbClient);
            system("pause");
            break;
        case 9:
            SuppressionClient(TClient, nbClient);
            system("pause");
            break;
        case 10:
            SuppressionCompte(TClient, *nbClient);
            system("pause");
            break;
        case 11:
            printf("\nEntrez le numero du compte sur lequel effectuer le versement : ");
            scanf("%d", &num_compte);
            Versement(TClient, num_compte, &r, &h);
            break;
        case 12:
            printf("\nEntrez le numero du compte sur lequel effectuer le retrait : ");
            scanf("%d", &num_compte);
            Retrait(TClient, num_compte, &r, &h);
            break;
        case 13:
            printf("\nEntrez le numero du compte source du transfert : ");
            scanf("%d", &num_compte);
            Transfert(TClient, num_compte, &r, &h);
            break;
        case 14:
            TotalComptesTousClients(TClient, *nbClient);
            system("pause");
            break;
        case 15:
            TotalCompteUnClient(TClient, *nbClient);
            system("pause");
            break;
        case 16:
            AfficherHistorique(&h);
            system("pause");
            break;
        case 17:
            EffacerHistorique(&h);
            system("pause");
            break;
        case 18:
            ClientLePlusRiche(TClient, *nbClient);
            system("pause");
            break;
        case 19:
            CompteLePlusRiche(TClient, *nbClient);
            system("pause");
            break;
        case 20:
            TriClientsParRichesse(TClient, *nbClient);
            system("pause");
            break;
        case 0:
            printf("\nAu revoir !\n");
            break;
        default:
            printf("\nErreur : choix invalide. Veuillez entrer un nombre entre 0 et 20.\n");
            system("pause");
            break;
        }

    }
    while (choix != 0);
}

int main()
{
    int nbClient = 5;
    CLIENT LesClients[MAXCLIENT]=
    {
        {
            "client1", {
                {1000,'A',1}, {5000,'B',2}
            }, 2
        },
        {
            "client2", {
                {3000,'A',1}, {8000,'B',2}
            }, 2
        },
        {
            "client3", {
                {4000,'A',1}, {1000,'B',2}
            }, 2
        },
        {
            "client4", {
                {6000,'A',1}, {18000,'B',2}
            }, 2
        },
        {
            "client5", {
                {34000,'A',1}, {90000,'B',2}
            }, 2
        }
    };

    // Authentification avant d'acceder au menu
    Authentification();
    Menu(LesClients, &nbClient);

    return 0;
}
