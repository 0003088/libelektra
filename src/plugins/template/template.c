/**
 * @file
 *
 * @brief Source for template plugin
 *
 * @copyright BSD License (see doc/LICENSE.md or http://www.libelektra.org)
 *
 */

#include "template.h"

#include <kdbhelper.h>


int elektraTemplateOpen (Plugin * handle ELEKTRA_UNUSED, Key * errorKey ELEKTRA_UNUSED)
{
	// plugin initialization logic
	// this function is optional

	return 1; // success
}

int elektraTemplateClose (Plugin * handle ELEKTRA_UNUSED, Key * errorKey ELEKTRA_UNUSED)
{
	// free all plugin resources and shut it down
	// this function is optional

	return 1; // success
}

int elektraTemplateGet (Plugin * handle ELEKTRA_UNUSED, KeySet * returned ELEKTRA_UNUSED, Key * parentKey ELEKTRA_UNUSED)
{
	if (!elektraStrCmp (keyName (parentKey), "system/elektra/modules/template"))
	{
		KeySet * contract =
			ksNew (30, keyNew ("system/elektra/modules/template", KEY_VALUE, "template plugin waits for your orders", KEY_END),
			       keyNew ("system/elektra/modules/template/exports", KEY_END),
			       keyNew ("system/elektra/modules/template/exports/open", KEY_FUNC, elektraTemplateOpen, KEY_END),
			       keyNew ("system/elektra/modules/template/exports/close", KEY_FUNC, elektraTemplateClose, KEY_END),
			       keyNew ("system/elektra/modules/template/exports/get", KEY_FUNC, elektraTemplateGet, KEY_END),
			       keyNew ("system/elektra/modules/template/exports/set", KEY_FUNC, elektraTemplateSet, KEY_END),
			       keyNew ("system/elektra/modules/template/exports/error", KEY_FUNC, elektraTemplateError, KEY_END),
			       keyNew ("system/elektra/modules/template/exports/checkconf", KEY_FUNC, elektraTemplateCheckConfig, KEY_END),
#include ELEKTRA_README (template)
			       keyNew ("system/elektra/modules/template/infos/version", KEY_VALUE, PLUGINVERSION, KEY_END), KS_END);
		ksAppend (returned, contract);
		ksDel (contract);

		return 1; // success
	}
	// get all keys

	//  0: Everything was OK and `returned` has not been changed
	//  1: Everything was OK and `returned` was updated
	// -1: There was an error
	return 1; // success
}

int elektraTemplateSet (Plugin * handle ELEKTRA_UNUSED, KeySet * returned ELEKTRA_UNUSED, Key * parentKey ELEKTRA_UNUSED)
{
	// set all keys
	// this function is optional

	return 1; // success
}

int elektraTemplateError (Plugin * handle ELEKTRA_UNUSED, KeySet * returned ELEKTRA_UNUSED, Key * parentKey ELEKTRA_UNUSED)
{
	// handle errors (commit failed)
	// this function is optional

	return 1; // success
}

int elektraTemplateCheckConfig (Key * errorKey ELEKTRA_UNUSED, KeySet * conf ELEKTRA_UNUSED)
{
	// validate plugin configuration
	// this function is optional

	// the return codes have the following meaning:
	// 0: The configuration was OK and has not been changed
	// 1: The configuration has been changed and now it is OK
	// -1: The configuration was not OK and could not be fixed. An error has to be set to errorKey.
	return 0;
}

Plugin * ELEKTRA_PLUGIN_EXPORT (template)
{
	// clang-format off
	return elektraPluginExport ("template",
		ELEKTRA_PLUGIN_OPEN,	&elektraTemplateOpen,
		ELEKTRA_PLUGIN_CLOSE,	&elektraTemplateClose,
		ELEKTRA_PLUGIN_GET,	&elektraTemplateGet,
		ELEKTRA_PLUGIN_SET,	&elektraTemplateSet,
		ELEKTRA_PLUGIN_ERROR,	&elektraTemplateError,
		ELEKTRA_PLUGIN_END);
}
