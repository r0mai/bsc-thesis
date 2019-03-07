#ifndef DN_VARIABLE_DECLARATION_HPP_
#define DN_VARIABLE_DECLARATION_HPP_

#include <clang/AST/Decl.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Basic/SourceLocation.h>

#include <vector>

namespace dn {

class VariableDeclaration {
public:
	VariableDeclaration(const clang::VarDecl&);
	std::string getName() const;
	std::string getType() const;
	std::string getLocation(const clang::SourceManager& sourceManager) const;
	bool operator==(const VariableDeclaration& rhs) const;
	const std::vector<std::string>& getOccurences() const;

	void addOccurence(clang::SourceLocation location,
			const clang::SourceManager& sourceManager);

private:
	std::string name;
	std::string type;
	clang::SourceLocation location;
	std::vector<std::string> occurences;
};

} // namespace dn

#endif // DN_VARIABLE_DECLARATION_HPP_
