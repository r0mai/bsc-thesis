#ifndef DN_ASTACTION_HPP_
#define DN_ASTACTION_HPP_

#include <clang/Frontend/FrontendAction.h>

#include "AstConsumer.hpp"

namespace dn {

class TrivialAction : public clang::PluginASTAction {
public:
	std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
			clang::CompilerInstance&,
			llvm::StringRef) override;

	bool ParseArgs(const clang::CompilerInstance&,
			const std::vector<std::string>&) override;

	clang::PluginASTAction::ActionType getActionType() override;
};


} // namespace dn

#endif // DN_ASTACTION_HPP_
