#include "gtest/gtest.h"

extern "C" {
#include "../executor/executor.h"
#include <string.h>
}

TEST(Executor, SimpleCommand)
{
	t_cmd	*cmd = new t_cmd;
	cmd->type = COMMAND;
	cmd->cmd.argv = (char **)malloc(sizeof(char *) * 3);
	cmd->cmd.argv[0] = strdup("/bin/ls");
	cmd->cmd.argv[1] = strdup("-l");
	cmd->cmd.argv[2] = NULL;
	int exit_status = execute(cmd);
}

/*
t_cmd	*init_example1()
{
	t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->type = PIPELINE;
	cmd->pipeline.pipe_count = 2;
	cmd->pipeline.pids = malloc(sizeof(int) * 2);
	cmd->pipeline.pipes = malloc(sizeof(int) * 4);

	cmd->pipeline.first_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->pipeline.first_cmd->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/ls");
	cmd->pipeline.first_cmd->cmd.argv[1] = strdup("-l");
	cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 2);
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/cat");
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = NULL;
	cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
	return (cmd);
}

// example with pipeline
t_cmd	*init_example2()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = PIPELINE;
	cmd->pipeline.pids = malloc(sizeof(int) * 3);
	cmd->pipeline.pipe_count = 3;
	cmd->pipeline.pipes = malloc(sizeof(int) * 6);

	// first_cmd
	cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->pipeline.first_cmd->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/ls");
	cmd->pipeline.first_cmd->cmd.argv[1] = strdup("-la");
	cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	// second_cmd
	cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/cat");
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = strdup("-e");
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
	cmd->pipeline.first_cmd->cmd.next->cmd.next = malloc(sizeof(t_cmd));
	// third_cmd
	cmd->pipeline.first_cmd->cmd.next->cmd.next->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv[0] = strdup("/bin/grep");
	cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv[1] = strdup("exe");
	cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv[2] = NULL;
	cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.next = NULL;
	return (cmd);
}

// this one should fail
t_cmd	*init_example3()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = COMMAND;
	cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->cmd.argv[0] = strdup("/bin/bc");
	cmd->cmd.argv[1] = strdup("not_existing_file");
	cmd->cmd.argv[2] = NULL;
	return (cmd);
}

t_cmd	*init_example4()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = PIPELINE;
	cmd->pipeline.pids = malloc(sizeof(int) * 2);
	cmd->pipeline.pipe_count = 2;
	cmd->pipeline.pipes = malloc(sizeof(int) * 4);

	cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->pipeline.first_cmd->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/echo");
	cmd->pipeline.first_cmd->cmd.argv[1] = strdup("salut");
	cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 2);
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/bc");
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = NULL;
	cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
	return (cmd);
}

t_cmd	*init_example5_logic()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = LOGIC_OR;
	//cmd->logic.op = AND;
	cmd->logic.left = malloc(sizeof(t_cmd));
	cmd->logic.left->type = COMMAND;
	cmd->logic.left->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->logic.left->cmd.argv[0] = strdup("/bin/bc");
	cmd->logic.left->cmd.argv[1] = strdup("true 1");
	cmd->logic.left->cmd.argv[2] = NULL;
	cmd->logic.left->cmd.next = NULL;
	cmd->logic.right = malloc(sizeof(t_cmd));
	cmd->logic.right->type = COMMAND;
	cmd->logic.right->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->logic.right->cmd.argv[0] = strdup("/bin/echo");
	cmd->logic.right->cmd.argv[1] = strdup("true 2");
	cmd->logic.right->cmd.argv[2] = NULL;
	cmd->logic.right->cmd.next = NULL;
	return (cmd);
}

t_cmd	*init_example6_redir() 
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = REDIR_IN;
	cmd->redir.filename = strdup("test.txt");
	cmd->redir.cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->type = PIPELINE;
	cmd->redir.cmd->pipeline.pipe_count = 2;
	cmd->redir.cmd->pipeline.pids = malloc(sizeof(int) * 2);
	cmd->redir.cmd->pipeline.pipes = malloc(sizeof(int) * 4);
	cmd->redir.cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/cat");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[1] = strdup("-e");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/grep");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = strdup("exe");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
	return (cmd);
}

t_cmd	*init_example7_redir_out()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = REDIR_OUT;
	cmd->redir.filename = strdup("test2.txt");
	cmd->redir.cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->type = PIPELINE;
	cmd->redir.cmd->pipeline.pipe_count = 2;
	cmd->redir.cmd->pipeline.pids = malloc(sizeof(int) * 2);
	cmd->redir.cmd->pipeline.pipes = malloc(sizeof(int) * 4);
	cmd->redir.cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/echo");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[1] = strdup("salut");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/cat");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = strdup("-e");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
	return (cmd);
}

t_cmd	*init_example8_redir_append()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = REDIR_APPEND;
	cmd->redir.filename = strdup("test2.txt");
	cmd->redir.cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->type = PIPELINE;
	cmd->redir.cmd->pipeline.pipe_count = 2;
	cmd->redir.cmd->pipeline.pids = malloc(sizeof(int) * 2);
	cmd->redir.cmd->pipeline.pipes = malloc(sizeof(int) * 4);
	cmd->redir.cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/echo");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[1] = strdup("salut append");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/cat");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = strdup("-e");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
	return (cmd);
}
*/
