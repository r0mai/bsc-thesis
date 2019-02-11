#ifndef DN_VARIABLE_DECLARATION_HPP_
#define DN_VARIABLE_DECLARATION_HPP_

#include <clang/AST/Decl.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Basic/SourceLocation.h>

namespace dn {

class VariableDeclaration {
public:
	VariableDeclaration(const clang::VarDecl&);
	std::string getName() const;
	std::string getType() const;
	std::string getLocation(const clang::SourceManager& sourceManager) const;

private:
	std::string name;
	std::string type;
	clang::SourceLocation location;
};

} // namespace dn

#endif // DN_VARIABLE_DECLARATION_HPP_
