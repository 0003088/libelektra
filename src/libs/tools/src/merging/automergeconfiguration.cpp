/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/LICENSE.md or http://www.libelektra.org)
 */

#include <merging/automergeconfiguration.hpp>
#include <merging/automergestrategy.hpp>
#include <merging/metamergestrategy.hpp>

namespace kdb
{

namespace tools
{

namespace merging
{

void AutoMergeConfiguration::configureMerger (ThreeWayMerge & merger)
{
	auto metaMergeStrategy = new MetaMergeStrategy (merger);
	allocatedStrategies.push_back (metaMergeStrategy);
	merger.addConflictStrategy (metaMergeStrategy);

	auto autoMergeStrategy = new AutoMergeStrategy ();
	allocatedStrategies.push_back (autoMergeStrategy);
	merger.addConflictStrategy (autoMergeStrategy);
}
}
}
}
