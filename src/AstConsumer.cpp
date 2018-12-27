#include <dn/AstConsumer.hpp>
#include <dn/AstVisitor.hpp>

dn::AstConsumer::AstConsumer(clang::CompilerInstance& ci,
		boost::optional<std::string> outputFilename) :
	ci{ci},
	outputFilename{
			outputFilename ?
					std::move(*outputFilename) :
					ci.getFrontendOpts().OutputFile + ".names.json"} {
	}

void dn::AstConsumer::HandleTranslationUnit(clang::ASTContext& astContext) {
	AstVisitor visitor{outputFilename};
	visitor.TraverseDecl(astContext.getTranslationUnitDecl());
	visitor.printVariableNames();
}
