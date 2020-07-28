#include <dn/AstVisitor.hpp>

#include <boost/algorithm/string/predicate.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <sstream>

namespace {

std::string indent(std::size_t count) {
	return std::string(count, ' ');
}

std::string normalizeLocation(const std::string& location,
		const std::map<std::string, std::string>& debugPrefixMap) {
	for (const auto& debugPrefix: debugPrefixMap) {
		const auto& prefix = debugPrefix.first;
		const auto& replacement = debugPrefix.second;
		if (boost::starts_with(location, prefix)) {
			std::string result = replacement;
			result += location.substr(prefix.length());
			return result;
		}
	}
	return location;
}

std::string escapeJsonString(const std::string& str) {
	std::stringstream ss;

	for (int i = 0; i < str.size(); ++i) {
		char ch = str[i];
		switch (ch) {
			case '\"':
			case '\\':
				ss << '\\';
			default:
				ss << ch;
				break;

		}
	}

	return ss.str();
}

} // unnamed namespace

dn::AstVisitor::AstVisitor(std::string outputFile,
		const clang::SourceManager& sourceManager,
		const std::map<std::string, std::string>& debugPrefixMap) :
		outputFile(std::move(outputFile)),
		sourceManager(sourceManager),
		debugPrefixMap{debugPrefixMap} {
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
		const clang::VarDecl& varDecl) {
	// In the case we're declaring an argument to a template function,
	// if the function has a trailing return type, then the arguments will be
	// referred to before declared. To make sure we catch everything, we'll
	// visit the declaration then and there, so we cannot assume the declaration
	// is new here.
	VariableDeclaration variableDeclaration{varDecl};
	auto it = std::find(
			variableDeclarations.begin(), variableDeclarations.end(),
			variableDeclaration);
	if (it == variableDeclarations.end()) {
		variableDeclarations.push_back(std::move(variableDeclaration));
	}
}

void dn::AstVisitor::visitFieldDeclaration(
		const clang::FieldDecl& fieldDeclaration) {
	// We'll register the field at the declaration or the first reference.
	// Because of this, we cannot assume that the fieldDeclaration is new.
	VariableDeclaration variableDeclaration{fieldDeclaration};
	auto it = std::find(
			variableDeclarations.begin(), variableDeclarations.end(),
			variableDeclaration);
	if (it == variableDeclarations.end()) {
		variableDeclarations.push_back(std::move(variableDeclaration));
	}
}

void dn::AstVisitor::visitDeclarationReferenceExpression(
		const clang::DeclRefExpr& declarationReferenceExpression) {
	auto* decl = declarationReferenceExpression.getDecl();
	if (auto* varDecl = clang::dyn_cast<clang::VarDecl>(decl)) {
		VariableDeclaration variableDeclaration{*varDecl};
		visitVariableDeclaration(*varDecl);
		auto it = std::find(variableDeclarations.begin(),
				variableDeclarations.end(), variableDeclaration);
		assert(it != variableDeclarations.end());
		addOccurence(*it, declarationReferenceExpression.getLocation());
	}
}

void dn::AstVisitor::visitMemberExpression(const clang::MemberExpr&
		memberExpression) {
	auto* decl = memberExpression.getFoundDecl().getDecl();
	if (auto* fieldDecl = clang::dyn_cast<clang::FieldDecl>(decl)) {
		VariableDeclaration variableDeclaration{*fieldDecl};
		// Members don't have to appear sooner than their first use, so
		// it's possible we encounter a reference before we encounter the
		// declaration.
		visitFieldDeclaration(*fieldDecl);
		auto it = std::find(variableDeclarations.begin(),
				variableDeclarations.end(), variableDeclaration);
		assert(it != variableDeclarations.end());
		addOccurence(*it, memberExpression.getExprLoc());
	} else if (clang::isa<clang::CXXMethodDecl>(decl)) {
		// Ignore methods
	} else if (clang::isa<clang::FunctionTemplateDecl>(decl)) {
		// Ignore template methods
	} else if (clang::isa<clang::IndirectFieldDecl>(decl)) {
		// Ignore indirect field access, the direct field will be visited
		// anyway.
	} else {
		std::cerr << "What other kind of memberExpr is there?" << std::endl;
		std::cerr << memberExpression.getExprLoc().printToString(sourceManager) << std::endl;
		std::cerr << decl->getLocation().printToString(sourceManager) << std::endl;
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

void dn::AstVisitor::printVariableNames(const std::string& inputFile) const {
	std::ofstream output{outputFile};
	output << "{\n";
	output << indent(4) << '"' << "Variables" << '"' << ": [";
	bool first = true;
	for (const auto& variableDeclaration: variableDeclarations) {
		if (variableDeclaration.getName().empty()) {
			continue; // Empty names are of no use to us.
		}
		if (!first) {
			output << ",";
		}
		first = false;
		output << "\n" << indent(8) << "{\n";
		output << indent(12)
				<< "\"type\": " << '"' << escapeJsonString(variableDeclaration.getType()) << '"'
				<< ",\n";
		output << indent(12)
				<< "\"name\": " << '"' << escapeJsonString(variableDeclaration.getName()) << '"'
				<< ",\n";
		output << indent(12)
				<< "\"location\": " << '"'
				<< escapeJsonString(normalizeLocation(
						variableDeclaration.getLocation(sourceManager),
						debugPrefixMap)) << '"'
				<< ",\n";
		output << indent(12)
				<< "\"occurences\": " << "[";
		bool firstOccurence = true;
		for (const auto& occurence: variableDeclaration.getOccurences()) {
			if (!firstOccurence) {
				output << ",";
			}
			output << "\n" << indent(16) << '"'
					<< escapeJsonString(normalizeLocation(occurence, debugPrefixMap)) << '"';
			firstOccurence = false;
		}
		output << "\n" << indent(12) << "]\n";
		output << indent(8) << "}";
	}
	output << "\n" << indent(4) << "],";
	output << "\n" << indent(4) << "\"Filename\": " << "\""
			<< escapeJsonString(normalizeLocation(inputFile, debugPrefixMap)) << "\"";
	output << "\n}\n";
}
