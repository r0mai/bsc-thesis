#ifndef DN_ASTCONSUMER_HPP_
#define DN_ASTCONSUMER_HPP_

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>

#include <boost/optional.hpp>

#include <map>
#include <string>

namespace dn {

class AstConsumer : public clang::ASTConsumer {
public:
	AstConsumer(clang::CompilerInstance& ci,
			std::string inputFile,
			boost::optional<std::string> = std::string{});

private:
	void HandleTranslationUnit(clang::ASTContext&) override;

	clang::CompilerInstance& ci;
	std::string inputFile;
	std::string outputFilename;
	std::map<std::string, std::string> debugPrefixMap;
};

} // namespace dn

#endif // DN_ASTACTION_HPP_
