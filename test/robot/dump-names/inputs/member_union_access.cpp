struct F {
	bool isInt;
	union {
		char c;
		int i;
	};
	void read() {
		if (isInt) {
			(void)i;
		} else {
			(void)c;
		}
	}
};
