/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/LICENSE.md or http://www.libelektra.org)
 */

#ifndef KDBMODULE_H
#define KDBMODULE_H

#include <kdb.h>
#include <kdbplugin.h>

#ifdef __cplusplus
namespace ckdb
{
extern "C" {
#endif

typedef Plugin * (*elektraPluginFactory) (void);

int elektraModulesInit (KeySet * modules, Key * error);
elektraPluginFactory elektraModulesLoad (KeySet * modules, const char * name, Key * error);
int elektraModulesClose (KeySet * modules, Key * error);


#ifdef __cplusplus
}
}
#endif

#endif
