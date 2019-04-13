int main() {
	bool isInt = true;;
	union {
		int i;
		char c;
	};
	if (isInt) {
		i = 0;
	} else {
		c = '\0';
	}
}
