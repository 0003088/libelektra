/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/LICENSE.md or http://www.libelektra.org)
 */

#include <kdbplugin.h>

extern "C" {

namespace ckdb
{
ssize_t keySetRaw (ckdb::Key * key, const void * newBinary, size_t dataSize);
}

int elektraDumpGet (ckdb::Plugin * handle, ckdb::KeySet * ks, ckdb::Key * parentKey);
int elektraDumpSet (ckdb::Plugin * handle, ckdb::KeySet * ks, ckdb::Key * parentKey);
ckdb::Plugin * ELEKTRA_PLUGIN_EXPORT (dump);

} // extern C
