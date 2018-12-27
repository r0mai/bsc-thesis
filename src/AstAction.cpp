#include <dn/AstAction.hpp>

#include <iostream>
#include <algorithm>

std::unique_ptr<clang::ASTConsumer> dn::Action::CreateASTConsumer(
		clang::CompilerInstance& ci,
		llvm::StringRef) {
	return std::make_unique<AstConsumer>(ci, outputFilename);
}

bool dn::Action::ParseArgs(const clang::CompilerInstance& ci,
		const std::vector<std::string>& args) {
	auto it = std::find(args.begin(), args.end(), "output-file");
	if (it == args.end()) {
		return true;
	}
	if (it+1 == args.end()) {
		std::cerr << "output-file requires an argument" << std::endl;
		return false;
	}
	outputFilename = *(it+1);
	return true;
}

clang::PluginASTAction::ActionType dn::Action::getActionType() {
	return AddAfterMainAction;
}
