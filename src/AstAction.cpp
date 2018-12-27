#include <dn/AstAction.hpp>

std::unique_ptr<clang::ASTConsumer> dn::TrivialAction::CreateASTConsumer(
		clang::CompilerInstance& ci,
		llvm::StringRef) {
	return std::make_unique<TrivialAstConsumer>(ci);
}

bool dn::TrivialAction::ParseArgs(const clang::CompilerInstance&,
		const std::vector<std::string>&) {
	return true;
}

clang::PluginASTAction::ActionType dn::TrivialAction::getActionType() {
	return AddAfterMainAction;
}
