# pipex
In this project you have to recreate unix pipes.
If you dont do the bonus you'll just handle 1 pipe ex below.
./pipex infile cmd1 cmd2 outfile -> The infile MUST exist.

On the first bonus you just have to handle N pipex
./pipex in cm1 cmd2 ... cmdN out

The last bonus consists of recreating the here_doc.
./pipex << here_doc delimiter cmd1 cmd2 ... cmdN outfile

PD: if you want to exec ls -la or any command with args you must send it to pipex with double quotes.
PD2: If you run this on MAC you'll find 2 leaks of kb each, this is due to MAC fork() function.
