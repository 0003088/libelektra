/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/LICENSE.md or https://www.libelektra.org)
 */

#ifndef LIST_H
#define LIST_H

#include <command.hpp>
#include <kdb.hpp>

class ListCommand : public Command
{
public:
	ListCommand ();
	~ListCommand ();

	virtual std::string getShortOptions () override
	{
		return "0vC";
	}

	virtual std::string getSynopsis () override
	{
		return "";
	}

	virtual std::string getShortHelpText () override
	{
		return "List available plugins.";
	}

	virtual std::string getLongHelpText () override
	{
		return "Currently it only lists plugins that were compiled\n"
		       "together with the source\n";
	}

	virtual int execute (Cmdline const & cmdline) override;
};

#endif
