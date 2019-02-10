#include "dn/VariableDeclaration.hpp"

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
	return location.printToString(sourceManager);
}
