#ifndef DN_ASTVISITOR_HPP_
#define DN_ASTVISITOR_HPP_

#include <clang/AST/DeclBase.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include <map>
#include <string>

namespace dn {

class AstVisitor : public clang::RecursiveASTVisitor<AstVisitor> {
public:
	AstVisitor(std::string outputFile,
			const clang::SourceManager& sourceManager);

	bool VisitDecl(clang::Decl* decl);

	void printVariableNames() const;

private:
	std::string outputFile;
	const clang::SourceManager& sourceManager;

	std::map<std::string, std::map<std::string, std::size_t>> variableNames;
};

} // namespace dn

#endif // DN_ASTVISITOR_HPP_
