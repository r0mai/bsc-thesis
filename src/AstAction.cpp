#include <dn/AstAction.hpp>

std::unique_ptr<clang::ASTConsumer> dn::Action::CreateASTConsumer(
		clang::CompilerInstance& ci,
		llvm::StringRef) {
	return std::make_unique<AstConsumer>(ci);
}

bool dn::Action::ParseArgs(const clang::CompilerInstance&,
		const std::vector<std::string>&) {
	return true;
}

clang::PluginASTAction::ActionType dn::Action::getActionType() {
	return AddAfterMainAction;
}
