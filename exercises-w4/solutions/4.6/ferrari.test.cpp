#include "ferrari.h"

#include <catch2/catch.hpp>

#include <type_traits>

TEST_CASE("ferrari is const-correct") {
    CHECK(std::is_invocable_v<decltype(&ferrari::get_details), const ferrari>);
    CHECK(std::is_invocable_v<decltype(&ferrari::vroom), const ferrari>);
    CHECK_FALSE(std::is_invocable_v<decltype(&ferrari::drive), const ferrari>);
}

TEST_CASE("ferrari is constructible with arguments") {
    auto fr = ferrari{"wagyu", 0xbeef};

    const auto &[owner, modelno] = fr.get_details();
    const auto vr = fr.vroom();

    CHECK(owner == "wagyu");
    CHECK(modelno == 0xbeef);
    CHECK(vr == "");
}

TEST_CASE("ferrari is default constructible") {
    auto fr = ferrari{};

    const auto &[owner, modelno] = fr.get_details();
    const auto vr = fr.vroom();

    CHECK(owner == "unknown");
    CHECK(modelno == 6771);
    CHECK(vr == "");
}

TEST_CASE("drive a ferrari with a set speed") {
    auto fr = ferrari{"taxi", 0xcab};
    fr.drive(6771);

    const auto vr = fr.vroom();
    CHECK(vr == "VROOOOOOOOM!!!");
    
}

TEST_CASE("drive ferrari with a default speed") {
    auto fr = ferrari{"taxi", 0xcab};
    fr.drive();

    const auto vr = fr.vroom();
    CHECK(vr == "VROOOOOOOOM!!!");
}

TEST_CASE("can get details of a ferrari") {
    auto fr = ferrari{"taxi", 0xcab};

    const auto &[owner, modelno] = fr.get_details();

    CHECK(owner == "taxi");
    CHECK(modelno == 0xcab);
}

TEST_CASE("does ferrari go vroom like the spec said?") {
    auto fr = ferrari{};

    const auto vr1 = fr.vroom();

    fr.drive(32);
    const auto vr2 = fr.vroom();

    fr.drive(88);
    const auto vr3 = fr.vroom();

    CHECK(vr1 == "");
    CHECK(vr2 == "vroom!!");
    CHECK(vr3 == "VROOOOOOOOM!!!");
}
