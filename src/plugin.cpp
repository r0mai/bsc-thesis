#include <clang/Frontend/FrontendPluginRegistry.h>

#include <iostream>

namespace dn {

class TrivialAstConsumer : public clang::ASTConsumer {
	void HandleTranslationUnit(clang::ASTContext&) override {
		std::cerr << "Have AST" << std::endl;
	}
};

class TrivialAction : public clang::PluginASTAction {
public:
	std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
			clang::CompilerInstance&,
			llvm::StringRef) override {
		return std::make_unique<TrivialAstConsumer>();
	}

	bool ParseArgs(const clang::CompilerInstance&,
			const std::vector<std::string>&) override {
		return true;
	}

	clang::PluginASTAction::ActionType getActionType() override {
		return AddAfterMainAction;
	}
};

} // namespace dn

clang::FrontendPluginRegistry::Add<dn::TrivialAction> _{
	"dump-names", "Dump names of types and symbols"
};
