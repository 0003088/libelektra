/**
 * @file
 *
 * @brief Tests for data type checker
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 *
 */


#include "ctype.h"

#include <kdbmodule.h>
#include <kdbplugin.h>
#include <tests_plugin.h>

static bool checkType (const Key * key)
{
	return elektraCTypeCheckType (key);
}

void test_validate (void)
{
	Key * parentKey = keyNew ("system/elektra/modules/ctype", KEY_END);
	KeySet * conf = ksNew (0, KS_END);

	PLUGIN_OPEN ("ctype");

	KeySet * ks = ksNew (0, KS_END);
	succeed_if (plugin->kdbGet (plugin, ks, parentKey) >= 1, "call to kdbGet was not successful");
	Key * key;
	key = ksLookupByName (ks, "system/elektra/modules/ctype/exports/validateKey", 0);
	exit_if_fail (key, "key not found");

	union
	{
		int (*f) (Key *, Key *);
		void * v;
	} conversation;

	exit_if_fail (keyGetBinary (key, &conversation.v, sizeof (conversation)) == sizeof (conversation),
		      "failed to load validateKey function");

	Key * k = keyNew ("user/anything", KEY_VALUE, "0", KEY_META, "check/type", "short", KEY_END);
	succeed_if (conversation.f (k, parentKey), "should validate as short");
	succeed_if (keyGetMeta (parentKey, "error/number") == NULL, "shouldn't find error number");

	keySetString (k, "a");
	succeed_if (!conversation.f (k, parentKey), "shouldn't validate as short");
	succeed_if (keyGetMeta (parentKey, "error/number") != NULL, "should find error number");

	keyDel (k);

	ksDel (ks);
	keyDel (parentKey);

	PLUGIN_CLOSE ();
}

void test_short (void)
{
	Key * k = keyNew ("user/anything", KEY_VALUE, "0", KEY_META, "check/type", "short", KEY_END);
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "-32768");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "-32769");
	succeed_if (!checkType (k), "should fail (number too low)");
	keySetString (k, "32768");
	succeed_if (!checkType (k), "should fail (number too high)");
	keySetString (k, "32767");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "x");
	succeed_if (!checkType (k), "should fail");
	keySetString (k, "");
	succeed_if (!checkType (k), "should fail");
	keySetString (k, "32767x");
	succeed_if (!checkType (k), "should fail because of garbage afterwards");
	keySetString (k, "32767 x");
	succeed_if (!checkType (k), "should fail because of garbage afterwards");

	keyDel (k);
}

void test_unsignedShort (void)
{
	Key * k = keyNew ("user/anything", KEY_VALUE, "0", KEY_META, "check/type", "unsigned_short", KEY_END);
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "0");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "-1");
	succeed_if (!checkType (k), "should fail (number too low)");
	keySetString (k, "65536");
	succeed_if (!checkType (k), "should fail (number too high)");
	keySetString (k, "65535");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "x");
	succeed_if (!checkType (k), "should fail");
	keySetString (k, "");
	succeed_if (!checkType (k), "should fail");
	keySetString (k, "32767x");
	succeed_if (!checkType (k), "should fail because of garbage afterwards");
	keySetString (k, "32767 x");
	succeed_if (!checkType (k), "should fail because of garbage afterwards");

	keyDel (k);
}

void test_float (void)
{
	Key * k = keyNew ("user/anything", KEY_VALUE, "0", KEY_META, "check/type", "float", KEY_END);
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "0");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "1.5");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "1,5");
	succeed_if (!checkType (k), "should fail");
	keySetString (k, "1233322.5");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "123233223322333322.5");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "123233223322333322.0001");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "x");
	succeed_if (!checkType (k), "should fail");
	keySetString (k, "");
	succeed_if (!checkType (k), "should fail");
	keySetString (k, ".");
	succeed_if (!checkType (k), "should fail");
	keySetString (k, "1.");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, ".5");
	succeed_if (checkType (k), "should check successfully");

	keyDel (k);
}

void test_bool (void)
{
	Key * k = keyNew ("user/anything", KEY_VALUE, "0", KEY_META, "check/type", "boolean", KEY_END);
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "1");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, ".");
	succeed_if (!checkType (k), "should fail");
	keySetString (k, "true");
	succeed_if (!checkType (k), "should fail");
	keySetString (k, "false");
	succeed_if (!checkType (k), "should fail");

	keyDel (k);
}

void test_none (void)
{
	Key * k = keyNew ("user/anything", KEY_VALUE, "anything", KEY_END);
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "1");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "any other");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "do not care");
	succeed_if (checkType (k), "should check successfully");
	keySetString (k, "");
	succeed_if (checkType (k), "should check successfully");

	keyDel (k);
}

void test_char (void)
{
	Key * k = keyNew ("user/anything", KEY_VALUE, "a", KEY_META, "check/type", "char", KEY_END);
	succeed_if (checkType (k), "a should check successfully as char");
	keySetString (k, "b");
	succeed_if (checkType (k), "b should check successfully as char");
	keySetString (k, " ");
	succeed_if (checkType (k), "space should check successfully as char");
	keySetString (k, "");
	succeed_if (!checkType (k), "empty string should not check successfully as char");
	keySetString (k, "ab");
	succeed_if (!checkType (k), "two chars should not check successfully as char");

	char x[2] = { 0, 0 };
	char msg[] = "\\xXX should check successfully as char";
	const char hex[] = "0123456789abcdef";
	for (int i = 1; i < 255; ++i)
	{
		x[0] = (char) i;
		keySetString (k, x);
		msg[2] = hex[i / 16];
		msg[3] = hex[i % 16];
		succeed_if (checkType (k), msg);
	}


	keyDel (k);
}

void test_wchar (void)
{
	Key * k = keyNew ("user/anything", KEY_VALUE, "a", KEY_META, "check/type", "wchar", KEY_END);
	keySetString (k, "");
	succeed_if (!checkType (k), "empty string should not check successfully as wchar");

	char * s = elektraCalloc (3 * MB_CUR_MAX + 1);
	wcstombs (s, L"ab", 3 * MB_CUR_MAX);
	keySetString (k, s);
	succeed_if (!checkType (k), "two wchars should not check successfully as wchar");

	size_t max = WCHAR_MAX;
	if (max > 0xFFFF)
	{
		max = 0xFFFF;
	}

	size_t c = 0;
	for (size_t i = 1; i < max; ++i)
	{
		size_t ret = wcstombs (s, (wchar_t[]){ (wchar_t) i, 0 }, 3 * MB_CUR_MAX);
		if (ret > 0)
		{
			c++;
			keySetString (k, s);
			nbTest++;
			if (!checkType (k))
			{
				yield_error ("the following should check successfully as wchar:");
				printf ("0x%lx\n", i);
			}
		}
		int x ELEKTRA_UNUSED = wctomb (NULL, 0);
	}

	elektraFree (s);

	keyDel (k);
}


void test_octet (void)
{
	Key * k = keyNew ("user/anything", KEY_VALUE, "a", KEY_META, "check/type", "octet", KEY_END);
	succeed_if (checkType (k), "a should check successfully as octet");
	keySetString (k, "b");
	succeed_if (checkType (k), "b should check successfully as octet");
	keySetString (k, " ");
	succeed_if (checkType (k), "space should check successfully as octet");
	keySetString (k, "");
	succeed_if (!checkType (k), "empty string should not check successfully as octet");
	keySetString (k, "ab");
	succeed_if (!checkType (k), "two chars should not check successfully as octet");

	char x[2] = { 0, 0 };
	char msg[] = "\\xXX should check successfully as octet";
	const char hex[] = "0123456789abcdef";
	for (int i = 1; i < 255; ++i)
	{
		x[0] = (char) i;
		keySetString (k, x);
		msg[2] = hex[i / 16];
		msg[3] = hex[i % 16];
		succeed_if (checkType (k), msg);
	}

	keyDel (k);
}

void test_string (void)
{
	Key * k = keyNew ("user/anything", KEY_VALUE, "a", KEY_META, "check/type", "string", KEY_END);
	keySetString (k, "");
	succeed_if (!checkType (k), "empty string should not check successfully as string");

	keySetString (k, "ab");
	succeed_if (checkType (k), "\"ab\" should check successfully as string");

	keySetString (k, "monkey circus");
	succeed_if (checkType (k), "\"monkey circus\" should check successfully as string");

	keySetString (k, "日本");
	succeed_if (checkType (k), "\"日本\" should check successfully as string");

	keySetString (k, "😂 😄 😃 😀 😊 😉 😍 😘 😚 😗 😙 😜 😝 😛 😳");
	succeed_if (checkType (k), "emoji sequence should check successfully as string");

	keyDel (k);
}

void test_wstring (void)
{
	Key * k = keyNew ("user/anything", KEY_VALUE, "a", KEY_META, "check/type", "wstring", KEY_END);
	keySetString (k, "");
	succeed_if (!checkType (k), "empty string should not check successfully as wstring");

	char s[255 * MB_CUR_MAX];
	wcstombs (s, L"ab", sizeof (s));
	keySetString (k, s);
	succeed_if (checkType (k), "two wchars should check successfully as wstring");

	wcstombs (s, L"monkey circus", sizeof (s));
	keySetString (k, s);
	succeed_if (checkType (k), "L\"monkey circus\" should check successfully as wstring");

	wcstombs (s, L"日本", sizeof (s));
	keySetString (k, s);
	succeed_if (checkType (k), "\"日本\" should check successfully as wstring");

	wcstombs (s, L"😂 😄 😃 😀 😊 😉 😍 😘 😚 😗 😙 😜 😝 😛 😳", sizeof (s));
	keySetString (k, s);
	succeed_if (checkType (k), "emoji sequence should check successfully as wstring");

	keyDel (k);
}


static void test_enum (void)
{
	Key * parentKey = keyNew ("user/tests/enum", KEY_VALUE, "", KEY_END);
	Key * k1 = keyNew ("user/tests/enum/valid1", KEY_VALUE, "LOW", KEY_META, "check/type", "enum", KEY_META, "check/enum", "#1",
			   KEY_META, "check/enum/#0", "LOW", KEY_META, "check/enum/#1", "MIDDLE", KEY_END);
	Key * k2 = keyNew ("user/tests/enum/valid2", KEY_VALUE, "LOW MIDDLE", KEY_META, "check/enum/multi", " ", KEY_META, "check/type",
			   "enum", KEY_META, "check/enum", "#2", KEY_META, "check/enum/#0", "LOW", KEY_META, "check/enum/#1", "MIDDLE",
			   KEY_META, "check/enum/#2", "HIGH", KEY_END);
	Key * k3 = keyNew ("user/tests/enum/valid3", KEY_VALUE, "HIGH", KEY_META, "check/type", "enum", KEY_META, "check/enum", "#2",
			   KEY_META, "check/enum/#0", "LOW", KEY_META, "check/enum/#2", "HIGH", KEY_END);

	KeySet * conf = ksNew (0, KS_END);
	KeySet * ks;
	PLUGIN_OPEN ("ctype");

	ks = ksNew (20, KS_END);
	ksAppendKey (ks, k1);
	ksRewind (ks);
	succeed_if (plugin->kdbSet (plugin, ks, parentKey) == (1), "kdbSet failed");
	ksDel (ks);

	ks = ksNew (20, KS_END);
	ksAppendKey (ks, k2);
	ksRewind (ks);
	succeed_if (plugin->kdbSet (plugin, ks, parentKey) == (1), "kdbSet failed");
	ksDel (ks);

	ks = ksNew (20, KS_END);
	ksAppendKey (ks, k3);
	ksRewind (ks);
	succeed_if (plugin->kdbSet (plugin, ks, parentKey) == (1), "kdbSet failed");
	ksDel (ks);

	keyDel (parentKey);
	PLUGIN_CLOSE ();
}

static void test_enumMulti (void)
{
	Key * parentKey = keyNew ("user/tests/enum", KEY_VALUE, "", KEY_END);
	Key * k1 = keyNew ("user/tests/enum/valid1", KEY_VALUE, "LOW", KEY_META, "check/enum/multi", "_", KEY_META, "check/type", "enum",
			   KEY_META, "check/enum", "#1", KEY_META, "check/enum/#0", "LOW", KEY_META, "check/enum/#1", "MIDDLE", KEY_END);
	Key * k2 = keyNew ("user/tests/enum/valid2", KEY_VALUE, "LOW_MIDDLE", KEY_META, "check/enum/multi", "_", KEY_META, "check/type",
			   "enum", KEY_META, "check/enum", "#1", KEY_META, "check/enum/#0", "LOW", KEY_META, "check/enum/#1", "MIDDLE",
			   KEY_END);
	Key * k3 = keyNew ("user/tests/enum/invalid1", KEY_VALUE, "HIGH", KEY_META, "check/enum/multi", "_", KEY_META, "check/type", "enum",
			   KEY_META, "check/enum", "#1", KEY_META, "check/enum/#0", "LOW", KEY_META, "check/enum/#1", "MIDDLE", KEY_END);
	Key * k4 = keyNew ("user/tests/enum/invalid2", KEY_VALUE, "MIDDLE_FAIL", KEY_META, "check/enum/multi", "_", KEY_META, "check/type",
			   "enum", KEY_META, "check/enum", "#1", KEY_META, "check/enum/#0", "LOW", KEY_META, "check/enum/#1", "MIDDLE",
			   KEY_END);
	KeySet * conf = ksNew (0, KS_END);
	KeySet * ks;
	PLUGIN_OPEN ("ctype");

	ks = ksNew (20, KS_END);
	ksAppendKey (ks, k1);
	ksRewind (ks);
	succeed_if (plugin->kdbSet (plugin, ks, parentKey) == (1), "kdbSet failed");
	ksDel (ks);

	ks = ksNew (20, KS_END);
	ksAppendKey (ks, k2);
	ksRewind (ks);
	succeed_if (plugin->kdbSet (plugin, ks, parentKey) == (1), "kdbSet failed");
	ksDel (ks);

	ks = ksNew (20, KS_END);
	ksAppendKey (ks, k3);
	ksRewind (ks);
	succeed_if (plugin->kdbSet (plugin, ks, parentKey) == (-1), "kdbSet should have failed");
	ksDel (ks);

	ks = ksNew (20, KS_END);
	ksAppendKey (ks, k4);
	ksRewind (ks);
	succeed_if (plugin->kdbSet (plugin, ks, parentKey) == (-1), "kdbSet should have failed");
	ksDel (ks);

	keyDel (parentKey);
	PLUGIN_CLOSE ();
}

int main (int argc, char ** argv)
{
	printf ("CTYPE     TESTS\n");
	printf ("==================\n\n");

	init (argc, argv);

	test_validate ();
	test_short ();
	test_unsignedShort ();
	test_float ();
	test_bool ();
	test_none ();
	test_char ();
	test_wchar ();
	test_octet ();
	test_string ();
	test_wstring ();

	test_enum ();
	test_enumMulti ();

	print_result ("testmod_ctype");

	return nbError;
}
