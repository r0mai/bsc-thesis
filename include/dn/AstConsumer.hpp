#ifndef DN_ASTCONSUMER_HPP_
#define DN_ASTCONSUMER_HPP_

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>

namespace dn {

class TrivialAstConsumer : public clang::ASTConsumer {
public:
	TrivialAstConsumer(clang::CompilerInstance& ci);

private:
	void HandleTranslationUnit(clang::ASTContext&) override;

	clang::CompilerInstance& ci;
};

} // namespace dn

#endif // DN_ASTACTION_HPP_
