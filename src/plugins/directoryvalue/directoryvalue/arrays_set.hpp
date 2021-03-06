// clang-format off

CppKeySet { 10,
	    keyNew (PREFIX "key", KEY_END),
	    keyNew (PREFIX "key/" DIRECTORY_POSTFIX, KEY_END),
	    keyNew (PREFIX "key/map", KEY_END),
	    keyNew (PREFIX "key/array", KEY_END),
	    keyNew (PREFIX "key/array/#0", KEY_VALUE, ARRAY_VALUE_PREFIX " ", KEY_END),
	    keyNew (PREFIX "key/array/#1", KEY_END),
	    keyNew (PREFIX "key/array/#2", KEY_END),
	    keyNew (PREFIX "key/array/#3/nested", KEY_END),
	    keyNew (PREFIX "key/array/#3/nested/#0", KEY_VALUE, ARRAY_VALUE_PREFIX " ", KEY_END),
	    keyNew (PREFIX "key/array/#3/nested/#1", KEY_END),
	    keyNew (PREFIX "key/array/#3/nested/#2", KEY_END),
	    keyNew (PREFIX "key/array/#4/not/an/array", KEY_END),
	    keyNew (PREFIX "key/array/#4/not/an/array/" DIRECTORY_POSTFIX, KEY_END),
	    keyNew (PREFIX "key/array/#4/not/an/array/#0", KEY_END),
	    keyNew (PREFIX "key/array/#4/not/an/array/key", KEY_END),
	    keyNew (PREFIX "key/array/#5/array/without/parent/#0", KEY_END),
	    keyNew (PREFIX "key/array/#5/array/without/parent/#1", KEY_END),
	    keyNew (PREFIX "key/empty/array", KEY_END),
	    keyNew (PREFIX "key/empty/array/#0", KEY_VALUE, ARRAY_VALUE_PREFIX " ", KEY_END),
	    KS_END }
