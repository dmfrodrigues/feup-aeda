#include "utils.h"

TEST_CASE("Utilities", "[utils]") {
    REQUIRE(utils::itos(123L) == "123");
    REQUIRE(utils::itos(539678576738205678L) == "539678576738205678");
}
