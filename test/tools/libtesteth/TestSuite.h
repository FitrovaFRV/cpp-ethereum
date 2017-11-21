/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
 */
/** @file
 * A base class for test suites
 */

#pragma once
#include <boost/filesystem/path.hpp>
#include <test/tools/libtesteth/JsonSpiritHeaders.h>

namespace dev
{
namespace test
{

class TestSuite
{
protected:
	// A folder of the test suite. like "VMTests". should be implemented for each test suite.
	virtual boost::filesystem::path suiteFolder() const = 0;

	// A folder of the test suite in src folder. like "VMTestsFiller". should be implemented for each test suite.
	virtual boost::filesystem::path suiteFillerFolder() const = 0;

public:
	virtual ~TestSuite() {}

	// Main test executive function. should be declared for each test suite. it fills and runs the test .json file
	virtual json_spirit::mValue doTests(json_spirit::mValue const&, bool) const = 0;

	// Execute all tests from suiteFolder()/_testFolder/*
	// This functions checks that tests in the repo are updated with /src/suiteFillerFolder()/*Filler tests
	// Then it looks for a Filler.json file in /src/suiteFillerFolder()/_testFolder and generates the actual tests
	// If src test file is named Copier it will just copy it from /src folder because such test is crafted and
	// it's RLP could not be generated by the client
	// If the src test does not end up with either Filler.json or Copier.json an exception occurs.
	void runAllTestsInFolder(std::string const& _testFolder) const;

	// Execute Filler.json or Copier.json test file in a given folder
	void executeTest(std::string const& _testFolder, boost::filesystem::path const& _jsonFileName) const;

	// Execute Test.json file
	void executeFile(boost::filesystem::path const& _file) const;

	// Return full path to folder for tests from _testFolder
	boost::filesystem::path getFullPathFiller(std::string const& _testFolder) const;

	// Structure  <suiteFolder>/<testFolder>/<test>.json
	boost::filesystem::path getFullPath(std::string const& _testFolder) const;

	void executeTests(const std::string& _name, boost::filesystem::path const& _testPathAppendix, boost::filesystem::path const& _fillerPathAppendix, std::function<json_spirit::mValue(json_spirit::mValue const&, bool)> doTests) const;
};

}
}
