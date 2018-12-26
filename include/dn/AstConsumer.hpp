#ifndef DN_ASTCONSUMER_HPP_
#define DN_ASTCONSUMER_HPP_

#include <clang/AST/ASTConsumer.h>

namespace dn {

class TrivialAstConsumer : public clang::ASTConsumer {
	void HandleTranslationUnit(clang::ASTContext&) override;
};

} // namespace dn

#endif // DN_ASTACTION_HPP_
