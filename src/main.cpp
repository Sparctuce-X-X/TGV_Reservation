#include <iostream>
#include <vector>
#include "../include/Train.h"
#include "../include/Passager.h"
#include "../include/Billet.h"
#include "../include/utils.h"

// Fonction pour afficher tous les trains disponibles
void afficherTousLesTrains(const std::vector<Train>& trains) {
    std::cout << "\n=== Liste des Trains Disponibles ===\n";
    for (const auto& train : trains) {
        train.afficherInfosTrain();
        std::cout << "-------------------------------\n";
    }
}

void afficherHistorique(const Passager& passager) {
    std::cout << "\n=== Historique des Billets ===\n";
    if (passager.getHistorique().empty()) {
        std::cout << "Aucun billet dans l'historique pour ce passager.\n";
    } else {
        passager.afficherHistorique();
    }
}

void consulterReservations(const Passager& passager) {
    std::cout << "\n=== Consultation des Réservations ===\n";
    if (passager.getReservations().empty()) {
        std::cout << "Aucune réservation en cours pour ce passager.\n";
    } else {
        passager.afficherReservations();
    }
}

Passager creerOuUtiliserUtilisateur(std::vector<Passager>& passagers) {
    int choix;
    std::cout << "1. Utiliser un passager existant\n";
    std::cout << "2. Créer un nouveau passager\n";
    std::cout << "Entrez votre choix : ";
    std::cin >> choix;

    if (choix == 1) {
        // Afficher les passagers existants
        std::cout << "\n=== Liste des Passagers ===\n";
        for (size_t i = 0; i < passagers.size(); ++i) {
            std::cout << i + 1 << ". " << passagers[i].getNom() << " " << passagers[i].getPrenom()
                      << " (ID : " << passagers[i].getIdentifiant() << ")\n";
        }

        int index;
        std::cout << "Entrez le numéro du passager : ";
        std::cin >> index;

        if (index > 0 && static_cast<size_t>(index) <= passagers.size()) {
            return passagers[index - 1];
        } else {
            std::cout << "Choix invalide. Création d'un nouveau passager.\n";
        }
    }

    // Création d'un nouveau passager
    std::string nom = validerEntreeNonVide("Entrez votre nom : ");
    std::string prenom = validerEntreeNonVide("Entrez votre prénom : ");
    int identifiant;

    std::cout << "Entrez votre identifiant : ";
    std::cin >> identifiant;

    Passager nouveauPassager(nom, prenom, identifiant);
    passagers.push_back(nouveauPassager);
    return nouveauPassager;
}

// Fonction pour charger les données au démarrage
std::vector<Train> chargerTrains() {
    verifierFichier("data/trains.txt");
    return Train::chargerTrains("data/trains.txt");
}

std::vector<Passager> chargerPassagers() {
    verifierFichier("data/passagers.txt");
    return Passager::chargerPassagers("data/passagers.txt");
}

std::vector<Billet> chargerReservations() {
    verifierFichier("data/reservations.txt");
    return Billet::chargerBillets("data/reservations.txt");
}

// Fonction pour sauvegarder les données
void sauvegarderTrains(const std::vector<Train>& trains) {
    Train::sauvegarderTrains(trains, "data/trains.txt");
}

void sauvegarderPassagers(const std::vector<Passager>& passagers) {
    Passager::sauvegarderPassagers(passagers, "data/passagers.txt");
}

// Fonction pour gérer une réservation
void reserverBillet(std::vector<Train>& trains, Passager& passager) {
    std::cout << "\n=== Réservation de Billet ===\n";
    afficherTousLesTrains(trains);

    int numeroTrain, typeClasse;
    std::cout << "Entrez le numéro du train à réserver : ";
    std::cin >> numeroTrain;

    // Rechercher le train sélectionné
    Train* trainChoisi = nullptr;
    for (auto& train : trains) {
        if (train.getNumeroTrain() == numeroTrain) {
            trainChoisi = &train;
            break;
        }
    }

    if (trainChoisi == nullptr) {
        std::cout << "Train non trouvé !\n";
        return;
    }

    if (!trainChoisi->verifierDisponibilite()) {
        std::cout << "Aucune place disponible pour ce train.\n";
        return;
    }

    // Choisir le type de billet
    std::cout << "Choisissez la classe :\n";
    std::cout << "1. Première Classe\n";
    std::cout << "2. Deuxième Classe\n";
    std::cout << "Entrez votre choix : ";
    std::cin >> typeClasse;

    std::string classe = (typeClasse == 1) ? "Première" : "Deuxième";
    float prix = (typeClasse == 1) ? 50.0 : 30.0;

    // Demander à l'utilisateur s'il veut utiliser ses points de fidélité
    std::cout << "Vous avez " << passager.getPointsFidelite() << " points de fidélité.\n";
    std::cout << "Souhaitez-vous utiliser vos points pour réduire le coût ? (O/N) : ";
    char utiliserPoints;
    std::cin >> utiliserPoints;

    if (utiliserPoints == 'O' || utiliserPoints == 'o') {
        int pointsUtilises = static_cast<int>(prix); // 1 point = 1 euro
        if (passager.utiliserPointsFidelite(pointsUtilises)) {
            prix -= pointsUtilises;
            prix = (prix < 0) ? 0 : prix; // Le prix ne peut pas être négatif
            std::cout << "Réduction appliquée. Nouveau prix : " << prix << " EUR\n";
        } else {
            std::cout << "Points insuffisants. Le prix reste inchangé.\n";
        }
    }

    // Créer et ajouter un billet au passager
    std::string dateVoyage = demanderDateValide("Entrez la date du voyage (YYYY-MM-DD) : ");
    Billet billet(passager.getReservations().size() + 1, classe, prix, trainChoisi->getNumeroTrain(),
                  dateVoyage, trainChoisi->getVilleDepart(), trainChoisi->getVilleArrivee());
    passager.ajouterReservation(billet);

    // Réduire les places disponibles dans le train
    trainChoisi->reserverPlace();

    // Ajouter les points de fidélité restants (1 point par euro dépensé)
    passager.ajouterPointsFidelite(static_cast<int>(prix));

    std::cout << "Réservation réussie !\n";
    billet.afficherDetailsBillet();
}


void afficherPointsFidelite(const Passager& passager) {
    std::cout << "\n=== Points de Fidélité ===\n";
    std::cout << "Vous avez " << passager.getPointsFidelite() << " points de fidélité.\n";
}


// Fonction pour annuler une réservation
void annulerReservation(std::vector<Train>& trains, Passager& passager) {
    std::cout << "\n=== Annulation de Réservation ===\n";

    passager.afficherReservations();

    int numeroBillet;
    std::cout << "Entrez le numéro du billet à annuler : ";
    std::cin >> numeroBillet;

    bool trouve = false;
    for (auto it = passager.getReservations().begin(); it != passager.getReservations().end(); ++it) {
        if (it->getNumeroBillet() == numeroBillet) {
            passager.ajouterHistorique(*it, "Annulé");

            // Rendre la place au train
            for (auto& train : trains) {
                if (train.getNumeroTrain() == it->getNumeroTrain()) {
                    train.annulerReservation();
                    break;
                }
            }

            passager.annulerReservation(numeroBillet);
            std::cout << "Réservation annulée avec succès.\n";
            trouve = true;
            break;
        }
    }

    if (!trouve) {
        std::cout << "Billet non trouvé.\n";
    }
}

// Fonction principale
int main() {
    // Charger les données
    std::vector<Train> trains = chargerTrains();
    std::vector<Passager> passagers = chargerPassagers();

    // Choisir un passager
    std::cout << "=== Bienvenue dans le système de réservation ===\n";
    Passager passager = creerOuUtiliserUtilisateur(passagers);

    int choix = 0;
    do {
        std::cout << "\n=== Menu Principal ===\n";
        std::cout << "1. Afficher les trains disponibles\n";
        std::cout << "2. Réserver un billet\n";
        std::cout << "3. Annuler une réservation\n";
        std::cout << "4. Consulter les réservations\n";
        std::cout << "5. Afficher l'historique des billets\n";
        std::cout << "6. Quitter\n";
        std::cout << "7. Afficher les points de fidélité\n";
        std::cout << "Entrez votre choix : ";
        std::cin >> choix;

        switch (choix) {
            case 1:
                afficherTousLesTrains(trains);
                break;
            case 2:
                reserverBillet(trains, passager);
                sauvegarderTrains(trains);
                break;
            case 3:
                annulerReservation(trains, passager);
                sauvegarderTrains(trains);
                break;
            case 4:
                consulterReservations(passager);
                break;
            case 5:
                afficherHistorique(passager);
                break;
            case 6:
                std::cout << "Au revoir !\n";
                sauvegarderTrains(trains);
                sauvegarderPassagers(passagers);
                break;
            case 7:
                 afficherPointsFidelite(passager);
                break;
            default:
                std::cout << "Choix invalide. Veuillez réessayer.\n";
        }
    } while (choix != 6);

    return 0;
}
