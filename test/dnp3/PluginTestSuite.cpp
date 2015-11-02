
#include <catch.hpp>

#include <dnp3cpp/DNP3Factory.h>

#include "mocks/MockParserCallbacks.h"
#include "mocks/HexData.h"

using namespace proxy;
using namespace proxy::dnp3;

#define SUITE(name) "Plugin - " name

TEST_CASE(SUITE("Construct and delete"))
{
    DNP3Factory factory;
    MockParserCallbacks callbacks;
    auto parser = factory.Create(callbacks);

    auto dest = parser->GetWriteSlice();

    REQUIRE(dest.Size() > 0); // this is a magic number inside the library
}

TEST_CASE(SUITE("Bad link data is rejected by parser"))
{
    DNP3Factory factory;
    MockParserCallbacks callbacks;
    auto parser = factory.Create(callbacks);

    HexData input("FF FF FF FF FF FF FF FF FF FF");
    REQUIRE(input.GetSlice().Size() == 10);

    auto dest = parser->GetWriteSlice();
    REQUIRE(dest.Size() >= 10);
    REQUIRE(input.GetSlice().CopyTo(dest).Size() > 0);

    REQUIRE_FALSE(parser->Parse(10));
}


