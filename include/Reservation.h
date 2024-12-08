#ifndef RESERVATION_H
#define RESERVATION_H

#include "Billet.h"
#include "Passager.h"

class Reservation {
private:
    int numeroReservation; // Numéro unique de réservation
    Passager passager;     // Passager associé à la réservation
    Billet billet;         // Billet associé à la réservation
    std::string etat;      // État de la réservation ("Confirmée", "Annulée", etc.)

public:
    // Constructeur
    Reservation(int numero, const Passager& passager, const Billet& billet);

    // Méthodes principales
    void confirmerReservation();       // Confirme la réservation
    void annulerReservation();         // Annule la réservation
    void afficherDetailsReservation() const; // Affiche les détails de la réservation

    // Getters
    int getNumeroReservation() const;  // Retourne le numéro de réservation
    const std::string& getEtat() const; // Retourne l'état de la réservation
    const Passager& getPassager() const; // Retourne le passager
    const Billet& getBillet() const;   // Retourne le billet
};

#endif // RESERVATION_H
