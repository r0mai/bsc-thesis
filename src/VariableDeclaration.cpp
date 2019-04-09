#include "dn/VariableDeclaration.hpp"
#include <clang/Basic/SourceLocation.h>

#include <utility>

namespace {

std::string sourceLocationToString(
		const clang::SourceLocation& location,
		const clang::SourceManager& sourceManager) {
	std::string fullPath;
	auto presumedLocation = sourceManager.getPresumedLoc(location);
	auto* file =
			sourceManager.getFileEntryForID(sourceManager.getFileID(location));
	if (file) {
		fullPath = file->tryGetRealPathName().str();
	} else {
		fullPath = presumedLocation.getFilename();
	}
	return fullPath
			+ ':' + std::to_string(presumedLocation.getLine())
			+ ':' + std::to_string(presumedLocation.getColumn());
}
} // unnamed namespace

dn::VariableDeclaration::VariableDeclaration(const clang::VarDecl& varDecl) :
	name{varDecl.getNameAsString()},
	type{varDecl.getType().getAsString()},
	location{varDecl.getLocation()},
	occurences{} {
}

std::string dn::VariableDeclaration::getName() const {
	return name;
}

std::string dn::VariableDeclaration::getType() const {
	return type;
}

std::string dn::VariableDeclaration::getLocation(
		const clang::SourceManager& sourceManager) const {
	return sourceLocationToString(location, sourceManager);
}

bool dn::VariableDeclaration::operator==(const dn::VariableDeclaration& rhs)
		const {
	return std::tie(name, type, location) ==
			std::tie(rhs.name, rhs.type, rhs.location);
}

const std::vector<std::string>& dn::VariableDeclaration::getOccurences() const {
	return occurences;
}

void dn::VariableDeclaration::addOccurence(
		clang::SourceLocation location, const clang::SourceManager& sourceManager) {
	occurences.push_back(sourceLocationToString(location, sourceManager));
}
