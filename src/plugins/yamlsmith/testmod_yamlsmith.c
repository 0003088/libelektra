/**
 * @file
 *
 * @brief Tests for yamlsmith plugin
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 *
 */

#include <stdlib.h>
#include <string.h>

#include <kdbconfig.h>

#include <tests_plugin.h>

static void test_basics (void)
{
	printf ("test basics\n");

	Key * parentKey = keyNew ("user/tests/yamlsmith", KEY_END);
	KeySet * conf = ksNew (0, KS_END);
	PLUGIN_OPEN ("yamlsmith");

	KeySet * ks = ksNew (0, KS_END);

	succeed_if (plugin->kdbGet (plugin, ks, parentKey) == ELEKTRA_PLUGIN_STATUS_NO_UPDATE, "call to kdbGet was not successful");

	succeed_if (plugin->kdbSet (plugin, ks, parentKey) == ELEKTRA_PLUGIN_STATUS_NO_UPDATE, "call to kdbSet was not successful");

	keyDel (parentKey);
	ksDel (ks);
	PLUGIN_CLOSE ();
}


int main (int argc, char ** argv)
{
	printf ("⚒ YAMLSMITH     TESTS\n");
	printf ("=======================\n\n");

	init (argc, argv);

	test_basics ();

	print_result ("testmod_yamlsmith");

	return nbError;
}
