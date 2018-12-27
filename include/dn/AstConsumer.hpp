#ifndef DN_ASTCONSUMER_HPP_
#define DN_ASTCONSUMER_HPP_

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>

#include <boost/optional.hpp>

#include <string>

namespace dn {

class AstConsumer : public clang::ASTConsumer {
public:
	AstConsumer(clang::CompilerInstance& ci,
			boost::optional<std::string> = std::string{});

private:
	void HandleTranslationUnit(clang::ASTContext&) override;

	clang::CompilerInstance& ci;
	std::string outputFilename;
};

} // namespace dn

#endif // DN_ASTACTION_HPP_
