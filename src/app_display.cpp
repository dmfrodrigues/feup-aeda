#include "app.h"

void App::print_list(const std::vector<const Client*> &v){
    std::cout << std::endl;
    std::cout << " ╭─╴╷   ┬ ╭─╴╷ ╷╶┬╴╭─╴ \n"
              << " │  │   │ ├─╴│╲│ │ ╰─╮ \n"
              << " ╰─╴╰─╴ ┴ ╰─╴╵ ╵ ╵ ╶─╯ \n";
    std::cout << std::endl;
    std::cout << "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╕" << std::endl;
    std::cout << "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │" << std::endl;
    std::cout << "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╡" << std::endl;
    for(const Client* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                 ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                     ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street"),28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()              ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                      ,16) <<   " │"
                  << std::endl;
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╛" << std::endl;
}

void App::print_list(const std::vector<const Driver*> &v){
    std::cout << std::endl;
    std::cout << " ┌─╮┌─╮ ┬ ╷  ╭─╴┌─╮╭─╴ \n"
              << " │ │├┬╯ │ │ ╱├─╴├┬╯╰─╮ \n"
              << " └─╯╵╰  ┴ │╱ ╰─╴╵╰ ╶─╯ \n";
    std::cout << std::endl;
    std::cout << "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╤═════════════════╕" << std::endl;
    std::cout << "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │ Base salary [5] │" << std::endl;
    std::cout << "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╪═════════════════╡" << std::endl;
    for(const Driver* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                  ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                      ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street") ,28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()               ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                       ,16) <<   " │ "
                  << utils::rjust(utils::ftos("%.2f",(double)p->get_base_salary()),15) <<   " │"
                  << std::endl;
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╧═════════════════╛" << std::endl;
}

void App::print_list(const std::vector<const Manager*> &v){
    std::cout << std::endl;
    std::cout << " ╭┬╮╭─╮╷ ╷╭─╮╭─╮╭─╴┌─╮╭─╴ \n"
              << " │╵│├─┤│╲│├─┤│ ╮├─╴├┬╯╰─╮ \n"
              << " ╵ ╵╵ ╵╵ ╵╵ ╵╰─╯╰─╴╵╰╴╶─╯ \n";
    std::cout << std::endl;
    std::cout << "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╤═════════════════╕" << std::endl;
    std::cout << "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │ Base salary [5] │" << std::endl;
    std::cout << "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╪═════════════════╡" << std::endl;
    for(const Manager* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                  ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                      ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street") ,28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()               ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                       ,16) <<   " │ "
                  << utils::rjust(utils::ftos("%.2f",(double)p->get_base_salary()),15) <<   " │"
                  << std::endl;
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╧═════════════════╛" << std::endl;
}

std::string App::get_cargo_string(const Truck *p){
    std::string s = "";
    const std::vector<const CargoTrans*> &w = p->get_cargo();
    size_t sz;
    if((sz = App::filter<CargoTrans,CargoTrans            ,Cargo::Type>(w, Cargo::Type::Normal      ).size())){ if(s != "") s += ", "; s += "Normal ("       + utils::itos((long long)sz) + ")"; }
    if((sz = App::filter<CargoTrans,CargoTransAnimal      ,Cargo::Type>(w, Cargo::Type::Animal      ).size())){ if(s != "") s += ", "; s += "Animal ("       + utils::itos((long long)sz) + ")"; }
    if((sz = App::filter<CargoTrans,CargoTransRefrigerated,Cargo::Type>(w, Cargo::Type::Refrigerated).size())){ if(s != "") s += ", "; s += "Refrigerated (" + utils::itos((long long)sz) + ")"; }
    if((sz = App::filter<CargoTrans,CargoTransDangerous   ,Cargo::Type>(w, Cargo::Type::Dangerous   ).size())){ if(s != "") s += ", "; s += "Dangerous ("    + utils::itos((long long)sz) + ")"; }
    return s;
}

void App::print_list(const std::vector<const Truck*> &v){
    std::cout << std::endl;
    std::cout << " ╶┬╴┌─╮╷ ╷╭─╴╷ ╱╭─╴ \n"
              << "  │ ├┬╯│ ││  │╱ ╰─╮ \n"
              << "  ╵ ╵╰╴╰─╯╰─╴│ ╲╶─╯ \n";
    std::cout << std::endl;
    std::cout << "╒════════════════════════╤═══════════════╤═══════════════╤════════════════╤══════════════╤═══════════════════════════════════════════════════════════════╕" << std::endl;
    std::cout << "│ Number plate [0]       │ Date [1]      │ Fuel [2]      │ Range (km) [3] │ Category [4] │ Cargo [5]                                                     │" << std::endl;
    std::cout << "╞════════════════════════╪═══════════════╪═══════════════╪════════════════╪══════════════╪═══════════════════════════════════════════════════════════════╡" << std::endl;
    for(const Truck* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_numberplate()                 ,21) << "\t │ "
                  << utils::ljust(p->get_plateregisterdate().format("%Y/%m/%d")     ,10) << "\t │ "
                  << utils::ljust(Truck::fuel_string(p->get_fuel())                 ,12) << "\t │ "
                  << utils::rjust(utils::ftos("%.1f", (float)p->get_range())        ,14) <<   " │ "
                  << utils::ljust((std::string)p->get_category()                    ,11) << "\t │ "
                  << utils::ljust(App::get_cargo_string(p)                          ,59) << "\t │ "
                  << std::endl;
    }
    std::cout << "╘════════════════════════╧═══════════════╧═══════════════╧════════════════╧══════════════╧═══════════════════════════════════════════════════════════════╛" << std::endl;

}

void App::display(const Client *p){
    std::cout << "╒══════════════════╤═════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username     │ " << utils::ljust((std::string)p->get_username()                        ,82) << "\t │\n"
              << "│ [1] Name         │ " << utils::ljust((std::string)p->get_name()                            ,82) << "\t │\n"
              << "│ [2] Address      │ " << utils::ljust(p->get_address().format("%street (%postal %city)")    ,82) << "\t │\n"
              << "│ [3] Phone number │ " << utils::ljust((std::string)p->get_phonenumber()                     ,82) << "\t │\n"
              << "│ [4] VAT          │ " << utils::ljust((std::string)p->get_vat()                             ,82) << "\t │\n"
              << "╘══════════════════╧═════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Driver *p){
    std::cout << "╒══════════════════╤═════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username     │ " << utils::ljust((std::string)p->get_username()                        ,82) << "\t │\n"
              << "│ [1] Name         │ " << utils::ljust((std::string)p->get_name()                            ,82) << "\t │\n"
              << "│ [2] Address      │ " << utils::ljust(p->get_address().format("%street (%postal %city)")    ,82) << "\t │\n"
              << "│ [3] Phone number │ " << utils::ljust((std::string)p->get_phonenumber()                     ,82) << "\t │\n"
              << "│ [4] VAT          │ " << utils::ljust((std::string)p->get_vat()                             ,82) << "\t │\n"
              << "│ [5] Base salary  │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_base_salary())      ,82) << "\t │\n"
              << "╘══════════════════╧═════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Manager *p){
    std::cout << "╒══════════════════╤═════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username     │ " << utils::ljust((std::string)p->get_username()                        ,82) << "\t │\n"
              << "│ [1] Name         │ " << utils::ljust((std::string)p->get_name()                            ,82) << "\t │\n"
              << "│ [2] Address      │ " << utils::ljust(p->get_address().format("%street (%postal %city)")    ,82) << "\t │\n"
              << "│ [3] Phone number │ " << utils::ljust((std::string)p->get_phonenumber()                     ,82) << "\t │\n"
              << "│ [4] VAT          │ " << utils::ljust((std::string)p->get_vat()                             ,82) << "\t │\n"
              << "│ [5] Base salary  │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_base_salary())      ,82) << "\t │\n"
              << "╘══════════════════╧═════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Truck *p){
    std::cout << "╒══════════════════╤═════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Number plate │ " << utils::ljust((std::string)p->get_numberplate()                     ,82) << "\t │\n"
              << "│ [1] Date         │ " << utils::ljust(p->get_plateregisterdate().format("%Y/%m/%d")         ,82) << "\t │\n"
              << "│ [2] Fuel         │ " << utils::ljust(Truck::fuel_string(p->get_fuel())                     ,82) << "\t │\n"
              << "│ [3] Range (km)   │ " << utils::ljust(utils::ftos("%.1f", (float)p->get_range())            ,82) << "\t │\n"
              << "│ [4] Category     │ " << utils::ljust((std::string)p->get_category()                        ,82) << "\t │\n";
    auto cargo = p->get_cargo();
    for(size_t i = 0; i < cargo.size(); ++i){
        const CargoTrans *q = cargo[i];
        std::cout << "├──────────────────┴─────────────────────────────────────────────────────────────────────────────────────┤\n"
                  << "│ [5] Cargo " << utils::rjust("#"+utils::itos((long long)i), 6)
                                    << " : " + utils::ljust(Cargo::type_string(q->get_type()), 82) << "\t │\n"
                  << "├──────────────────┬─────────────────────────────────────────────────────────────────────────────────────┤\n";
        App::display(q);
    }
    std::cout << "╘══════════════════╧═════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const CargoTrans             *p){
    std::cout << "│ [0] Weight (kg)  │ " << utils::ljust(utils::ftos("%.0f",(float )p->get_weight())       ,82) << "\t │\n"
              << "│ [1] Description  │ " << utils::ljust(p->get_description()                              ,82) << "\t │\n"
              << "| [2] Price base € │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_pricebase())    ,82)<< "\t │\n"
              << "│ [3] Expense €/km │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_expensesperkm()),82)<<"\t │\n";
    switch(p->get_type()){
        case Cargo::Animal      : display(dynamic_cast<const CargoTransAnimal      *>(p)); break;
        case Cargo::Refrigerated: display(dynamic_cast<const CargoTransRefrigerated*>(p)); break;
        case Cargo::Dangerous   : display(dynamic_cast<const CargoTransDangerous   *>(p)); break;
        case Cargo::Normal      : break;
        default: throw std::invalid_argument("invalid Cargo type");
    }
}
void App::display(const CargoTransAnimal       *p){
}
void App::display(const CargoTransRefrigerated *p){
    std::cout << "│ [4] Ref temp °C  │ " << utils::ljust(utils::ftos("%.1f",(float )p->get_reference_temperature()), 82) << "\t │\n"
              << "│ [5] Temp factor  │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_temperaturefactor())    , 82) << "\t │\n";
}
void App::display(const CargoTransDangerous    *p){
    std::cout << "│ [4] Danger level │ " << utils::ljust(Cargo::dangerlevel_string(p->get_dangerlevel())          , 82) << "\t │\n";
}

void App::display(const Service *p) const{
    const Client *c = dynamic_cast<const Client*>(*utils::find_if(users_.begin(), users_.end(),
      [p](const User *q){ return (q->get_username() == p->get_client()); }));
    std::cout << "╒══════════════════╤═════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] ID           │ " << utils::ljust(p->get_id()                                           ,82) << "\t │\n"
              << "│ [1] Client       │ " << utils::ljust("["+std::string(c->get_username())+"] "+c->get_name()+c->get_address().format(" (%street, %district)"),82) << "\t │\n"
              << "╘══════════════════╧═════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}
