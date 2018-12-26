#include <dn/AstConsumer.hpp>

#include <iostream>

void dn::TrivialAstConsumer::HandleTranslationUnit(clang::ASTContext&) {
	std::cerr << "Have AST" << std::endl;
}
