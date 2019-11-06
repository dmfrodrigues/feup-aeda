#include "truck.h"

#include "utils.h"

Truck::Truck(const Truck &truck):
    number_plate_(truck.number_plate_), plate_register_date_(truck.plate_register_date_),
    fuel_        (truck.fuel_        ), max_reach_          (truck.max_reach_          ),
    category_    (truck.category_    ){}

Truck::Truck(const NumberPlate &number_plate, const Time     &plate_register_date,
             const Fuel        &fuel        , const Distance &max_reach          ,
             const Category    &category):
    number_plate_(number_plate), plate_register_date_(plate_register_date),
    fuel_        (fuel        ), max_reach_          (max_reach          ),
    category_    (category    ){}
