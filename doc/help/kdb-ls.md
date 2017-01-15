kdb-ls(1) -- List keys in the key database
================================

## SYNOPSIS

`kdb ls <key name>`  

Where `key name` is the path in which the user would like to list keys below.

## DESCRIPTION

This command will list the name of all keys below a given path.  

## OPTIONS

- `-H`, `--help`:
  Show the man page.
- `-V`, `--version`:
  Print version info.
- `-p`, `--profile`=<profile>:
  Use a different kdb profile.
- `-v`, `--verbose`:
  Explain what is happening.
- `-0`, `--null`:
  Use binary 0 termination.
- `-C`, `--color`=[when]:
  Print never/auto(default)/always colored output.

## EXAMPLES

To list all keys below `user/example`:  
`kdb ls user/example`  


## SEE ALSO

- If the user would also like to see the values of the keys below `path` then you should
consider the [kdb-export(1)](kdb-export.md) command.
- [elektra-key-names(7)](elektra-key-names.md) for an explanation of key names.