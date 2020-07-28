#ifndef DN_ASTVISITOR_HPP_
#define DN_ASTVISITOR_HPP_

#include "VariableDeclaration.hpp"

#include <clang/AST/DeclBase.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/SourceLocation.h>

#include <map>
#include <string>
#include <vector>
#include <map>

namespace dn {

class AstVisitor : public clang::RecursiveASTVisitor<AstVisitor> {
public:
	AstVisitor(std::string outputFile,
			const clang::SourceManager& sourceManager,
			const std::map<std::string, std::string>& debugPrefixMap);

	bool VisitDecl(clang::Decl* decl);
	bool VisitStmt(clang::Stmt* stmt);

	void printVariableNames(const std::string& inputFile) const;

private:

	void visitVariableDeclaration(const clang::VarDecl& variableDeclaration);
	void visitFieldDeclaration(const clang::FieldDecl& fieldDeclaration);

	void visitDeclarationReferenceExpression(const clang::DeclRefExpr&
			declarationReferenceExpression);
	void visitMemberExpression(const clang::MemberExpr& memberExpression);

	void addOccurence(VariableDeclaration& variableDeclaration,
			const clang::SourceLocation& location);

	std::string outputFile;
	const clang::SourceManager& sourceManager;
	const std::map<std::string, std::string>& debugPrefixMap;

	std::map<VariableDeclKey, VariableDeclaration> variableDeclarations;
};

} // namespace dn

#endif // DN_ASTVISITOR_HPP_
