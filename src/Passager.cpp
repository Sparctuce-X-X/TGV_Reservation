#include "../include/Passager.h"
#include <fstream>
#include <sstream>
#include <iostream> 
// Constructeur
Passager::Passager(const std::string& nom, const std::string& prenom, int id)
    : nom(nom), prenom(prenom), identifiant(id) {}

// Ajouter une réservation
void Passager::ajouterReservation(const Billet& billet) {
    reservations.push_back(billet);
}

// Annuler une réservation
void Passager::annulerReservation(int numeroBillet) {
    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        if (it->getNumeroBillet() == numeroBillet) {
            // Ajouter le billet annulé à l'historique
            ajouterHistorique(*it, "Annulé");
            reservations.erase(it);
            std::cout << "Billet #" << numeroBillet << " annulé avec succès.\n";
            return;
        }
    }
    std::cout << "Billet #" << numeroBillet << " non trouvé.\n";
}

// Afficher toutes les réservations
void Passager::afficherReservations() const {
    if (reservations.empty()) {
        std::cout << "Aucune réservation pour ce passager.\n";
        return;
    }

    std::cout << "Réservations en cours pour " << nom << " " << prenom << ":\n";
    for (const auto& billet : reservations) {
        billet.afficherDetailsBillet();
    }
}

// Ajouter un billet à l'historique avec un état spécifique
void Passager::ajouterHistorique(const Billet& billet, const std::string& etat) {
    historiqueReservations.push_back(std::make_pair(billet, etat));
}

// Afficher tout l'historique des billets
void Passager::afficherHistorique() const {
    if (historiqueReservations.empty()) {
        std::cout << "Aucun billet dans l'historique pour ce passager.\n";
        return;
    }

    std::cout << "Historique des billets pour " << nom << " " << prenom << ":\n";
    for (const auto& [billet, etat] : historiqueReservations) {
        billet.afficherDetailsBillet();
        std::cout << "État : " << etat << "\n";
        std::cout << "-------------------------------\n";
    }
}

// Filtrer l'historique selon un critère
void Passager::filtrerHistorique(const std::string& critere, const std::string& valeur) const {
    bool match = false;
    std::cout << "Filtrage de l'historique par " << critere << ": " << valeur << "\n";

    for (const auto& [billet, etat] : historiqueReservations) {
        if ((critere == "villeDepart" && billet.getVilleDepart() == valeur) ||
            (critere == "villeArrivee" && billet.getVilleArrivee() == valeur) ||
            (critere == "classe" && billet.getTypeClasse() == valeur) ||
            (critere == "etat" && etat == valeur)) {
            billet.afficherDetailsBillet();
            std::cout << "État : " << etat << "\n";
            std::cout << "-------------------------------\n";
            match = true;
        }
    }

    if (!match) {
        std::cout << "Aucun billet correspondant à ce critère.\n";
    }
}

// Charger les passagers depuis un fichier
std::vector<Passager> Passager::chargerPassagers(const std::string& fichier) {
    std::vector<Passager> passagers;
    std::ifstream file(fichier);

    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << fichier << "\n";
        return passagers;
    }

    std::string ligne;
    while (std::getline(file, ligne)) {
        std::stringstream ss(ligne);
        std::string identifiant, nom, prenom;

        std::getline(ss, identifiant, '|');
        std::getline(ss, nom, '|');
        std::getline(ss, prenom, '|');

        passagers.emplace_back(nom, prenom, std::stoi(identifiant));
    }

    file.close();
    return passagers;
}

// Sauvegarder les passagers dans un fichier
void Passager::sauvegarderPassagers(const std::vector<Passager>& passagers, const std::string& fichier) {
    std::ofstream file(fichier);

    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << fichier << " pour l'écriture.\n";
        return;
    }

    for (const auto& passager : passagers) {
        file << passager.getIdentifiant() << "|"
             << passager.getNom() << "|"
             << passager.getPrenom() << "\n";
    }

    file.close();
}


// Obtenir le nom du passager
const std::string& Passager::getNom() const {
    return nom;
}

// Obtenir le prénom du passager
const std::string& Passager::getPrenom() const {
    return prenom;
}

// Obtenir l'identifiant du passager
int Passager::getIdentifiant() const {
    return identifiant;
}

// Obtenir la liste des réservations
const std::vector<Billet>& Passager::getReservations() const {
    return reservations;
}

// Getter pour l'historique
const std::vector<std::pair<Billet, std::string>>& Passager::getHistorique() const {
    return historiqueReservations;
}

void Passager::ajouterPointsFidelite(int points) {
    pointsFidelite += points;
    std::cout << points << " points de fidélité ajoutés !\n";
}

bool Passager::utiliserPointsFidelite(int points) {
    if (points > pointsFidelite) {
        std::cout << "Erreur : Points de fidélité insuffisants.\n";
        return false;
    }
    pointsFidelite -= points;
    std::cout << points << " points de fidélité utilisés avec succès !\n";
    return true;
}

int Passager::getPointsFidelite() const {
    return pointsFidelite;
}
