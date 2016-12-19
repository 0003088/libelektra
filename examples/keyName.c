/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/LICENSE.md or http://www.libelektra.org)
 */

#include <assert.h>
#include <string.h>

#include <kdb.h>

int main ()
{
	// clang-format off
//! [add name]
Key * k = keyNew ("user/x/r", KEY_END);
keyAddName (k, "../y/a//././z");
assert (!strcmp (keyName (k), "user/x/y/a/z"));
keyDel (k);
//! [add name]
//! [namespace]
Key * n = keyNew ("user/away", KEY_END);
keyAddName (n, "../../../new/name");
assert (!strcmp (keyName (n), "user/new/name"));
keyDel (n);
//! [namespace]
}
