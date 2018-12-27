#ifndef DN_ASTACTION_HPP_
#define DN_ASTACTION_HPP_

#include <clang/Frontend/FrontendAction.h>

#include <boost/optional.hpp>

#include "AstConsumer.hpp"

#include <string>

namespace dn {

class Action : public clang::PluginASTAction {
public:
	std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
			clang::CompilerInstance&,
			llvm::StringRef) override;

	bool ParseArgs(const clang::CompilerInstance&,
			const std::vector<std::string>&) override;

	clang::PluginASTAction::ActionType getActionType() override;

private:
	boost::optional<std::string> outputFilename;
};


} // namespace dn

#endif // DN_ASTACTION_HPP_
