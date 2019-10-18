TEST_CASE("Utilities", "[utils]") {
    REQUIRE(itos(123L) == "123");
    REQUIRE(itos(539678576738205678L) == "539678576738205678");
}
