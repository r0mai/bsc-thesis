#include <dn/AstConsumer.hpp>
#include <dn/AstVisitor.hpp>

dn::AstConsumer::AstConsumer(clang::CompilerInstance& ci) :
	ci{ci} {
	}

void dn::AstConsumer::HandleTranslationUnit(clang::ASTContext& astContext) {
	AstVisitor visitor{ci.getFrontendOpts().OutputFile};
	visitor.TraverseDecl(astContext.getTranslationUnitDecl());
	visitor.printVariableNames();
}
