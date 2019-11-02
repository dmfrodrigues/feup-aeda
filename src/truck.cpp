#include "../include/truck.h"

#include "../include/utils.h"

/* Truck Superclass */
Truck::Truck(const Truck &truck):
    max_weight_(truck.max_weight_), max_reach_(truck.max_reach_), taxes_(truck.taxes_){}

Truck::Truck(unsigned int max_weight, unsigned int max_reach, float taxes):
    max_weight_(max_weight), max_reach_(max_reach), taxes_(taxes){}

unsigned int Truck::getMaxWeight() const { return max_weight_; }

void Truck::setMaxWeight(unsigned int max_weight) {
    max_weight_ = max_weight;
    updatePrice();
}

Currency Truck::getPrice() const { return price_; }

std::vector<Cargo>::iterator Truck::removeCargo(std::vector<Cargo>::const_iterator it) {
    if (it >= cargo_.end() || it < cargo_.begin()) throw utils::InvalidIterator();

    return cargo_.erase(it);
}

void Truck::clearCargo() { cargo_.clear(); }

std::vector<Cargo>::iterator Truck::cargoBegin() { return cargo_.begin(); }

std::vector<Cargo>::iterator Truck::cargoEnd() { return cargo_.end(); }

