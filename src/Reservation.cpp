#include "Reservation.h"
#include <iostream>

// Constructeur
Reservation::Reservation(int numero, const Passager& passager, const Billet& billet)
    : numeroReservation(numero), passager(passager), billet(billet), etat("En attente") {}

// Confirmer la réservation
void Reservation::confirmerReservation() {
    etat = "Confirmée";

    // Calcul des points de fidélité : 1 point par euro dépensé
    int points = static_cast<int>(billet.getPrix());
    passager.ajouterPointsFidelite(points);

    std::cout << "Réservation #" << numeroReservation << " confirmée avec succès.\n";
}

// Annuler la réservation
void Reservation::annulerReservation() {
    etat = "Annulée";
    std::cout << "Réservation #" << numeroReservation << " annulée avec succès.\n";
}

// Afficher les détails de la réservation
void Reservation::afficherDetailsReservation() const {
    std::cout << "\n=== Détails de la Réservation ===\n";
    std::cout << "Numéro de Réservation : " << numeroReservation << "\n";
    std::cout << "État : " << etat << "\n";
    std::cout << "Passager : " << passager.getNom() << " " << passager.getPrenom() << "\n";
    billet.afficherDetailsBillet();
    std::cout << "-------------------------------\n";
}

// Getters
int Reservation::getNumeroReservation() const {
    return numeroReservation;
}

const std::string& Reservation::getEtat() const {
    return etat;
}

const Passager& Reservation::getPassager() const {
    return passager;
}

const Billet& Reservation::getBillet() const {
    return billet;
}
