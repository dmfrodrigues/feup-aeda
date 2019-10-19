TEST_CASE("Time", "[Time]") {
    {
        std::stringstream ss;
        ss << Time("20191019_011132");
        std::string s; ss >> s;
        REQUIRE(s == "20191019_011132");
    }
}
