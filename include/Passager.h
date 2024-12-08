#ifndef PASSAGER_H
#define PASSAGER_H

#include <string>
#include <vector>
#include "Billet.h"

class Passager {
private:
    std::string nom;
    std::string prenom;
    int identifiant;
    int pointsFidelite;  // Points de fidélité accumulés
    std::vector<Billet> reservations;  // Réservations en cours
    std::vector<std::pair<Billet, std::string>> historiqueReservations;  // Historique des billets

public:
    // Constructeur
    Passager(const std::string& nom, const std::string& prenom, int id);

    // Gestion des réservations
    void ajouterReservation(const Billet& billet);
    void annulerReservation(int numeroBillet);
    void afficherReservations() const;

    // Gestion de l'historique
    void ajouterHistorique(const Billet& billet, const std::string& etat);
    void afficherHistorique() const;
    void filtrerHistorique(const std::string& critere, const std::string& valeur) const;

    // Gestion des points de fidélité
    void ajouterPointsFidelite(int points);   // Ajouter des points
    bool utiliserPointsFidelite(int points); // Utiliser des points
    int getPointsFidelite() const;           // Obtenir les points actuels

    // Getters pour les informations du passager
    const std::string& getNom() const;
    const std::string& getPrenom() const;
    int getIdentifiant() const;
    const std::vector<Billet>& getReservations() const;
    const std::vector<std::pair<Billet, std::string>>& getHistorique() const;

    // Gestion des fichiers
    static std::vector<Passager> chargerPassagers(const std::string& fichier);
    static void sauvegarderPassagers(const std::vector<Passager>& passagers, const std::string& fichier);
};

#endif // PASSAGER_H
