TEST_CASE("VAT", "[vat]"){
    REQUIRE_THROWS_AS(VAT("0123456789abcdef"), VAT::InvalidVAT);
    REQUIRE_NOTHROW(VAT("0123456789ABCDE"));
}
