#include "glhelperfunctions/glhelperfunctions.h"
#include <catch2/catch.hpp>
#include <exception>
#include <filesystem>

#define CONFIG_CATCH_MAIN
#define GET_CODE(path) GLHelper::GetSourceCode(path)


TEST_CASE("Succeeds and parses correctly if file is found", "[GLHelperFunctions]")
{
    std::string const sourceCode = "This is a test\nWho knows what happens next";
    auto shaderPath = std::filesystem::current_path();
    REQUIRE(sourceCode.compare(GET_CODE(shaderPath /= path(TEST_FILE))) == 0);
}

TEST_CASE("Fails if file is not found", "[GLHelperFunctions]")
{
	REQUIRE_THROWS_AS(GLHelper::GetSourceCode("WrongPath"), std::filesystem::filesystem_error);
}
