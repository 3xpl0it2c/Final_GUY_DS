unsigned long hash(unsigned long id, int arraySize) {
		// Starting point.
        unsigned long hash = 5381;
		unsigned long digit;

        while (id != 0) {
			digit = id % 10;
            hash = ((hash << 5) + hash) + digit; /* hash * 33 + c */
			id = id / 10;
		}
        return hash % arraySize;

}
