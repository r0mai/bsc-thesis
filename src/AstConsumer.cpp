#include <dn/AstConsumer.hpp>
#include <dn/AstVisitor.hpp>

#include <iostream>

dn::AstConsumer::AstConsumer(clang::CompilerInstance& ci,
		boost::optional<std::string> outputFilename) :
	ci{ci},
	outputFilename{
			outputFilename ?
					std::move(*outputFilename) :
					ci.getFrontendOpts().OutputFile + ".names.json"},
	debugPrefixMap{ci.getCodeGenOpts().DebugPrefixMap} {
	}

void dn::AstConsumer::HandleTranslationUnit(clang::ASTContext& astContext) {
	AstVisitor visitor{outputFilename, ci.getSourceManager(),
			debugPrefixMap};
	visitor.TraverseDecl(astContext.getTranslationUnitDecl());
	visitor.printVariableNames();
}
