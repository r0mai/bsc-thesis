#ifndef DN_ASTVISITOR_HPP_
#define DN_ASTVISITOR_HPP_

#include "VariableDeclaration.hpp"

#include <clang/AST/DeclBase.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include <map>
#include <string>
#include <vector>

namespace dn {

class AstVisitor : public clang::RecursiveASTVisitor<AstVisitor> {
public:
	AstVisitor(std::string outputFile,
			const clang::SourceManager& sourceManager);

	bool VisitDecl(clang::Decl* decl);
	bool VisitStmt(clang::Stmt* stmt);

	void printVariableNames() const;

private:
	std::string outputFile;
	const clang::SourceManager& sourceManager;

	std::vector<VariableDeclaration> variableDeclarations;
};

} // namespace dn

#endif // DN_ASTVISITOR_HPP_
