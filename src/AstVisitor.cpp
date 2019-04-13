#include <dn/AstVisitor.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>

namespace {

std::string indent(std::size_t count) {
	return std::string(count, ' ');
}

} // unnamed namespace

dn::AstVisitor::AstVisitor(std::string outputFile,
		const clang::SourceManager& sourceManager) :
		outputFile(std::move(outputFile)),
		sourceManager(sourceManager) {
}

bool dn::AstVisitor::VisitDecl(clang::Decl* decl) {
	auto* variableDeclaration = clang::dyn_cast<clang::VarDecl>(decl);
	if (variableDeclaration) {
		visitVariableDeclaration(*variableDeclaration);
		return true;
	}
	auto* fieldDeclaration = clang::dyn_cast<clang::FieldDecl>(decl);
	if (fieldDeclaration) {
		visitFieldDeclaration(*fieldDeclaration);
		return true;
	}
	return true;
}

void dn::AstVisitor::visitVariableDeclaration(
		const clang::VarDecl& variableDeclaration) {
	variableDeclarations.emplace_back(variableDeclaration);
}

void dn::AstVisitor::visitFieldDeclaration(
		const clang::FieldDecl& fieldDeclaration) {
	variableDeclarations.emplace_back(fieldDeclaration);
}

void dn::AstVisitor::visitDeclarationReferenceExpression(
		const clang::DeclRefExpr& declarationReferenceExpression) {
	auto* decl = declarationReferenceExpression.getDecl();
	if (auto* varDecl = clang::dyn_cast<clang::VarDecl>(decl)) {
		VariableDeclaration variableDeclaration{*varDecl};
		auto it = std::find(variableDeclarations.begin(),
				variableDeclarations.end(), variableDeclaration);
		if (it == variableDeclarations.end()) {
			std::cerr << "What" << std::endl;
		} else {
			addOccurence(*it, declarationReferenceExpression.getLocation());
		}
	}
}

void dn::AstVisitor::visitMemberExpression(const clang::MemberExpr&
		memberExpression) {
	auto* decl = memberExpression.getFoundDecl().getDecl();
	if (auto* fieldDecl = clang::dyn_cast<clang::FieldDecl>(decl)) {
		VariableDeclaration variableDeclaration{*fieldDecl};
		auto it = std::find(variableDeclarations.begin(),
				variableDeclarations.end(), variableDeclaration);
		if (it == variableDeclarations.end()) {
			std::cerr << "What" << std::endl;
		} else {
			addOccurence(*it, memberExpression.getExprLoc());
		}
	} else {
		std::cerr << "What other kind of memberExpr is there?" << std::endl;
	}
}

void dn::AstVisitor::addOccurence(dn::VariableDeclaration& variableDeclaration,
		const clang::SourceLocation& location) {
	variableDeclaration.addOccurence(location, sourceManager);
}

bool dn::AstVisitor::VisitStmt(clang::Stmt* stmt) {
	if (clang::DeclRefExpr* expr = clang::dyn_cast<clang::DeclRefExpr>(stmt)) {
		visitDeclarationReferenceExpression(*expr);
	}
	if (clang::MemberExpr* expr = clang::dyn_cast<clang::MemberExpr>(stmt)) {
		visitMemberExpression(*expr);
	}
	return true;
}

void dn::AstVisitor::printVariableNames() const {
	std::ofstream output{outputFile};
	output << "{\n";
	output << indent(4) << '"' << "Variables" << '"' << ": [\n";
	bool first = true;
	for (const auto& variableDeclaration: variableDeclarations) {
		if (!first) {
			output << ",\n";
		}
		first = false;
		output << indent(8) << "{\n";
		output << indent(12)
				<< "\"type\": " << '"' << variableDeclaration.getType() << '"'
				<< ",\n";
		output << indent(12)
				<< "\"name\": " << '"' << variableDeclaration.getName() << '"'
				<< ",\n";
		output << indent(12)
				<< "\"location\": " << '"'
				<< variableDeclaration.getLocation(sourceManager) << '"'
				<< ",\n";
		output << indent(12)
				<< "\"occurences\": " << "[\n";
		bool firstOccurence = true;
		for (const auto& occurence: variableDeclaration.getOccurences()) {
			if (!firstOccurence) {
				output << ",\n";
			}
			output << indent(16) << '"' << occurence << '"';
			firstOccurence = false;
		}
		output << indent(12) << "]\n";
		output << indent(8) << "}";
	}
	output << "\n" << indent(4) << "]\n";
	output << "}\n";
}
