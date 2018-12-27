#include <dn/AstConsumer.hpp>

#include <iostream>

dn::TrivialAstConsumer::TrivialAstConsumer(clang::CompilerInstance& ci) :
	ci{ci} {
	}

void dn::TrivialAstConsumer::HandleTranslationUnit(clang::ASTContext&) {
	std::cerr << "Have AST" << std::endl;
	std::cerr << "Output file: " <<
			ci.getFrontendOpts().OutputFile << std::endl;
}
