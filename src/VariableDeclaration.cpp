#include "dn/VariableDeclaration.hpp"
#include <clang/Basic/SourceLocation.h>
#include <clang/Basic/FileManager.h>

#include <utility>
#include <iostream>

#include <limits.h>
#include <stdlib.h>

namespace {

std::string realPath(std::string path) {
	char* realPathResult = ::realpath(path.c_str(), nullptr);
	if (!realPathResult) {
		std::cerr << ::strerror(errno) << std::endl;
		return path;
	}
	std::string result;
	result = realPathResult;
	free(realPathResult);
	return result;
}

std::string sourceLocationToString(
		const clang::SourceLocation& location,
		const clang::SourceManager& sourceManager) {
	std::string fullPath;
	auto presumedLocation = sourceManager.getPresumedLoc(location);
	if (!presumedLocation.isValid()) {
		std::cerr << "Invalid source location found" << std::endl;
		return "null_location:0:0";
	}
	auto* file =
			sourceManager.getFileEntryForID(sourceManager.getFileID(location));
	if (file) {
		fullPath = file->tryGetRealPathName().str();
	} else {
		fullPath = realPath(presumedLocation.getFilename());
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

dn::VariableDeclaration::VariableDeclaration(const clang::FieldDecl& fieldDecl) :
	name{fieldDecl.getNameAsString()},
	type{fieldDecl.getType().getAsString()},
	location{fieldDecl.getLocation()},
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
