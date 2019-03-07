#include "dn/VariableDeclaration.hpp"
#include <clang/Basic/SourceLocation.h>

dn::VariableDeclaration::VariableDeclaration(const clang::VarDecl& varDecl) :
	name{varDecl.getNameAsString()},
	type{varDecl.getType().getAsString()},
	location{varDecl.getLocation()} {
}

std::string dn::VariableDeclaration::getName() const {
	return name;
}

std::string dn::VariableDeclaration::getType() const {
	return type;
}

std::string dn::VariableDeclaration::getLocation(
		const clang::SourceManager& sourceManager) const {
	auto* file =
			sourceManager.getFileEntryForID(sourceManager.getFileID(location));
	auto presumedLocation = sourceManager.getPresumedLoc(location);
	return file->tryGetRealPathName().str()
			+ ':' + std::to_string(presumedLocation.getLine())
			+ ':' + std::to_string(presumedLocation.getColumn());
}
