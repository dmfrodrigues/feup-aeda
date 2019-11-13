#include "app.h"

void App::print_list(const std::vector<const Client*> &v){
    std::cout << "\n"
                 " ╭─╴╷   ┬ ╭─╴╷ ╷╶┬╴╭─╴ \n"
                 " │  │   │ ├─╴│╲│ │ ╰─╮ \n"
                 " ╰─╴╰─╴ ┴ ╰─╴╵ ╵ ╵ ╶─╯ \n"
                 "\n"
                 "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╕\n"
                 "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │\n"
                 "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╡\n";
    for(const Client* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                 ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                     ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street"),28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()              ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                      ,16) <<   " │"
                  << std::endl;
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╛\n"
              << std::flush;
}

void App::print_list(const std::vector<const Driver*> &v){
    std::cout << "\n"
                 " ┌─╮┌─╮ ┬ ╷  ╭─╴┌─╮╭─╴ \n"
                 " │ │├┬╯ │ │ ╱├─╴├┬╯╰─╮ \n"
                 " └─╯╵╰  ┴ │╱ ╰─╴╵╰ ╶─╯ \n"
                 "\n"
                 "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╤═════════════════╕\n"
                 "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │ Base salary [5] │\n"
                 "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╪═════════════════╡\n";
    for(const Driver* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                  ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                      ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street") ,28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()               ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                       ,16) <<   " │ "
                  << utils::rjust(utils::ftos("%.2f",(double)p->get_base_salary()),15) <<   " │\n";
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╧═════════════════╛\n"
              << std::flush;
}

void App::print_list(const std::vector<const Manager*> &v){
    std::cout << "\n"
                 " ╭┬╮╭─╮╷ ╷╭─╮╭─╮╭─╴┌─╮╭─╴ \n"
                 " │╵│├─┤│╲│├─┤│ ╮├─╴├┬╯╰─╮ \n"
                 " ╵ ╵╵ ╵╵ ╵╵ ╵╰─╯╰─╴╵╰╴╶─╯ \n"
                 "\n"
                 "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╤═════════════════╕\n"
                 "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │ Base salary [5] │\n"
                 "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╪═════════════════╡\n";
    for(const Manager* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                  ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                      ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street") ,28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()               ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                       ,16) <<   " │ "
                  << utils::rjust(utils::ftos("%.2f",(double)p->get_base_salary()),15) <<   " │\n";
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╧═════════════════╛\n"
              << std::flush;
}

void App::print_list(const std::vector<const Truck*> &v){
    std::cout << "\n"
                 " ╶┬╴┌─╮╷ ╷╭─╴╷ ╱╭─╴ \n"
                 "  │ ├┬╯│ ││  │╱ ╰─╮ \n"
                 "  ╵ ╵╰╴╰─╯╰─╴│ ╲╶─╯ \n"
                 "\n"
                 "╒══════════════════╤════════════╤══════════════╤════════════════╤══════════════╤════════════════╤══════════════════╤════════════════╕\n"
                 "│ Number plate [0] │ Date [1]   │ Fuel [2]     │ Range (km) [3] │ Category [4] │ Cargo type [5] │ Cargo weight [6] │ Price base [7] │\n"
                 "╞══════════════════╪════════════╪══════════════╪════════════════╪══════════════╪════════════════╪══════════════════╪════════════════╡\n";
    for(const Truck* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_numberplate()                     ,16) << " │ "
                  << p->get_plateregisterdate().format("%Y/%m/%d")                           << " │ "
                  << utils::ljust(Truck::fuel_string(p->get_fuel())                     ,12) << " │ "
                  << utils::rjust(utils::ftos("%.1f", (double)p->get_range())           ,14) << " │ "
                  << utils::ljust((std::string)p->get_category()                        ,12) << " │ "
                  << utils::ljust(Cargo::type_string(p->get_cargo()->get_type())        ,14) << " │ "
                  << utils::rjust(utils::ftos("%.1f", (double)p->get_cargo()->get_W())  ,16) << " │ "
                  << utils::rjust(utils::ftos("%+.2f",(double)p->get_cargo()->get_P_B()),14) << " │\n";
    }
    std::cout << "╘══════════════════╧════════════╧══════════════╧════════════════╧══════════════╧════════════════╧══════════════════╧════════════════╛\n"
              << std::flush;
}

void App::print_list(const std::vector<const Service*> &v) const{
    Currency EXPENSES(0), PRICE(0);
    for(const Service *p:v){
        EXPENSES += p->get_expenses();
        PRICE += p->get_price();
    }
    EXPENSES = -EXPENSES;
    std::cout << "\n"
                 " ╭─╴╭─╴┌─╮╷   ┬ ╭─╴╭─╴╭─╴ \n"
                 " ╰─╮├─╴├┬╯│ ╱ │ │  ├─╴╰─╮ \n"
                 " ╶─╯╰─╴╵╰╴│╱  ┴ ╰─╴╰─╴╶─╯ \n"
                 "\n"
                 "╒═════╤══════════════╤═══════════════════════════════════╤══════════════════╤════════════════════════════╤═══════════════╤═══════════════════════════╤═════════════╤═════════════╕\n"
                 "│ ID  │ Client [1]   │ Contact 1 [2]                     │ Time begin [4]   │ Address begin [6]          │ Cargo:        │ [10] Truck/driver         │ Costs       │ Revenue     │\n"
                 "│ [0] │              │                                   │                  │                            │ Type [8]      │                           │ [11]        │ [12]        │\n"
                 "│     │              │ Contact 2 [3]                     │ Time end   [5]   │ Address end   [7]          │ Weight [9]    │                           │             │             │\n"
                 "╞═════╪══════════════╪═══════════════════════════════════╪══════════════════╪════════════════════════════╪═══════════════╪═══════════════════════════╪═════════════╪═════════════╡\n";
    for(const Service* p:v){
        const User *c = App::find_user(p->get_client());
        const std::vector<Truck::NumberPlate> &tv = p->get_trucks ();
        const std::vector<Driver::Username  > &dv = p->get_drivers();
        std::cout << "│ "
                  << utils::rjust(p->get_id()                                                                                           , 3) <<   " │ "
                  << utils::ljust(std::string(c->get_username())                                                                        ,12) <<   " │ "
                  << utils::ljust(utils::ljust(p->get_contact1().get_name()  ,11)+" / "+std::string(p->get_contact1().get_phonenumber()),32) << "\t │ "
                  << p->get_tbegin().format("%Y/%m/%d %H:%M")                                                                                <<   " │ "
                  << utils::ljust(p->get_abegin().format("(%district) %city")                                                           ,25) << "\t │ "
                  << utils::ljust(Cargo::type_string(p->get_cargo()->get_type())                                                        ,13) <<   " │ "
                  << utils::ljust(std::string(tv[0]), 12) + " " + utils::ljust(std::string(dv[0])                                       ,12) <<   " │ "
                  << utils::rjust(utils::ftos("%+.2f", -double(p->get_expenses()))                                                      ,11) <<   " │ "
                  << utils::rjust(utils::ftos("%+.2f",  double(p->get_price   ()))                                                      ,11) <<   " │\n";
        std::cout << "│     │ ";
        if(c == NULL) std::cout << "(DELETED)    │ ";
        else          std::cout << "             │ ";
        std::cout << utils::ljust(utils::ljust(p->get_contact2().get_name()  ,11)+" / "+std::string(p->get_contact2().get_phonenumber()),32) << "\t │ "
                  << p->get_tend  ().format("%Y/%m/%d %H:%M")                                                                                <<   " │ "
                  << utils::ljust(p->get_aend  ().format("(%district) %city")                                                           ,25) << "\t │ "
                  << utils::rjust(utils::ftos("%.1fT", double(p->get_cargo()->get_W())/1000.0)                                          ,13) <<   " │ ";
        if(tv.size() > 1) std::cout << utils::ljust("("+std::string(tv[1])+")", 14) + " " + utils::ljust(std::string(dv[1]), 12) << " │               │               │\n";
        else              std::cout << "                          │             │             │\n";
        for(size_t i = 2; i < tv.size(); ++i){
            std::cout << "│        │              │                                   │                  │                            │                       │ "
                      << utils::ljust(std::string(tv[i]), 12) + " " + utils::ljust(std::string(dv[i]), 13) << " │               │               │\n";
        }
    }
    std::cout << "╘═════╧══════════════╧═══════════════════════════════════╧══════════════════╧════════════════════════════╧═══════════════╪═══════════════════════════╪═════════════╪═════════════╡\n"
              << "                                                                                                                         │                     TOTAL │ "+utils::rjust(utils::ftos("%+.2f", double(EXPENSES)), 11)
                                                                                                                                                                                  +" │ "+utils::rjust(utils::ftos("%+.2f", double(PRICE)), 11)+" │\n"
              << "                                                                                                                         ╘═══════════════════════════╧═════════════╧═════════════╛\n"
              << std::flush;
}

void App::display(const Client *p){
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username      │ " << utils::ljust((std::string)p->get_username()                       ,81) << "\t │\n"
              << "│ [1] Name          │ " << utils::ljust((std::string)p->get_name()                           ,81) << "\t │\n"
              << "│ [2] Address       │ " << utils::ljust(p->get_address().format("%street (%postal %city)")   ,81) << "\t │\n"
              << "│ [3] Phone number  │ " << utils::ljust((std::string)p->get_phonenumber()                    ,81) << "\t │\n"
              << "│ [4] VAT           │ " << utils::ljust((std::string)p->get_vat()                            ,81) << "\t │\n"
              << "╘═══════════════════╧════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Driver *p){
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username      │ " << utils::ljust((std::string)p->get_username()                       ,81) << "\t │\n"
              << "│ [1] Name          │ " << utils::ljust((std::string)p->get_name()                           ,81) << "\t │\n"
              << "│ [2] Address       │ " << utils::ljust(p->get_address().format("%street (%postal %city)")   ,81) << "\t │\n"
              << "│ [3] Phone number  │ " << utils::ljust((std::string)p->get_phonenumber()                    ,81) << "\t │\n"
              << "│ [4] VAT           │ " << utils::ljust((std::string)p->get_vat()                            ,81) << "\t │\n"
              << "│ [5] Base salary   │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_base_salary())     ,81) << "\t │\n"
              << "╘═══════════════════╧════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Manager *p){
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username      │ " << utils::ljust((std::string)p->get_username()                       ,81) << "\t │\n"
              << "│ [1] Name          │ " << utils::ljust((std::string)p->get_name()                           ,81) << "\t │\n"
              << "│ [2] Address       │ " << utils::ljust(p->get_address().format("%street (%postal %city)")   ,81) << "\t │\n"
              << "│ [3] Phone number  │ " << utils::ljust((std::string)p->get_phonenumber()                    ,81) << "\t │\n"
              << "│ [4] VAT           │ " << utils::ljust((std::string)p->get_vat()                            ,81) << "\t │\n"
              << "│ [5] Base salary   │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_base_salary())     ,81) << "\t │\n"
              << "╘═══════════════════╧════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Truck *p){
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Number plate  │ " << utils::ljust((std::string)p->get_numberplate()                    ,81) << "\t │\n"
              << "│ [1] Date          │ " << utils::ljust(p->get_plateregisterdate().format("%Y/%m/%d")        ,81) << "\t │\n"
              << "│ [2] Fuel          │ " << utils::ljust(Truck::fuel_string(p->get_fuel())                    ,81) << "\t │\n"
              << "│ [3] Range (km)    │ " << utils::ljust(utils::ftos("%.1f", (double)p->get_range())          ,81) << "\t │\n"
              << "│ [4] Category      │ " << utils::ljust((std::string)p->get_category()                       ,81) << "\t │\n";
    const CargoTrans *q = p->get_cargo();
    std::cout << "├───────────────────┴────────────────────────────────────────────────────────────────────────────────────┤\n"
              << "│ [5] Cargo         : "<< utils::ljust(Cargo::type_string(q->get_type()), 81) << "\t │\n"
              << "├───────────────────┬────────────────────────────────────────────────────────────────────────────────────┤\n";
    App::display(q);
    std::cout << "╘═══════════════════╧════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Service *p) const{
    const User *c = App::find_user(p->get_client());
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] ID            │ " << utils::ljust(p->get_id()                                          ,81) << "\t │\n";
    if(c == NULL) std::cout << "│ [1] Client        │ " << utils::ljust("["+std::string(c->get_username())+"] (DELETED)"                                                      ,81) << "\t │\n";
    else          std::cout << "│ [1] Client        │ " << utils::ljust("["+std::string(c->get_username())+"] "+c->get_name()+c->get_address().format(" (%street, %district)"),81) << "\t │\n";
    std::cout << "│ [2] Contact 1     │ " << utils::ljust(p->get_contact1().get_name()+" / "+std::string(p->get_contact1().get_phonenumber()) ,81) << "\t │\n"
              << "│ [3] Contact 2     │ " << utils::ljust(p->get_contact2().get_name()+" / "+std::string(p->get_contact2().get_phonenumber()) ,81) << "\t │\n"
              << "│ [4] Time begin    │ " << utils::ljust(p->get_tbegin().format("%Y/%m/%d %H:%M:%S")          ,81) << "\t │\n"
              << "│ [5] Time end      │ " << utils::ljust(p->get_tend  ().format("%Y/%m/%d %H:%M:%S")          ,81) << "\t │\n"
              << "│ [6] Address begin │ " << utils::ljust(p->get_abegin().format("%street (%postal, %city) [%district, %country]"),81) << "\t │\n"
              << "│ [7] Address end   │ " << utils::ljust(p->get_aend  ().format("%street (%postal, %city) [%district, %country]"),81) << "\t │\n";
    std::cout << "├───────────────────┴────────────────────────────────────────────────────────────────────────────────────┤\n"
              << "│ [8] Cargo         : " << utils::ljust(Cargo::type_string(p->get_cargo()->get_type())       ,81) << "\t │\n"
              << "├───────────────────┬────────────────────────────────────────────────────────────────────────────────────┤\n";
    App::display(p->get_cargo());
    std::cout << "├───────────────────┴────────────────────────────────────────────────────────────────────────────────────┤\n"
              << "│ [9] Truck/driver                                                                                       │\n"
              << "├───────────────────┬────────────────────────────────────────────────────────────────────────────────────┤\n";
    const auto &tv = p->get_trucks ();
    const auto &dv = p->get_drivers();
    for(size_t i = 0; i < tv.size(); ++i){
        const User *d = find_user(dv[i]);
        std::cout << "│ Truck/driver " << utils::rjust("#"+utils::itos((long long)i), 4)
                                 << " │ " << utils::ljust("[0] Truck : " + std::string(tv[i])                  , 81) << "\t │\n";
        std::cout << "│                   │ ";
        if(d == NULL) std::cout           << utils::ljust("[1] Driver: ["+std::string(dv[i])+"] (DELETED)"                                             , 81) << "\t │\n";
        else          std::cout           << utils::ljust("[1] Driver: ["+std::string(dv[i])+"] "+d->get_name()+" / "+std::string(d->get_phonenumber()), 81) << "\t │\n";
        if(i+1 != tv.size()) std::cout << "├───────────────────┼────────────────────────────────────────────────────────────────────────────────────┤\n";
    }
    std::cout << "╘═══════════════════╧════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Cargo *p){
    std::cout << "│ [0] Weight (kg)   │ " << utils::ljust(utils::ftos("%.0f",(double)p->get_W())       ,81) << "\t │\n"
              << "│ [1] Description   │ " << utils::ljust(p->get_description()                              ,81) << "\t │\n";
    switch(p->get_type()){
      case Cargo::Animal      : display(dynamic_cast<const CargoAnimal      *>(p)); break;
      case Cargo::Refrigerated: display(dynamic_cast<const CargoRefrigerated*>(p)); break;
      case Cargo::Dangerous   : display(dynamic_cast<const CargoDangerous   *>(p)); break;
      case Cargo::Normal      : break;
      default: throw std::invalid_argument("invalid Cargo type");
    }
}

void App::display(const CargoAnimal *p){
}
void App::display(const CargoRefrigerated *p){
    std::cout << "│ [2] Temp range °C │ " << utils::ljust("["+utils::ftos("%.1f",(double)p->get_Tr().min)+", "+utils::ftos("%.1f",(double)p->get_Tr().max)+"]", 81) << "\t │\n";
}
void App::display(const CargoDangerous *p){
    std::cout << "│ [2] Danger level  │ " << utils::ljust(Cargo::dangerlevel_string(p->get_dangerlevel())   ,81) << "\t │\n";
}

void App::display(const CargoTrans             *p){
    std::cout << "│ [0] Weight (kg)   │ " << utils::ljust(utils::ftos("%.0f",(double)p->get_W())       ,81) << "\t │\n"
              << "│ [1] Description   │ " << utils::ljust(p->get_description()                              ,81) << "\t │\n"
              << "| [2] Price base €  │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_P_B())    ,81)<< "\t │\n"
              << "│ [3] Expenses €/km │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_E_D()),81)<<"\t │\n";
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
    std::cout << "| [4] Temp range    │ " << utils::ljust("["+utils::ftos("%.1f",(double)p->get_Tr().min)+", "+utils::ftos("%.1f",(double)p->get_Tr().max)+"]", 81) << "\t │\n"
              << "│ [5] Ref temp °C   │ " << utils::ljust(utils::ftos("%.1f",(double)p->get_T0()), 81) << "\t │\n"
              << "│ [6] Temp factor   │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_E_T())    , 81) << "\t │\n";
}
void App::display(const CargoTransDangerous    *p){
    std::cout << "│ [4] Danger level  │ " << utils::ljust(Cargo::dangerlevel_string(p->get_dangerlevel())          , 81) << "\t │\n";
}
