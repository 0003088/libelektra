# Use Case: Setup instance

## Summary

Title: Setup instance
Scope: Setup
Level: User Goal
Actors: User (usually a sysadmin)
Brief: User sets up a daemon on the instance and connects it to elektra-web.

## Scenarios

Precondition: elektra-web is set up
Main success scenario: User successfully sets up elektrad on the instance (by
	installing the dependencies and starting elektrad) and connects it to
	elektra-web (clusterd) by specifying the host and an API key in a config file.
Alternative scenario: Authentication issues when connecting the services,
	e.g. wrong API key.
Alternative scenario: The instance is already connected to elektra-web. A
  message informs the user about this.
Error scenario: Technical problems - the user is informed about the issue.
Postcondition: User can now access the instance via the client.
Non-functional Constraints:
	- Security mechanism
	- Is precondition to use configuration functions
