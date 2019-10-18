TEST_CASE("Person", "[person]") {
    REQUIRE_NOTHROW(
        Person("Rosvaldo de Albuquerque e Sousa",
               Address("Rua das Oliveiras, 25", "4020-318", "BACIAS", "Trás-os-Montes", "Portugal"),
               VAT("0123456789abcde"),
               PhoneNumber("(+351) 91 234 56 78")
              )
    );
}
