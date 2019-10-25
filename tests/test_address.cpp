TEST_CASE("Address", "[address]") {
    {
        Address a("Rua das Oliveiras, 25", "4020-318", "BACIAS", "Trás-os-Montes", "Portugal");
        REQUIRE(a.format() == "Rua das Oliveiras, 25\n4020-318 BACIAS\nTrás-os-Montes, Portugal");
        std::stringstream ss; ss << a << std::endl;
        Address b;
        ss >> b;
        REQUIRE(b.format() == "Rua das Oliveiras, 25\n4020-318 BACIAS\nTrás-os-Montes, Portugal");
    }
}
